/*
Copyright (c) 2015, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

double bytes_local(unsigned int i_timesteps) {
  double bytes = static_cast<double>(m_timeKernel.bytesAder() + m_localKernel.bytesIntegral());
  double elems = static_cast<double>(m_cells->numberOfCells);
  double timesteps = static_cast<double>(i_timesteps);
  
  return elems * timesteps * bytes;
}

double bytes_neigh(unsigned int i_timesteps) {
  double bytes = static_cast<double>(m_neighborKernel.bytesNeighborsIntegral());
  double elems = static_cast<double>(m_cells->numberOfCells);
  double timesteps = static_cast<double>(i_timesteps);
  
  return elems * timesteps * bytes;
}

double bytes_all(unsigned int i_timesteps) {
  return bytes_local(i_timesteps) + bytes_neigh(i_timesteps);
}

double noestimate(unsigned) {
  return 0.0;
}
