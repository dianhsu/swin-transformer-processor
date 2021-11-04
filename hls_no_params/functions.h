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

template<typename T, ptr_t C = 96>
void layer_norm(T* basePtr) {
    T sum = 0;
    T sum2 = 0;
    T eps = 0.0001;
    T gamma = 0;
    T beta = 0;
    for (ptr_t i = 0; i < C; ++i) {
        sum += basePtr[i + regs[65]];
        sum2 += basePtr[i + regs[65]] * basePtr[i + regs[65]];
    }
    T avg = sum / C, avg2 = sum2 / C;
    T varx = avg2 - avg * avg;
    for (int j = 0; j < C; ++j) {
        basePtr[j + regs[66]] = (basePtr[j + regs[65]] - avg) / sqrt(varx + eps) * gamma + beta;
    }
}

#endif //STP_FUNCTIONS_H
