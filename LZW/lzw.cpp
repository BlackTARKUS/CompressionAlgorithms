#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>

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
    if(tmp == "compress") {
      string directory = argv[2];

    }
    else if(tmp == "uncompress") {
      string directory = argv[2];

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

  vector<int> compressed;
  compress("TOBEORNOTTOBEORTOBEORNOT", std::back_inserter(compressed));
  copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(cout, ", "));
  cout << endl;
  string decompressed = decompress(compressed.begin(), compressed.end());
  cout << decompressed << endl;
 
  return 0;
}