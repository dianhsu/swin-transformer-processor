/**
 * @brief 计算Softmax
 * @param input 输入基址
 * @param output 输出基址
 * @param batch 组大小
 * @note 指数函数需要自己实现一下，一是定点数并没有实现指数函数，二是拟合可以加快求解速度
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
