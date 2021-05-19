#ifndef __SWIN_MOV_H__
#define __SWIN_MOV_H__

template<typename T>
void mov_vec(T* dst, T* src, int size) {
    for (int i = 0; i < size; ++i) {
        dst[i] = src[i];
    }
}

#endif