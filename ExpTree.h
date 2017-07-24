#include <iostream>
using namespace std;
#include <string>
#include <stack>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include "TNode.h"
class ExpTree
{
public:
	ExpTree():m_pRoot(NULL){}
	~ExpTree();
	void Def(char type[], char name[]);
	double Value();

	void PostOrderCreate(string str);

	void In2Last(char *in, char *last);
	bool JudgeExp(char *in);
private:
	void Destroy(TNode *cur);	
	double Cacul(double a, char op, double b);
	double Val(TNode *cur);
	void LastOrderPrint();
	void LastOrderPrint(TNode *p);	
	bool IsOperator(char ch);
	int Precedence(char op1, char op2);
	void Create(string str);
public:
	static string def[10]; //存储最多10个变量的名字
	static int count; //目前存储的是第几个变量
	static string ans[10]; //存储对应的结果
	TNode *m_pRoot;
}; 

