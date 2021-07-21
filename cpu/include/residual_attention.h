//
// Created by dianhsu on 2021/6/30.
//

#ifndef STP_RESIDUAL_ATTENTION_H
#define STP_RESIDUAL_ATTENTION_H

#include <istream>
#include "functions.h"
#include "config.h"

const int64_t WINDOW_SIZE = 7;

template<typename T>
void qkv(std::istream &pIns) {
    regs[39] = regs[38] + regs[37];
    regs[9] = regs[39] + regs[41] * regs[41];
    T *basePtr = reinterpret_cast<T *>(regs[0]);
    // K^T x Q
    for (int i = 0; i < regs[41]; ++i) {
        for (int j = 0; j < regs[41]; ++j) {
            T tmp = 0;
            for (int k = 0; k < regs[40]; ++k) {
                tmp += basePtr[regs[34] + k * regs[41] + i] * basePtr[regs[33] + k * regs[41] + j];
            }
            basePtr[regs[39] + i * regs[41] + j] = tmp;
        }
    }
    T scale;
    pIns >> scale;
    for (int i = 0; i < regs[41]; ++i) {
        for (int j = 0; j < regs[41]; ++j) {
            basePtr[regs[39] + i * regs[41] + j] *= scale;
        }
    }
    T pe;
    for (int i = 0; i < regs[41]; ++i) {
        for (int j = 0; j < regs[41]; ++j) {
            pIns >> pe;
            basePtr[regs[39] + i * regs[41] + j] += pe;
        }
    }
    regs[42] = regs[41];
    for (int i = 0; i < regs[41]; ++i) {
        regs[43] = regs[39] + i * regs[41];
        softmax<T>();
    }
    for (int i = 0; i < regs[40]; ++i) {
        for (int j = 0; j < regs[41]; ++j) {
            T tmp = 0;
            for (int k = 0; k < regs[41]; ++k) {
                tmp += basePtr[regs[35] + i * regs[41] + k] * basePtr[regs[39] + k * regs[41] + j];
            }
            basePtr[regs[38] + i * regs[41] + j] = tmp;
        }
    }
    regs[9] = regs[39];
}

template<typename T>
void residualAttention(std::istream &pIns) {
    regs[29] = regs[1];
    regs[30] = regs[2];
    regs[31] = regs[3];
    regs[32] = regs[29] * regs[30] * regs[31];

    regs[33] = regs[9];
    regs[9] += regs[32];

    regs[22] = regs[32];
    regs[23] = regs[32];
    regs[24] = 96;
    regs[25] = regs[0];
    regs[26] = regs[33];
    linear<T>(pIns);

    regs[34] = regs[9];
    regs[9] += regs[32];
    regs[26] = regs[34];
    linear<T>(pIns);

    regs[35] = regs[9];
    regs[9] += regs[32];
    regs[26] = regs[35];
    linear<T>(pIns);

    regs[11] = regs[31] / regs[36];
    regs[12] = WINDOW_SIZE;
    regs[13] = WINDOW_SIZE;
    regs[14] = regs[29];
    regs[15] = regs[30];
    regs[16] = regs[31];
    regs[37] = regs[11] * regs[12] * regs[13];
    for (int64_t i = 0; i < regs[14]; i += regs[11]) {
        for (int64_t j = 0; j < regs[15]; j += WINDOW_SIZE) {
            for (int64_t k = 0; k < regs[16]; k += WINDOW_SIZE) {
                regs[21] = regs[9];
                regs[20] = regs[33];
                regs[17] = i;
                regs[18] = j;
                regs[19] = k;
                regs[9] += regs[37];
                select_data<T>();

                regs[21] = regs[9];
                regs[20] = regs[34];
                regs[9] += regs[37];
                select_data<T>();

                regs[21] = regs[9];
                regs[20] = regs[35];
                regs[9] += regs[37];
                select_data<T>();
                regs[40] = regs[11];
                regs[41] = WINDOW_SIZE * WINDOW_SIZE;
                qkv<T>(pIns);

                regs[17] = i;
                regs[18] = j;
                regs[19] = k;
                regs[21] = regs[8];
                regs[20] = regs[38];
                arrange_data<T>();
                regs[9] -= regs[37] * 4;
            }
        }
    }
}

#endif //STP_RESIDUAL_ATTENTION_H
