#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	HCTree trie;
	vector<int> freq(256);
	ifstream f;

	//Check for Arguments
	if (argc != 3) {
		cout << "Invalid number of arguments.\n"
			<< "Usage: ./main <input filename> <output filename>.\n";
		return -1;
	}

	f.open(argv[1]);
	
	int frequency = 0;
	string s;
	for (int i = 0; i < freq.size(); ++i)
	{
		getline(f, s);
		frequency = stoi(s);
		freq[i] = frequency;
	}
	trie.build(freq);

	ofstream o;
	o.open(argv[2]);
	int nextByte;
	unsigned char nextChar;
	while ((nextByte = trie.decode(f)))
	{
		nextChar = (unsigned char)nextByte;
		o << nextChar;
	}
	o.close();
	f.close();
	return 0;
}