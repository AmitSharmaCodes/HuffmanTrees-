#include "BitOutputStream.hpp"

void BitOutputStream::flush()
{
	out.put(buf);
	out.flush();
	buf = nbits = 0;
}

void BitOutputStream::writeBit(int i)
{
	buf = (buf | (i << (7 - nbits)));
	++nbits;
	if (nbits == 8)
		flush();
}
