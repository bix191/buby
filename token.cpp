#include "token.h"

TokenCommon::TokenCommon(TokenType _tokenType) {
  tokenType=_tokenType;
}

TokenType TokenCommon::getType(void) {
  return tokenType;
}



TokenRP::TokenRP() : TokenCommon(TOKEN_RIGHT_PARENTHESIS) {
}

TokenLP::TokenLP() : TokenCommon(TOKEN_LEFT_PARENTHESIS) {
}

TokenCR::TokenCR() : TokenCommon(TOKEN_CR) {
}

TokenSymbol::TokenSymbol(std::string _strdata) : TokenCommon(TOKEN_CDATA) {
  strdata=_strdata;
}

std::string TokenSymbol::getSymbolStr(void) {
  return strdata;
}

TokenLtStr::TokenLtStr(std::string _ltstr) : TokenCommon(TOKEN_LT_STRING) {
  strdata=_ltstr;
}

std::string TokenLtStr::get(void) {
  return strdata;
}
