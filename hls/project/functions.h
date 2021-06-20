#ifndef __STP_FUNCTIONS_H__
#define __STP_FUNCTIONS_H__


/**
 * @brief 计算Softmax
 * @param input 输入基址
 * @param output 输出基址
 * @param batch 组大小
 * @note 指数函数需要自己实现一下，一是定点数并没有实现指数函数，二是拟合可以加快求解速度
 * @note 还需要线性拟合一下
 * */
template<typename T>
void softmax(T* input, T* output, int batch){
    T sum = 0;
    for(int i = 0; i < batch; ++i){
#pragma HLS pipeline
        sum += exp(input[i]);
    }
    for(int i = 0; i < batch; ++i){
#pragma HLS pipeline
        output[i] = exp(input[i]) / sum;
    }
}

/**
 * @brief 计算Gelu
 * @param input 输入基址
 * @param output 输出基址
 * @param batch 组大小
 * @note 这个函数目前还没用线性拟合
 * */
template<typename T>
void gelu(T* input, T* output, int batch){
    for(int i = 0; i < batch; ++i){
        output[i] = input[i] * 0.5 * (1 + tanh(sqrt(2/3.14159265359)*
            (input[i] + 0.044715 * input[x] * input[x] * input[x])));
    }
}


template<typename T>
void vector_add(T *input, T *output, int batch){
    for(int i = 0; i < batch; ++i){
        output[i] += input[i];
    }
}

template<typename T>
void vector_scalar_add(T *input, T* output, int batch){
    for(int i = 0; i < batch; ++i){
        output[i] += input[i];
    }
}
/**
 * @brief Layer Normalization
 * @param input 输入基址
 * @param output 输出基址
 * @param batch 单组输入数据大小
 * @param eps 见公式中描述
 * @param gamma 见公式中描述
 * @param beta 见公式中描述
 * @note 好像做不到unroll
 * */
template<typename T>
void layer_normalization(T* input, T* output, int batch, T eps, T gamma, T beta){
    T sum = 0;
    T sum2 = 0;

    for(int i = 0; i < batch; ++i){
#pragma HLS pipeline
        sum += input[i];
        sum2 += input[i] * input[i];
    }
    // Variance
    T avg = sum / batch;
    T varx =sum2 / batch -  sum * avg; 
    for (int j = 0; j < batch; ++j) {
#pragma HLS pipeline
        output[j] = (input[j] - avg) / sqrt(varx  + eps) * gamma + beta;
    }
}

#endif