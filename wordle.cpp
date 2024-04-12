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
void wordhelper(set<string>&, string, const set<string>&);
void fixfloat(set<string>&, string, string);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> list;
    string inn = in;
    string floatt = floating;

    wordhelper(list, inn, dict);

    fixfloat(list, inn, floatt);

    return list;
}

// Define any helper functions here
void wordhelper(set<string>& list, string in, const set<string>& dict){
    for(int i = 0; i < ((int) in.length()); i++){
        if(in[i] == '-'){
            for(int j = 97; j < 123; j++){
                in[i] = j;
                wordhelper(list, in, dict);
            }
            in[i] = '-';
        }
    }
    if((dict.find(in)) == dict.end()){
        return;
    }
    list.insert(in);
}

void fixfloat(set<string>& list, string in, string floating){
    set<string>::iterator i = list.begin();
    set<string>::iterator j = list.begin();
    string inn;
    while(i != list.end()){
        bool flag = true;
        inn = *i;
        for(int k = 0; k < ((int) in.length()); k++){
            if(in[k] == '-'){}
            else if(inn[k] != in[k]){
                j = i;
                ++i;
                list.erase(j);
                flag = false;
                break;
            }
            else{
                inn[k] = '-';
            }
        }
        if(flag){
            for(int k = 0; k < ((int) floating.length()); k++){
                bool match = true;
                for(int l = 0; l < ((int) inn.length()); l++){
                    if(inn[l] == floating[k]){
                        match = false;
                        inn[l] = '-';
                        break;
                    }
                }
                if(match){
                    j = i;
                    ++i;
                    list.erase(j);
                    flag = false;
                    break;
                }
            }
            if(flag){
                ++i;
            }

        }
    }
}