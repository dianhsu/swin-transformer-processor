#ifndef __SWIN_MULTIPLY_H__
#define __SWIN_MULTIPLY_H__

template<typename T, int WINDOWS_SIZE>
void multiply(T* dst, T* src, T* param) {
    T dst_local[WINDOWS_SIZE][WINDOWS_SIZE];
#pragma HLS array_partition variable=dst_local complete dim=0
    T src_local[WINDOWS_SIZE][WINDOWS_SIZE];
#pragma HLS array_partition variable=src_local complete dim=2
    T param_local[WINDOWS_SIZE][WINDOWS_SIZE];
#pragma HLS array_partition variable=param_local complete dim=1

    for (int i = 0; i < WINDOWS_SIZE; ++i) {
        for (int j = 0; j < WINDOWS_SIZE; ++j) {
            src_local[i][j] = src[i * WINDOWS_SIZE + j];
            param_local[i][j] = param[i * WINDOWS_SIZE + j];
        }
    }

    for (int i = 0; i < WINDOWS_SIZE; ++i) {
        for (int j = 0; j < WINDOWS_SIZE; ++j) {
            dst_local[i][j] = 0;
            for (int k = 0; k < WINDOWS_SIZE; ++k) {
#pragma HLS unroll
                dst_local[i][j] += src_local[i][k] * param_local[k][j];
            }
        }
    }
    for (int i = 0; i < WINDOWS_SIZE; ++i) {
        for (int j = 0; j < WINDOWS_SIZE; ++i) {
            dst[i * WINDOWS_SIZE + j] = dst_local[i][j];
        }
    }
}


#endif