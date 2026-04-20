//
//  main.cpp
//  CS3339 Homework 3 Cache
//
//  Created by Jason Strouphauer on 4/19/26.
//
// Take mem adress ->HIT/MISS ->

// Cache entry = valid bit + tag - struct

//Assume: Cache empty, each block contains one word, mem references are word addresses

//Output in cahce.sim_output
//Format : ADDR: HIT/MISS

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct cacheLine {
    bool bitValid;
    //string tag;
    int tag;
    
    cacheLine() {
        bitValid = false;
        tag = -1; //change?
    }
};

int main(int argc, const char * argv[]) {
    //3 command line args: num_entries, associativity of chache, memory_reference_file
    
    if (argc < 4) {
        cout << "Usage: " << endl;
        cout << "   ./cache num_entries associativity filename" << endl;
        return 0;
      }
    
    int num_entries = stoi(argv[1]);
    int associativity = stoi(argv[2]);
    
    int numSets = num_entries/ associativity;
    
    ifstream input(argv[3]);
    ofstream output("cache_sim_output");
    
    //vector<vector<cacheLine>> cache(numSets, vector<cacheLine>(associativity));
    
    cacheLine** cache = new cacheLine*[numSets];
    
    for (int i= 0; i < numSets; i++) {
        cache[i] = new cacheLine[associativity];
    }
    
    int address;
    
    while (input >> address) {
        int setIndex = address % numSets;
        int tag = address / numSets;
        
        bool hit = false;
        
        for (int i=0; i < associativity; i++) {
            if (cache[setIndex][i].bitValid && cache[setIndex][i].tag == tag) {
                hit = true;
                break;
            }
        }
        if (hit == false) {
            bool placed = false;
            for (int i = 0; i < associativity; i++) {
                if (!cache[setIndex][i].bitValid) {
                    cache[setIndex][i].bitValid = true;
                    cache[setIndex][i].tag = tag;
                    placed = true;
                    break;

                }
            }
            
            if (placed == false) { //change
                cache[setIndex][0].bitValid = true;
                cache[setIndex][0].tag = tag;
            }
        }
        //if (hit == true) {
           // cout
        output << address << " : " << (hit ? "HIT" : "MISS") << endl;
    }
    
    for (int i = 0; i < numSets; i++) {
        delete[] cache[i];
    }
    
    delete[] cache;
    
    return 0;
}
