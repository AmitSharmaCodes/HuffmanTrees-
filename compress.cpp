#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HCTree.hpp"
using namespace std;

//loads the first 3 bytes of a integer into a file
void integerto3byte(int i, BitOutputStream out) {
	int value = 0;
	for (int i = 0; i < 12; i++) {
		value = ((i >> (11 - i)) & 1);
		out.writeBit(value);
	}
}

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
	ofstream o;
	
	//open the input file and get all the frequencies
	f.open(argv[1], ios::binary);
	unsigned char nextChar;
	int nextByte;
	BitOutputStream out(o);
	while ((nextByte = f.get()) != EOF) {
		nextChar = (unsigned char)nextByte;
	//	cout << nextByte << ": " << nextChar << endl;
		++freq[nextByte];
	}
	f.close();

	//build huff trie
	trie.build(freq);
	
	//open output file
	
	
	o.open(argv[2], ios::binary);
	if (!o.is_open())
		cout << "NOT OPENED" << endl;
	//write the header
	int frequency;
	for (int i = 0; i < freq.size(); ++i) {
		frequency = freq[i];
		o.write((char *)&frequency, sizeof(frequency));
		//integerto3byte(frequency, out);
	}

	//open input file again
	f.open(argv[1], ios::binary);
	//encode 
	int characterCount = 0;
	while ((nextByte = f.get()) != EOF) {
		nextChar = (unsigned char)nextByte;
		trie.encode(nextChar, out);
		++characterCount;
	//	if (characterCount % 10000 == 0) { //for checking progress on long files
	//		cout << "Characters Processed: " << characterCount << endl;
	//	}
	}
	out.flush();
	f.close();
	o.close();
	return 0;
}