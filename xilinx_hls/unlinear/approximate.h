#ifndef __SWIN_APPROXIMATE_H__
#define __SWIN_APPROXIMATE_H__

/**
 * @brief 牛顿迭代法求平方根
 * @ref https://zh.wikipedia.org/wiki/%E7%89%9B%E9%A1%BF%E6%B3%95
 * */
template<typename T, int IT>
T newton_sqrt(T x) {
    T ret = x;
    for (int i = 0; i < IT; ++i) {
        ret = (ret + x / ret) / 2.0;
    }
    return ret;
}

#endif