#include <iostream>
#include <vector>
#include <map>
#include "brainz.hpp"

int main() 
{ 
  Brainz::LSTM b;
  Brainz::LSTM ba;

  b.Generate();
  b.Run(3);
  auto base = b.Save();


  ba.Load(base);

  std::cout<<(ba.Save() == base)<<std::endl;
}