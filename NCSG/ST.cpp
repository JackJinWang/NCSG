#include"ST.h"
#include<limits.h>
const int NOSUCCESSOR = INT_MAX;
ST::ST(char *character, int number_character, string *T, int number_T)
{
	this->number_T = number_T;
	this->number_character = number_character;
	this->T = T;
	//重新开辟内存空间防止野指针
	this->character = new char[number_character];
	for (int i = 0; i < number_character; i++)
	{
		this->character[i] = character[i];
	}
	this->T = new string[number_T];
	for (int i = 0; i < number_T; i++)
	{
		this->T[i] = T[i];
	}	
}
ST::ST(const ST &st)
{
	this->character = st.character;
	this->number_character = st.number_character;
	this->number_T = st.number_T;
	this->st = st.st;
	this->T = st.T;
}
void ST::show()
{
	/*
	for (int i = 0; i < number_character; i++)
	{
		cout << character[i] << ",";
	}
	cout << endl;
	for (int i = 0; i < number_T; i++)
	{
		cout << T[i] << ",";
	}
	*/
	int str_number;
	for (int i = 0; i < number_T; i++)
	{
		cout << T[i] << endl;
		str_number = T[i].size();              //获取每个字符串长度(后继表长度要增加一位)
		for (int k = 0; k < number_character; k++)
		{
			for (int m = 0; m < str_number + 1; m++)
			{
				if (st[i][k][m] == INT_MAX)
					cout << "*" << " ";
				else
				cout << st[i][k][m] << " ";
			}
				
			cout << endl;
		}
	//	cout << endl;
	}
}
vector<int **> ST::getST()
{
	return st;
}
//构建后继表
void ST::buildST()
{
	int str_number = 0;   //当前字符串长度
	
	for (int i = 0; i < number_T; i++)
	{
		T[i].insert(0, "=");                   //每个字符串前插入  
		str_number = T[i].size();              //获取每个字符串长度(后继表长度要增加一位)
		int **temp = new int*[number_character];                                  
		for (int j = 0; j < number_character; j++)             //为指针数组的每个元素分配一个数组
			temp[j] = new int[str_number];

		for (int k = 0; k < number_character; k++)          //寻找每个字符后继
		{
			for (int m = 0; m < str_number; m++)
			{
				int flag = 0;//	标记匹配到的位置
				int n = 0;
				for (n = m + 1; n < str_number; n++)
				{
					if (T[i][n] == character[k])
					{
						flag = n;
						break;
					}						
				}
				if (n+1 > str_number)      //str加了“=”
				{
					temp[k][m] = NOSUCCESSOR;
				}				
				else
				{
					temp[k][m] = flag;
				}					
			}			
		}
		st.push_back(temp);
		T[i].erase(0, 1);

	}
}
ST::~ST()
{
	//消除内存vector中new的空间
	for (int i = 0; i < st.size(); i++)
	{
		int **temp = st[i];
		int number = T[i].size();
		for (int j = 0; j<number_character; j++)
		{
			delete[number]temp[j];
			temp[j] = NULL;
		}
		delete[number_character]temp;
		temp = NULL;
	}
	st.clear();


	if (character != nullptr)
		delete[]character;
	if (T != nullptr)
		delete[]T;
}