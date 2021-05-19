#ifndef __SWIN_SOFTMAX_H__
#define __SWIN_SOFTMAX_H__

#include <cmath>

/**
 * @brief 计算Softmax
 * @param dst 目标存放位置
 * @param src 处理数据来源
 * @param dx  处理数据维度1
 * @param dy  处理数据维度2
 * @return 无返回值
 * */

template<typename T>
void softmax(T* dst, T* src, int dx, int dy) {
    for (int i = 0; i < dx; ++i) {
        T sum = 0;
        for (int j = 0; j < dy; ++j) {
            sum += exp(src[i * dy + j]);
        }
        for (int j = 0; j < dy; ++j) {
            dst[i * dy + j] = src[i * dy + j] / sum;
        }
    }
}

#endif