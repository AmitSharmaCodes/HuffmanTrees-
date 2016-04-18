#include "HCNode.hpp"

bool HCNode::operator<(const HCNode & other) const
{
	if (count != other.count)
		return count > other.count;
	return symbol > other.symbol;
}
