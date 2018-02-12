#ifndef SYNTAXTREE
#define SYNTAXTREE

#include <string>
#include "tokenreader.h"

typedef enum {
  NODE_PROC=0,
  NODE_CALLFUNC,
  NODE_FUNCPARAMLTSTR,
  NODE_END
} NodeCode;

class NodeCommon  {
  NodeCode nodeCode;
  class NodeCommon *next;
  class NodeCommon *inner;
 public:
  NodeCommon(NodeCode nodeCode);
  void addInner(class NodeCommon *inner);
  void addNext(class NodeCommon *next);
  class NodeCommon *getNext();
  class NodeCommon *getInner();
  NodeCode getNodeCode();
};


class NodeProc : public NodeCommon{
  std::string procName;
 public:
  NodeProc(std::string procName);
  void execute(void);
};

class NodeCallFunc : public NodeCommon {
  std::string funcName;
 public:
  NodeCallFunc(TokenSymbol *tkSymbol,NodeCommon *paramListProc);
  std::string getFuncName();
};

class NodeFuncParamLtStr : public NodeCommon {
  std::string paramStr;
 public:
  NodeFuncParamLtStr(std::string _paramStr);
  std::string getParamStr(void);
 };

class SyntaxParser {
  std::string fileName;
  NodeProc *mainProc;
 public:
  SyntaxParser();
  void load(std::string _fileName);
  NodeCommon *parseVal(TokenReader *tr, TokenCommon *tk);
  NodeCommon *parseFuncParam(TokenReader *tr);
  NodeProc *getMainProc(void);
};

#endif
