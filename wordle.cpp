#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
int unfilledCount(const string&);
void wordhelper(set<string>&, string, string, const set<string>&, unsigned int);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    string floatingg = floating;
    set<string> list;
    string inn = in;

    wordhelper(list, inn, floatingg, dict, 0);
    return list;
}


// Define any helper functions here
int unfilledCount(const string& currstr){
  int count = 0;
  for (int k = 0; k < ((int) currstr.length()); k++){
    if(currstr[k] == '-'){
        count++;
    }
  }
  return count;
}

void wordhelper(set<string>& list, string in, string floating, const set<string>& dict, unsigned int curr)
{
    if(curr == in.size()){
        if((dict.find(in) != dict.end()) && (floating.length() == 0)){ 
            list.insert(in);
        }
        return;
    }
    else if(in[curr] != '-'){
        wordhelper(list, in, floating, dict, curr + 1);
    }
    else{
        for(int j = 0; j < ((int) floating.length()); j++){
            in[curr] = floating[j];
            string substr = (floating.substr(0,j) + floating.substr(j+1));
            wordhelper(list, in, substr, dict, curr + 1);
        }
        if(unfilledCount(in) >= ((int) floating.length())){
            for(char i = 97; i < 123; i++){
                in[curr] = i;
                wordhelper(list, in, floating, dict, curr + 1);
            }
        }
    }
}