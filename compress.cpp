#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HCTree.hpp"
using namespace std;

int main()
{
	HCTree trie;
	vector<int> freq(256);
	ifstream f;
	f.open("C:\\Users\\ashar_000\\Desktop\\Workspace\\CSE100\\PA2\\repo_st_733_4844_14410_pa2_huffman\\t.txt");
	unsigned char nextChar;
	int nextByte;
	while ((nextByte = f.get()) != EOF) {
		nextChar = (unsigned char)nextByte;
		cout << nextByte << ": " << nextChar << endl;
		++freq[nextByte];
	}
	f.close();
	
	ofstream o;
	o.open("C:\\Users\\ashar_000\\Desktop\\Workspace\\CSE100\\PA2\\repo_st_733_4844_14410_pa2_huffman\\output.txt");
	if (o.is_open())
		cout << "OPENED" << endl;

	trie.build(freq);
	f.open("C:\\Users\\ashar_000\\Desktop\\Workspace\\CSE100\\PA2\\repo_st_733_4844_14410_pa2_huffman\\t.txt");
	while ((nextByte = f.get()) != EOF) {
		nextChar = (unsigned char)nextByte;
		trie.encode(nextChar, o);
	}
	f.close();
	o.close();

	f.open("C:\\Users\\ashar_000\\Desktop\\Workspace\\CSE100\\PA2\\repo_st_733_4844_14410_pa2_huffman\\output.txt");
	while ((nextByte = trie.decode(f))) {
		
		nextChar = (unsigned char)nextByte;
		cout << nextByte << ": " << nextChar << endl;
	}

	return 0;
}