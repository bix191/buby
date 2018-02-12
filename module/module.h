#ifndef MODULE
#define MODULE

#include <string>
#include "modid.h"

class Module {
  ModID modid;
  std::string modname;
 public:
  Module(ModID modid);
}

#endif

