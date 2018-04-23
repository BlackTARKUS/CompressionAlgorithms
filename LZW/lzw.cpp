#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;
 
// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
template <typename Iterator>
Iterator compress(const string &uncompressed, Iterator result) {
  // Build the dictionary.
  int dictSize = 256;
  map<string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[string(1, i)] = i;
 
  string w;
  for (string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary.
      dictionary[wc] = dictSize++;
      w = string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}
 
// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
string decompress(Iterator begin, Iterator end) {
  // Build the dictionary.
  int dictSize = 256;
  map<int,string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = string(1, i);
 
  string w(1, *begin++);
  string result = w;
  string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";
 
    result += entry;
 
    // Add w+entry[0] to the dictionary.
    dictionary[dictSize++] = w + entry[0];
 
    w = entry;
  }
  return result;
}
 
int main(int argc, char* argv[]) {
  if(argc == 1) {
    cout << "Missing command arguement. Specify Compress or Uncompress." << endl;
    exit(1);
  }
  else if(argc == 2) {
    string tmp = argv[1];

    // Simple error handling
    if(tmp == "--help") {
      cout << "Usage: \"compress [FILE]\" or \"uncompress [FILE]\"" << endl;
      cout << "Compress a text file using LZW encoding." << endl;
      cout << "--help: Provide help on command." << endl;
    }
    else {
      cout << "Invalid operation." << endl;
      exit(1);
    }
  }
  else if(argc == 3) {
    string tmp = argv[1];
    if(tmp == "compress") {
      string contents;
      string directory = argv[2];
      if(directory.substr(directory.size()-4) == ".zip") {
        cout << "invalid file type. Must not be a compressed archive." << endl;
        exit(1);
      }

      // reads in the contents of the file
      string line;
      ifstream infile(directory.c_str());
      if(infile.is_open()) {
        while(getline(infile, line)) {
          contents.append(line);
        }
        infile.close();
      }

      // compresses the contents of the file into a vector of ints representing
      // the encoded pointers of the data
      vector<int> compressed;
      compress(contents, std::back_inserter(compressed));

      // writes the compressed data to a file on disk using CSV.
      directory = directory.substr(0, directory.size()-4);
      directory.append(".zip");
      ofstream outfile(directory.c_str());
      if(outfile.is_open()) {
        for(int i = 0; i < compressed.size(); i++) {
          outfile << compressed[i];
          if(i < compressed.size()-1) {
            outfile << ",";
          }
        }
      outfile.close();
      }
      cout << "compression complete" << endl; 
    }
    else if(tmp == "uncompress") {
      string directory = argv[2];
      if(directory.substr(directory.size()-4) != ".zip") {
        cout << "invalid file type. Must be of type .zip" << endl;
        exit(1);
      }

      // Reads in the contents of the .zip file and builds a vector.
      string contents;
      string line;
      ifstream infile(directory.c_str());
      if(infile.is_open()) {
        while(getline(infile, line)) {
          contents.append(line);
        }
        infile.close();
      }
      stringstream ss(contents);
      vector<int> compressed;
      int j;
      while(ss >> j) {
        compressed.push_back(j);

        if(ss.peek() == ',') {
          ss.ignore();
        }
      }

      // Performs the decompression algorithm on the newly built vector
      // outputs the decompressed data to a string
      string decompressed = decompress(compressed.begin(), compressed.end());
      
      // Outputs the uncompressed data to a .txt file of the same name as the
      // archive. Writes the uncompressed data to disk.
      directory = directory.substr(0, directory.length()-4);
      directory = directory.append(".txt");
      ofstream outfile(directory.c_str());
      if(outfile.is_open()) {
        outfile << decompressed;
      }
      outfile.close();
      cout << "decompression complete" << endl;
    }
    else {
      cout << "Invalid operation." << endl;
      exit(1); 
    }
  }
  else {
    cout << "Invalid operation." << endl;
    exit(1);
  }
 
  return 0;
}
