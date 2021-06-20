#include "linear.h"
typedef float data_t;
int main() {
    data_t it[10000];
    data_t ot[100000];
    data_t param[100000];
    linear<data_t, 96>(it, ot, param, 96, 96);
    return 0;
}