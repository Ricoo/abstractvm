#ifndef CHIPSET_HH__
# define CHIPSET_HH__

#include <map>
#include "CentralProcessingUnit.hh"
#include "InputOutput.hh"
#include "VMException.hh"

//class CentralProcessingUnit;

class Chipset {
private:
  CentralProcessingUnit _cpu;
  InputOutput _io;
  unsigned int _line;
  std::map<std::string, eInstructionType> _tokenMap;
  std::map<std::string, eOperandType> _operandMap;

public:
  Chipset(std::istream *is);
  void parseLines();
  unsigned int getLine() const ;
  void handleError(VMException e) const;
  const InputOutput &getIO() const;

private:
  eInstructionType getToken(const std::string &line) const;
  eOperandType getType(const std::string &line) const;
  std::string *getValue(const std::string &line) const;
  std::string *extract(const std::string &str, const char end, const char begin = '\0') const;
};

#endif
