class TNode
{
public:
	char optr;
	double opnd;
	TNode *left;
	TNode *right;
	TNode(char op, TNode *lef, TNode *rgt):optr(op), left(lef), right(rgt){}
	TNode(double num):opnd(num), left(NULL), right(NULL){}

}; 

