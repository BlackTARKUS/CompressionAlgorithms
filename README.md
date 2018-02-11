# CompressionAlgorithms

This repository is a means of organizing and demonstrating Cody Lee's student research project detailing the strengths and differences between various text-data oriented compression algorithms.

**Algorithms:**
Huffman Coding
Adaptive Huffman Coding
Shannon-Fano Coding
Lempel-Ziv-Welch (LZW)

Project  Breakdown:
The research in this project is broken down into three main categories:
Documentation, Implementation, and Comparison

In Documentation, the algorithms chosen for research are explained in words and pseudo code.
In Implementation, the algorithms are implemented in C++ code and compiled in an executable format.
In Comparison, the performance metrics of the algorithms are analyzed and compared across a spectrum of use cases.

**Documentation:**

Huffman Coding:

  Huffman Coding is a form of lossless data compression. Huffman Coding is a greedy algorithm developed in 1952 by David A. Huffman. Huffman's algorithm outputs a type of variable-length coding table which is then used to encode ASCII text documents. The algorithm derives the table from the frequency of occurrence (also known as weight) for each possible value in the source document. More commonly occurring symbols are assigned a greater weight value. Symbols with a high-frequency value are assigned "codes", unique binary alternatives, with a low number of bits such that the compressed document assigns as few bits to the total as possible. Huffman's algorithm can be efficiently implemented by finding a code for a given symbol, which takes an amount of time linear to the number of input weights, assuming that weights are sorted. These codes are known to be "prefix-free" such that the bit string representing a particular symbol is never a prefix of the bit string representing any other symbol.
 
Adaptive Huffman Coding:

  Adaptive Huffman Coding, also known as Dynamic Huffman Coding, is an alternative to Huffman Coding that follows Adaptive Coding principles. Adaptive Huffman Coding (AHC) involves building the code as the symbols are being transmitted, without knowing the entirety of the dataset. In other words, the AHC uses an algorithm called Faller-Gallager-Knuth (FGK) which dynamically adjusts the Huffman Tree as data is added. In FGK the Huffman tree utilizes a special external node, called the 0-node, in order to identify new characters as they are added to the tree. The result of this is that AHC is able to implement Huffman Coding in an online environment  where data is constantly being added by either the end user or the server because the compression tree is constantly being rebuilt until the final command is sent, causing the table to be generated, and the compressed file to be output.
 
*Shannon-Fano Coding:*
  Shannon-Fano Coding is... TODO: WRITE ME (Shannon-Fano Coding Analysis)
 
*Lempel-Ziv-Welch*
  Lempel-Ziv-Welch is... TODO: WRITE ME (Lempel-Ziv-Welch Analysis)
 

**Implementation:**
The source code for the implementations of the algorithms go here


**Comparison:**
DATA TABLES AND NUMBER CRUNCHING GO HERE
