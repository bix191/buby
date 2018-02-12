

#include "valobj.h"

ValObj::ValObj(VALTYPE _valType) {
  valType=_valType;
}

VALTYPE ValObj::getValType() {
  return valType;
}


ValObjInteger::ValObjInteger(int _val):ValObj(VALTYPE_INTEGER) {
  val=_val;
}

void ValObjInteger::setVal(int _val) {
  val=_val;
}

int ValObjInter::getVal() {
  return val;
}

ValObjString::ValObjString(std::string _val):ValObj(VALTYPE_STRING) {
  val=_val;
}

void ValObjString::setVal(std::string _val) {
  val=_val;
}

std::string ValObjInter::getVal() {
  return val;
}
