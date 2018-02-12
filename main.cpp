#include "tokenreader.h"
#include "syntaxparser.h"



int main(int argc, char *argv[]) {
  std::string fileName;
  NodeProc *mainProc;
  
  fileName=argv[1];
  
  SyntaxParser sp;
  sp.load(fileName);
  mainProc=sp.getMainProc();
  
  mainProc->execute();
  return 0;
}
