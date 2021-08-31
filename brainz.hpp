#include <iostream>
#include <vector>
#include "Neuron.hpp"


//make brainz class 
class Brainz{
    //Basic Deep learning class deculation
    public:
    class Basic{
      private:
        std::vector<Neuron *> network;
      public:
        //Generate network and save to self
        void Generate(int Columns, std::vector<int> ColumnMatrix,int type,int numberofinputs);

        //Run network
        std::map<std::string,double> Run(std::vector<double>);

        //Deconstructor
        ~Basic();
   }; 

    //Deconstructor 
    ~Brainz();
};


