//
// Created by dianhsu on 2021/6/21.
//

#ifndef STP_CONTROLLER_H
#define STP_CONTROLLER_H

#include "config.hpp"
#include "partition_merge.hpp"
#include "residual_attention.hpp"
#include "residual_feed_forward.hpp"

/**
 * 中央控制器
 * @tparam T 操作数据类型
 * @param cIns 指令流
 * @param pIns 参数流
 */
template <typename T>
void control(T *basePtr, ptr_stream &cIns, param_stream &pIns) {
  ptr_t t;
  while (1) {
    cIns >> t;
    if (t == 0) {
      ptr_t pos;
      cIns >> pos;
      cIns >> regs[pos];
    } else if (t == 1) {
      regs[7] = 0;
      regs[8] = regs[1] * regs[2] * regs[3];
      regs[9] = regs[8] + regs[4] * regs[5] * regs[6];
      partition_merge<T>(basePtr, pIns);
    } else if (t == 2) {
      if (regs[55]) {
        for (ptr_t i = 0; i < regs[4] * regs[5] * regs[6]; ++i) {
#pragma HLS pipeline off
          basePtr[regs[7] + i] += basePtr[regs[8] + i];
        }
      } else {
        for (ptr_t i = 0; i < regs[4] * regs[5] * regs[6]; ++i) {
          basePtr[regs[7] + i] = basePtr[regs[8] + i];
        }
      }
      regs[1] = regs[4];
      regs[2] = regs[5];
      regs[3] = regs[6];
      regs[9] = regs[1] * regs[2] * regs[3];
    } else if (t == 3) {
      regs[7] = 0;
      regs[8] = regs[1] * regs[2] * regs[3];
      regs[9] = regs[8] + regs[4] * regs[5] * regs[6];
      residualAttention<T>(basePtr, pIns);
    } else if (t == 4) {
      residualFeedForward<T>(basePtr, pIns);
    } else {
      return;
    }
  }
}

#endif // STP_CONTROLLER_H
