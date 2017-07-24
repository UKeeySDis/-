/*************************************************************************
    > File Name: Define.cpp
    > Author: Ukey
    > Mail: gsl110809@gmail.com
    > Created Time: 2016年12月26日 星期一 10时15分18秒
 ************************************************************************/

#include "Define.h"
#include "ExpTree.h"
#include <stdio.h>
Define :: Define()
{
	table[0] = "int";
	table[1] = "float";
	table[2] = "double";
	table[3] = "char";
	table[4] = "bool";
	cout<<"请输入定义的语句:"<<endl;
	getline(cin, str);

}
bool Define :: JgType(int &typePos, int &defPos)
{
	/*-----------检测定义的变量类型是否有错，目前只支持int, float, double, char, bool---------*/
	int temp, flag = 0;;
	for(int i = 0; i < 5; i++)  //找到定义的变量的类型
	{
		if((temp = str.find(table[i])) != -1)
		{
			typePos = i;
			defPos = temp;
			flag++;
			continue;
		}
	}
	if(defPos == -1 || typePos == -1 || flag > 1)
	{
		cout<<"未找到合法的变量类型"<<endl;
		return false;

	}
	this->type = table[typePos];
	if(str[defPos+table[typePos].size()] != ' ')		//定义的变量类型后一位必须是' '
	{
		cout<<"未找到合法的变量类型"<<endl;
		return false;
	}
	for(int i = 0; i < defPos; i++)
		if(str[i] != ' ')
		{
			cout<<"未找到合法的变量类型"<<endl;
			return false;
		}
	return true;
}
bool Define :: JgName(int typePos, int defPos)
{
	/*-----------检测定义的变量名是否合法，合法的变量名只能有字母数组和下划线，并且数字不能作为开头----------*/
	int equalPos = str.find('=');

	int flag = 0;
	if(equalPos == -1)
	{
		cout<<"语句中没有'='号"<<endl;
		return false;
	}
	for(int i = defPos + table[typePos].size(); i < equalPos; i++)
	{
		if(str[i] != ' ')
		{
			flag = i;
			break;
		}
	}
	if(flag == 0)
	{
		cout<<"变量名未输入!"<<endl;
		return false;
	}
	else if(str[flag] >= '0' && str[flag] <= '9')
	{
		cout<<"变量名开头只能是字母或者下划线"<<endl;
		return false;
	}
	for(int i = flag; i < equalPos; i++)
	{
		
		if(str[i] == ' ')
		{
			for(; i < equalPos; i++)
			{
				if(str[i] != ' ')
				{
					cout<<"变量名中间有空格"<<endl;
					return false;
				}
			}
			
		}
		if(i == equalPos)
			return true;
		if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_' ) || (str[i] >= '0' && str[i] <= '9'))
		{
			name.push_back(str[i]);   //取得变量名
		}
		else
		{
			cout<<"变量名中含有非法字符"<<endl;
			return false;
		}
	}
	return true;
}
bool Define :: JgEnd()
{
	/*-----------检测语句是否有结束符";"-----------*/
	int endPos = str.find(';');
	if(endPos == -1)
	{
		cout<<"该语句需要;结束"<<endl;
		return false;
	}
	for(int i = endPos+1; i < str.size(); i++)
	{
		if(str[i] != ' ' || str[i] != '\n')
		{
			cout<<";后有未知的错误"<<endl;
			return false;
		}
	}
	return true;
}
//检验定义时的错误
bool Define :: JudgeDef()
{
	int typePos = -1, defPos = -1 ;  //接收定义的变量类型的位置

	if(!JgType(typePos, defPos))
	{
		return false;
	}

	if(!JgName(typePos, defPos))
	{
		return false;
	}

	if(!JgEnd())
	{
		return false;
	}


	return true;
}
//取得表达式
void Define :: GetExp(char exp[])
{
	int j = 0;
	int equalPos = str.find('=');
	int agoPos;

	//取表达式之前先进行替换
	for(int i = 0; i < ExpTree::count; i++)
	{
			
		if((agoPos = str.find(ExpTree::def[i], equalPos+1)) != -1)
		{
			cout<<"要替换的字符串为:"<<ExpTree::def[i]<<endl;
			str.replace(agoPos, ExpTree::def[i].size(), ExpTree::ans[i]);
			cout<<"替换后的字符串为"<<str<<endl;
		}
	}

	//过滤掉空格和换行
	for(int i = equalPos + 1; i < str.size(); i++)
	{
		if(str[i] == ' ' || str[i] == '\n' || str[i] == ';')
			continue;
		exp[j++] = str[i];
	}
	exp[j] = '\0';
}
//获得变量的类型
void Define :: GetType(char t[])
{
	int i = 0;
	for(; i < type.size(); i++)
		t[i] = type[i];
	t[i] = '\0';
}
//获得变量的名字
bool Define :: GetName(char n[])
{
	int i = 0;
	for(; i < name.size(); i++)
		n[i] = name[i];
	n[i] = '\0';
	for(int i = 0; i < ExpTree::count; i++)
	{
		if(name == ExpTree::def[i])
		{
			cout<<"该变量已经定义了，不要重复定义"<<endl;
			return false;
		}
	}
	return true;
}
bool Define :: GetMessage(char exp[], char t[], char n[])
{
	GetExp(exp);
	GetType(t);
	if(!GetName(n))
		return false;
	return true;
}
