//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_PARTITION_MERGE_H
#define STP_PARTITION_MERGE_H

#include <istream>

#include "config.hpp"
#include "data_selection_and_arrangement.hpp"
#include "linear.hpp"
#include "matrix_multiply.hpp"


const ptr_t BATCH_SIZE = 96;
const ptr_t DOWN_SCALE = 2;

/**
 * @tparam T 数据类型
 * @param pIns 参数流
 */
template <typename T> void partition_merge(T *basePtr, param_stream &pIns) {

  for (ptr_t i = 0; i < regs[2]; i += DOWN_SCALE) {
    for (ptr_t j = 0; j < regs[3]; j += DOWN_SCALE) {

      regs[11] = regs[1];                            // Inter H
      regs[12] = DOWN_SCALE;                         // Inter X
      regs[13] = DOWN_SCALE;                         // Inter Y
      regs[14] = regs[1];                            // Main H
      regs[15] = regs[2];                            // Main X
      regs[16] = regs[3];                            // Main Y
      regs[17] = 0;                                  // offset h
      regs[18] = i;                                  // offset x
      regs[19] = j;                                  // offset y
      regs[20] = 0;                                  // src offset
      regs[21] = regs[9];                            // dst offset
      regs[9] += regs[11] * DOWN_SCALE * DOWN_SCALE; // max stack reserved
      select_data<T>(basePtr);

      regs[22] = regs[11] * regs[12] * regs[13]; // input dimension
      regs[23] = regs[11] * regs[12];            // output dimension
      regs[24] = BATCH_SIZE;                     // batch size
      regs[25] = regs[21];                       // src offset
      regs[26] = regs[25] + regs[22];            // dst offset
      regs[9] += regs[23];                       // max stack reserved
      linear<T>(basePtr, pIns);

      regs[11] = regs[23];       // Inter H
      regs[12] = 1;              // Inter X
      regs[13] = 1;              // Inter Y
      regs[14] = regs[4];        // Main H
      regs[15] = regs[5];        // Main X
      regs[16] = regs[6];        // Main Y
      regs[17] = 0;              // offset h
      regs[18] = i / DOWN_SCALE; // offset x
      regs[19] = j / DOWN_SCALE; // offset y
      regs[20] = regs[21];       // src offset
      regs[21] = regs[8];        // dst offset

      regs[9] -= regs[22];
      regs[9] -= regs[23];
      arrange_data<T>(basePtr);
    }
  }
}

#endif // STP_PARTITION_MERGE_H
