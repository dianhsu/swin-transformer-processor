//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_MATRIX_MULTIPLY_H
#define STP_MATRIX_MULTIPLY_H

#include "config.hpp"

// const static ptr_t C = 96;

template <typename T, ptr_t C = 96>
void matrix(T *basePtr, param_stream &pIns) {
  T localInput[C];
  T localOutput[C];
  T paramLocal[C][C];
#pragma HLS array_partition variable = localInput complete
#pragma HLS array_partition variable = localOutput complete
#pragma HLS array_partition variable = paramLocal complete
  for (ptr_t i = 0; i < C; ++i) {
#pragma HLS pipeline
    localInput[i] = basePtr[regs[27] + i];
  }
  for (ptr_t i = 0; i < C; ++i) {
    for (ptr_t j = 0; j < C; ++j) {
#pragma HLS pipeline
      pIns >> paramLocal[i][j];
    }
  }
  for (ptr_t i = 0; i < C; ++i) {
#pragma HLS unroll
    localOutput[i] = 0;
  }
  for (ptr_t i = 0; i < C; ++i) {
#pragma HLS pipeline off
    for (ptr_t j = 0; j < C; ++j) {
#pragma HLS unroll
      localOutput[j] += localInput[i] * paramLocal[i][j];
    }
  }
  for (ptr_t i = 0; i < C; ++i) {
#pragma HLS pipeline off
    basePtr[regs[28] + i] += localOutput[i];
  }
}

#endif // STP_MATRIX_MULTIPLY_H
