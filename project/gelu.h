#include <cmath>

template<typename T>
void gelu(T* input, T* output, int batch){
    for(int i = 0; i < batch; ++i){
        output[i] = input[i] * 0.5 * (1 + tanh(sqrt(2/3.14159265359)*
            (input[i] + 0.044715 * input[x] * input[x] * input[x])));
    }
}
