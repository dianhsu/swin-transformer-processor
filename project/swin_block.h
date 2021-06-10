#include "linear.h"
#include "data_selection.h"
#include "functions.h"

/**
 * @brief 计算整块内容
 * @param input 输入基址
 * @param output 输出基址
 * @param param 参数基址
 * @param id1 第一维宽度
 * @param id2 第二维宽度
 * @param ic3 通道数
 * @param ws window的大小
 * @param heads 多头的数量
 * */
template<typename T>
void swin_block(T* input, T* param, T* output, int id1, int id2, int ic3, int ws, int heads) {
    T tmp1[100000];
    for (int i = 0; i < id1 * id2 * ic3; ++i) {
        tmp1[i] = input[i];
    }
    T tmp[100000];
    int c = ic3 / heads;
    for (int i = 0; i < id1; ++i) {
        for (int j = 0; j < id2; ++j) {
            select_data<T>(input, tmp, id1, id2, ic3, 1, 1, ic3, i, j, 0);
            layer_normalization<T>(tmp, tmp, ic3, param[0], param[1], param[2]); // TODO: 修改这个部分参数
            arrange_data<T>(tmp, input, id1, id2, ic3, 1, 1, ic3, i, j, 0);
        }
    }
    int qkv[3][100000];
    int tmp2[10000];
    int tmp3[3][10000];
    for (int i = 0; i < id1; i += ws) {
        for (int j = 0; j < id2; j += ws) {
            for (int i1 = 0; i1 < ws; ++i1) {
                for (int j1 = 0; j1 < ws; ++j1) {
                    select_data<T>(input, tmp, id1, id2, ic3, 1, 1, ic3, i + i1, j + j1, 0);
                    for (int kase = 0; kase < 3; ++kase) {
                        linear<T>(tmp1, tmp2, param, ic3, ic3);
                        arrange_data<T>(tmp2, qkv[kase], ws, ws, ic3, 1, 1, ic3, i1, j1, 0);
                    }
                }
            }
            for (int k = 0; k < ic3; k += c) {
                select_data<T>(qkv[0], tmp3[0], ws, ws, ic3, ws, ws, c, 0, 0, k);
                // TODO: ?!?! 小立方体压缩相乘

                arrange_data<T>(tmp3, input, id1, id2, ic3, ws, ws, c, i, j, k);
            }
        }
    }
    for (int i = 0; i < id1 * id2 * ic3; ++i) {
        output[i] += input[i];
    }
}


/**
 * @brief 计算整块内容
 * @param input 输入基址
 * @param output 输出基址
 * @param param 参数基址
 * @param id1 第一维宽度
 * @param id2 第二维宽度
 * @param ic3 通道数
 * @param ws window的大小
 * @param heads 多头的数量
 * @param sf shift的大小
 * */
template<typename T>
void swin_block_shift(T* input, T* param, T* output, int id1, int id2, int ic3, int ws, int heads, int sf) {
    for (int i = 0; i < id1 * id2 * ic3; ++i) {
        output[i] = input[i];
    }
}