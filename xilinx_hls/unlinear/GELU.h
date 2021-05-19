#ifndef __SWIN_GELU_H__
#define __SWIN_GELU_H__

#include <cmath>

/**
 * @brief 计算GELU
 * @ref https://arxiv.org/pdf/1606.08415.pdf
 * @param x 输出参数
 * @return 输出参数
 * */

template<typename T>
T GELU(T x){
    return 0.5 * x * (1 + tanh(sqrt(2.0 / M_PI) * (x + 0.044715 * x * x * x)));
}

#endif