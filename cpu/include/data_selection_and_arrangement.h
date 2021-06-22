//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_DATA_SELECTION_AND_ARRANGEMENT_H
#define STP_DATA_SELECTION_AND_ARRANGEMENT_H

#include "config.h"

/**
 * @brief 从大矩阵中选择小矩阵
 * @param dst 目标地址偏移量
 * @param src 原地址偏移量
 * @param basePtr 基址
 * @note regs[10] 小立方体第一维大小
 * @note regs[11] 小立方体第二维大小
 * @note regs[12] 小立方体第三维大小
 * @note regs[13] 大立方体第一维大小
 * @note regs[14] 大立方体第二维大小
 * @note regs[15] 大立方体第三维大小
 * @note regs[16] 大立方体中小立方体第一维偏移量大小
 * @note regs[17] 大立方体中小立方体第二维偏移量大小
 * @note regs[18] 大立方体中小立方体第三维偏移量大小
 * */
template<typename T>
void select_data(int dst, int src, T *basePtr) {
    for (int i = 0; i < regs[13]; ++i) {
        for (int j = 0; j < regs[14]; ++j) {
            for (int k = 0; k < regs[15]; ++k) {
                basePtr[i * regs[14] * regs[15] + j * regs[15] + k + dst] = basePtr[
                        (i + regs[16]) * regs[11] * regs[12] +
                        (j + regs[17]) * regs[12] +
                        (k + regs[18]) +
                        src
                ];
            }
        }
    }
}

/**
 * @brief 从大矩阵中选择小矩阵，支持循环选择
 * @param dst 目标地址偏移量
 * @param src 原地址偏移量
 * @param basePtr 输入地址的基址
 * @note regs[10] 小立方体第一维大小
 * @note regs[11] 小立方体第二维大小
 * @note regs[12] 小立方体第三维大小
 * @note regs[13] 大立方体第一维大小
 * @note regs[14] 大立方体第二维大小
 * @note regs[15] 大立方体第三维大小
 * @note regs[16] 大立方体中小立方体第一维偏移量大小
 * @note regs[17] 大立方体中小立方体第二维偏移量大小
 * @note regs[18] 大立方体中小立方体第三维偏移量大小
 * * */
template<typename T>
[[maybe_unused]] void select_data_roll(int dst, int src, T *basePtr) {
    for (int i = 0; i < regs[13]; ++i) {
        for (int j = 0; j < regs[14]; ++j) {
            for (int k = 0; k < regs[15]; ++k) {
                basePtr[i * regs[14] * regs[15] + j * regs[15] + k + dst] = basePtr[
                        (i + regs[16]) % regs[10] * regs[11] * regs[12] +
                        (j + regs[17]) % regs[11] * regs[12] +
                        (k + regs[18]) % regs[12] +
                        src
                ];
            }
        }
    }
}

/**
 * @brief 将小立方体安置到大立方体中
 * @param basePtr 输入地址的基址
 * @param dst 目标地址偏移量
 * @param src 原地址偏移量
 * @note regs[10] 小立方体第一维大小
 * @note regs[11] 小立方体第二维大小
 * @note regs[12] 小立方体第三维大小
 * @note regs[13] 大立方体第一维大小
 * @note regs[14] 大立方体第二维大小
 * @note regs[15] 大立方体第三维大小
 * @note regs[16] 大立方体中小立方体第一维偏移量大小
 * @note regs[17] 大立方体中小立方体第二维偏移量大小
 * @note regs[18] 大立方体中小立方体第三维偏移量大小
 * * */
template<typename T>
[[maybe_unused]] void arrange_data(int dst, int src, T *basePtr) {
    for (int i = 0; i < regs[10]; ++i) {
        for (int j = 0; j < regs[11]; ++j) {
            for (int k = 0; k < regs[12]; ++k) {
                basePtr[
                        (i + regs[16]) * regs[14] * regs[15] +
                        (j + regs[17]) * regs[15] +
                        (k + regs[18]) +
                        dst
                ] = basePtr[
                        i * regs[11] * regs[12] +
                        j * regs[12] +
                        k +
                        src];
            }
        }
    }
}

/**
 * @brief 将小矩阵安置到大矩阵中，支持循环安置
 * @param dst 目标地址偏移量
 * @param src 原始地址偏移量
 * @param basePtr 输入地址的基址
 * @note regs[10] 小立方体第一维大小
 * @note regs[11] 小立方体第二维大小
 * @note regs[12] 小立方体第三维大小
 * @note regs[13] 大立方体第一维大小
 * @note regs[14] 大立方体第二维大小
 * @note regs[15] 大立方体第三维大小
 * @note regs[16] 大立方体中小立方体第一维偏移量大小
 * @note regs[17] 大立方体中小立方体第二维偏移量大小
 * @note regs[18] 大立方体中小立方体第三维偏移量大小
 * * */
template<typename T>
[[maybe_unused]] void arrange_data_roll(int dst, int src, T *basePtr) {
    for (int i = 0; i < regs[10]; ++i) {
        for (int j = 0; j < regs[11]; ++j) {
            for (int k = 0; k < regs[12]; ++k) {
                basePtr[
                        (i + regs[16]) % regs[13] * regs[14] * regs[15] +
                        (j + regs[17]) % regs[14] * regs[15] +
                        (k + regs[18]) % regs[15] +
                        dst
                ] = basePtr[
                        i * regs[11] * regs[12] +
                        j * regs[12] +
                        k +
                        src];
            }
        }
    }
}

#endif //STP_DATA_SELECTION_AND_ARRANGEMENT_H
