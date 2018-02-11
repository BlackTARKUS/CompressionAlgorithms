#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>

using namespace std;

void decompress(string directory);
void readFile(string directory, vector<string> &fileContents);
void writeFile(string uncompressed, string directory);

int main(int argc, char* argv[]) {
  
  // Terminates the program if incorrect arguments are used
  switch(argc) {  
    case 1:
      cout << "Missing target file." << endl;
      exit(1);
      break;
    case 2:
      {

      string directory = argv[1];
      if(directory == "--help") {
        cout << "Usage: UNZIP [FILE]... [OPTION]" << endl;
        cout << "Compress a text file using Huffman encoding." << endl;
        cout << "--help: Provide help on command." << endl;
      }
      // if the target is a zip file, runs the decompress function
      else if( directory.substr(directory.length()-4) == ".zip" ) {
        decompress(directory);
      }
      else {
        cout << "Invalid file type!" << endl;
        exit(1);
      }
      
      }
      break;
    default:
      cout << "Invalid arguements." << endl;
      exit(1);
      break;
  }

  return 0;
}

//  Build a map of N keys where N is the first line of the header of the zip
//  file. Then convert the bottom of the zip file into plain text using
//  the map.
void decompress(string directory) {
  vector <string> fileContents;
  readFile(directory, fileContents);
  map<string, char> data;

  int j = atoi( fileContents.front().c_str() );
  int pos;
  for(int i = 1; i <= j; i++) {
    pos = fileContents.at(i).find(" ");
    string tmp;
    // grab left collumn and convert to character
    char tmp1 = atoi( fileContents.at(i).substr(0, pos).c_str() );
    // grab right collumn and store as string
    string tmp2 = fileContents.at(i).substr(pos+1).c_str();
    data.insert( pair<string, char>(tmp2, tmp1) );
  }
  
  string curr;
  curr = fileContents.at(j+1);
  string uncompressed = "";
  // in the compressed binary line, step through each bit until the substring
  // up to that bit matches a key in the map. Translate that substring into
  // a proper string and then remove that substring from the binary line 
  pos = 1;
  while( pos < curr.length()+1 ) {
    // if the substring is not a key, include the next bit to the substring
    if( data.find(curr.substr(0, pos)) == data.end() ) {
      pos++;
    }
    // if substring is a key, append corresponding char to output string
    // then remove substring from original string and start over.
    else {
      uncompressed += data.find( curr.substr(0, pos) )->second;
      curr = curr.substr(pos);
      pos = 1;
    }
    if(curr.length() == 0) 
      break;
  } 

  writeFile(uncompressed, directory);
}

// reads in the contents of the .zip file and saves it as a vector
void readFile(string directory, vector<string> &fileContents) {
  string line;
  ifstream target ( directory.c_str() );
  // Input all contents of the zip file into a vector as strings
  // that way all data can be easily manipulated
  while(getline(target, line)) {
    fileContents.push_back(line);
  }
  target.close();
}

void writeFile(string uncompressed, string directory) { 
  // Writes to disk
  ofstream outFile ( directory.substr(0, directory.length()-4).c_str() );
  outFile << uncompressed;
  outFile.close();

  // Deletes original .zip file
  remove(directory.c_str());

  cout << "File successfully uncompressed." << endl;  
}
