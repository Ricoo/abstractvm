#ifndef IOPERAND_HH__
# define IOPERAND_HH__

#include <string>

enum eOperandType {
  Int8,
  Int16,
  Int32,
  Float,
  Double
};

class IOperand {
public:
  virtual const std::string &toString() const = 0;
  
  virtual int getPrecision() const = 0;
  virtual eOperandType getType() const = 0;

  virtual IOperand *operator+(const IOperand &) const = 0;
  virtual IOperand *operator-(const IOperand &) const = 0;
  virtual IOperand *operator*(const IOperand &) const = 0;
  virtual IOperand *operator/(const IOperand &) const = 0;
  virtual IOperand *operator%(const IOperand &) const = 0;

  virtual ~IOperand() {}
};

#endif
