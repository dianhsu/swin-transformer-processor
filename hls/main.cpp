#include "main.h"

void project_top(data_t* basePtr, ptr_stream& cIns, param_stream& pIns) {
    regs[0] = (ptr_t) (basePtr);
    control<data_t>(cIns, pIns);
}