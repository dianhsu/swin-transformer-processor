
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