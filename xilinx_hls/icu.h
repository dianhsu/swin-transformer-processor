#ifndef __SWIN_ICU_H__
#define __SWIN_ICU_H__

/**
 * @brief Instruction Control Unit
 * @param ip Instruction Pointer
 * @param size Instructions Count
 * */

#define MOVV 0x01
#define ADDV 0x02
#define MMR  0x03
#define LOAD 0x04
#define SAVE 0x05
#define MEMLOAD 0x06
#define MEMSAVE 0x07
#define SWT1 0x06
#define SWT2 0x07


template<typename T>
void icu(int *eip, int size){
    for(int i = 0; i < size; ++i){
        switch(*eip){
            
            default:
                break;
        }
        ++eip;
    }
}

#endif