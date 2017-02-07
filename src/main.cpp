#include <iostream>
#include <fstream>
#include "Chipset.hh"

int main(int ac, char **av)
{
  std::ifstream is;

  if (ac > 1) {
    is.open(av[1]);
    if (is.is_open()) {
      Chipset chipset(&is);
      is.close();
    }
    else
      return (-1); 
  }
  else
    Chipset chipset(&std::cin);
  return (0);
}
