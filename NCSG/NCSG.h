#pragma once 
#include"DM.h"
#include<vector>
using namespace std;
class NCSG{
private:
	int index;    //dom���
	int ncsgindex;
	string *T;
	int number_T;
	int dimension; //����ά��
	int number_character;//��ĸ������
	vector<DM> V;//���㼯��      �ռ仹δ�ͷż�ס
	int number_dominant;  //dominant������������㣩
//	DM *V;      //��c����
	int number_v; //��c��Ŀ
	int number_e; //߅��Ŀ
	int **E;    //߅����
	int **topsort; //ǰ������������
	int **backsort; //����������
	int *k_level_forward;
	int *k_level_backward;
	int MAX_LEVEL; //���㼶

	vector<int> delete_point_back;//��������ɾ���ĵ�
	vector<vector<int>> k_dominants;   //���ڴ��֧������
	vector<vector<int>>k_dominants_back;//���ڴ�ź�������
	vector<int **>st;               //���^�혋��

	vector<int>stack;     //ջ

	vector<int> singlePath;
	vector<vector<int>>allPath;
	int *state_isstack;
public:
	void setString(string *T,int number);
	NCSG(int dimension, int number_character, vector<int **>st);
	~NCSG();
	void getDominant();//���1��֧���
	void getAllDominant(int *point);//��ȡʣ��֧���
	void getNCSG();
	void search();
	void buildNCSG();    //����NCSGͼ
	void buildAllNCSG(int *point,int index); //��������NCSGͼ(�ݹ�)
	void forwardTopSort();//ǰ����������,�ֲ�
	void backTopSort();//��������ɾ���ǹؼ���
	void getPath();
	void searchPath(int precursor);
	void getAllPath(int precursor);//�ݹ���ȡ����·��
	void show();
	int getPointIndex(int *point);        //��ȡ�㼯����point���
	bool haveSuccessor(int *point);      //�жϵ��Ƿ��к��
	bool isInDM(int *point);          //�жϵ��Ƿ������DM
	bool isSuccessor(int *point);      //�жϵ��Ƿ�Ϊ������
	
};