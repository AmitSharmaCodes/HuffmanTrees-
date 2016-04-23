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
		int value = buf & (1 << (nbits - 1));
	value = value >> (nbits - 1);
	--nbits;
	return value;
}
