//
// Created by dianhsu on 2021/6/22.
//

#ifndef STP_CONFIG_H
#define STP_CONFIG_H


/**
 * ***********************************************************
 * @section basic level
 *
 * @note regs[0] basePtr，不可修改，也是输出存放的地址
 * @note regs[1] 输入立方体第一维大小，二级映射不可修改
 * @note regs[2] 输入立方体第二维大小，二级映射不可修改
 * @note regs[3] 输入立方体第三维大小，二级映射不可修改
 * @note regs[4] 输出立方体第一维大小，二级映射不可修改
 * @note regs[5] 输出立方体第二维大小，二级映射不可修改
 * @note regs[6] 输出立方体第三维大小，二级映射不可修改
 * @note regs[7] 一级映射src原地址偏移量
 * @note regs[8] 一级映射dst目标地址偏移量
 * @note regs[9] 当前已经使用或者预留的空间大小
 *
 * ***********************************************************
 *
 * @section  data selection and data arrangement
 *
 * @note regs[10] shift大小，swin block偏移量，二级映射不可修改
 * @note regs[11] 小立方体第一维大小；
 * @note regs[12] 小立方体第二维大小；
 * @note regs[13] 小立方体第三维大小；
 * @note regs[14] 大立方体第一维大小；
 * @note regs[15] 大立方体第二维大小；
 * @note regs[16] 大立方体第三维大小
 * @note regs[17] 大立方体中小立方体第一维相对偏移量大小
 * @note regs[18] 大立方体中小立方体第二维相对偏移量大小
 * @note regs[19] 大立方体中小立方体第三维相对偏移量大小
 * @note regs[20] src基址偏移量
 * @note regs[21] dst基址偏移量
 *
 * ***********************************************************
 *
 * @section Linear
 *
 * @note regs[22] Linear输入维度
 * @note regs[23] Linear输出维度
 * @note regs[24] batch 大小
 * @note regs[25] src基址偏移量
 * @note regs[26] dst基址偏移量
 *
 * ***********************************************************
 *
 * @section Matrix Param Multiply
 *
 * @note regs[27] src基址偏移量
 * @note regs[28] dst基址偏移量
 *
 * ***********************************************************
 * @section Attention
 *
 * @note regs[29] dim1
 * @note regs[30] dim2
 * @note regs[31] dim3
 * @note regs[32] sz
 *
 * @note regs[33] Q offset
 * @note regs[34] K offset
 * @note regs[35] V offset
 * @note regs[36] Heads
 * @note regs[37] Cube size
 *
 * @note regs[38] Result offset
 * @note regs[39] Tmp offset
 *
 * @note regs[40] Q dim1
 * @note regs[41] Q dim2
 *
 * @note regs[44] TQ offset
 * @note regs[45] TK offset
 * @note regs[46] TV offset
 * @note regs[47] tmp1 offset
 * @note regs[48] tmp2 offset
 * @note regs[49] tmp3 offset
 *
 * @note regs[42] Softmax Batch
 * @note regs[43] Softmax Input offset
 * @note regs[54] Softmax Output offset
 * @note regs[56] 1height offset
 * @note regs[57] QHeight Offset
 * @note regs[58] KHeight Offset
 * @note regs[59] VHeight Offset
 * @note regs[60] 1Qheight result
 * @note regs[61] 1Kheight result
 * @note regs[62] 1Vheight result
 * ***********************************************************
 *
 * @section Feed Forward
 *
 * @note regs[50] sz
 * @note regs[51] tmp1 Offset
 * @note regs[52] tmp2 Offset
 * @note regs[53] tmp3 Offset
 *
 * @note regs[63] linear_ins_offset
 * @note regs[64] linear_ots_offset
 *
 * @note regs[55] move data add or overlay
 *
 * @note 所有偏移量的表示，都是单个数据作为单位，不考虑数据在内存中实际所占用的存储空间。
 *
 * */

int64_t regs[70];
const int MAX_MEMORY_SIZE = 1024 * 1024 * 1024;

#ifdef VERBOSE
#define show_regs(x) std::cout << "regs[" << (x) << "]: " << regs[x]
#endif

#endif //STP_CONFIG_H
