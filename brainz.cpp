#include "brainz.hpp"
#include "QMath.hpp"
#include <math.h>

QMath qm;

template <typename T>

bool contains(std::vector<T> vec, const T & elem)
{
    bool result = false;
    for (auto & x : vec)
    {
        if (x == elem)
        {
            result = true;
            break;
        }
    }
    return result;
}

//merge sort algorithm
std::vector<double> Mergesort(std::vector<double> x)
{
  //if array size is 1 just return self
  if (x.size() <= 1)
  {
    return x;
  }

  //cut in half and get start and stop
  int x1 = (int)(x.size() / 2);
  int x2 = x.size() - x1;

  std::vector<double> a1;

  //make temp array1
  for (int i = 0; i != x1;i++)
  {
    a1.push_back(x[i]);
  }

  std::vector<double> a2;

  //make temp array2
  for (int i = x1; i != x.size();i++)
  {
    a2.push_back(x[i]);
  }

  //mergesorts
  std::vector<double> m1 = Mergesort(a1);
  std::vector<double> m2 = Mergesort(a2);

  //array counters
  int m1x = 0;
  int m2x = 0;


  //merged array
  std::vector<double> merged;

  //loop through arrays and compares
  while (m1x != m1.size() and m2x != m2.size())
  {
    if (m1[m1x] >= m2[m2x])
    {
      merged.push_back(m2[m2x]);
      m2x++;
    }else{
      merged.push_back(m1[m1x]);
      m1x++;
    }
  }

//loop through any remaining vars
while (m1x != m1.size() or m2x != m2.size()){
  //add last var to merged
  if (m1x != m1.size())
  {
    merged.push_back(m1[m1x]);
    m1x++;
  }else{
    merged.push_back(m2[m2x]);
    m2x++;
  }
}

  return merged;

};


//Generate network and save to self
void Brainz::Basic::Generate(int Columns, std::vector<int> ColumnMatrix,int type,int numberofinputs,std::vector<std::string> OutputNames)
{
  //Set outputnames vector array
  this->names = OutputNames;
  //loop through columns and make a neurons
  for (int c = 0;c != Columns;c++)
  {
    //make neurons for this layer
    for (int r = 0;r != ColumnMatrix[c];r++)
    {
      //create new neuron pointer
      Neuron* n = new Neuron;

      //Set neuron types
      n->SetNeuronType(type);

      //if on first column, set as input layer
      if (c == 0)
      {
        n->SetAsFirstNeuron(numberofinputs);
      }else{
        //if not on first column, use previous column as input

        //get current size of network
        int s = this->network.size();

        //loop through previous layer and add to neuron as input
        for (int pl = 0; pl != ColumnMatrix[c-1];pl++ )
        {
          //count back on the network adding them as input
          n->AddInputNeuron(s-pl);
        }

        //if on the last layer, set as output neuron
        if (c == Columns-1)
        {
          n->SetAsOutput();
        }
      }

      //set pointer for neuron
      n->SetPointer(this->network);

      //add neuron to network
      this->network.push_back(n);
    }

  }

};

//Run network
std::map<std::string,double> Brainz::Basic::Run(std::vector<double> inp)
{
 //declare output var
 std::map<std::string,double> Output; 

 //Output counter
 int counter = 0;

 //loop through network and give input vars
 for (int i = 0;i != this->network.size();i++)
 {
   //compute neuron data
   this->network[i]->Compute(inp);

   //if neuron is output neuron, put output into map
   if (this->network[i]->IsOutput())
   {
     //put output into map
     Output[this->names[counter]] = this->network[i]->GetOutput();

     //count up for output name
     counter++;
   };
 }

 //return network output
 return Output;
};

//Save network as Json
nlohmann::json Brainz::Basic::Save()
{
  //make json var to return later
  nlohmann::json j;

  //neuron vector array
  std::vector<nlohmann::json> tj;

  //loop through Neurons and grab save data then add it to vector array
  for (int i = 0; i != this->network.size();i++)
  {
    //grab neuron save data
    auto temp = this->network[i]->Save();
    
    //add neruon save data to vector array
    tj.push_back(temp);
  }

  //convert json vector array into json as a list of neurons
  j["Neurons"] = tj; 

  //save names of outputs
  j["OutputNames"] = this->names;

  //return json
  return j;
}

void Brainz::Basic::Load(nlohmann::json j)
{
  //netowrk var to send to self
  std::vector<Neuron *> net;

  //make json to array of neruon data
  std::vector<nlohmann::json> tj = j["Neurons"];

  //loop through json vector array and load neurons to network
  for(int i = 0;i != tj.size();i++)
  {
    //make new nureon pointer
    Neuron* n = new Neuron;

    //set network pointer
    n->SetPointer(this->network);

    //load data to neuron
    n->Load(tj[i]);

    //load neuron into network
    this->network.push_back(n);

  };

  this->names = j["OutputNames"].get<std::vector<std::string>>();
}


//natrual selection based training
Brainz::Basic Brainz::Basic::NatrualSelection(Brainz::Basic BaseNetwork,int NumCreatures,int NumGenerations,double MutationChance,double SurvivalRate,nlohmann::json InputsWithExpectedOuputs)
{
  //Creatures array
  std::vector<Brainz::Basic> Creatures;

  //initilize creatures
  //-------------------------

  //add initial creature to creature array
  Creatures.push_back(BaseNetwork);

  //get json of base network and use to generate networks
  auto bn = BaseNetwork.Save(); 
  
  //error array
  std::vector<double> Errors;

  //Run training
  //-----------------------------

  //get input and set as a var
  auto inp = InputsWithExpectedOuputs["Inputs"].get<std::vector<std::vector<double>>>();

  //get output and set as a var
  auto out = InputsWithExpectedOuputs["Outputs"].get<std::vector<std::vector<double>>>();

  //loop through Generations
  for(int g = 0; g != NumGenerations; g++)
  {
    //make creatures, run them, calculate error, and then add them to creature array
    for(int c = Creatures.size(); c != NumCreatures;c++)
   {
      //make a new network
      Brainz::Basic temp;

      //load new network with base network
      temp.Load(bn);

      //get size of network
      int s = temp.GetSize();

      //load seed
      srand(this->seed);

      //get random number within the size of the network
     int d = rand() % (s-1);

     //set a new seed
     this->seed = (rand() % 500000000) + d;

     //get neuron from network
     Neuron* n = temp.GetNeuron(d);

      //get amount of weights in neuron
      int s2 = n->GetNumWeights();

     //pick a random weight
     d = rand() % (s2-1);

      //randomize that weight
     n->RandomizeWeight(this->seed, d);

      //loop through inputs
      for (int i = 0; i != inp.size();i++){
        //run creature 
        auto g = temp.Run(inp[i]);
        
        //map iterator
        std::map<std::string, double>::iterator it;

        int r = 0;

        //loop through results and calculate error
        for (it = g.begin(); it != g.end(); it++)
        {
          //calculate error
          //Y = |Expected - result|
          double te = qm.ABS(out[i][r] - g[it->first]);

          //if on first input, make new element to error array
          if (i == 1){
            Errors.push_back(te);
          }else{
            Errors[c] += te;
          }
          r++;
        }
      }
      //add new creature to creature array
     Creatures.push_back(temp);
  }

  //flip errors and creature number and remove duplicates
  std::map<double,int> ErrorsFlipped;

  std::vector<double> ErrorsFlippedDoublesOnly;

  for(int e = 0; e != Errors.size();e++)
  {
    //if error is unique, add it to the array and the map to be compared
    if (ErrorsFlipped.find(Errors[e]) == ErrorsFlipped.end())
    {
      ErrorsFlipped[Errors[e]] = e;
      ErrorsFlippedDoublesOnly.push_back(Errors[e]);
    }
  }

  //sort ErrorsFlippedDoublesOnly
  ErrorsFlippedDoublesOnly = Mergesort(ErrorsFlippedDoublesOnly);

  //temp creature array
  std::vector<Brainz::Basic> tempC;

  //loop through the survived creatures and add them to new creture list as survived
    for(int c = 0; c != ErrorsFlippedDoublesOnly.size() and c <= NumCreatures * SurvivalRate;c++)
    {
      //set survived creature
      tempC[c] = Creatures[ErrorsFlipped[ErrorsFlippedDoublesOnly[c]]];
    }
  }

  //return best network
  return Creatures[0];
};

//returns size of network
int Brainz::Basic::GetSize()
{
  return this->network.size();
}


//get a neuron
Neuron* Brainz::Basic::GetNeuron(int num)
{
  return this->network[num];
};



Brainz::~Brainz(){

};

Brainz::Basic::~Basic(){

};