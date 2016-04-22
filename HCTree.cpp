#include "HCTree.hpp"
#include <string>

//recursively delete all the nodes
void HCTree::deleteAll(HCNode * n)
{
	if (n == NULL)
		return;
	deleteAll(n->c0);
	deleteAll(n->c1);
	delete n;
}

HCTree::~HCTree()
{
	deleteAll(root);
}

/** Use the Huffman algorithm to build a Huffman coding trie.
*  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
*  the frequency of occurrence of byte i in the message.
*  POSTCONDITION:  root points to the root of the trie,
*  and leaves[i] points to the leaf node containing byte i.
*/
void HCTree::build(const vector<int>& freqs)
{
	/*create a priority queue that takes in HCNodes pointers
	uses a vector as the underlining data structure and uses the
	function class HCNodesPtrComp for comparison
	*/
	priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> que;

	/*load in all the symbols into the priority queue
	unless they are zero, then they do not show up in the file
	and we do not need to keep track of them in the tree
	*/
	int currentFreq;
	HCNode* currentNode;
	for (int i = 0; i < freqs.size(); i++)
	{
		currentFreq = freqs[i];
		if (currentFreq != 0)
		{
			//the freq is stored in currentFreq, and the symbol
			//is the ascii value which is the i varaible
			//all of these are the leaves in the tree
			currentNode = new HCNode(currentFreq, i);
			leaves[i] = currentNode;
			que.push(currentNode);
		}
	}
	//all the frequencies are zero, empty file, no tree is needed
	if (que.size() == 0)
		return;
	//if there is only one element left in the queue, it is the top
	// of the tree, and should be the root
	//otherwise pop the top two nodes, zero, and one and compine them
	//into a new node, and add that node into the queue
	HCNode* zero;
	HCNode* one;
	HCNode* combine;
	while (!que.empty()) {
		if (que.size() == 1) {
			root = que.top();
			que.pop();
		}
		else {
			//pop the top two
			zero = que.top();
			que.pop();
			one = que.top();
			que.pop();
			//create the combined node, the count is the sum of its children
			// the symbol is arbitrarily from the zero child
			// and make sure the children know who the parent is
			//then add the combine back into the queue
			combine = new HCNode((zero->count + one->count), zero->symbol, zero, one);
			zero->p = combine;
			one->p = combine;
			que.push(combine);
		}
	}
}

void HCTree::encode(byte symbol, BitOutputStream & out) const
{
	/* Find the symbol in the leaves vector, and then
	work backwards from the leave to the root, which will
	give you the reversed encoding, reverse it, and add it
	to the ofstream
	*/
	int index = symbol;
	HCNode* sym = leaves[index];
	HCNode* symParent;
	//keep looping til you hit the root
	while ((symParent = sym->p) != NULL)
	{
		//if the symbol was a 0 child or a 1 child
		//insert the 0 or 1 at the beginning rather than
		//the end
		if (symParent->c0 == sym)
			out.writeBit(0);
		else
			out.writeBit(1);
		sym = sym->p;
	}
	//cout << symbol << ": " << encoding << endl;

}

int HCTree::decode(BitInputStream & in) const
{
	HCNode* begin = root;
	int nextByte;
	while (!(begin->c0 == NULL && begin->c1 == NULL))
	{
		int branch = in.readBit();
		if (branch == 0)
			begin = begin->c0;
		else if (branch == 1)
			begin = begin->c1;
		else
			return 0; //reached the end of file
	}
	return begin->symbol;
}


/** Write to the given ofstream
*  the sequence of bits (as ASCII) coding the given symbol.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
*  BE USED IN THE FINAL SUBMISSION.
*/

//void HCTree::encode(byte symbol, ofstream & out) const
//{
//	/* Find the symbol in the leaves vector, and then
//	work backwards from the leave to the root, which will
//	give you the reversed encoding, reverse it, and add it
//	to the ofstream
//	*/
//	int index = symbol;
//	HCNode* sym = leaves[index];
//	HCNode* symParent;
//	string encoding;
//	//keep looping til you hit the root
//	while ((symParent = sym->p) != NULL)
//	{
//		//if the symbol was a 0 child or a 1 child
//		//insert the 0 or 1 at the beginning rather than
//		//the end
//		if (symParent->c0 == sym)
//			encoding.insert(0, "0");
//		else
//			encoding.insert(0, "1");
//		sym = sym->p;
//	}
//	//cout << symbol << ": " << encoding << endl;
//	out << encoding;
//
//}

/** Return the symbol coded in the next sequence of bits (represented as
*  ASCII text) from the ifstream.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
*  IN THE FINAL SUBMISSION.
*/
//int HCTree::decode(ifstream & in) const
//{
//	HCNode* begin = root;
//	int nextByte;
//	while (!(begin->c0 == NULL && begin->c1 == NULL))
//	{
//		unsigned char branch = (unsigned char)in.get();
//		if (branch == '0')
//			begin = begin->c0;
//		else if (branch == '1')
//			begin = begin->c1;
//		else
//			return 0; //reached the end of file
//	}
//	return begin->symbol;
//}
