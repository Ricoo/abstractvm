#include <string>
#include <cmath>
#include "IOperand.hh"
#include "OperandCreator.hh"
#include "VMException.hh"
#include "Type.hh"

template <typename T>
IOperand *Type<T>::operator+(const IOperand &op) const {
  OperandCreator creator;

  if (this->getType() >= op.getType()) {
    return (creator.createOperand(this->getType(), str<long double>(val<long double>(*this) + val<long double>(op))));
  }
  return (creator.createOperand(op.getType(), str<long double>(val<long double>(*this) + val<long double>(op))));
}

template <typename T>
IOperand *Type<T>::operator-(const IOperand &op) const {
  OperandCreator creator;

  if (this->getType() >= op.getType())
    return (creator.createOperand(this->getType(), str<long double>(val<long double>(*this) - val<long double>(op))));
  return (creator.createOperand(op.getType(), str<long double>(val<long double>(*this) - val<long double>(op))));
}

template <typename T>
IOperand *Type<T>::operator*(const IOperand &op) const {
  OperandCreator creator;

  if (this->getType() >= op.getType())
    return (creator.createOperand(this->getType(), str<long double>(val<long double>(*this) *
							       val<long double>(op))));
  return (creator.createOperand(op.getType(), str<long double>(val<long double>(*this) *
							  val<long double>(op))));
}

template <typename T>
IOperand *Type<T>::operator/(const IOperand &op) const {
  OperandCreator creator;

  if (val<long double>(op) == 0)
    throw FloatingPointException(0, "division");
  if (this->getType() >= op.getType())
    return (creator.createOperand(this->getType(), str<long double>(val<long double>(*this) /
							       val<long double>(op))));
  return (creator.createOperand(op.getType(), str<long double>(val<long double>(*this) /
							  val<long double>(op))));
}

template <typename T>
IOperand *Type<T>::operator%(const IOperand &op) const {
  OperandCreator creator;
  double val1;
  double val2;

  val1 = val<long double>(*this);
  val2 = val<long double>(op);
  while (ABS(val1) > ABS(val2)) {
    val1 -= val2;
  }
  if (val<long double>(op) == 0)
    throw FloatingPointException(0, "modulo");
  if (this->getType() >= op.getType())
    return (creator.createOperand(this->getType(), str<long double>(val1)));
  return (creator.createOperand(op.getType(), str<long double>(val1)));
}

template<>
char val<char>(const std::string &op) {
  short int value;
  std::stringstream stream(op);

  stream >> value;
  if (stream.fail() || value > 127 || value < -128) {
    throw ValueOverflowException(0);
  }
  return value;
}

template<>
std::string str<char>(const char val)
{
  short int cpy = val;
  std::stringstream stream("");

  stream << cpy;
  return stream.str();
}
