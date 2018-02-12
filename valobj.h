#ifndef VALOBJ
#define VALOBJ

typedef enum {
  VALTYPE_INTEGER,
  VALTYPE_STRING
} VALTYPE;


class ValObj {
  VALTYPE valType;
 public:
  ValObj(VALTYPE _valtype);
  VALTYPE getValType(void);
};

class ValObjInteger public ValObj {
  int val;
public:
  ValObjInteger(int _val);
  int getVal(void);
  void setVal(int _val);
}

class ValObjString public ValObj {
  int val;
public:
  ValObjString(std::string  _val);
  std::string getVal(void);
  void setVal(std::string _val);
}

#endif
