#include <sstream>
#include "VMException.hh"
#include "CentralProcessingUnit.hh"

CentralProcessingUnit::~CentralProcessingUnit() {
  IOperand *op;

  while (this->_memory._list.size() > 0) {
    op = this->_memory._list.front();
    this->_memory._list.pop_front();
    delete op;
  }
}

void CentralProcessingUnit::interpreteInstruction(eInstructionType instr, IOperand *op) {
  instrPtr p[] = {&CentralProcessingUnit::push,
		  &CentralProcessingUnit::pop,
		  &CentralProcessingUnit::dump,
		  &CentralProcessingUnit::assert,
		  &CentralProcessingUnit::add,
		  &CentralProcessingUnit::sub,
		  &CentralProcessingUnit::mul,
		  &CentralProcessingUnit::div,
		  &CentralProcessingUnit::mod,
		  &CentralProcessingUnit::print};

  (this->*p[instr])(op);
}

void CentralProcessingUnit::push(IOperand *op) {
  this->_memory._list.push_front(op);
}

void CentralProcessingUnit::pop(IOperand *op) {
  if (this->_memory._list.size() < 1)
    throw EmptyStackException("pop");
  op = this->_memory._list.front();
  this->_memory._list.pop_front();
  delete op;
}

void CentralProcessingUnit::dump(IOperand *op) {
  (void) op;
  if (this->_memory._list.size() < 1)
    throw EmptyStackException("dump");
  for (std::list<IOperand *>::iterator it = this->_memory._list.begin();
       it != this->_memory._list.end(); ++it) {
    this->_chipset->getIO().print((*it)->toString());
  }
}

void CentralProcessingUnit::assert(IOperand *op) {
  IOperand *top;

  if (this->_memory._list.size() < 1)
    throw EmptyStackException("assert");
  top = this->_memory._list.front();
  if (op->toString() != top->toString() ||
      op->getType() != top->getType() ||
      op->getPrecision() != top->getPrecision())
    throw AssertException(0);
  delete op;
}

void CentralProcessingUnit::add(IOperand *op) {
  IOperand *op1;
  IOperand *op2;

  (void) op;
  if (this->_memory._list.size() < 2)
    throw InvalidOperationException(0);
  op1 = this->_memory._list.front();
  this->_memory._list.pop_front();
  op2 = this->_memory._list.front(); 
  this->_memory._list.pop_front();
  this->push(*op1 + *op2);
  delete op1;
  delete op2;
}

void CentralProcessingUnit::sub(IOperand *op) {
  IOperand *op1;
  IOperand *op2;

  (void) op;
  if (this->_memory._list.size() < 2)
    throw InvalidOperationException(0);
  op1 = this->_memory._list.front();
  this->_memory._list.pop_front();
  op2 = this->_memory._list.front(); 
  this->_memory._list.pop_front();
  this->push(*op1 - *op2);
  delete op1;
  delete op2;
}

void CentralProcessingUnit::mul(IOperand *op) {
  IOperand *op1;
  IOperand *op2;

  (void) op;
  if (this->_memory._list.size() < 2)
    throw InvalidOperationException(0);
  op1 = this->_memory._list.front();
  this->_memory._list.pop_front();
  op2 = this->_memory._list.front(); 
  this->_memory._list.pop_front();
  this->push(*op1 * *op2);
  delete op1;
  delete op2;
}

void CentralProcessingUnit::div(IOperand *op) {
  IOperand *op1;
  IOperand *op2;

  (void) op;
  if (this->_memory._list.size() < 2)
    throw InvalidOperationException(0);
  op1 = this->_memory._list.front();
  this->_memory._list.pop_front();
  op2 = this->_memory._list.front(); 
  this->_memory._list.pop_front();
  this->push(*op1 / *op2);
  delete op1;
  delete op2;
}

void CentralProcessingUnit::mod(IOperand *op) {
  IOperand *op1;
  IOperand *op2;

  (void) op;
  if (this->_memory._list.size() < 2)
    throw InvalidOperationException(0);
  op1 = this->_memory._list.front();
  this->_memory._list.pop_front();
  op2 = this->_memory._list.front(); 
  this->_memory._list.pop_front();
  this->push(*op1 % *op2);
  delete op1;
  delete op2;
}

void CentralProcessingUnit::print(IOperand *op) {
  (void) op;
  if (this->_memory._list.size() < 1)
    throw EmptyStackException("print");
  if (this->_memory._list.front()->getType() != Int8)
    throw AssertException(0);
  std::stringstream stream(this->_memory._list.front()->toString());
  std::string str;
  short int val; 
  char cpy;

  stream >> val;
  cpy = val;
  str += cpy;
  this->_chipset->getIO().printchar(str);
}
