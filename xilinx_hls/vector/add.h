#ifndef __SWIN_ADD_H__
#define __SWIN_ADD_H__

template<typename T>
void add_vec(T* dst, T* src, int size) {
    for (int i = 0; i < size; ++i) {
        dst[i] += src[i];
    }
}

#endif