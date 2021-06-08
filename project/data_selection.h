/**
 * @brief 从大矩阵中选择小矩阵
 * @param input 输入地址的基址
 * @param output 输出地址的基址
 * @param dim1 输入数据第一维大小
 * @param dim2 输入数据第二维大小
 * @param dim3 输入数据第三维大小
 * @param sz1 选择的数据第一维大小
 * @param sz2 选择的数据第二维大小
 * @param sz3 选择的数据第三维大小
 * @param off1 选择的数据第一维偏移量大小
 * @param off2 选择的数据第二维偏移量大小
 * @param off3 选择的数据第三维偏移量大小
 * */
template<typename T>
void select_data(T* input, T* output, 
        int dim1, int dim2, int dim3, 
        int sz1, int sz2, int sz3, 
        int off1, int off2, int off3){
    for(int i = 0; i < sz1; ++i){
        for(int j = 0; j < sz2; ++j){
            for(int k = 0; k < sz3; ++k){
                output[i * sz2 * sz3 + j * sz3 + k] = input[
                    (sz1 + off1) * dim2 * dim3 + 
                    (sz2 + off2) * dim3 + 
                    (sz3 + off3)
                    ];
            }
        }
    }
}
template<typename T>
void select_data_roll(T* input, T* output, 
        int dim1, int dim2, int dim3, 
        int sz1, int sz2, int sz3, 
        int off1, int off2, int off3){
    for(int i = 0; i < sz1; ++i){
        for(int j = 0; j < sz2; ++j){
            for(int k = 0; k < sz3; ++k){
                output[i * sz2 * sz3 + j * sz3 + k] = input[
                    (sz1 + off1 + dim1) % dim1 * dim2 * dim3 + 
                    (sz2 + off2 + dim2) % dim2 * dim3 + 
                    (sz3 + off3 + dim3) % dim3
                ];
            }
        }
    }
}
/**
 * @brief 将小矩阵安置到大矩阵中
 * @param input 输入地址的基址
 * @param output 输出地址的基址
 * @param dim1 输入数据第一维大小
 * @param dim2 输入数据第二维大小
 * @param dim3 输入数据第三维大小
 * @param sz1 选择的数据第一维大小
 * @param sz2 选择的数据第二维大小
 * @param sz3 选择的数据第三维大小
 * @param off1 选择的数据第一维偏移量大小
 * @param off2 选择的数据第二维偏移量大小
 * @param off3 选择的数据第三维偏移量大小
 * */
template<typename T>
void arrange_data(T* input, T* output,
        int dim1, int dim2, int dim3, 
        int sz1, int sz2, int sz3, 
        int off1, int off2, int off3){
    for(int i = 0; i < sz1; ++i){
        for(int j = 0; j < sz2; ++j){
            for(int k = 0; k < sz3; ++k){
                output[(sz1 + off1) * dim2 * dim3 + (sz2 + off2) * dim3 + (sz3 + off3)]=input[i * sz2 * sz3 + j * sz3 + k];
            }
        }
    }
}