#include "ExpTree.h"
#include "Define.h"
int main()
{
	
	while(1) 
	{
		//初始化
		char in[1000] = {0};
		char last[1000] = {0};
		char type[10] = {0};
		char name[20] = {0};
		ExpTree tree;
		Define test;

		//判断定义是否正确
		if(!test.JudgeDef())	continue;

		//获取定义的变量和表达式的信息
		if(!test.GetMessage(in, type, name))	continue;

		//判断表达式是否正确
		if(!tree.JudgeExp(in))	continue;
		
		//中缀转后缀
		tree.In2Last(in, last);
		
		//建立二叉树并后序遍历
		string str = last;
		tree.PostOrderCreate(str);
		
		//计算结果并存储变量名和值
		tree.Def(type, name);
	}
	return 0;
}
