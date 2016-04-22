#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HCTree.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	//Check for Arguments
	if (argc != 3) {
		cout << "Invalid number of arguments.\n"
			<< "Usage: ./main <input filename> <output filename>.\n";
		return -1;
	}

	HCTree trie;
	vector<int> freq(256);
	ifstream f;
	
	//open the input file and get all the frequencies
	f.open(argv[1], ios::binary);
	unsigned char nextChar;
	int nextByte;
	while ((nextByte = f.get()) != EOF) {
		nextChar = (unsigned char)nextByte;
	//	cout << nextByte << ": " << nextChar << endl;
		++freq[nextByte];
	}
	f.close();

	//build huff trie
	trie.build(freq);
	
	//open output file
	ofstream o;
	BitOutputStream out(o);
	o.open(argv[2]);
	if (!o.is_open())
		cout << "NOT OPENED" << endl;
	//write the header
	for (int i = 0; i < freq.size(); ++i)
		o << freq[i];  //4 byte header

	//open input file again
	f.open(argv[1]);

	//encode 
	while ((nextByte = f.get()) != EOF) {
		nextChar = (unsigned char)nextByte;
		trie.encode(nextChar, out);
	}
	f.close();
	o.close();

	return 0;
}