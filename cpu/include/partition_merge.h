//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_PARTITION_MERGE_H
#define STP_PARTITION_MERGE_H

#include <istream>

#include "config.h"
#include "linear.h"
#include "matrix_multiply.h"
#include "data_selection_and_arrangement.h"

const int64_t BATCH_SIZE = 96;

/**
 * @tparam T 数据类型
 * @param pIns 参数流
 */
template<typename T>
void partition_merge(std::istream &pIns) {
    regs[7] = regs[4] * regs[5] * regs[6]; // local offset
    regs[13] = regs[1]; // Main H
    regs[14] = regs[2]; // Main X
    regs[15] = regs[3]; // Main Y
    for (int64_t i = 0; i < regs[14]; i += regs[9]) {
        for (int64_t j = 0; j < regs[15]; j += regs[9]) {

            regs[10] = regs[1]; // Inter H
            regs[11] = regs[9]; // Inter X
            regs[12] = regs[9]; // Inter Y
            regs[13] = regs[1]; // Main H
            regs[14] = regs[2]; // Main X
            regs[15] = regs[3]; // Main Y
            regs[16] = 0;   // offset h
            regs[17] = i;   // offset x
            regs[18] = j;   // offset y
            regs[19] = 0;   // src offset
            regs[20] = regs[21]; // dst offset
            regs[21] += regs[1] * regs[9] * regs[9];    // max stack reserved
#ifdef VERBOSE2
            std::cout << "\tDATA SELECTION" << std::endl;
            std::cout << "\t", show_regs(10), std::cout << std::endl;
            std::cout << "\t", show_regs(11), std::cout << std::endl;
            std::cout << "\t", show_regs(12), std::cout << std::endl;
            std::cout << "\t", show_regs(19), std::cout << std::endl;
            std::cout << "\t", show_regs(20), std::cout << std::endl;
            std::cout << "\t", show_regs(21), std::cout << std::endl;
#endif
            select_data<T>();

            regs[10] = regs[1] * regs[9] * regs[9]; // input dimension
            regs[11] = regs[1] * regs[9];   // output dimension
            regs[12] = BATCH_SIZE;  // batch size
            regs[19] = regs[20];    // src offset
            regs[20] += regs[10];   // dst offset
            //regs[21] = regs[20] + regs[11];
            linear<T>(pIns);

            regs[10] = regs[1]; // Inter H
            regs[11] = regs[9]; // Inter X
            regs[12] = regs[9]; // Inter Y
            regs[13] = regs[1]; // Main H
            regs[14] = regs[2]; // Main X
            regs[15] = regs[3]; // Main Y
            regs[16] = 0;   // offset h
            regs[17] = i / regs[9];   // offset x
            regs[18] = j / regs[9];   // offset y
            regs[19] = regs[20]; // src offset
            regs[20] = regs[7]; // dst offset
            regs[21] -= regs[1] * regs[9] * regs[9];    // max stack reserved
            arrange_data<T>();
        }
    }
}

#endif //STP_PARTITION_MERGE_H
