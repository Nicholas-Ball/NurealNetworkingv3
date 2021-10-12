#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
#include "../brainz/brainz.hpp"
#include "../brainz/nlohmann/json.hpp"

int main() 
{
  Brainz::Basic b;
  
  nlohmann::json j;

  std::vector inp = {3,2,3}; 
  std::vector out = {1,2}; 

  j["Inputs"] = {inp};

  j["Output"] = {out};


  b.Generate(2,{3,2},0,3,{"Test1","Test2"});

  b.BackPropagation(j);
}