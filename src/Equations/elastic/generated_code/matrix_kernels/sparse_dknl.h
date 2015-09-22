// Copyright (c) 2015, Intel Corporation
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of its contributors
//       may be used to endorse or promote products derived from this software
//       without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// @file
// This file is part of SeisSol.
// 
// @author Alexander Breuer (breuer AT mytum.de, http://www5.in.tum.de/wiki/index.php/Dipl.-Math._Alexander_Breuer)
// @author Alexander Heinecke (alexander.heinecke AT mytum.de, http://www5.in.tum.de/wiki/index.php/Alexander_Heinecke,_M.Sc.,_M.Sc._with_honors)
// 
// @date 2015-08-14 10:02:43.265033
// 
// @section LICENSE
// Copyright (c) 2012-2015, SeisSol Group
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from this
//    software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// 
// @section DESCRIPTION
// Remark: This file was generated.
#ifndef SPARSEDKNLH
#define SPARSEDKNLH

#if defined( __SSE3__) || defined(__MIC__)
#include <immintrin.h>
#endif

#include <cstddef>
#ifndef NDEBUG
extern long long libxsmm_num_total_flops;
#endif

void dsparse_kXiDivMT_m1_n9_k4_ldAna2_ldB8_ldC8_beta0_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m1_n9_k9_ldA8_ldBna2_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m4_n9_k9_ldA8_ldBna3_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m1_n9_k9_ldA8_ldBna3_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m10_n9_k9_ldA16_ldBna4_ldC16_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m4_n9_k9_ldA8_ldBna4_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m1_n9_k9_ldA8_ldBna4_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m20_n9_k9_ldA24_ldBna5_ldC24_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m10_n9_k9_ldA16_ldBna5_ldC16_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m4_n9_k9_ldA8_ldBna5_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m1_n9_k9_ldA8_ldBna5_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m35_n9_k9_ldA40_ldBna6_ldC40_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m20_n9_k9_ldA24_ldBna6_ldC24_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m10_n9_k9_ldA16_ldBna6_ldC16_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m4_n9_k9_ldA8_ldBna6_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m1_n9_k9_ldA8_ldBna6_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m56_n9_k9_ldA56_ldBna7_ldC56_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m35_n9_k9_ldA40_ldBna7_ldC40_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m20_n9_k9_ldA24_ldBna7_ldC24_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m10_n9_k9_ldA16_ldBna7_ldC16_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m4_n9_k9_ldA8_ldBna7_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m1_n9_k9_ldA8_ldBna7_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m4_n9_k9_ldA8_ldBna2_ldC8_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m10_n9_k9_ldA16_ldBna3_ldC16_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m20_n9_k9_ldA24_ldBna4_ldC24_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m35_n9_k9_ldA40_ldBna5_ldC40_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m56_n9_k9_ldA56_ldBna6_ldC56_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
void dsparse_starMatrix_m84_n9_k9_ldA88_ldBna7_ldC88_beta1_pfsigonly(const real *i_A, const real *i_B, real *io_C,const real *i_APrefetch, const real *i_BPrefetch, const real *i_CPrefetch );
#endif
