#include <iostream>
#include <climits>
#include <sstream>
#include "huffman.h"

using namespace std;

HuffmanTree:: HuffmanTree()
: numChars(0), built(false) {}

int characters[256];

void HuffmanTree:: insert(char ch, int weight) {
  HNode newNode = {ch, weight, -1, -1}; 
  built = false;
  nodes.push_back(newNode);
  numChars++;

}

bool HuffmanTree:: inTree(char ch) {
  if( lookUp(ch) == -1 ) { return false; }
  else
    return true;
}

int HuffmanTree:: numNodes() {
  return nodes.size();
}

// PUBLIC
int HuffmanTree:: GetFrequency(char ch) {
  if( inTree(ch) ) { return GetFrequency(lookUp(ch)); }
  else
    return -1;
}

// PRIVATE
int HuffmanTree:: GetFrequency(int i) {
  return (nodes[i]).weight; 
}

int HuffmanTree:: lookUp(char ch) {
  for(int i = 0; i < nodes.size(); i++) {
    if( nodes[i].ch == ch ) { return i; }
  }
  return -1;
}

// PUBLIC
string HuffmanTree:: GetCode(char ch) {
  return GetCode(lookUp(ch));
}

// PRIVATE
string HuffmanTree:: GetCode(int i) {
  if( nodes[i].parent == 0 ) return ""; }
  else
    return ( GetCode(nodes[i].parent) + (char) (nodes[i].childType+'0') );
}

// returns the header information for the file
string HuffmanTree:: getHeader() {
  ostringstream s;
  s << numChars << endl;
  for(int i = 0; i < nodes.size(); i++) {
    if( nodes[i].ch != '\0' )
      s << int(nodes[i].ch) << " " << GetCode(nodes[i].ch) << endl;
  } 
  string outString(s.str());
  return outString;
}

void HuffmanTree:: PrintTable() {
  int t = 1;
  cout << "\t\t-++++- ENCODING TABLE -++++-" << endl;
  cout << "\tIndex\tChar\tWeight\tParent\tChildType" << endl;
  for( int i = 0; i < nodes.size(); i++ ) {
    cout << "\t" << i << "\t";

    if(nodes[i].ch == ' ') { cout << "sp"; }
    else if( nodes[i].ch == '\n' ) { cout << "nl"; }
    else if( nodes[i].ch == '\0' ) { cout << "T" << t; t++; }
    else
      cout << nodes[i].ch;
  
    cout << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t";
    if( nodes[i].childType != -1 ) { cout << nodes[i].childType << endl; }
    else
      cout << "N/A" << endl;
  }

}

void HuffmanTree:: build() {
  // Makes a Huffman Tree out of the HNodes. Assigns each child node to parent
  // and combines nodes of lowest frequency until only a single node remains

  for(int i = 0; i < (numChars-1); i++) {
    int leastweight1index;
    int leastweight1 = INT_MAX;
    int leastweight2index;
    int leastweight2 = INT_MAX;

    for(int j = 0; j < nodes.size(); j++) {
      if(nodes[j].parent == -1) {
        if(nodes[j].weight < leastweight1) {
          leastweight1 = nodes[j].weight;
          leastweight1index = j; 
        } 
      }
    }

    for(int k = 0; k < nodes.size(); k++) {
      if( nodes[k].parent == -1 ) { 
        if( (nodes[k].weight < leastweight2) && (k!=leastweight1index) ) {
          leastweight2 = nodes[k].weight;
          leastweight2index = k;
        }
      }
    }

    nodes[leastweight1index].parent = nodes.size();
    nodes[leastweight2index].parent = nodes.size(); 

    nodes[leastweight1index].childType = 0; 
    nodes[leastweight2index].childType = 1; 

    HNode newNode = {'\0', leastweight1 + leastweight2, -1, -1}; 
    nodes.push_back(newNode); 
  }
  nodes[nodes.size()-1].parent = 0;
  built = true;
}
