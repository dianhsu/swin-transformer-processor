#ifndef __SWIN_ICU_H__
#define __SWIN_ICU_H__

/**
 * @brief Instruction Control Unit
 * @param ip Instruction Pointer
 * @param size Instructions Count
 * */

#define EXIT 0x00
#define MOVV 0x01
#define ADDV 0x02
#define MMR  0x03
#define LOAD 0x04
#define SAVE 0x05
#define MEMLOAD 0x06
#define MEMSAVE 0x07
#define SWT1 0x06
#define SWT2 0x07

static int eax = 0;

template<typename T>
void icu(int* eip, T* param, T* data, T* local) {
    while (1) {
        switch (*eip) {
        case EXIT:
            return;
        case MEMLOAD:
                        
            break;
        default:
            break;
        }
    }
}

#endif