/*************************************************************************
    > File Name: Define.h
    > Author: Ukey
    > Mail: gsl110809@gmail.com
    > Created Time: 2016年12月26日 星期一 08时39分37秒
 ************************************************************************/

#include <iostream>
using namespace std;
#include <string>

class Define
{
	public:
		Define();
		~Define(){};
		bool JudgeDef();
		bool GetMessage(char exp[], char t[], char n[]);
	private:
		void GetExp(char exp[]);
		void GetType(char t[]);
		bool GetName(char n[]);
		bool JgType(int &typePos, int &defPos);
		bool JgName(int typePos, int defPos);
		bool JgEnd();
	private:
		string str;
		string type;
		string name;  //变量名
		string table[10] ;
};

