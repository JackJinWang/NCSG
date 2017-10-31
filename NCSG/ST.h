#pragma once
#include<string>
#include<vector>
#include<iostream>
using  namespace std;
class ST{
private:
	char  *character;        //字母表
	int number_character;    //字母數量
	string *T;              //輸入字符序列
	int number_T;           //輸入字符序列數量
	vector<int **>st;               //後繼表構造
public:
	ST(){};
	ST(char *character, int number_character, string *T, int number_T); //构造函数
	~ST();
	ST(const ST &st);             //拷贝构造函数
	void setCharacter(char * character);
	void setNumberCharacter(int number);
	void setT(string *T);
	void setNumberT(int number);

	char* getCharacter();
	int getNumberCharacter();
	string* getT();
	int getNumberT();
	vector<int **> getST();

	void buildST();   //构建后继表
	void show();

};