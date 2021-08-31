#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include "nlohmann/json.hpp"


//make brainz class 
class Brainz{
    //Basic Deep learning class deculation
    public:
    class Basic{
      private:
        //network array
        std::vector<Neuron *> network;

        //output names array
        std::vector<std::string> names;
      public:
        //Generate network and save to self
        void Generate(int Columns, std::vector<int> ColumnMatrix,int type,int numberofinputs,std::vector<std::string> OutputNames);

        //Run network
        std::map<std::string,double> Run(std::vector<double> inp);

        //Save network as Json
        nlohmann::json Save();

        //Load network with Json
        void Load(nlohmann::json j);

        //Deconstructor
        ~Basic();
   }; 

    //Deconstructor 
    ~Brainz();
};


