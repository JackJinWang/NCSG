#include<iostream>
#include<time.h>
#include"ST.h"
#include"NCSG.h"
using namespace std;
int main()
{



	char  *character;        //��ĸ��
	int number_character;    //��ĸ����
	int number_T;
	string *T;              //ݔ���ַ�����
	cout << "��ĸ�픵��";
	cin >> number_character;
	cout << endl;
	cout << "ݔ����ĸ";
	character = new char[number_character];
	for (int i = 0; i < number_character; i++)
	{
		cin >> character[i];
	}
	cout << "���Д���";
	cin >> number_T;
	cout << endl;
	cout << "ݔ������";
	T = new string[number_T];
	for (int i = 0; i < number_T; i++)
	{
		cin >> T[i];
	}
	ST st(character, number_character, T, number_T);
	st.buildST();

	NCSG ncsg(number_T,number_character,st.getST());
	ncsg.setString(T,number_T);
	ncsg.getDominant();
	ncsg.buildNCSG();
	ncsg.forwardTopSort();
	ncsg.backTopSort();
	
	/*
	int *point = new int[number_T];
	point[0] = 6;
	point[1] = 7;
	point[2] = 6;
	cout<<ncsg.haveSuccessor(point);
	cout << endl;
	cout <<"�Ƿ����"<< ncsg.isInDM(point)<<endl;
	*/
	cout << "********************��̱�****************" << endl;
	st.show();
	ncsg.show();	
cout << endl;
	cout << "********************����������ʼѰ��****************" << endl;
	ncsg.getPath();
	system("pause");
	return 0;
}