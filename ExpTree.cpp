#include "ExpTree.h"
#include <cstdio>
string ExpTree::def[10];
string ExpTree::ans[10];
int ExpTree::count = 0;

void ExpTree :: Destroy(TNode *cur)
{
	if(cur)
	{
		Destroy(cur->left);
		Destroy(cur->right);
		delete cur;
	}
}
ExpTree :: ~ExpTree()
{
	Destroy(m_pRoot);
}
//计算
double ExpTree :: Cacul(double  a, char op, double  b)
{
	switch(op)
	{
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
	}
}
//求值函数
double ExpTree :: Val(TNode *cur)
{
	if(cur->left == NULL && cur->right == NULL)
	{
		return cur->opnd;
	}
	else
		return Cacul(Val(cur->right), cur->optr, Val(cur->left));
}

double ExpTree :: Value()
{
	return Val(m_pRoot);
}
void ExpTree :: LastOrderPrint()
{
	cout<<"后缀遍历:";
	LastOrderPrint(m_pRoot);
	cout<<endl;
}
void ExpTree :: LastOrderPrint(TNode *p)
{
	if(p != NULL)
	{
		LastOrderPrint(p->left);
		LastOrderPrint(p->right);
		if(p->left == NULL && p->right == NULL)
		{
			cout<<p->opnd;
		}	
		else
			cout<<p->optr;
		cout<<" ";	
	}
}
void ExpTree :: Create(string str)
{
	stack<TNode *>nodeStack;
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] == ' ') continue;
		switch(str[i])
		{
			case '+':
			case '-':
			case '*':
			case '/':
				{
					TNode* temp1 = nodeStack.top();
					nodeStack.pop();
					TNode* temp2 = nodeStack.top();
					nodeStack.pop();
					nodeStack.push(new TNode(str[i], temp1, temp2));
					break;
				}
			default:
				{
					char temp[100] = {0};
					int j = 0;
					double num;	
					while(str[i] != '#')
					{
						temp[j++] = str[i];
						i++;		
					}
					
					temp[j] = '\0';
					num = atof(temp);
					nodeStack.push(new TNode(num));
					break;
				}	
		}	
	}
	m_pRoot = nodeStack.top();
	nodeStack.pop();
}
void  ExpTree::PostOrderCreate(string str)
{
	Create(str);

	LastOrderPrint();
}

//求值并存储历史变量的值和名字
void ExpTree::Def(char type[], char name[])
{
	char s[100];
	int len = strlen(name);
	for(int i = 0; i < len; i++)
	{
		def[count].push_back(name[i]);
	}
	if(strcmp(type, "int") == 0)
	{
		int res = (int)Value();
		cout<<"表达式的值为:"<<res<<endl;
		sprintf(s, "%d", res);
		int len1 = strlen(s);
		for(int i = 0; i < len1; i++)
		{
			ans[count].push_back(s[i]);  
		}
	}
	else if(strcmp(type, "float") == 0)
	{
		float res = (float)Value();
		cout<<"表达式的值为:"<<res<<endl;
		sprintf(s, "%f", res);
		int len1 = strlen(s);
		for(int i = 0; i < len1; i++)
		{
			ans[count].push_back(s[i]);  
		}
	}
	else if(strcmp(type, "double") == 0)
	{
		double res = (double)Value();
		cout<<"表达式的值为:"<<res<<endl;
		sprintf(s, "%lf", res);
		int len1 = strlen(s);
		for(int i = 0; i < len1; i++)
		{
			ans[count].push_back(s[i]);  
		}
	}
	else if(strcmp(type, "bool") == 0)
	{
		bool res = (bool)Value();
		if(res)
			cout<<"表达式的值为:True"<<endl;
		else
			cout<<"表达式的值为:False"<<endl;
		sprintf(s, "%d", res);
		int len1 = strlen(s);
		for(int i = 0; i < len1; i++)
		{
			ans[count].push_back(s[i]);  
		}
	}
	else 
	{
		char res = Value();
		cout<<"表达式的值为:"<<res<<endl;

		sprintf(s, "%d", res);
		int len1 = strlen(s);
		for(int i = 0; i < len1; i++)
		{
			ans[count].push_back(s[i]);  
		}
	}
	cout<<"变量的数据类型为"<<type<<endl;
	cout<<"变量名为:"<<def[count]<<endl;
	count++;
}
//判断是否为运算符
bool ExpTree :: IsOperator(char ch)
{
	char ops[] = "+-*/";
	for(int i = 0; i < sizeof(ops); i++)
	{
		if(ch == ops[i])
			return true;
	}
	return false;
}
//判断优先级
int ExpTree :: Precedence(char op1, char op2)
{
	if(op1 == '(')
	{
		return -1;
	}
	if(op1 == '+' || op1 == '-')
	{
		if(op2 == '*' || op2 == '/')
		{
			return -1;
		}
		else
			return 0;
	}
	if(op1 == '*' || op1 == '/')
	{
		if(op2 == '+' || op2 == '-')
		{
			return 1;
		}
		else
			return 0;
	}
}
//中缀表达式转后缀表达式
void ExpTree :: In2Last(char *in, char *last)
{
	int j = 0, len;
	char c;
	stack<char>st;

	len = strlen(in);
	for(int i = 0; i < len; i++)
	{
		c = in[i];
		if(c == '(')
			st.push(c);
		else if(c == ')')
		{
			while(st.top() != '(')
			{
				last[j++] = st.top();
				st.pop();
			}
			st.pop();
		}
		else
		{
			//数字
			char temp;
			if(!IsOperator(c))
			{
				while(!IsOperator(c) && ((c >= '0' && c <= '9') || c == '.')) 
				{
					last[j++] = c;
					i++;
					c = in[i];
				}
				i--;
				last[j++] = '#';
				
			}
			else
			{
				while(st.empty() == false && Precedence(st.top(), c) >= 0)
				{
					last[j++] = st.top();
					st.pop();
				}
				st.push(c);
			}
		}
	}
	while(st.empty() == false)
	{
		last[j++] = st.top();
		st.pop();
	}
	last[j] = 0;
}
//验证表达式
bool ExpTree :: JudgeExp(char *in)
{
	int len = strlen(in), count = 0;
	stack<char>test;
	for(int i = 0; i < len; i++)
	{
		if(in[i] >= '0' && in[i] <= '9')
			count++;
		if(in[i] == '(')
		{
			count++;	
			test.push('(');
			if(i < len-1)
			{
				if(in[i+1] == ')' || (in[i+1] == '+' || in[i+1] == '-' || in[i+1] == '*' || in[i+1] == '/') )
				{
					cout<<"'('右边一位不应该是运算符"<<endl;
					return false;
				}
				if(i > 0 && in[i-1] >= '0' && in[i-1] <= '9')
				{
					cout<<"'('左边不能是数字"<<endl;
					return false;
				}
			}
		}
		else if(in[i] == ')')
		{
			count++;
			if(!test.empty())
			{
				test.pop();
			}
			else
			{
				cout<<"左右括号不匹配"<<endl;
				return false;
			}
			if(i > 0)
			{
				if(in[i-1] == '(' || (in[i-1] == '+' || in[i-1] == '-' || in[i-1] == '*' || in[i-1] == '/') )
				{
					cout<<"')'左边一位不应该是运算符"<<endl;
					return false;
				}
				if(i < len-1 && in[i+1] >= '0' && in[i+1] <= '9')
				{
					cout<<"')'右边不能是数字"<<endl;
					return false;
				}
			}
		}
		else if(in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/')
		{
			count++;
			if(i > 0 && i < len-1)
			{
				if(in[i+1] == '+' || in[i+1] == '-' || in[i+1] == '/' || in[i+1] == '*' || in[i+1] == '.')
				{
					cout<<"运算符旁不应该是运算符"<<endl;
					return false;
				}
			}
			else
			{
				cout<<"运算符不应作为开头或结束"<<endl;
				return false;
			}
			if(in[i] == '/' && in[i+1] == '0')
			{
				cout<<"0不能作为除数"<<endl;
				return false;
			}
		}
		else if(in[i] == '.')
		{
			count++;
			if(i > 0 && i < len-1)
			{
				for(int j = i+1; j < len - 1; j++)
				{
					if(in[j] == '+' || in[j] == '-' || in[j] == '*' || in[j] == '/' || in[j] == ')')
					{
						break;
					}
					else if(in[j] == '.')
					{
						cout<<"一个数中只有有一个小数点"<<endl;
						return false;
					}
				}
			}
			else
			{
				cout<<"小数点不能作为开头/结束"<<endl;
				return false;
			}
		}	
	}
	if(!test.empty())
	{
		cout<<"左右括号数目不一样"<<endl;
		return false;
	}
	if(count != len)
	{
		cout<<"运算符中含有非法/未定义字符"<<endl;
		return false;
	}
	return true;
}
