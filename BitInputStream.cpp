#include "BitInputStream.hpp"

void BitInputStream::fill()
{
	buf = in.get();
	nbits = 8;
}

int BitInputStream::readBit()
{
	if (nbits == 0)
		fill();
	unsigned int mask = 1 << 7;
	int value = ((buf & mask) >> 7);
	buf = buf << 1;
	return value;
}
