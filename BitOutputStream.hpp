#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
	unsigned char buf;	  // one byte buffer of bits
	int nbits;    // how many bits have been written to buf
	ostream& out; // reference to the output stream to use

public:
	/** Initialize a BitOutputStream that will use
	* the given ostream for output.
	*/
	BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
		// clear buffer and bit counter
	}

	void flush();
	void writeBit(int i);
};
#endif