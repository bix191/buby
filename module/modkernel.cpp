
#include "modkernel.h"


ModKernel::ModKernel() : Module(MODID_KERNEL) {
  funclist = g_funcList;
  funcId=FUNCID_INIT;
}

bool ModKernel::setupFunc(std::string funcName,vector<ValueObj> param) {
  
}
