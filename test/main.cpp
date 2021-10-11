#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
#include "../brainz/brainz.hpp"

int main() 
{
  Brainz::Basic b;
  
  b.Generate(2,{3,2},0,3,{"Test1","Test2"});

  auto out = b.Run({3,4,1});

  std::cout<<out["Test1"]<<std::endl;

  

}