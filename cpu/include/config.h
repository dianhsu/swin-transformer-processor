//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_CONFIG_H
#define STP_CONFIG_H


/**
 * @note regs[0] 输入立方体第一维大小
 * @note regs[1] 输入立方体第二维大小
 * @note regs[2] 输入立方体第三维大小
 * @note regs[3] 输出立方体第一维大小
 * @note regs[4] 输出立方体第二维大小
 * @note regs[5] 输出立方体第三维大小
 *
 * @note regs[10] 小立方体第一维大小
 * @note regs[11] 小立方体第二维大小
 * @note regs[12] 小立方体第三维大小
 * @note regs[13] 大立方体第一维大小
 * @note regs[14] 大立方体第二维大小
 * @note regs[15] 大立方体第三维大小
 * @note regs[16] 大立方体中小立方体第一维偏移量大小
 * @note regs[17] 大立方体中小立方体第二维偏移量大小
 * @note regs[18] 大立方体中小立方体第三维偏移量大小
 *
 *
 * */
unsigned regs[32];

#endif //STP_CONFIG_H
