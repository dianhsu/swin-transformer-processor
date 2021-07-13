//
// Created by dianhsu on 2021/7/13.
//

#ifndef STP_FUNCTIONS_H
#define STP_FUNCTIONS_H

#include "config.h"

template<typename T>
void softmax() {
    T *basePtr = reinterpret_cast<T *>(regs[0]);
    T sum = 0;
    for (int i = 0; i < regs[42]; ++i) {
        sum += exp(basePtr[regs[43] + i]);
    }
    for (int i = 0; i < regs[42]; ++i) {
        basePtr[regs[43] + i] = exp(basePtr[regs[43] + i]) / sum;
    }
}

template<typename T>
T GELU(T x) {
    return x * 0.5 * (1 + tanh(sqrt(2 / 3.14159265359) *
                               (x + 0.044715 * x * x * x)));
}

#endif //STP_FUNCTIONS_H
