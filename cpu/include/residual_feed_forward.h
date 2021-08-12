//
// Created by dianhsu on 2021/6/30.
//

#ifndef STP_RESIDUAL_FEED_FORWARD_H
#define STP_RESIDUAL_FEED_FORWARD_H

#include <istream>
#include "config.h"

template<typename T>
void residualFeedForward(std::istream &pIns) {
    regs[50] = regs[1] * regs[2] * regs[3];
    T *basePtr = reinterpret_cast<T *>(regs[0]);
    regs[51] = regs[8] + regs[50];
    regs[52] = regs[51] + regs[50];
    regs[53] = regs[52] + regs[50];
    regs[9] = regs[53] + regs[50];

    regs[63] = regs[9];
    regs[9] += regs[1];
    regs[64] = regs[9];
    regs[9] += regs[1];


    regs[11] = regs[1];
    regs[12] = 1;
    regs[13] = 1;
    regs[14] = regs[1];
    regs[15] = regs[2];
    regs[16] = regs[3];

    for (int64_t j = 0; j < regs[2]; ++j) {
        for (int64_t k = 0; k < regs[3]; ++k) {
            regs[17] = 0;
            regs[18] = j;
            regs[19] = k;
            regs[20] = 0;
            regs[21] = regs[63];

            select_data<T>();

            regs[22] = regs[1];
            regs[23] = regs[1];
            regs[24] = 96;
            regs[25] = regs[63];
            regs[26] = regs[64];
            linear<T>(pIns);

            regs[20] = regs[64];
            regs[21] = regs[52];
            arrange_data<T>();
        }
    }
    //linear<T>(pIns);


    for (int i = 0; i < regs[50]; ++i) {
        basePtr[regs[52] + i] = GELU(basePtr[regs[51] + i]);
    }

    regs[25] = regs[52];
    regs[26] = regs[53];
    linear<T>(pIns);

    for (int i = 0; i < regs[50]; ++i) {
        basePtr[regs[8] + i] = basePtr[regs[53] + i] + basePtr[i];
    }
    regs[9] = regs[51];
}

#endif //STP_RESIDUAL_FEED_FORWARD_H
