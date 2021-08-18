//
// Created by dianhsu on 2021/7/13.
//

#ifndef STP_FUNCTIONS_H
#define STP_FUNCTIONS_H
#include "config.h"


template<typename T>
void softmax(T* basePtr) {
    T sum = 0;
    for (ptr_t i = 0; i < regs[42]; ++i) {
        sum += (T) exp(basePtr[regs[43] + i]);
    }
    for (ptr_t i = 0; i < regs[42]; ++i) {
        basePtr[regs[54] + i] = (T) exp(basePtr[regs[43] + i]) / sum;
    }
}

template<typename T>
T GELU(T x) {
    return (T) (x * (T) 0.5 * (T) ((T) 1 + (T) tanh(sqrt((T) 2 / (T) 3.14159265359)) *
        (T) (x + (T) 0.044715 * x * x * x)));
}

#endif //STP_FUNCTIONS_H
