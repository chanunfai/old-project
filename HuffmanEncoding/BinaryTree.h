class BinaryTreePtr
{
public:
	BinaryTreePtr(char ch, int cnt);
	BinaryTreePtr(){

	}
	char character;
	int count;
	BinaryTreePtr* left;
	BinaryTreePtr* right;
	friend bool operator<(const BinaryTreePtr& left,const BinaryTreePtr& right);
	void printTree(int* huffman_ar, int huffman_count);

};