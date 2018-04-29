
# Compression Algorithms
Research by Cody Lee
for CSC 499

**Algorithms:** Lempel-Ziv-Welch (LZW) Coding,  Huffman Coding, and Adaptive Huffman Coding

Project Breakdown: This project will describe and exemplify key concepts in computer encoding using LZW, Huffman coding, and Adaptive Huffman Coding. The key components this project will focus on are the theory and the implementation of specifically LZW and Huffman Coding. For the sake of focus and simplicity, all theory in this project will refer to encoding performed on standard ASCII based text strings, and not multi-media files. All code is implemented in C++ which is compiled on a Linux server using a modified compiler made by Dr. Pounds of Mercer University for educational purposes.

**Documentation:**

*[Huffman Coding](https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/)*:

Huffman Coding is a form of lossless data compression. Huffman Coding is a greedy algorithm developed in 1952 by David A. Huffman. Huffman's algorithm outputs a type of variable-length coding table which is then used to encode ASCII text documents. The algorithm derives the table from the frequency of occurrence (also known as weight) for each possible value in the source document. More commonly occurring symbols are assigned a greater weight value. Symbols with a high-frequency value are assigned "codes", unique binary alternatives, with a low number of bits such that the compressed document assigns as few bits to the total as possible. Huffman's algorithm can be efficiently implemented by finding a code for a given symbol, which takes an amount of time linear to the number of input weights, assuming that weights are sorted. These codes are known to be "prefix-free" such that the bit string representing a particular symbol is never a prefix of the bit string representing any other symbol.

*[Adaptive Huffman Coding](https://www.sciencedirect.com/science/article/pii/0196677485900367)*:

Adaptive Huffman Coding, also known as Dynamic Huffman Coding, is an alternative to Huffman Coding that follows Adaptive Coding principles. Adaptive Huffman Coding (AHC) involves building the code as the symbols are being transmitted, without knowing the entirety of the dataset. In other words, the AHC uses an algorithm called Faller-Gallager-Knuth (FGK) which dynamically adjusts the Huffman Tree as data is added. In FGK the Huffman tree utilizes a special external node, called the 0-node, in order to identify new characters as they are added to the tree. The result of this is that AHC is able to implement Huffman Coding in an online environment where data is constantly being added by either the end user or the server because the compression tree is constantly being rebuilt until the final command is sent, causing the table to be generated, and the compressed file to be output.


[*Lempel-Ziv-Welch*](https://sites.google.com/site/datacompressionguide/lzw):
Lempel-Ziv-Welch is one of three coding techniques which falls within the Lempel-Ziv umbrella. The LZ Family includes LZ77, LZ78, and LZW encoding. This project focuses on LZW, the improved version of the LZ78 encoding practice. LZW can be applied to text strings in order to create a compressed representation of the original set of data. LZW acts by creating a non-literal "dictionary" for storing and looking up phrases. The algorithm accumulates strings of two or more cahracters which are built from phrases which are modeled from sets of symbols in the original data. Unlike earlier iterations of the LZ family, LZW does not use a literal dictionary to decode the compressed data. LZW instead enables the decoder to recreate the string table used by the encoder for the decompression process. LZW constantly gathers strings and tests if a particular string  is already in the table as the encoding process executes. If the new string is tested and not found within the string table, it is inserted into the table and the index of the previous string is transmitted as an LZW output code. The LZW code is usually of size 12 bits. LZW has 4096 possible codes for a given symbol set. There is potential that the LZW algorithm will not enocunter a match for two-byte strings, and as such must be enabled to output a code which can represent a single byte. The first 256 codes (starting at code 0) are reserved for single byte cases. As such, the non-matching single bytes are given 12 bits of reserved memory rather than 8 bits of reserved memory. LZW is more effective with longer strings becasue of this reservation system. When the algorithm is used to decompress the data, the original string table is rebuilt and used to guide the decoder. The algorithm receives the output LZW codes from the table in the order which they were originally sent to the string table, and reverses the process to determine the original data. There are a number of common practices to improve LZW codes which have been developed in the past decades, however for this project the base LZW algorithm is used. 

# Runtime and Complexity
This segment refers to the algorithmic complexity and efficiency of the Huffman and LZW algorithms. The runtime complexity of each is measured in [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation). This section also provides practical examples of the runtime by executing example implementations of the code on Mercer University's Cobra server under the effects of the Linux "time" command. All values reported as runtime are the aggregate "real" time values of the time command. This command outputs the time it takes the hardware to execute the command, as such is not entirely accurate to the efficiency of the code, and merely represents a possible practical example of the runtime of the code on user hardware.

*Huffman*:
On average Huffman encoding requires O(N) for time complexity and O(LogK) for space complexity wherein K is the number of nodes contained within the Huffman tree.

*LZW*: 
in LZW each byte is read only once, and the complexity of operation for each character is constant, and as such, the complexity is O(n)

**LZW Coding Runtimes**

| Sample | Characters | Runtime |
|--------|------------|---------|
| 1 | 37 | 0.004s |
| 2 | 620 | 0.006s |
| 3 | 1381 | 0.008s |

**Huffman Coding Runtimes**

| Sample | Characters | Runtime |
|--------|------------|---------|
| 1 | 37 | 0.007s |
| 2 | 620 | 0.008s |
| 3 | 1381 | 0.009s |


| First Header  | Second Header |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |

# Conclusion
Both Huffman and LZW are powerful and useful compression algorithms which continue to be used in the modern environment despite their age. Huffman, due to its greedy nature, is primarily used in older mainstream media compression. This includes Winzip, Gzip, Bzip2, and JPEG (image) applications. Although Huffman is eclipsed by some modern proprietary arithmetic and range based coding solutions, Huffman remains a commonly used standard. LZW is similarly used in lossless data files. Most commonly LZW is found in GIF and TIFF media formats, as well as in Modem compression (wireless internet data transfer). The low system requirements of LZW makes it an ideal encoding and decoding technique for machines which lack large amounts of innate processing power, or when the allocated resources to the encoding and decoding are limited (such as in web applications). LZW is a popular choice because of its unique ability to handle a large variety of data with similar results, and as such remains a popular choice in modern computing. 

# Implementations
The implementations for this project are found within the data files of the GitHub repository. In order to keep the readme clean and legible, the code has been omitted from the documentation. All code can be found in this repository for modification and further use. 

# Sources
Geek For Geeks: https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
Google Code Guide: https://sites.google.com/site/datacompressionguide/lzw
Donald E Knuth, Dynamic Huffman Coding: https://www.sciencedirect.com/science/article/pii/0196677485900367
Mamta Sharma, Compression Using Huffman Coding: https://pdfs.semanticscholar.org/89c2/03919ce446762d9b768ac0974f54021f338e.pdf
 Computerphile, Elegant Compression in Text: https://www.youtube.com/watch?v=goOa3DGezUA
 

# Sample Data Used
This section lists the sample text files on which the code implementations were executed. The strings are meaningless and were chosen from internet forums to simply illustrate how the algorithms perform when run on English text.

*sample 1*: 
how much wood could a woodchuck chuck

*sample 2*:
I sexually Identify as an Attack Helicopter. Ever since I was a boy I dreamed of soaring over the oilfields dropping hot sticky loads on disgusting foreigners. People say to me that a person being a helicopter is Impossible and I'm fucking retarded but I don't care, I'm beautiful. I'm having a plastic surgeon install rotary blades, 30 mm cannons and AMG-114 Hellfire missiles on my body. From now on I want you guys to call me "Apache" and respect my right to kill from above and kill needlessly. If you can't accept me you're a heliphobe and need to check your vehicle privilege. Thank you for being so understanding.

*sample 3*:
What in Davy Jones' locker did ye just bark at me, ye scurvy bilgerat? I'll have ye know I be the meanest cutthroat on the seven seas, and I've led numerous raids on fishing villages, and raped over 300 wenches. I be trained in hit-and-run pillaging and be the deadliest with a pistol of all the captains on the high seas. Ye be nothing to me but another source o' swag. I'll have yer guts for garters and keel haul ye like never been done before, hear me true. You think ye can hide behind your newfangled computing device? Think twice on that, scallywag. As we parley I be contacting my secret network o' pirates across the sea and yer port is being tracked right now so ye better prepare for the typhoon, weevil. The kind o' monsoon that'll wipe ye off the map. You're sharkbait, fool. I can sail anywhere, in any waters, and can kill ye in o'er seven hundred ways, and that be just with me hook and fist. Not only do I be top o' the line with a cutlass, but I have an entire pirate fleet at my beck and call and I'll damned sure use it all to wipe yer arse off o' the world, ye dog. If only ye had had the foresight to know what devilish wrath your jibe was about to incur, ye might have belayed the comment. But ye couldn't, ye didn't, and now ye'll pay the ultimate toll, you buffoon. I'll shit fury all over ye and ye'll drown in the depths o' it. You're fish food now, lad.
