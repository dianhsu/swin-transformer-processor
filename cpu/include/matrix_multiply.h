//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_MATRIX_MULTIPLY_H
#define STP_MATRIX_MULTIPLY_H

#include <istream>

#include "config.h"

template<typename T, int C = 96>
void matrix(int dst, int src, T *basePtr, std::istream &pIns) {
    T localInput[C];
    T localOutput[C];
    T paramLocal[C][C];
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
            pIns >> paramLocal[i][j];
        }
    }
    for (int i = 0; i < C; ++i) {
        localInput[i] = basePtr[i + src];
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
        basePtr[i + dst] = localOutput[i];
    }
}

#endif //STP_MATRIX_MULTIPLY_H
