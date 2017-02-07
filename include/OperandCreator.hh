#ifndef OPERANDCREATOR_HH__
# define OPERANDCREATOR_HH__

#include "IOperand.hh"
#include "Type.hh"

class OperandCreator {
public:
  IOperand *createOperand(eOperandType, const std::string &);

private:
  IOperand *createInt8(const std::string &value) {return new Type<char>(value, Int8);}
  IOperand *createInt16(const std::string &value) {return new Type<short int>(value, Int16);}
  IOperand *createInt32(const std::string &value) {return new Type<int>(value, Int32);}
  IOperand *createFloat(const std::string &value) {return new Type<float>(value, Float);}
  IOperand *createDouble(const std::string &value) {return new Type<double>(value, Double);}
};

typedef IOperand *(OperandCreator::*typePtr)(const std::string &);

#endif
