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
      }


      //set pointer for neuron
      n->SetPointer(this->network);



      //add neuron to network
      this->network.push_back(n);


    }

  }

};

//Run network
std::map<std::string,double> Brainz::Basic::Run(std::vector<double>)
{
  
};

Brainz::~Brainz(){

};

Brainz::Basic::~Basic(){

};