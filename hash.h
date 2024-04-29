#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#define fox(i,s,e) for(int i=s;i<=e;i++)

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      if(k.length()==0)
        return 0;
      int c[6];
      unsigned long long w[6];
      fox(i,0,5){
        c[i]=std::pow(36,i);
        w[i]=0;
      }
      int wcnt=4;
      std::string str=k;
      fox(i,0,str.length()-1){
        str[i]=std::tolower(str[i]);
      }
      while(str.length()>0){
        int l=str.length()-1;
        fox(i,0,5){
          if(l-i<0){
            str.resize(0);
            break;
          }
          w[wcnt]+=c[i]*letterDigitToNumber(str[l-i]);
        }
        wcnt--;
        if(str.length()!=0)
          str.resize(l-5);
      }
      HASH_INDEX_T h=0;
      fox(i,0,4){
        h+=rValues[i]*w[i];
      }
      return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      if(letter>='a' && letter<='z'){
        return letter-'a';
      }
      else return letter-'0'+26;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
