#include <iostream>
#include <string>
#include "InputOutput.hh"
#include "VMException.hh"

void InputOutput::loadProgram() {
  unsigned int lineNb;
  bool isExit = false;
  std::string line;

  lineNb = 0;
  while (std::getline(*(this->_is), line)) {
    if (line.substr(0, 2) == ";;") {
      this->_program.push_back(";;");
      break ;
    }
    if (line.substr(0,4).find("exit") != std::string::npos)
      isExit = true;
    this->_program.push_back(line);
    ++lineNb;
  }
  if (!isExit)
    throw MissingExitException(this->_program.size());
  this->_program.push_back(";;");
  return ;
}

std::string InputOutput::getLine(unsigned int line) const {
  return ((this->_program[line - 1]));
}

void InputOutput::print(const std::string &msg) const {
  std::cout << msg << std::endl;
}

void InputOutput::printchar(const std::string &msg) const {
  std::cout << msg;
}

void InputOutput::printError(const std::string &msg) const {
  std::cerr << msg << std::endl;
}
