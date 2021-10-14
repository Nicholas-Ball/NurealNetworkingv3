#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
#include "../brainz/brainz.hpp"
#include "../brainz/nlohmann/json.hpp"
#include "../brainz/QMath.hpp"

int main() 
{
  std::cout << QMath::POW(-3.3,2)<<std::endl;
  Brainz::Basic b;
  
  nlohmann::json j;

  std::vector<double> inp = {3,2,3}; 
  std::vector<double> out = {1,2}; 

  std::vector<std::vector<double>> outs = {out,out};
  std::vector<std::vector<double>> inps = {inp,inp};

  j["Inputs"] = inps;

  j["Output"] = outs;


  b.Generate(2,{3,2},0,3,{"Test1","Test2"});

  b.BackPropagation(j,1);
}