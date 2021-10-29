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
//deriviative function array
math Dfuncs[4] = {
  QMath::SigmoidPrime,
  QMath::TanhPrime,
  QMath::ReluPrime,
  QMath::LReluPrime,
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
  if (!(this->IsInputNeuron))
  {

    //loop through inputs
    for(int i = 0; i != this->Inputs.size();i++)
    {
      //get output of pervious neuron with neuron number  
      double n = this->NetworkPointer[this->Inputs[i]-1]->GetOutput();

			//add input to input array for backpropgation
			this->InputNum.push_back(n);

      //multiply it by it's weight and add to output
      this->Output += (this->Weights[i] * n);
    }
  }
  else //if is input neuron, use parm input data
  {

    //loop through inputs
    for(int i = 0; i != inputs.size();i++)
    {

      //get input data
      double temp = inputs[i];

			//add input to input array for backpropgation
			this->InputNum.push_back(temp);

      //multiply it by it's weight and add to output
      this->Output += (this->Weights[i] * temp);

    }
    

  }

	this->BeforeAFunc = (this->Output + this->Bias);

  //add bias,Compute neuron, and set as output
  this->Output = Afuncs[type](this->BeforeAFunc);
};

//calulate derivative
double Neuron::GetDerivative()
{
	return Dfuncs[this->type](this->BeforeAFunc);
}

//Add Neuron to neurons to use in computation and make random weights
void Neuron::AddInputNeuron(int n)
{
  //generate random weight and add to weights
  this->Weights.push_back(this->Rand(-10, 20));

  //get size of the weight array for more random
  int s = this->Weights.size();

  //randomize the weight more
  this->RandomizeWeight(this->seed, s-1);

  //add input neuron to inputs array
  this->Inputs.push_back(n);
};

//Set neuron is in the first layer in should take an input. Also take the amount of inputs that will be passed.
void Neuron::SetAsFirstNeuron(int num)
{
  this->IsInputNeuron = true;
  for (int i = 0; i != num;i++)
  {
    this->Weights.push_back(Rand(-10,20));
  };
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
  this->NetworkPointer = net;
};

//set error of neuron
void Neuron::SetError(double err)
{
	this->Error = err;
}

//get input of neuron
std::vector<double> Neuron::GetInput()
{
	return this->InputNum;
}

//Error accesor
double Neuron::GetError()
{
	return this->Error;
}

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

  //load is Output bool
  j["IsOutput"] = this->IsOutputNeuron;

  return j;
};

//Load json data to neuron
void Neuron::Load(nlohmann::json j)
{
  //load bias
  this->Bias = j["Bias"];

  //load weights
  this->Weights = j["Weights"].get<std::vector<double>>();

  //load inputs
  this->Inputs = j["Inputs"].get<std::vector<int>>();

  //load neuron type
  this->type = j["Type"];

  //load is first bool
  this->IsInputNeuron = j["IsFirst"];

  //load neuron name
  this->name = j["Name"];

  //load is Output bool
  this->IsOutputNeuron = j["IsOutput"];

};

//Accecor to check if neuron is an output neuron
bool Neuron::IsOutput()
{
  return this->IsOutputNeuron;
};

//Set neuron as output neuron
void Neuron::SetAsOutput()
{
  this->IsOutputNeuron = true;
}

//Randomize a weight for this neuron
void Neuron::RandomizeWeight(int seed,int WeightNum)
{
  //set a new seed
  srand(seed);

  //check if it should be negitive
  double r = (rand() % 10);

  //add random number to weight
  this->Weights[WeightNum] += ((double) ((rand() % 10) + (float)(rand() % 30) / 100)) * (1 + (double)((r > 5) * -2));
};
//Randomize a weight for this neuron
void Neuron::RandomizeBias(int seed)
{
  //set a new seed
  srand(seed);

  //check if it should be negitive
  double r = (rand() % 10);

  //add random number to bias
  this->Bias += ((double) ((rand() % 10)) + (float)(rand() % 30) / 100) * (1 + (double)((r > 5) * -2));
};

//returns the amount of weights 
int Neuron::GetNumWeights()
{
  return this->Weights.size();
}

Neuron::~Neuron(){

}