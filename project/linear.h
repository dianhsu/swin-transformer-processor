#include "matrix_multiply.h"

template<typename T, int C>
void linear(T *input, T *output, T* param, int input_dim, int output_dim){
    int rows = input_dim / C;
    int cols = output_dim / C;
    T outputTmp[C];
#pragma HLS array_partition variable=outputTmp complete dim=1    
    T outputBoxTmp[C];
#pragma HLS array_partition variable=outputBoxTmp complete dim=1
    T paramTmp[C * C];

    for(int j = 0; j < cols; ++j){
        for(int i = 0; i < C; ++i){
            outputTmp[i] = 0;
        }
        for(int i = 0; i < rows; ++i){
#pragma HLS pipeline off
            for(int d = 0; d < C; ++d){
                outputBoxTmp[d] = 0;
            }
            // data selection, select a C by C matrix from Parameters
            for(int d1 = 0; d1 < C; ++d1){
                for(int d2 = 0; d2 < C; ++d2){
                    paramTmp[d1 * C + d2] = param[(i * C + d1) * output_dim + j * C + d2];
                }
            }
            matrix<T, C>(input + j * C, outputBoxTmp, paramTmp);
        }
        for(int i = 0; i < C; ++i){
            output[j * C + i] = outputTmp[i];
        }
    }
}

