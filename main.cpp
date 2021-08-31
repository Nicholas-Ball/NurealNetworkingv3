#include <iostream>
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

  b.Generate(2, {1,3}, 2, 3);

}