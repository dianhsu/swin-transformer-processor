//
// Created by dianhsu on 2021/6/30.
//

#ifndef STP_RESIDUAL_ATTENTION_H
#define STP_RESIDUAL_ATTENTION_H

#include <istream>

#include "config.h"

const int64_t WINDOW_SIZE = 7;

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
    for (int64_t i = 0; i < regs[14]; i += regs[36]) {
        for (int64_t j = 0; j < regs[15]; j += WINDOW_SIZE) {
            for (int64_t k = 0; k < regs[16]; k += WINDOW_SIZE) {
                regs[21] = regs[9];
                regs[9] += regs[11] * regs[12] * regs[13];
                select_data<T>();

                arrange_data<T>();
                regs[9] -= regs[11] * regs[12] * regs[13];
            }
        }
    }
}

#endif //STP_RESIDUAL_ATTENTION_H
