#include "main.hpp"

void project_top(data_t *basePtr, ptr_stream &cIns, param_stream &pIns) {
  // control<data_t>(basePtr, cIns, pIns);
  // matrix<data_t>(basePtr, pIns);
  regs[9] = 2;
  regs[1] = 96;
  regs[2] = 56;
  regs[3] = 56;
  regs[4] = 192;
  regs[5] = 28;
  regs[6] = 28;
  regs[55] = 0;
  partition_merge<data_t>(basePtr, pIns);
}
