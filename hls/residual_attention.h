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
void qkv(T* basePtr,param_stream& pIns) {
    // K^T x Q
    for (ptr_t i = 0; i < regs[41]; ++i) {
        for (ptr_t j = 0; j < regs[41]; ++j) {
            T tmp = 0;
            for (ptr_t k = 0; k < regs[40]; ++k) {
                tmp += basePtr[regs[34] + k * regs[41] + i] * basePtr[regs[33] + k * regs[41] + j];
            }
            basePtr[regs[39] + i * regs[41] + j] = tmp;
        }
    }
    // tmp -> tmp1
    T scale;
    pIns >> scale;
    for (ptr_t i = 0; i < regs[37]; ++i) {
        basePtr[regs[47] + i] = basePtr[regs[39] + i] * scale;
    }
    // tmp1 -> tmp2
    T position_encoding;
    for (ptr_t i = 0; i < regs[37]; ++i) {
        pIns >> position_encoding;
        basePtr[regs[48] + i] = basePtr[regs[47] + i] + position_encoding;
    }
    // tmp2 -> tmp3
    regs[42] = regs[41];
    for (ptr_t i = 0; i < regs[41]; ++i) {
#pragma HLS pipeline off
        regs[43] = regs[48] + i * regs[41];
        regs[54] = regs[49] + i * regs[41];
        softmax<T>(basePtr);
    }
    // tmp3 -> result
    for (ptr_t i = 0; i < regs[40]; ++i) {
        for (ptr_t j = 0; j < regs[41]; ++j) {
            T tmp = 0;
            for (ptr_t k = 0; k < regs[41]; ++k) {
                tmp += basePtr[regs[46] + i * regs[41] + k] * basePtr[regs[49] + k * regs[41] + j];
            }
            basePtr[regs[38] + i * regs[41] + j] = tmp;
        }
    }
}

template<typename T>
void residualAttention(T* basePtr,param_stream& pIns) {
    regs[29] = regs[1];
    regs[30] = regs[2];
    regs[31] = regs[3];
    regs[32] = regs[29] * regs[30] * regs[31];

    regs[33] = regs[9];
    regs[9] += regs[32];
    regs[34] = regs[9];
    regs[9] += regs[32];
    regs[35] = regs[9];
    regs[9] += regs[32];

    regs[22] = regs[32];
    regs[23] = regs[32];

    regs[24] = 96;
    regs[25] = 0;

    regs[26] = regs[33];
    linear<T>(basePtr,pIns);

    regs[26] = regs[34];
    linear<T>(basePtr,pIns);

    regs[26] = regs[35];
    linear<T>(basePtr, pIns);

    regs[11] = regs[29] / regs[36];
    regs[12] = WINDOW_SIZE;
    regs[13] = WINDOW_SIZE;
    regs[14] = regs[29];
    regs[15] = regs[30];
    regs[16] = regs[31];
    regs[37] = regs[11] * regs[12] * regs[13];

    regs[44] = regs[9];
    regs[9] += regs[37];
    regs[45] = regs[9];
    regs[9] += regs[37];
    regs[46] = regs[9];
    regs[9] += regs[37];

    regs[40] = regs[11];
    regs[41] = WINDOW_SIZE * WINDOW_SIZE;

    regs[38] = regs[9]; // result
    regs[9] += regs[37];
    regs[39] = regs[9]; // tmp
    regs[9] += regs[41] * regs[41];
    regs[47] = regs[9]; // tmp1
    regs[9] += regs[41] * regs[41];
    regs[48] = regs[9]; // tmp2
    regs[9] += regs[41] * regs[41];
    regs[49] = regs[9];
    regs[9] += regs[41] * regs[41];

    for (ptr_t i = 0; i < regs[14]; i += regs[11]) {
        for (ptr_t j = 0; j < regs[15]; j += WINDOW_SIZE) {
            for (ptr_t k = 0; k < regs[16]; k += WINDOW_SIZE) {
                regs[17] = i;
                regs[18] = j;
                regs[19] = k;

                regs[21] = regs[9];
                regs[20] = regs[44];
                select_data<T>(basePtr);

                regs[21] = regs[9];
                regs[20] = regs[45];
                select_data<T>(basePtr);

                regs[21] = regs[9];
                regs[20] = regs[46];
                select_data<T>(basePtr);

                qkv<T>(basePtr, pIns);

                regs[17] = i;
                regs[18] = j;
                regs[19] = k;
                regs[21] = regs[8];
                regs[20] = regs[38];
                arrange_data<T>(basePtr);

            }
        }
    }
    regs[9] = regs[33];
}

#endif //STP_RESIDUAL_ATTENTION_H
