#include "Init.hpp"
#include "InitMesh.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "utils/logger.h"

#include "SeisSol.h"
#ifdef USE_NETCDF
#include "Geometry/NetcdfReader.h"
#endif // USE_NETCDF
#if defined(USE_HDF) && defined(USE_MPI)
#include "Geometry/PUMLReader.h"
#endif // defined(USE_HDF) && defined(USE_MPI)
#include "Modules/Modules.h"
#include "Monitoring/instrumentation.hpp"
#include "Monitoring/Stopwatch.h"
#include "Numerical_aux/Statistics.h"
#include "Initializer/time_stepping/LtsWeights/WeightsFactory.h"
#include "Solver/time_stepping/MiniSeisSol.h"
#include "ResultWriter/MiniSeisSolWriter.h"

#include "Parallel/MPI.h"

static void postMeshread(seissol::geometry::MeshReader& meshReader,
                         bool hasFault,
                         const std::array<double, 3>& displacement,
                         const std::array<std::array<double, 3>, 3>& scalingMatrix) {
  logInfo(seissol::MPI::mpi.rank()) << "The mesh has been read. Starting post processing.";

  if (meshReader.getElements().empty()) {
    logWarning(seissol::MPI::mpi.rank())
        << "There are no local mesh elements on this rank. Is your mesh big enough?";
  }

  meshReader.displaceMesh(displacement);
  meshReader.scaleMesh(scalingMatrix);

  if (hasFault) {
    logInfo(seissol::MPI::mpi.rank()) << "Extracting fault information.";

    auto* drParameters = seissol::SeisSol::main.getMemoryManager().getDRParameters();
    VrtxCoords center{drParameters->referencePoint[0],
                      drParameters->referencePoint[1],
                      drParameters->referencePoint[2]};
    meshReader.extractFaultInformation(center, drParameters->refPointMethod);
  }

  logInfo(seissol::MPI::mpi.rank()) << "Exchanging ghostlayer metadata.";
  meshReader.exchangeGhostlayerMetadata();

  seissol::SeisSol::main.getLtsLayout().setMesh(meshReader);

  // Setup the communicator for dynamic rupture
  seissol::MPI::mpi.fault.init(meshReader.getFault().size() > 0);
}

static void readMeshPUML(const seissol::initializer::parameters::SeisSolParameters& seissolParams) {
#if defined(USE_HDF) && defined(USE_MPI)
  const int rank = seissol::MPI::mpi.rank();
  double nodeWeight = 1.0;

#ifdef USE_MINI_SEISSOL
  if (seissol::MPI::mpi.size() > 1) {
    logInfo(rank) << "Running mini SeisSol to determine node weight";
    auto elapsedTime = seissol::miniSeisSol(seissol::SeisSol::main.getMemoryManager(),
                                            seissolParams.model.plasticity);
    nodeWeight = 1.0 / elapsedTime;

    const auto summary = seissol::statistics::parallelSummary(nodeWeight);
    logInfo(rank) << "Node weights: mean =" << summary.mean << " std =" << summary.std
                  << " min =" << summary.min << " median =" << summary.median
                  << " max =" << summary.max;

    writer::MiniSeisSolWriter writer(seissolParams.output.prefix.c_str());
    writer.write(elapsedTime, nodeWeight);
  }
#else
  logInfo(rank) << "Skipping mini SeisSol";
#endif

  logInfo(rank) << "Reading PUML mesh";

  seissol::Stopwatch watch;
  watch.start();

  bool readPartitionFromFile = seissol::SeisSol::main.simulator().checkPointingEnabled();

  using namespace seissol::initializers::time_stepping;
  LtsWeightsConfig config{seissolParams.model.materialFileName,
                          static_cast<unsigned int>(seissolParams.timestepping.lts.rate),
                          seissolParams.timestepping.vertexWeight.weightElement,
                          seissolParams.timestepping.vertexWeight.weightDynamicRupture,
                          seissolParams.timestepping.vertexWeight.weightFreeSurfaceWithGravity};

  const auto* ltsParameters = seissol::SeisSol::main.getMemoryManager().getLtsParameters();
  auto ltsWeights =
      getLtsWeightsImplementation(seissolParams.timestepping.lts.weighttype, config, ltsParameters);
  auto meshReader =
      new seissol::geometry::PUMLReader(seissolParams.mesh.meshFileName.c_str(),
                                        seissolParams.mesh.partitioningLib.c_str(),
                                        seissolParams.timestepping.maxTimestepWidth,
                                        seissolParams.output.checkpointParameters.fileName.c_str(),
                                        ltsWeights.get(),
                                        nodeWeight,
                                        readPartitionFromFile);
  seissol::SeisSol::main.setMeshReader(meshReader);

  watch.pause();
  watch.printTime("PUML mesh read in:");

#else // defined(USE_HDF) && defined(USE_MPI)
#ifndef USE_MPI
  logError() << "Tried to load a PUML mesh. However, PUML is currently only supported with MPI "
                "(and this build of SeisSol does not use MPI).";
#endif
#ifndef USE_HDF
  logError() << "Tried to load a PUML mesh. However, PUML needs SeisSol to be linked against HDF5.";
#endif
#endif // defined(USE_HDF) && defined(USE_MPI)
}

void seissol::initializer::initprocedure::initMesh() {
  SCOREP_USER_REGION("init_mesh", SCOREP_USER_REGION_TYPE_FUNCTION);

  const auto& seissolParams = seissol::SeisSol::main.getSeisSolParameters();

  logInfo(seissol::MPI::mpi.rank()) << "Begin init mesh.";

  // Call the pre mesh initialization hook
  seissol::Modules::callHook<seissol::PRE_MESH>();

  const auto meshFormat = seissolParams.mesh.meshFormat;

  logInfo(seissol::MPI::mpi.rank()) << "Mesh file:" << seissolParams.mesh.meshFileName;

  seissol::Stopwatch watch;
  watch.start();

  const auto commRank = seissol::MPI::mpi.rank();
  const auto commSize = seissol::MPI::mpi.size();

  std::string realMeshFileName = seissolParams.mesh.meshFileName;
  switch (meshFormat) {
  case seissol::geometry::MeshFormat::Netcdf:
#if USE_NETCDF
    realMeshFileName = seissolParams.mesh.meshFileName + ".nc";
    logInfo(seissol::MPI::mpi.rank())
        << "By old SeisSol conventions for Netcdf meshes, the Netcdf file extension \".nc\" is "
           "always appended. Thus, the (new) mesh file name is"
        << realMeshFileName;
    seissol::SeisSol::main.setMeshReader(
        new seissol::geometry::NetcdfReader(commRank, commSize, realMeshFileName.c_str()));
#else
    logError()
        << "Tried to load a Netcdf mesh, however this build of SeisSol is not linked to Netcdf.";
#endif
    break;
  case seissol::geometry::MeshFormat::PUML:
    readMeshPUML(seissolParams);
    break;
  default:
    logError() << "Mesh reader not implemented for format" << static_cast<int>(meshFormat);
  }

  postMeshread(seissol::SeisSol::main.meshReader(),
               seissolParams.dynamicRupture.hasFault,
               seissolParams.mesh.displacement,
               seissolParams.mesh.scaling);

  watch.pause();
  watch.printTime("Mesh initialized in:");

  // Call the post mesh initialization hook
  seissol::Modules::callHook<seissol::POST_MESH>();

  logInfo(seissol::MPI::mpi.rank()) << "End init mesh.";
}
