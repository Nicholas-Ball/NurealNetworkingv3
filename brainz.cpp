#include "brainz.hpp"



//Generate network and save to self
void Brainz::Basic::Generate(int Columns, std::vector<int> ColumnMatrix,int type,int numberofinputs)
{
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

 //loop through network and give input vars
 for (int i = 0;i != this->network.size();i++)
 {
   //compute neuron data
   this->network[i]->Compute(inp);

   //if neuron is output neuron, put output into map
   if (this->network[i]->IsOutput())
   {
     Output["Output"] = this->network[i]->GetOutput();
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

  //return json
  return j;
}


Brainz::~Brainz(){

};

Brainz::Basic::~Basic(){

};