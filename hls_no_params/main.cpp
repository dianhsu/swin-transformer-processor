#include "main.h"

void project_top(data_t* basePtr, ptr_stream& cIns, param_stream& pIns) {
    control<data_t>(basePtr, cIns, pIns);
    //matrix<data_t>(basePtr, pIns);
}
