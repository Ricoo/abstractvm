#ifndef CPU_HH__
# define CPU_HH__

#include "IOperand.hh"
#include "Memory.hh"

class Chipset;

enum eInstructionType {
  PUSH, POP,
  DUMP,
  ASSERT,
  ADD, SUB, MUL, DIV, MOD,
  PRINT,
  EXIT
};

class CentralProcessingUnit {
private:
  Memory _memory;
  Chipset *_chipset;

public:
  CentralProcessingUnit(Chipset *chipset) : _chipset(chipset) {}
  ~CentralProcessingUnit();
  void interpreteInstruction(eInstructionType t, IOperand *op = NULL);
  void push(IOperand *op = NULL);
  void pop(IOperand *op = NULL);
  void dump(IOperand *op = NULL);
  void assert(IOperand *op = NULL);
  void add(IOperand *op = NULL);
  void sub(IOperand *op = NULL);
  void mul(IOperand *op = NULL);
  void div(IOperand *op = NULL);
  void mod(IOperand *op = NULL);
  void print(IOperand *op = NULL);
};

typedef void (CentralProcessingUnit::*instrPtr)(IOperand *);

#include "Chipset.hh"

#endif
