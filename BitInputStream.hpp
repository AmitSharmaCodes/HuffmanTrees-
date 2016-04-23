#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;
class BitInputStream {

private:

	unsigned char buf; // one byte buffer of bits
	int nbits; // how many bits have been read from buf
	std::istream & in;

public:

	/** Initialize a BitInputStream that will use

	* the given istream for input.

	*/

	BitInputStream(std::istream & is) : in(is)
	{
		buf = 0; // clear buffer
		nbits = 0;
	}

	/** Fill the buffer from the input */
	void fill();

	/** Read the next bit from the bit buffer
	* Fill the buffer from the input stream first if needed
	* Return 1 if the bit read is 1
	* return 0 if the bit read is 0
	*
	*/
	int readBit();
};
#endif