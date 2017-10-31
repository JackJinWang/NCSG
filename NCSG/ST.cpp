#include"ST.h"
#include<limits.h>
const int NOSUCCESSOR = INT_MAX;
ST::ST(char *character, int number_character, string *T, int number_T)
{
	this->number_T = number_T;
	this->number_character = number_character;
	this->T = T;
	//���¿����ڴ�ռ��ֹҰָ��
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
		str_number = T[i].size();              //��ȡÿ���ַ�������(��̱���Ҫ����һλ)
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
//������̱�
void ST::buildST()
{
	int str_number = 0;   //��ǰ�ַ�������
	
	for (int i = 0; i < number_T; i++)
	{
		T[i].insert(0, "=");                   //ÿ���ַ���ǰ����  
		str_number = T[i].size();              //��ȡÿ���ַ�������(��̱���Ҫ����һλ)
		int **temp = new int*[number_character];                                  
		for (int j = 0; j < number_character; j++)             //Ϊָ�������ÿ��Ԫ�ط���һ������
			temp[j] = new int[str_number];

		for (int k = 0; k < number_character; k++)          //Ѱ��ÿ���ַ����
		{
			for (int m = 0; m < str_number; m++)
			{
				int flag = 0;//	���ƥ�䵽��λ��
				int n = 0;
				for (n = m + 1; n < str_number; n++)
				{
					if (T[i][n] == character[k])
					{
						flag = n;
						break;
					}						
				}
				if (n+1 > str_number)      //str���ˡ�=��
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
	//�����ڴ�vector��new�Ŀռ�
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