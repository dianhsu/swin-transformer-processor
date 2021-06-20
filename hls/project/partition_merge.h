#include "linear.h"
#include "matrix_multiply.h"
#include "data_selection.h"

/**
 * @param input 输入数据
 * @param param 参数
 * @param output 输出数据
 * @param id1 输入维度1
 * @param id2 输入维度2
 * @param ic3 输入通道数
 * @param od1 输出维度1
 * @param od2 输出维度2
 * @param oc3 输出通道数
 * */

template<typename T>
void partition_merge(T* input, T* param, T* output, int ds,
    int id1, int id2, int ic3,
    int od1, int od2, int oc3) {
    T tmp1[100000];
    int output_offset = 0;
    for (int i = 0; i < id1; i += ds) {
        for (int j = 0; j < id2; j += ds) {
            select_data(input, tmp1, id1, id2, ic3, ds, ds, ic3, i, j, 0);
            linear<T, 96>(tmp1, output + output_offset, param, ds * ds * ic3, ds * ic3);
            output_offset += ds * ic3;
        }
    }
}