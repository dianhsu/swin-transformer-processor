//
// Created by dianhsu on 2021/6/23.
//

#ifndef STP_LINEAR_H
#define STP_LINEAR_H

#include "matrix_multiply.h"

template<typename T, int64_t C = 96>
void linear(std::istream &pIns) {
    int64_t rows = regs[10] / C;
    int64_t cols = regs[11] / C;
    T *basePtr = reinterpret_cast<T *>(regs[0]);
    for (int j = 0; j < cols; ++j) {
        regs[13] = regs[19] + j * C;
        regs[14] = regs[21];
        regs[21] += C;

        T *outputTmp = basePtr + regs[14];
        for (int i = 0; i < C; ++i) {
            outputTmp[i] = 0;
        }

        for (int i = 0; i < rows; ++i) {
            matrix<T, C>(pIns);
        }

        for (int i = 0; i < C; ++i) {
            basePtr[regs[20] + j * C + i] = outputTmp[i];
        }
        regs[21] -= C;
    }
}

#endif //STP_LINEAR_H