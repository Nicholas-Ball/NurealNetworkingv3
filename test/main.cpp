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
  Brainz::Basic b;
  
  nlohmann::json j;
  

  std::vector<double> inp = {3,2,3}; 
  std::vector<double> out = {1,2}; 

  std::vector<std::vector<double>> outs = {out,out};
  std::vector<std::vector<double>> inps = {inp,inp};

  j["Inputs"] = inps;

  j["Outputs"] = outs;
  b.Generate(2,{3,2},2,3,{"Test1","Test2"});
  std::cout<<"test1"<<std::endl;
  b = b.NatrualSelection(b,100,10000,0.5,0.5,j);
  auto g = b.Run(inp);
  std::cout<<g["Test1"]<<std::endl;
  std::cout<<g["Test2"]<<std::endl;

}