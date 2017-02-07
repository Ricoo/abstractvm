#include <iostream>
#include <map>
#include <string>
#include "InputOutput.hh"
#include "CentralProcessingUnit.hh"
#include "IOperand.hh"
#include "OperandCreator.hh"
#include "VMException.hh"

Chipset::Chipset(std::istream *is) : _cpu(this), _io(is), _line(1) {
  this->_tokenMap["push"] = PUSH;
  this->_tokenMap["pop"] = POP;
  this->_tokenMap["dump"] = DUMP;
  this->_tokenMap["assert"] = ASSERT;
  this->_tokenMap["add"] = ADD;
  this->_tokenMap["sub"] = SUB;
  this->_tokenMap["mul"] = MUL;
  this->_tokenMap["div"] = DIV;
  this->_tokenMap["mod"] = MOD;
  this->_tokenMap["print"] = PRINT;
  this->_tokenMap["exit"] = EXIT;
  this->_operandMap["int8"] = Int8;
  this->_operandMap["int16"] = Int16;
  this->_operandMap["int32"] = Int32;
  this->_operandMap["float"] = Float;
  this->_operandMap["double"] = Double;
  this->parseLines();
}

void Chipset::parseLines() {
  OperandCreator creator;
  std::string line;
  eInstructionType inst;
  eOperandType op;
  std::string *value;

  try {
    this->_io.loadProgram();
  }
  catch (VMException e) {
    handleError(e);
    return ;
  }
  while ((line = (this->_io.getLine(this->_line))) != ";;") {
    if (line != "" and line.substr(0, 1) != ";")
      try {
	inst = this->getToken(line);
	if (inst == EXIT)
	  return ;
	if (inst == PUSH || inst == ASSERT) {
	  op = this->getType(line);
	  value = this->getValue(line);
	  this->_cpu.interpreteInstruction(inst, creator.createOperand(op, *value));
	  delete value;
	}
	else
	  this->_cpu.interpreteInstruction(inst, NULL);
      }
      catch (VMException e) {
	e.setLine(this->_line);
	handleError(e);
	this->_io.print("\"" + this->_io.getLine(this->_line) + "\"");
	return ;
      }
    this->_line += 1;
  }
}

void Chipset::handleError(VMException e) const {
  this->_io.printError("at line " + str<int>(e.getLine()) + " : " + e.what());
}

const InputOutput &Chipset::getIO() const {
  return (this->_io);
}

unsigned int Chipset::getLine() const {
  return (this->_line);
}

eInstructionType Chipset::getToken(const std::string &line) const {
  eInstructionType type;
  std::string *token;

  try {
    token = extract(line, ' ');
  }
  catch (VMException e) {
    token = extract(line, '\0');
  }
  if (this->_tokenMap.find(*token) == this->_tokenMap.end())
    throw UnknownInstructionException(this->_line, *token);
  type = this->_tokenMap.find(*token)->second;
  delete token;
  return type;
}

eOperandType Chipset::getType(const std::string &line) const {
  eOperandType op;
  std::string *type;

  type = extract(line, '(', ' ');
  if (this->_operandMap.find(*type) == this->_operandMap.end())
    throw UnknownTypeException(this->_line, *type);
  op = this->_operandMap.find(*type)->second;
  delete type;
  return op;
}

std::string *Chipset::getValue(const std::string &line) const {
  std::string *value;

  try {
    value = extract(line, ')', '(');
  }
  catch (VMException e) {
    throw;
  }
  return value;
}

std::string *Chipset::extract(const std::string &str, const char end, const char begin) const {
  std::string *substr = new std::string("");
  unsigned int i = 0;
  
  while (begin != '\0' && str[i] != begin)
    ++i;
  if (str[i] == begin)
    ++i;
  while (str[i] && str[i] != end) {
    *substr += str[i];
    ++i;
  }
  if (end != '\0' && !(str[i])) {
    delete substr;
    throw SyntaxErrorException(this->_line);
  }
  return (substr);
}
