/**
 * @param input 输出数据，维度[1,C]
 * @param output 输出数据，维度[1,C]
 * @param param 参数，维度[C,C]
 * @note 
 * */
template<typename T, int C>
void matrix(T* input, T* output, T* param) {
    T localInput[C];
#pragma HLS array_partition variable=localInput dim=1
    T localOutput[C];
#pragma HLS array_partition variable=localOutput dim=1
    T paramLocal[C][C];
#pragma HLS array_partition variable=paramLocal dim=2
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
#pragma HLS pipeline
            paramLocal[i][j] = param[i * C + j];
        }
    }
    for (int i = 0; i < C; ++i) {
#pragma HLS pipeline
        localInput[i] = input[i];
    }
    for (int i = 0; i < C; ++i) {
#pragma HLS UNROLL
        localOuput[i] = 0;
    }
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
#pragma HLS UNROLL
            localOutput[j] += input[i] * paramLocal[i][j];
        }
    }
    for (int i = 0; i < C; ++i) {
#pragma HLS pipeline
        output[i] = localOutput[i];
    }
}
