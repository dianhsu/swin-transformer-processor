//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_MATRIX_MULTIPLY_H
#define STP_MATRIX_MULTIPLY_H


#include "config.h"

template<typename T, ptr_t C = 96>
void matrix(param_stream& pIns) {
    T* basePtr = (T*) (regs[0]);
    T localInput[C];
    T localOutput[C];
    T paramLocal[C][C];
    for (ptr_t i = 0; i < C; ++i) {
        localInput[i] = basePtr[regs[27] + i];
    }
    for (ptr_t i = 0; i < C; ++i) {
        for (ptr_t j = 0; j < C; ++j) {
            pIns >> paramLocal[i][j];
        }
    }
    for (ptr_t i = 0; i < C; ++i) {
        localOutput[i] = 0;
    }
    for (ptr_t i = 0; i < C; ++i) {
        for (ptr_t j = 0; j < C; ++j) {
            localOutput[j] += localInput[i] * paramLocal[i][j];
        }
    }
    for (ptr_t i = 0; i < C; ++i) {
        basePtr[regs[28] + i] += localOutput[i];
    }
}

#endif //STP_MATRIX_MULTIPLY_H
