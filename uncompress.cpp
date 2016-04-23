#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HCTree.hpp"

using namespace std;

//reads first 3 bytes of a file into an integer
int threebytestoInt(BitInputStream in)
{
	int value = 0;
	int incoming;
	for (int i = 0; i < 12; i++) {
		incoming = in.readBit();
		value = (value << 1) | incoming;
	}
	return value;
}

int main(int argc, char* argv[])
{
	HCTree trie;
	vector<int> freq(256);
	ifstream f;
	BitInputStream inp(f);

	//Check for Arguments
	if (argc != 3) {
		cout << "Invalid number of arguments.\n"
			<< "Usage: ./main <input filename> <output filename>.\n";
		return -1;
	}

	f.open(argv[1], ios::binary);
	
	int frequency;
	int total = 0;
	for (int i = 0; i < freq.size(); ++i)
	{
		f.read((char*)&frequency, sizeof(frequency));
		total += frequency;
		freq[i] = frequency;
	}
	trie.build(freq);

	ofstream o;
	o.open(argv[2], ios::binary);
	int nextByte;
	unsigned char nextChar;
	for (int i = 0; i < total; i++)
	{
		nextByte = trie.decode(inp);
		nextChar = (unsigned char)nextByte;
		o.write((char*)&nextChar, sizeof(nextChar));

	}
	o.close();
	f.close();
	return 0;
}