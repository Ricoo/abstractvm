#ifndef TYPE_HH__
# define TYPE_HH__

#include <string>
#include <sstream>
#include "VMException.hh"
#include "IOperand.hh"

#define ABS(a) (a > 0 ? a : -a)

template <typename T>
T val(const IOperand &op) {
  T	value;
  std::stringstream stream(op.toString());

  stream >> value;
  if (stream.fail()) {
    throw ValueOverflowException(0);
  }
  return value;
}

template <typename T>
T val(const std::string &op) {
  T	value;
  std::stringstream stream(op);
  
  stream >> value;
  if (stream.fail()) {
    throw ValueOverflowException(0);
  }
  return value;
}

template <typename T>
std::string str(T val) {
  std::stringstream stream("");

  stream << val;
  return stream.str();
}

template <>
char val<char>(const std::string &op);

template<>
std::string str<char>(char val);

template <typename T>
class Type : public IOperand {
private:
  std::string _str;
  eOperandType _type;

public:
  Type(const std::string &value, eOperandType op = Int8) : _str(str<T>(val<T>(value))), _type(op) {}
  ~Type() {}
  const std::string &toString() const {return this->_str;}

  int getPrecision() const {return sizeof(T) + this->_type;}
  eOperandType getType() const {return this->_type;}

  virtual IOperand *operator+(const IOperand &) const;
  virtual IOperand *operator-(const IOperand &) const;
  virtual IOperand *operator*(const IOperand &) const;
  virtual IOperand *operator/(const IOperand &) const;
  virtual IOperand *operator%(const IOperand &) const;
};

template class Type<char>;
template class Type<short int>;
template class Type<int>;
template class Type<float>;
template class Type<double>;

#endif
