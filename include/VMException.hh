#ifndef VMEXCEPTION_HH__
# define VMEXCEPTION_HH__

#include <exception>
#include <string>

class VMException : public std::exception {
public:
  VMException(unsigned int line = 1, const std::string &message = "") :
    _message(message), _line(line) {}
  virtual ~VMException() throw() {}
  unsigned int getLine() const {return this->_line;}
  void setLine(unsigned int line) {this->_line = line;}
  const char *what() const throw() {return _message.c_str();}

private:
  std::string _message;
  unsigned int _line;
};

class SyntaxErrorException : public VMException {
public:
  SyntaxErrorException(unsigned int line) :
    VMException(line, "Syntax Error") {}
};

class UnknownInstructionException : public VMException {
public:
  UnknownInstructionException(unsigned int line, const std::string &instruction) :
    VMException(line, "Error : unknown instruction : " + instruction) {}
};

class UnknownTypeException : public VMException {
public:
  UnknownTypeException(unsigned int line, const std::string &type) :
    VMException(line, "Error : unknown type : " + type) {}
};

class ValueOverflowException : public VMException {
public:
  ValueOverflowException(unsigned int line) :
    VMException(line, "Error : value overflow") {}
};

class EmptyStackException : public VMException {
public:
  EmptyStackException(std::string error) :
    VMException(0, "Error : " + error + " on empty stack") {}
};

class FloatingPointException : public VMException {
public:
  FloatingPointException(unsigned int line, const std::string &operation) :
    VMException(line, "Error : invalid " + operation + " by 0") {}
};

class MissingExitException : public VMException {
public:
  MissingExitException(unsigned int line) :
    VMException(line, "Error : missing exit instruction") {}
};

class AssertException : public VMException {
public:
  AssertException(unsigned int line) :
    VMException(line, "Assert failed") {}
};

class InvalidOperationException : public VMException {
public:
  InvalidOperationException(unsigned int line) :
    VMException(line, "Error : stack contains less than two values") {}
};

#endif
