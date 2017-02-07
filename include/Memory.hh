#ifndef MEMORY_HH__
# define MEMORY_HH__

#include <list>
#include "IOperand.hh"

class Memory {
public:
  std::list<IOperand *> _list;
};

#endif
