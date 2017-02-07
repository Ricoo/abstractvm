#ifndef INPUTOUTPUT_HH__
# define INPUTOUTPUT_HH__

#include <iostream>
#include <vector>
#include <string>

class InputOutput {
private:
  std::istream *_is;
  std::vector<std::string> _program;

public:
  InputOutput(std::istream *is) {_is = is;}
  std::string getLine(unsigned int line) const;
  void loadProgram();
  void print(const std::string &str) const;
  void printchar(const std::string &str) const;
  void printError(const std::string &str) const;
};

#endif
