#include <iostream>
#include "HCTree.hpp"
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	HCTree trie;
	vector<int> freq(256);
	ifstream f;

	//Check for Arguments
	if (argc != 2) {
		cout << "Invalid number of arguments.\n"
			<< "Usage: ./main <input filename> <output filename>.\n";
		return -1;
	}

	f.open(argv[1]);
	
	int frequency = 0;
	for (int i = 0; i < freq.size(); ++i)
	{
		frequency = f.get();
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