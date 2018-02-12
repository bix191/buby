#ifndef TOKENREADER
#define TOKENREADER

#include <string>
#include <fstream>
#include "token.h"

class TokenReader {
 private:
  std::string filename;
  std::fstream *ifs;
  int chdata;
 public:
  TokenReader(std::string filename);
  void open();
  TokenCommon *nextToken();
  
  
};

#endif

