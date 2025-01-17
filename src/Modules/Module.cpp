#include "Module.h"

#include "Parallel/MPI.h"
#include "utils/logger.h"
#include <cassert>
#include <cmath>
#include <limits>

namespace seissol {
Module::Module()
    : isyncInterval(0), nextSyncPoint(0), lastSyncPoint(-std::numeric_limits<double>::infinity()) {}

double Module::potentialSyncPoint(double currentTime, double timeTolerance, bool forceSyncPoint) {
  if (std::abs(currentTime - lastSyncPoint) < timeTolerance) {
    int const rank = seissol::MPI::mpi.rank();
    logInfo(rank) << "Ignoring duplicate synchronisation point at time" << currentTime
                  << "; the last sync point was at " << lastSyncPoint;
  } else if (forceSyncPoint || std::abs(currentTime - nextSyncPoint) < timeTolerance) {
    syncPoint(currentTime);
    lastSyncPoint = currentTime;
    nextSyncPoint += isyncInterval;
  }

  return nextSyncPoint;
}

void Module::setSimulationStartTime(double time) {
  assert(isyncInterval > 0);
  lastSyncPoint = time;
  nextSyncPoint = time + isyncInterval;
}

/**
 * Set the synchronization interval for this module
 *
 * This is only required for modules that register for {@link SYNCHRONIZATION_POINT}.
 */
void Module::setSyncInterval(double interval) {
  if (isyncInterval != 0) {
    logError() << "Synchronization interval is already set";
  }
  isyncInterval = interval;
}
} // namespace seissol
