// By Cody Lee - CSC 245
// An example of Huffman Encoding written in C++

#include "huffman.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

void compress(string directory, HuffmanTree &tree);
void writeFile(string directory, HuffmanTree tree, string encodedString);

int main(int argc, char* argv[]) {
  HuffmanTree tree;

  // Terminates the program if incorrect arguments are used
  if(argc == 1) {
    cout << "Missing target file." << endl;
    exit(1);
  }
  else if(argc == 2) {
    string tmp = argv[1];
    if(tmp == "--help") {
      cout << "Usage: ZIP [FILE]... [OPTION]" << endl;
      cout << "Compress a text file using Huffman encoding." << endl;
      cout << "--t: Display the Huffman encoding table." << endl;
      cout << "--help: Provide help on command." << endl;
    }
    else {
      // Encodes the file, then writes to a file
      string directory = argv[1];
      compress(directory, tree);
    }
  }
  else if(argc == 3) {
    string tmp = argv[2];
    if(tmp == "--t") {
      // Encodes the file, then prints encoding table
      string directory = argv[1];
      compress(directory, tree);
      tree.PrintTable();
    }
    else {
      cout << "Invalid arguements!" << endl;
      exit(1);
    }
  }
  else {
    cout << "Invalid arguements!" << endl;
    exit(1);
  }
  
  return 0;
}

// reads in the contents of the .zip file and saves it as a vector
void compress(string directory, HuffmanTree &tree) {
  ostringstream s;
  int sourceSize = 0;
  char curr;
  int characters[256];
  for(char ch = char(0); ch <= char(126); ch++)
    characters[ch] = 0;
  ifstream target ( directory.c_str() );
  // Counts how many times each character occurs to find the weight
  target.get(curr);
  while( target ) {
    s << curr;
    characters[curr] += 1;  
    sourceSize += 1;
    target.get(curr);
  }
  target.close();
  string ref(s.str());

  // Adds each char and their weight to the Huffman Tree
  for(char ch = char(0); ch <= char(126); ch++) {
    if(characters[ch] != 0)
      tree.insert(ch, characters[ch]);
  }
  tree.build();

  ostringstream d;
  for(int i = 0; i < ref.size(); i++) {
    d << tree.GetCode(ref[i]);
  }
  string encodedString(d.str());

  writeFile(directory, tree, encodedString);

  // Prints out the compression rate of the file in zip form
  double ratio = ( 1.0 - ( ( encodedString.size() + 0.0 ) /
        ( (sourceSize * 8) + 0.0 ) ) ) * 100 ;
  cout << "File sucessfully compressed to " << encodedString.size()
    << " bits (" << ratio << "\% Less)" << endl;
}

void writeFile(string directory, HuffmanTree tree,string encodedString) { 
  // removes the uncompressed file
  remove(directory.c_str());

  // writes the encoded file to a zip file
  directory += ".zip";
  ofstream outFile ( directory.c_str() );
  if( outFile.is_open() ) {
    outFile << tree.getHeader();
    outFile << encodedString;
  }
  outFile.close();
}
