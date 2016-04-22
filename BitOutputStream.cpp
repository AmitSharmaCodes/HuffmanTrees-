#include "BitOutputStream.hpp"

void BitOutputStream::flush()
{
	out.put(buf);
	out.flush();
	buf = nbits = 0;
}

void BitOutputStream::writeBit(int i)
{
	if (nbits == 8)
		flush();
	buf = (buf << 1) | i;
	++nbits;
}
