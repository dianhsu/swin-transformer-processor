#include "main.h"

void project_top(data_t* basePtr, ptr_stream& cIns, param_stream& pIns) {
#pragma HLS TOP name=project_top
#pragma HLS INTERFACE mode=axis register_mode=both port=cIns register
#pragma HLS INTERFACE mode=ap_memory port=basePtr
#pragma HLS INTERFACE mode=axis register_mode=both port=pIns register
    control<data_t>(basePtr, cIns, pIns);
    //matrix<data_t>(basePtr, pIns);
}
