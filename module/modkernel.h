#ifndef MODKERNEL
#define MODKERNEL

#include "modid.h"


typedef enum {
  FUNCID_INIT=0,
  FUNCID_PRINT,
  FUNCID_PRINTF,
  FUNCID_END
} KernelFuncID;

typedef struct {
  FuncID funcID;
  char *funcName;
} FuncList;

static FuncList g_funcList[] = {
  {FUNCID_PRINT, "print" },
  {NULL},
}


class ModKernel  : public Module {
  FuncList *funcList;
  KernelFuncID funcId;
  vector<ValueObj> param;
 public:
  ModKernel();
  bool setupFunc(string funcName);
}

#endif
