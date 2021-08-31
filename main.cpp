#include <iostream>
#include <vector>
#include <map>
#include "brainz.hpp"

int main() 
{
  /*
  //declare neuron var
  Neuron n;

  //set as input neuron
  n.SetAsFirstNeuron(3);

  //set type of activation function
  n.SetNeuronType(3);

  //dummy input values
  std::vector<double> inp = {3,-5,0};

  //neuron compute data
  n.Compute(inp);

  //save neuron
  auto j = n.Save();

  //create new neuron
  Neuron nn;

  //load neuron data
  nn.Load(j,{});

  //run new neuron
  nn.Compute(inp);

  //show json of the neurons
  std::cout<<j<<std::endl;*/
  
  Brainz::Basic b;
  Brainz::Basic ba;

  b.Generate(2, {2,3}, 2, 3,{"output1","output2","output3"});

  auto j = b.Save();


  auto m = b.Run({3,6,-2});

  ba.Load(j);

  auto ma = ba.Run({3,6,-2});

  std::cout<<ma["output1"] <<std::endl;
  std::cout<<m["output1"]<<std::endl;

}