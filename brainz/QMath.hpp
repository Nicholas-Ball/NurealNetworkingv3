#include <math.h>
#define MOD 1000000007
#define E 2.71828



class QMath{
  private:
    //exponent if the number is negitive (AKA root of a number)
    static inline double nPOW(double a, double b)
    {
      return  a / POW(a,(b*-1)+1);
    }
  public:

    //exponent
    static inline double POW(double a, double b) {
      if(b < 0) return nPOW(a,b);
      // calculate approximation with fraction of the exponent
      int e = (int) b;
      union {
      double d;
      int x[2];
     } u = { a };
      u.x[1] = (int)((b - e) * (u.x[1] - 1072632447) + 1072632447);
      u.x[0] = 0;

      // exponentiation by squaring with the exponent's integer part
      // double r = u.d makes everything much slower, not sure why
      double r = 1.0;
      while (e) {
        if (e & 1) {
          r *= a;
        }
        a *= a;
        e >>= 1;
      }

      return r * u.d;
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

    //Leaky Relu derivitave
    static double LReluPrime(double num)
    {
      //if x <= 0; return 0.01; 
      double out = 0.01;
      return out + ((num > 0.0)*0.99);
    } 

    //Relu derivitave
    static double ReluPrime(double num)
    {
      // if x > 0; return 1;
      return (num > 0);
    } 

    //tanh derivitave
    static double TanhPrime(double inp)
    {
      return 1/(POW(ABS(inp)+1,2));
    }

    //sigmoid derivitave
    static double SigmoidPrime(double inp)
    {
      return (Sigmoid(inp) * (1 - Sigmoid(inp)));
    }

    //Square Difference of two numbers
    static double SquareDifference(double Predicted, double Expected)
    {
      return 0.5 * POW((Predicted-Expected),2);
    }
    
    //Square Difference of two numbers derivitave
    static double SquareDifferencePrime(double Predicted, double Expected)
    {
      return (Predicted-Expected);
    }

};