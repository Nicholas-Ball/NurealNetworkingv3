#include "Neuron.hpp"
#include "QMath.hpp"
#include <ctime>
#include <chrono>
#include <math.h>
#include "nlohmann/json.hpp"

typedef double (*math) (double);


//activation function array
math Afuncs[4] = {
  QMath::Sigmoid,
  QMath::Tanh,
  QMath::Relu,
  QMath::LRelu,
};


//construct the neuron
Neuron::Neuron()
{
  //make generation seed 
  auto unix_timestamp = std::chrono::seconds(std::time(NULL));

  //set generation seed
  srand(std::chrono::milliseconds(unix_timestamp).count());

  //set random bias -10 to 10 range
  this->Bias = Rand(-10, 20);

};

//compute neuron
void Neuron::Compute(std::vector<double> inputs)
{
  //Get neuron type id
  int type = this->GetType();

  //if this is the fist neuron use input data else use input from previous layer
  if (!this->IsInputNeuron)
  {
    //loop through inputs
    for(int i = 0; i != this->Inputs.size();i++)
    {
      //get output of pervious neuron with neuron number
       std::vector<Neuron*> temp = *this->NetworkPointer;
       double n = temp[i]->GetOutput();

      //multiply it by it's weight and add to output
      this->Output += (this->Weights[i] * n);
    }
  }
  else //if is input neuron, use parm input data
  {
    //loop through inputs
    for(int i = 0; i != inputs.size();i++)
    {
      //get output
      double temp = inputs[i];

      //multiply it by it's weight and add to output
      this->Output += (this->Weights[i] * temp);
    }
    

  }

  //add bias,Compute neuron, and set as output
  this->Output = Afuncs[type](this->Output + this->Bias);

  


  std::cout<<this->Output<<std::endl;

  
};

//Add Neuron to neurons to use in computation
void Neuron::AddInputNeuron(int n)
{
  this->Inputs.push_back(n);
};

//Set neuron is in the first layer in should take an input. Also take the amount of inputs that will be passed.
void Neuron::SetAsFirstNeuron(int num)
{
  for (int i = 0; i != num;i++)
  {
    this->Weights.push_back(Rand(-10,20));
  };
  this->IsInputNeuron = true;
};

//Get type of neuron
int Neuron::GetType()
{ 
  //Nums to neuron types
  // 0 = Sigmoid
  // 1 = Tanh
  // 2 = Relu
  // 3 = Leaky Relu 

  return this->type;
};

//Set type of neuron
void Neuron::SetNeuronType(int n)
{
  this->type = n;
};

//output accesor
double Neuron::GetOutput()
{
  return this->Output;
};

//generate random number
double Neuron::Rand(int min,int max)
{
  return rand() % max + min;
};

//set name of neuron
void Neuron::SetName(std::string name)
{
  this->name = name;
};

//set network pointer
void Neuron::SetPointer(std::vector<Neuron*> net)
{
  this->NetworkPointer = &net;
};

//save neuron
nlohmann::json Neuron::Save()
{
  //make a json object
  nlohmann::json j;

  //save bias
  j["Bias"] = this->Bias;

  //save Weights
  j["Weights"] = this->Weights;

  //save inputs
  j["Inputs"] = this->Inputs;

  //save neuron type
  j["Type"] =  this->type;

  //save if neuron is first neuron
  j["IsFirst"] = this->IsInputNeuron;

  //save neuron name
  j["Name"] = this->name;



  return j;

};

//Load json data to neuron
void Neuron::Load(nlohmann::json j,std::vector<int> inputs)
{
  //load bias
  this->Bias = j["Bias"];

  //load weights
  this->Weights = j["Weights"].get<std::vector<double>>();

  //load inputs
  this->Inputs = inputs;

  //load neuron type
  this->type = j["Type"];

  //load is first bool
  this->IsInputNeuron = j["IsFirst"];

  //load neuron name
  this->name = j["Name"];


};

Neuron::~Neuron(){

}