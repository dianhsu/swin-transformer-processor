#ifndef __SWIN_MMU_H__
#define __SWIN_MMU_H__

template<typename T>
void mem_load(T *dst, T* src, int size){
    for(int i = 0; i < size; ++i){
        dst[i] = src[i];
    }
}

template<typename T>
void mem_save(T *dst, T *src, int size){
    for(int i = 0; i < size; ++i){
        dst[i] = src[i];
    }
}
#endif