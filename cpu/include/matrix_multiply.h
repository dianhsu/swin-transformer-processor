//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_MATRIX_MULTIPLY_H
#define STP_MATRIX_MULTIPLY_H

#include <istream>

#include "config.h"

template<typename T, int C = 96>
void matrix(std::istream &pIns) {
    T *basePtr = reinterpret_cast<T *>(regs[0]);
    T localInput[C];
    T localOutput[C];
    T paramLocal[C][C];
    for (int i = 0; i < C; ++i) {
        localInput[i] = basePtr[regs[13] + i];
    }
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
            pIns >> paramLocal[i][j];
        }
    }
    for (int i = 0; i < C; ++i) {
        localOutput[i] = 0;
    }
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
            localOutput[j] += localInput[i] * paramLocal[i][j];
        }
    }
    for (int i = 0; i < C; ++i) {
        basePtr[regs[14] + i] += localOutput[i];
    }
}

#endif //STP_MATRIX_MULTIPLY_H
