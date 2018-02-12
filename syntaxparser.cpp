#include <iostream>

#include "syntaxparser.h"
#include "token.h"
#include "tokenreader.h"

NodeCommon::NodeCommon(NodeCode _nodeCode) {
  nodeCode=_nodeCode;
}
void NodeCommon::addNext(class NodeCommon *_next) {
  next=_next;
}
void NodeCommon::addInner(class NodeCommon *_inner) {
  inner=_inner;
}

NodeCommon *NodeCommon::getNext(void) {
  return next;
}

NodeCommon *NodeCommon::getInner(void) {
  return inner;
}

NodeCode NodeCommon::getNodeCode(void)  {
  return nodeCode;
}

NodeProc::NodeProc(std::string _procName):NodeCommon(NODE_PROC) {
  procName=_procName;
}

void NodeProc::execute() {
  NodeCommon *cur;
  NodeCallFunc *curFunc;
  NodeFuncParamLtStr *funcParam;
  std::string funcName;

  cur=getNext();
  while(cur!=NULL) {
    NodeCode nc;
    nc=cur->getNodeCode();
    switch(nc) {
    case NODE_CALLFUNC:
      curFunc=(NodeCallFunc*)cur;
      funcName = curFunc->getFuncName();
      if (funcName.compare("print")==0) {
	std::string outStr;
	funcParam=(NodeFuncParamLtStr *)curFunc->getInner();
	outStr=funcParam->getParamStr();

	std::cout<<outStr;
      }
      break;
    default:
      abort();
    }
    cur = cur->getNext();
  }
}



NodeCallFunc::NodeCallFunc(TokenSymbol *tkSymbol,NodeCommon *paramListProc):
  NodeCommon(NODE_CALLFUNC) {
  funcName=tkSymbol->getSymbolStr();
  addInner(paramListProc);
}

std::string NodeCallFunc::getFuncName() {
  return funcName;
}

NodeFuncParamLtStr::NodeFuncParamLtStr(std::string _paramStr):NodeCommon(NODE_FUNCPARAMLTSTR) {
  paramStr=_paramStr;
}

std::string NodeFuncParamLtStr::getParamStr(void) {
  return paramStr;
}

SyntaxParser::SyntaxParser(void) {
  mainProc=NULL;
}

NodeProc *SyntaxParser::getMainProc(void) {
  return mainProc;
}

void SyntaxParser::load(std::string _fileName) {
  NodeCommon *cur;
  NodeCommon *val;
  fileName=_fileName;

  
  TokenCommon *tk;
  TokenReader *tr = new TokenReader(fileName);
  mainProc = new NodeProc(fileName);
  cur=mainProc;

  tr->open();

  
  tk = tr->nextToken();
  while(tk!=NULL) {
    switch(tk->getType()) {
    case TOKEN_CDATA:
      val = parseVal(tr,tk);
      cur->addNext(val);
      cur=val;
      break;
    case TOKEN_CR:
      break;
    default:
      abort();
    }
    tk = tr->nextToken();
  }
  delete tr;
}

NodeCommon *SyntaxParser::parseVal(TokenReader *tr,
				   TokenCommon *tk) {
  NodeCommon *rtnNode;
  TokenCommon *ntk;
  NodeCommon *paramListProc;
  TokenSymbol *tkStr;
  NodeCallFunc *nodeCallFunc;
  
  ntk = tr->nextToken();
  switch(ntk->getType()) {
  case TOKEN_LEFT_PARENTHESIS:
    //Function call
    paramListProc= parseFuncParam(tr);
    tkStr=(TokenSymbol *)tk;
    nodeCallFunc =
      new NodeCallFunc(tkStr,paramListProc);
    rtnNode = (NodeCommon*)nodeCallFunc;
    break;
  default:
    abort();
  }
  return rtnNode;
}

NodeCommon *SyntaxParser::parseFuncParam(TokenReader *tr) {
  bool loopb;
  NodeCommon *rtnNode=NULL;
  NodeCommon *curNode=NULL;
  NodeCommon *wkNode=NULL;
  std::string str;
  TokenLtStr *tkLtStr;

  TokenCommon *tk = tr->nextToken();

  loopb=true;
  while(loopb) {
    switch(tk->getType()) {
    case TOKEN_LT_STRING:
      tkLtStr=(TokenLtStr*)tk;

      str = tkLtStr->get();
      wkNode = new NodeFuncParamLtStr(str);
      if (curNode!=NULL) {
	curNode->addNext(wkNode);
      }
      curNode=(NodeCommon *)wkNode;

      if (rtnNode==NULL) {
	rtnNode=curNode;
      }
      break;
    case TOKEN_RIGHT_PARENTHESIS:
      loopb=false;
      break;
    default:
      abort();
    }
    tk = tr->nextToken();
  }
  return rtnNode;
}

