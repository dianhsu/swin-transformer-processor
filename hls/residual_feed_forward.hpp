//
// Created by dianhsu on 2021/6/30.
//

#ifndef STP_RESIDUAL_FEED_FORWARD_H
#define STP_RESIDUAL_FEED_FORWARD_H

#include "config.hpp"
#include <istream>


template <typename T> void residualFeedForward(T *basePtr, param_stream &pIns) {
  regs[50] = regs[1] * regs[2] * regs[3];
  regs[25] = regs[7];
  regs[26] = regs[8] + regs[50];
  regs[24] = 96;
  regs[22] = regs[50];
  regs[23] = regs[50];
  linear<T>(basePtr, pIns);

  regs[51] = regs[26];
  regs[52] = regs[51] + regs[50];
  regs[53] = regs[52] + regs[50];
  for (ptr_t i = 0; i < regs[50]; ++i) {
#pragma HLS pipeline off
    basePtr[regs[52] + i] = GELU(basePtr[regs[51] + i]);
  }

  regs[25] = regs[52];
  regs[26] = regs[53];
  linear<T>(basePtr, pIns);

  for (ptr_t i = 0; i < regs[50]; ++i) {
    basePtr[regs[8] + i] = basePtr[regs[53] + i] + basePtr[i];
  }
}

#endif // STP_RESIDUAL_FEED_FORWARD_H
