#pragma once 
#include"DM.h"
#include<vector>
using namespace std;
class NCSG{
private:
	int index;    //dom序号
	int ncsgindex;
	string *T;
	int number_T;
	int dimension; //顶点维度
	int number_character;//字母表数量
	vector<DM> V;//顶点集合      空间还未释放记住
	int number_dominant;  //dominant数量（包含汇点）
//	DM *V;      //頂點集合
	int number_v; //頂點數目
	int number_e; //邊數目
	int **E;    //邊集合
	int **topsort; //前向拓扑排序结果
	int **backsort; //后向排序结果
	int *k_level_forward;
	int *k_level_backward;
	int MAX_LEVEL; //最大层级

	vector<int> delete_point_back;//后向排序删除的点
	vector<vector<int>> k_dominants;   //用于存放支配点队列
	vector<vector<int>>k_dominants_back;//用于存放后序序列
	vector<int **>st;               //後繼表構造

	vector<int>stack;     //栈

	vector<int> singlePath;
	vector<vector<int>>allPath;
	int *state_isstack;
public:
	void setString(string *T,int number);
	NCSG(int dimension, int number_character, vector<int **>st);
	~NCSG();
	void getDominant();//求得1级支配点
	void getAllDominant(int *point);//获取剩余支配点
	void getNCSG();
	void search();
	void buildNCSG();    //构建NCSG图
	void buildAllNCSG(int *point,int index); //构建所有NCSG图(递归)
	void forwardTopSort();//前向拓扑排序,分层
	void backTopSort();//后向排序删除非关键点
	void getPath();
	void searchPath(int precursor);
	void getAllPath(int precursor);//递归或获取所有路径
	void show();
	int getPointIndex(int *point);        //获取点集合中point序号
	bool haveSuccessor(int *point);      //判断点是否还有后继
	bool isInDM(int *point);          //判断点是否存在于DM
	bool isSuccessor(int *point);      //判断点是否为后嵇点
	
};