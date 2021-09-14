#include <iostream>
#include <vector>
#include <map>
#include "brainz/brainz.hpp"

int main() 
{ 
  Brainz::LSTM b;
  Brainz::LSTM ba;

  b.Generate();
  b.Run(3);
  auto j1 = b.Save();
  auto j = b.Mutate();

  std::cout<<j1<<"\n\n"<<std::endl;
  std::cout<<j<<std::endl;
}