//
// Created by dianhsu on 2021/6/21.
//

#ifndef STP_CONTROLLER_H
#define STP_CONTROLLER_H

#include <iostream>

unsigned regs[32];

template<typename T>
void control(std::istream &din, T *input, T *output, std::istream &param) {
    unsigned c;
    while (din >> c) {
        unsigned x;
        switch (c) {
            case 0:
                // 批量修改寄存器
                din >> x;
                for (unsigned i = 0; i < x; ++i) {
                    din >> regs[i];
                }
                break;
            case 1:
                // 修改单个寄存器
                din >> x;
                din >> regs[x];
                break;
            case 2:

                break;
            default:
                return;
        }
    }
}

#endif //STP_CONTROLLER_H
