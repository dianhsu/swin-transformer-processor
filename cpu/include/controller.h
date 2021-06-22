//
// Created by dianhsu on 2021/6/21.
//

#ifndef STP_CONTROLLER_H
#define STP_CONTROLLER_H

#include <istream>

#include "config.h"
#include "partition_merge.h"

/**
 * 中央控制器
 * @tparam T 数据类型
 * @param cIns 指令流
 * @param basePtr 基址
 * @param pIns 参数流
 */
template<typename T>
void control(std::istream &cIns, T *basePtr, std::istream &pIns) {
    unsigned c;
    while (cIns >> c) {
        unsigned x;
        switch (c) {
            case 0:
                // 批量修改寄存器
                cIns >> x;
                for (unsigned i = 0; i < x; ++i) {
                    cIns >> regs[i];
                }
                break;
            case 1:
                // 修改单个寄存器
                cIns >> x;
                cIns >> regs[x];
                break;
            case 2:
                // 数据移动：dst，src, size
                cIns >> regs[0] >> regs[1] >> regs[2];
                for (unsigned i = 0; i < regs[2]; ++i) {
                    basePtr[regs[0] + i] = basePtr[regs[1] + i];
                }
                break;
            case 3:
                // Partition Merge
                partition_merge<T>(basePtr, pIns);
                break;
            default:
                return;
        }
    }
}

#endif //STP_CONTROLLER_H
