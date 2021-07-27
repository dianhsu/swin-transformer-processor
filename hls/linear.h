//
// Created by dianhsu on 2021/6/23.
//

#ifndef STP_LINEAR_H
#define STP_LINEAR_H

#include "matrix_multiply.h"

template<typename T, ptr_t C = 96>
void linear(param_stream& pIns) {
    ptr_t rows = regs[22] / C;
    ptr_t cols = regs[23] / C;
    T* basePtr = reinterpret_cast<T*>(regs[0]);
    for (ptr_t i = 0; i < regs[23]; ++i) {
        basePtr[regs[26] + i] = 0;
    }
    for (ptr_t j = 0; j < cols; ++j) {
        for (ptr_t i = 0; i < rows; ++i) {
            regs[27] = regs[25] + i * C;
            regs[28] = regs[26] + j * C;
            matrix<T, C>(pIns);
        }
    }
}

#endif //STP_LINEAR_H
