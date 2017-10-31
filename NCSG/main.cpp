#include<iostream>
#include<time.h>
#include"ST.h"
#include"NCSG.h"
using namespace std;
int main()
{



	char  *character;        //字母表
	int number_character;    //字母數量
	int number_T;
	string *T;              //輸入字符序列
	cout << "字母表數量";
	cin >> number_character;
	cout << endl;
	cout << "輸入字母";
	character = new char[number_character];
	for (int i = 0; i < number_character; i++)
	{
		cin >> character[i];
	}
	cout << "序列數量";
	cin >> number_T;
	cout << endl;
	cout << "輸入序列";
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
	cout <<"是否存在"<< ncsg.isInDM(point)<<endl;
	*/
	cout << "********************后继表****************" << endl;
	st.show();
	ncsg.show();	
cout << endl;
	cout << "********************构建结束开始寻径****************" << endl;
	ncsg.getPath();
	system("pause");
	return 0;
}