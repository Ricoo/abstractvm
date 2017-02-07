#include "OperandCreator.hh"
#include "IOperand.hh"

IOperand *OperandCreator::createOperand(eOperandType type, const std::string &value) {
  typePtr p[] = {&OperandCreator::createInt8,
		 &OperandCreator::createInt16,
		 &OperandCreator::createInt32,
		 &OperandCreator::createFloat,
		 &OperandCreator::createDouble};

  return ((this->*p[type])(value));
}
