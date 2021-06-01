#ifndef __SWIN_LAYER_NORM_H__
#define __SWIN_LAYER_NORM_H__

/**
 * @brief 计算Layer Normalization
 * @param dst 目标存放位置
 * @param src 处理数据来源
 * @param dx  处理数据维度1
 * @param dy  处理数据维度2
 * @param param 参数。需要三个参数, param[0]: eps, param[1]: beta, param[2]: gamma
 * @return 无返回值
 * */

template<typename T>
void layer_norm(T* dst, T* src, int dx, int dy, T* param) {
    for (int i = 0; i < dx; ++i) {
        T avg = 0;
        T sum = 0;
        T avg2 = 0;
        T sum2 = 0;
        // Var(x) = E(x^2) - E(x)^2
        for (int j = 0; j < dy; ++j) {
            sum += src[i * dy + j];
            sum2 += src[i * dy + j] * src[i * dy + j];
        }
        avg = sum / dy;
        avg2 = sum2 / dy;
        T varx = avg2 - avg * avg;
        // y = \frac{x - E[x]}{\sqrt{Var[x] + \epsilon}} * \gamma + \beta
        for(int j = 0; j < dy; ++j){
            dst[i * dy + j] = (src[i * dy + j] - avg) / sqrt(varx + eps) * gamma + beta;
        }
    }
}

#endif