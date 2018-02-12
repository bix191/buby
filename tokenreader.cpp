#include <fstream>
#include "tokenreader.h"


TokenReader::TokenReader(std::string _filename) {
  filename=_filename;
  chdata=0;
}


void TokenReader::open() {
  ifs = new std::fstream(filename.c_str(),std::ifstream::in);
}
  
TokenCommon *TokenReader::nextToken() {
  std::string  workstr;
  bool loopb;
  TokenCommon *retToken;

  workstr.reserve(8192);

  loopb=true;

  if (chdata==0) {
    chdata = ifs->get();
  } else {
    switch(chdata){
    case '(':
      retToken = new TokenLP();
      chdata = ifs->get();
      return retToken;
      break;
    case ')':
      retToken = new TokenRP();
      chdata = ifs->get();
      return retToken;
      break;
    case '\n':
      retToken = new TokenCR();
      chdata = ifs->get();
      return retToken;
    case EOF:
      return NULL;
      break;
    }
  }


  while(loopb) {
    if (isalnum(chdata)) {
      workstr.push_back(chdata);
    } else if (chdata=='(') {
      retToken = new TokenSymbol(workstr);
      loopb=false;
      continue;
    } else if (chdata==')') {
      retToken = new TokenRP();
      loopb=false;
      continue;
    } else if (chdata=='\"') {
      chdata=ifs->get();

      while(chdata!='\"' && chdata!=EOF) {
	if (chdata=='\\') {
	  chdata=ifs->get();
	  if (chdata=='n') {
	    chdata='\n';
	  }
	}
	workstr.push_back(chdata);
	chdata=ifs->get();
      }
      chdata=ifs->get();
      retToken = new TokenLtStr(workstr);
      loopb=false;
      continue;
    } else if (chdata=='\n') {
      chdata=ifs->get();
      retToken = new TokenCR();
      loopb=false;
      continue;
    }
    chdata=ifs->get();
  }
  return retToken;
}
