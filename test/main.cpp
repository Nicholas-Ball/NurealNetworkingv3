#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
//#include "../brainz/brainz.hpp"
#include "../brainz/QMath.hpp"

int main() 
{
  QMath q;
  
  auto out = q.SigmoidPrime(0);

  std::cout<<out<< "\n";

}