#pragma once
#include<string>
#include<vector>
#include<iostream>
using  namespace std;
class ST{
private:
	char  *character;        //��ĸ��
	int number_character;    //��ĸ����
	string *T;              //ݔ���ַ�����
	int number_T;           //ݔ���ַ����Д���
	vector<int **>st;               //���^�혋��
public:
	ST(){};
	ST(char *character, int number_character, string *T, int number_T); //���캯��
	~ST();
	ST(const ST &st);             //�������캯��
	void setCharacter(char * character);
	void setNumberCharacter(int number);
	void setT(string *T);
	void setNumberT(int number);

	char* getCharacter();
	int getNumberCharacter();
	string* getT();
	int getNumberT();
	vector<int **> getST();

	void buildST();   //������̱�
	void show();

};