#ifndef TOKEN
#define TOKEN

#include <string>
#include "tokenlabel.h"

class TokenCommon {
  TokenType tokenType;
 public:
  TokenCommon(TokenType _tokenType);
  TokenType getType(void);
};

class TokenLP : public TokenCommon {
 public:
   TokenLP();
};

class TokenRP : public TokenCommon {
 public:
   TokenRP();
};

class TokenCR : public TokenCommon {
 public:
   TokenCR();
};

class TokenSymbol : public TokenCommon {
  std::string strdata;
 public:
   TokenSymbol(std::string strdata);
   std::string getSymbolStr(void);
};


class TokenLtStr : public TokenCommon {
  std::string strdata;
 public:
  TokenLtStr(std::string strdata);
  std::string get(void);
};

#endif
