//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_CONFIG_H
#define STP_CONFIG_H


/**
 * @note regs[0] basePtr，不可修改，也是输出存放的地址
 * @note regs[1] 输入立方体第一维大小，二级映射不可修改
 * @note regs[2] 输入立方体第二维大小，二级映射不可修改
 * @note regs[3] 输入立方体第三维大小，二级映射不可修改
 * @note regs[4] 输出立方体第一维大小，二级映射不可修改
 * @note regs[5] 输出立方体第二维大小，二级映射不可修改
 * @note regs[6] 输出立方体第三维大小，二级映射不可修改
 * @note regs[7] 输出存储地址，二级映射不可修改
 * @note regs[8] shift大小，swin block偏移量，二级映射不可修改
 * @note regs[9] down scaling，二级映射不可修改
 * @note regs[10] 小立方体第一维大小；Linear输入维度
 * @note regs[11] 小立方体第二维大小；Linear输出维度
 * @note regs[12] 小立方体第三维大小；Linear中batch数目
 * @note regs[13] 大立方体第一维大小；Matrix Multiply src偏移量
 * @note regs[14] 大立方体第二维大小；Matrix Multiply dst偏移量
 * @note regs[15] 大立方体第三维大小
 * @note regs[16] 大立方体中小立方体第一维偏移量大小
 * @note regs[17] 大立方体中小立方体第二维偏移量大小
 * @note regs[18] 大立方体中小立方体第三维偏移量大小
 * @note regs[19] 一级映射src原地址偏移量
 * @note regs[20] 一级映射dst目标地址偏移量
 * @note regs[21] max stack used
 * @note 所有偏移量的表示，都是单个数据作为单位，不考虑数据在内存中实际所占用的存储空间。
 * */

int64_t regs[32];
const int MAX_MEMORY_SIZE = 1024 * 1024 * 1024;

#ifdef VERBOSE
#define show_regs(x) std::cout << "regs[" << (x) << "]: " << regs[x]
#endif

#endif //STP_CONFIG_H