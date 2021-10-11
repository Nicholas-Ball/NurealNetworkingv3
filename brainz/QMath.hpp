#include <math.h>
#define MOD 1000000007
#define E 2.71828

class QMath{
  public:

    static inline double POW(double a, double b) {
      union {
        double d;
        int x[2];
      } u = { a };
      u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
      u.x[0] = 0;
      return u.d;
    }

    //Absoulte value math
    static double ABS(double num)
    {
      return fabs(num);  
    }

    //tanh function
    static double Tanh(double num)
    {
      // y = x / 1+|x| 
      return (num/(1.0+ABS(num)));
    }

    //sigmoid function
    static double Sigmoid(double num)
    {
      // sigmoid formula 1/((e^-x)+1)
      return 1/(POW(E,(num*-1.0))+1);
      
    }

    //Leaky Relu Function
    static double LRelu(double num)
    {
      //if num > 0; y = x; else y = 0.01*x
      return ((num < 0) * num * 0.01) + ((num >= 0) * num);
    } 

    //Relu
    static double Relu(double num)
    {
      // if x > 0; y = x; else y = 0
      return (num >= 0) * num;
    } 

    //tanh derivitave
    static double TanhPrime(double inp)
    {
      return (1/POW((ABS(inp)+1),2.0));
    }

    //sigmoid derivitave
    static double SigmoidPrime(double inp)
    {
      return (Sigmoid(inp) * (1 - Sigmoid(inp)));
    }

    //square Square Difference of two numbers
    static SquareDifference(double Predicted, double Expected)
    {
      return POW((Expected-Predicted),2);
    }

};