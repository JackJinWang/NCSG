#include"NCSG.h"
#include<iostream>
#include<limits.h>
using namespace std;
const int NOSUCCESSOR = INT_MAX;
NCSG::NCSG(int dimension, int number_character, vector<int **>st)
{
	this->dimension = dimension;
	this->number_character = number_character;
	this->st = st;
}
void NCSG::getDominant()
{
//	vector<int *> k_th_dominant;
//	int index = 0;            //DM表序号
	int *source_point = new int[dimension];
	for (int i = 0; i < dimension; i++)
	{
		source_point[i] = 0;
	}
	DM dm(index,source_point,dimension);
	this->V.push_back(dm);                            //加入到边集合
//	k_th_dominant.push_back(source_point);             //加入（0，。。。0）点
//	dominants.push_back(k_th_dominant);

//	st_temp[i][j][k] i表示第几个序列 j表示序列第几个字符 k表示序列的第几列
//	vector<int *> first_th_dominant;
	for (int i = 0; i < number_character; i++)
	{
		int *point = new int[dimension];
		for (int j = 0; j < dimension; j++)
			point[j] = st[j][i][0]; 
		index++;
		
		DM dm(index, point, dimension);
		this->V.push_back(dm);                            //加入到边集合
		getAllDominant(point);
//		first_th_dominant.push_back(point);	
	}
//	dominants.push_back(first_th_dominant);
}
void NCSG::getAllDominant(int *inpoint)
{
	if (!haveSuccessor(inpoint))   //无后继终止递归
		return;
	for (int i = 0; i < number_character; i++)
	{
		int *point = new int[dimension];
		
		for (int j = 0; j < dimension; j++)
		{
			int number = inpoint[j];
			point[j] = st[j][i][number];
		}
		if (!isInDM(point)&&isSuccessor(point))
		{
			index++;
			DM dm(index, point, dimension);
			this->V.push_back(dm);		//加入到边集合
//			cout <<"输出位置"<< index<<endl;
			getAllDominant(point);       //递归求解
		}
	}
}
void NCSG::buildNCSG()
{
	ncsgindex = 0;
	
	int size = V.size()+1;  //加入汇点（无穷点）
	number_dominant = size;
	E = new int*[size];
	for (int i = 0; i < size; i++)
		E[i] = new int[size];
	//初始化E矩阵
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			E[i][j] = 0;
		}
	}
	//构造d0与d1；
	int *source_point = new int[dimension];
	for (int i = 0; i < dimension; i++)
	{
		source_point[i] = 0;
	}
	V.clear();
	DM dm(ncsgindex, source_point, dimension);
	this->V.push_back(dm);                            //加入到边集合
	for (int i = 0; i < number_character; i++)
	{
		int *point = new int[dimension];
		for (int j = 0; j < dimension; j++)
			point[j] = st[j][i][0];
		ncsgindex++;
		E[0][ncsgindex] = 1;
		DM dm(ncsgindex, point, dimension);
		this->V.push_back(dm);
		buildAllNCSG(point, ncsgindex);
		//		first_th_dominant.push_back(point);	
	}
	
}
void NCSG::buildAllNCSG(int *inpoint,int inindex)
{
	if (!haveSuccessor(inpoint) && isSuccessor(inpoint))   //无后继终止递归,//如果不存在后嵇点与汇点相连
	{
		E[inindex][number_dominant - 1] = 1;
		return;
	}
	
	for (int i = 0; i < number_character; i++)
	{
		int *point = new int[dimension];

		for (int j = 0; j < dimension; j++)
		{
			int number = inpoint[j];
			point[j] = st[j][i][number];
		}

		//如果不存在加入点
		if (!isInDM(point) && isSuccessor(point))
		{
			
			ncsgindex++;
			E[inindex][ncsgindex] = 1;
			DM dm(ncsgindex, point, dimension);
			this->V.push_back(dm);		//加入到边集合
			buildAllNCSG(point, ncsgindex);       //递归求解
		}else if (isInDM(point) && isSuccessor(point))
		{

			//如果存在边相连
			/*
			cout << "******************" << endl;
			cout << "已存在" << endl;
			cout << "前驱点" << endl;
			for (int j = 0; j < dimension; j++)
			{
				cout<<inpoint[j]<<" ";
				
			}
			cout << endl;
			cout << "后继点" << endl;
			for (int j = 0; j < dimension; j++)
			{
				cout << point[j] << " ";

			}
			this->show();
			cout <<"******************"<<endl;
			*/
			//找到存在点的序号
			int exitnumber = getPointIndex(point);
			E[inindex][exitnumber] = 1;
	//		buildAllNCSG(point, ncsgindex);       //递归求解
		}
		

	}
}
void NCSG::forwardTopSort()
{
	int levelnum = -1;
	//初始化矩阵
	vector<int> dominatindex; //将dominant序列放入
	k_level_forward = new int[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		dominatindex.push_back(i);
	}
	int **tempE;
	tempE = new int*[number_dominant];
	 topsort = new int*[number_dominant];
	 for (int i = 0; i < number_dominant; i++)
	 {
		 topsort[i] = new int[number_dominant];
		 tempE[i] = new int[number_dominant];
	 }
		 
	 for (int i = 0; i < number_dominant; i++)
	 {
		 for (int j = 0; j < number_dominant; j++)
		 {
			 tempE[i][j] = E[i][j];
			 topsort[i][j] = E[i][j];
		 }
	 }
	 //不断删除入度为0的点
	 //计算入度放入indegeree
	 while (dominatindex.size() > 0)
	 {
		 vector<int> k_level; //存放index;
		 //计算入度
		 int flag = 0; //退出时删除点
		 for (int i = 0; i < dominatindex.size(); i++)
		 {
			 
			 int count = dominatindex[i];
			 int sum = 0;
			 //计算入度
			 for (int j = 0; j < number_dominant; j++)
			 {
				 sum = sum + tempE[j][count];
			 }
			
			 //入度为0则存入级别
			 if (sum == 0)
			 {
				 k_level_forward[count] = levelnum + 1;
				 k_level.push_back(count);
			 }

			
		 }
		 k_dominants.push_back(k_level);
		 levelnum++;
		
		 //删除入度为0点
		 for (int i = 0; i < k_level.size(); i++)
		 {
			 int count = k_level[i];
			 vector <int>::iterator Iter;
			 Iter = dominatindex.begin();
			 while (Iter != dominatindex.end())
			 {
				 if (count == *Iter)
				 {
					 dominatindex.erase(Iter);
					 Iter = dominatindex.begin();
					 //如果删除点与前向点有关系则需构建图
					 
					 vector<int> record;
					 for (int i = 0; i < number_dominant; i++)
					 {
						 if (E[i][count] == 1)
							 record.push_back(i);
					 }
					 for (int i = 0; i < record.size(); i++)
					 {
						 for (int j = i + 1; j < record.size(); j++)
						 {
							 int number1 = record[i];
							 int number2 = record[j];
							 if (E[number1][number2] == 1)
							 {
								 topsort[number1][count] = 0;
							 }
							 if (E[number2][number1] == 1)
							 {
								 topsort[number2][count] = 0;
							 }
						 }
					 }
					 break;
				 }
				 else
					 ++Iter;
			 }
			 //更改矩阵删除边
			 for (int j = 0; j < number_dominant; j++)
			 {
				 tempE[count][j] = 0;
			 }
		 }
		
		
		 
	 }
	 MAX_LEVEL = levelnum;
	 //跨级别边删除
	 for (int i = 0; i < number_dominant; i++)
	 {
		 for (int j = 0; j < number_dominant; j++)
		 {
			 if ((topsort[i][j] == 1) && (j != number_dominant - 1) && ((k_level_forward[j] - k_level_forward[i])>1))
				 topsort[i][j] = 0;
		 }
	 }
	 int number = 0;
	 for (int i = 0; i < number_dominant; i++)
	 {
		 number = 0;
		 for (int j = 0; j < number_dominant; j++)
		 {
			 if (topsort[i][j] == 1)
				 break;
			 else
				 number++;
		 }
		 if (number == number_dominant)
		 for (int j = 0; j < number_dominant; j++)
		 {
			 topsort[i][j] = E[i][j];
		 }
	 }
	 for (int i = 0; i < number_dominant; i++)
	 {
		 delete[] tempE[i];
	 }
	 delete[] tempE;
	 

}
void NCSG::backTopSort()
{
	backsort = new int*[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		backsort[i] = new int[number_dominant];
	}
	//拓扑矩阵赋值
	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < number_dominant; j++)
		{
			backsort[i][j] = topsort[i][j];
		}
	}
	//拓扑矩阵反向求路径
	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int temp = backsort[i][j];
			backsort[i][j] = backsort[j][i];
			backsort[j][i] = temp;
		}
	}
	//后向拓扑排序
	int levelnum = -1;
	k_level_backward = new int[number_dominant];
	//初始化矩阵
	vector<int> dominatindex; //将dominant序列放入
	for (int i = 0; i < number_dominant; i++)
	{
		dominatindex.push_back(i);
	}
	int **tempE;
	tempE = new int*[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		tempE[i] = new int[number_dominant];
	}

	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < number_dominant; j++)
		{
			tempE[i][j] = backsort[i][j];
		}
	}
	//不断删除入度为0的点
	//计算入度放入indegeree
	while (dominatindex.size() > 0)
	{
		vector<int> k_level; //存放index;
		//计算入度
		int flag = 0; //退出时删除点
		for (int i = 0; i < dominatindex.size(); i++)
		{

			int count = dominatindex[i];
			int sum = 0;
			//计算入度
			for (int j = 0; j < number_dominant; j++)
			{
				sum = sum + tempE[j][count];
			}

			//入度为0则存入级别
			if (sum == 0)
			{
				k_level.push_back(count);
				k_level_backward[count] = levelnum + 1;
			}
				

		}
		k_dominants_back.push_back(k_level);
		levelnum++;

		//删除入度为0点
		for (int i = 0; i < k_level.size(); i++)
		{
			int count = k_level[i];
			vector <int>::iterator Iter;
			Iter = dominatindex.begin();
			while (Iter != dominatindex.end())
			{
				if (count == *Iter)
				{
					dominatindex.erase(Iter);
					Iter = dominatindex.begin();
					//如果删除点与前向点有关系则需构建图

					vector<int> record;
					for (int i = 0; i < number_dominant; i++)
					{
						if (E[i][count] == 1)
							record.push_back(i);
					}
					for (int i = 0; i < record.size(); i++)
					{
						for (int j = i + 1; j < record.size(); j++)
						{
							int number1 = record[i];
							int number2 = record[j];
							if (E[number1][number2] == 1)
							{
								topsort[number1][count] = 0;
							}
							if (E[number2][number1] == 1)
							{
								topsort[number2][count] = 0;
							}
						}
					}
					break;
				}
				else
					++Iter;
			}
			//更改矩阵删除边
			for (int j = 0; j < number_dominant; j++)
			{
				tempE[count][j] = 0;
			}
		}



	}
	//判断前向后巷相加不为最大层级删除
	for (int i = 0; i < number_dominant; i++)
	{
		if ((k_level_backward[i] + k_level_forward[i]) != MAX_LEVEL)
		{
			delete_point_back.push_back(i);
		}
	}
	//构造后巷图
	for (int i = 0; i < delete_point_back.size(); i++)
	{
		for (int j = 0; j < number_dominant; j++)
		{
			backsort[j][delete_point_back[i]] = 0;
			backsort[delete_point_back[i]][j] = 0;
		}
	}
	for (int i = 0; i < number_dominant; i++)
	{
		delete[] tempE[i];
	}
	delete[] tempE;


}
void NCSG::getPath()
{

	//拓扑矩阵反向求路径
	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int temp = backsort[i][j];
			backsort[i][j] = backsort[j][i];
			backsort[j][i] = temp;
		}
	}
	state_isstack = new int[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		state_isstack[i] = 0;
	}
//	state_isstack[0] = 1;
//	stack.push_back(0);
//	searchPath(0);
	search();
}
void NCSG::setString(string *T,int number)
{
	this->T = new string[number];
	for (int i = 0; i < number; i++)
	{
		this->T[i] = T[i];
	}
}
void NCSG::search()
{
	int **tempE;
	tempE = new int*[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		tempE[i] = new int[number_dominant];
	}
	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < number_dominant; j++)
		{
			tempE[i][j] = 0;
		}
	}

	stack.push_back(0);
	state_isstack[0] = 1;
	while(!stack.empty())
	{
		int elem = stack[stack.size()-1];//获得栈顶元素
		if (elem == number_dominant - 1)//找到了一条路径
		{
		//	path = Traverse(mystack);
		//	if (stack.size() == MAX_LEVEL + 1)
		//	{
				for (int i = 0; i < stack.size(); i++)
				{
					singlePath.push_back(stack[i]);
					if (stack[i] == 0)
						cout << 0 << "->";
					else if (stack[i] == number_dominant - 1)
						cout << "终点" << "->";
					else
					{
						int show_number = (V[stack[i]].getPoint())[0];
						char show = T[0][show_number - 1];
						cout << show << "(" << stack[i] << ")" << "->";
					}

				}
				cout << endl;
				allPath.push_back(singlePath);
		//	}
			state_isstack[elem] = 0;
			for (int i = 0; i < number_dominant; i++)
			{
				if ((backsort[elem][i] == 1) && (state_isstack[i] == 0))
				{
					tempE[elem][i] = 0;
				}
				if ((backsort[i][elem] == 1) && (state_isstack[i] == 0))
				{
					tempE[i][elem] = 0;
				}
			}
	//		UpdateArcStatus();//更新ArcStatus[][]，使得所有两个端点都不在栈内的边的状态为0
			stack.pop_back();//移除栈顶元素
		}
		else
		{
			int i = 0;
			for (; i < number_dominant; i++)
			{
				if( (state_isstack[i] == 0) && (tempE[elem][i] == 0 )&& (backsort[elem][i]==1))
				{
					state_isstack[i] = 1;
					tempE[elem][i] = 1;
					stack.push_back(i);//入栈
					break;
				}

			}
			if (i == number_dominant)//该节点没有符合要求的后续节点
			{
				state_isstack[elem] = 0;
				for (int i = 0; i < number_dominant; i++)
				{
					if ((backsort[elem][i] == 1) && (state_isstack[i] == 0))
					{
						tempE[elem][i] = 0;
					}
					if ((backsort[i][elem] == 1) && (state_isstack[i] == 0))
					{
						tempE[i][elem] = 0;
					}
				}
			//	UpdateArcStaus();////更新ArcStatus[][]，使得所有两个端点都不在栈内的边的状为0
				stack.pop_back();//出栈

			}


		}
	}
	for (int i = 0; i < number_dominant; i++)
	{
		delete[] tempE[i];
	}
	delete[] tempE;
}
void NCSG::searchPath(int precursor)
{
	if (stack.size() == 0)
		return;
	if (precursor == number_dominant - 1)
	{
		if (stack[0] == 0)
		{
			for (int i = 0; i < stack.size(); i++)
			{
				if (stack[i] ==0)
					cout << 0 << "->";
				else if (stack[i]==number_dominant -1 )
					cout << "终点" << "->";
				else
				{
					int show_number = (V[stack[i]].getPoint())[0];
					char show = T[0][show_number - 1];
					cout << show << "->";
				}

			}
			cout << endl;
		}

		state_isstack[stack[stack.size()-1]] = 0;
		int top_first = stack[stack.size() - 1];
		stack.pop_back();	
		while (stack.size()>0)
		{
			int top = stack[stack.size()-1];
			int flag = 0;
			for (int i = 0; i < number_dominant; i++)
			{
				if ((backsort[top][i] == 1) && (i != top_first) && (state_isstack[i] == 0))
				{
					stack.push_back(i);
					state_isstack[i] = 1;
					searchPath(i);
					break;
				}
				flag++;
			}
			if (flag == number_dominant)
			{
				top_first = stack[stack.size() - 1];
				if (stack.size() > 1)
				{

					int top_second = stack[stack.size() - 2];
					int i;
					for (i = 0; i < number_dominant; i++)
					{
						if ((backsort[top_second][i] == 1) && (state_isstack[i] == 0) && (i != top_first))
						{
							state_isstack[top_first] = 1;
							break;
						}
					}
					if (i == number_dominant)
						state_isstack[top] = 0;
				}
				stack.pop_back();
			}
				
		}		
		return;
	}
	for (int i = 0; i < number_dominant; i++)
	{
		if ((backsort[precursor][i] == 1) && (state_isstack[i])==0)
		{
			state_isstack[i] = 1;
			stack.push_back(i);
			searchPath(i);
		}
	}
}
void NCSG::getAllPath(int precursor)
{
	vector<int> path;
	int **tempBcak;//用以标记走过的路径
	tempBcak = new int*[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		tempBcak[i] = new int[number_dominant];
	}
	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < number_dominant; j++)
		{
			tempBcak[i][j] = 0;
		}
	}
	//拓扑矩阵反向求路径
	for (int i = 0; i < number_dominant; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int temp = backsort[i][j];
			backsort[i][j] = backsort[j][i];
			backsort[j][i] = temp;
		}
	}
	int *outdegree; //计算出度表
	outdegree = new int[number_dominant];
	for (int i = 0; i < number_dominant; i++)
	{
		int sum = 0;
		for (int j = 0; j < number_dominant; j++)
		{
			sum = sum + backsort[i][j];
			outdegree[i] = sum;
		}
	}
	int flag = 0;

	for (int j = 0; j < number_dominant; j++)
	{
		if ((backsort[precursor][j] == 1) && (tempBcak[precursor][j])==0)
		{

			path.push_back(j);
			if (outdegree[precursor]>1)
			{
				tempBcak[precursor][j] == 1;				
			}
			outdegree[precursor] = outdegree[precursor] - 1;
			getAllPath(j);
		}
		else
			flag++;
	}
	if (flag == number_dominant)
	{
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << "->";
		}
		cout << endl;
		while (path.size()>0)
		{
			
		}
		return;
		
			

	}
	
}
int NCSG::getPointIndex(int *point)
{
	int size = V.size();
	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		flag = 0;
		for (int j = 0; j < dimension; j++)
		{
			if ((V[i].getPoint())[j] == point[j])
				flag++;
		}
		if (flag == dimension)
		{
			/*
			cout << V[i].getIndex()<<":"<<endl;
			for (int f = 0; f < dimension; f++)
			{
				cout << (V[i].getPoint())[f] << " ";
			}
			cout << endl;
			cout  << "传入点:" << endl;
			for (int f = 0; f < dimension; f++)
			{
				cout << point[f] << " ";
			}
			cout << endl;
			*/
			return V[i].getIndex();
		}
			
	}
	return INT_MAX;
	
}
bool NCSG::isSuccessor(int *point)
{
	int flag = 0;
	for (int i = 0; i < dimension; i++)
	{
		if (point[i] == NOSUCCESSOR)
			return false;
	}
	return true;
}
//判断是否有后继点
bool NCSG::haveSuccessor(int *point)
{
//	vector<int*> successor;
	int flag = 0;
	bool remember;//是否是后继点 是存储 不是
	for (int i = 0; i < number_character; i++)
	{
		remember = true;
		int *temp_point;
	//	cout << "i:" << i << endl;
		for (int j = 0; j < dimension; j++)
		{
			temp_point = new int[dimension];
			int number = point[j];
			temp_point[j] = st[j][i][number];			
			if (temp_point[j] == NOSUCCESSOR)
			{
				remember = false;
				flag++;
				break;
			}
		//	cout << temp_point[j] << " ";
		}
		cout << endl;
//		if (remember)
//		successor.push_back(temp_point);
	}
	if (flag == number_character)
		return false;
	else
		return true;

}
bool NCSG::isInDM(int *point)
{
	DM temp_dm;
	int flag = 0;
	for (int i = 0; i < V.size(); i++)
	{
		flag = 0;
		temp_dm = V[i];
		for (int j = 0; j < dimension; j++)
		{
			if (point[j] == (temp_dm.getPoint())[j])
				flag++;
		}
		if (flag == dimension)
			return true;
	}
	return false;
}
void NCSG::show()
{
	cout << "********************分层结果****************" << endl;
	int number = k_dominants.size();
	for (int i = 0; i < number; i++)
	{
		cout << i << "-th" << endl;
		int queuenumber = k_dominants[i].size();
		for (int j = 0; j < queuenumber; j++)
		{

				cout << k_dominants[i][j]<< " ";
			    cout << endl;
		}
	}
	cout << "********************DM索引表结果****************" << endl;
	cout << "DM" << endl;
	for (int i = 0; i < V.size(); i++)
	{
		cout << V[i].getIndex()<<",";
		for (int j = 0; j < dimension; j++)
		{
			cout << (V[i].getPoint())[j] << " ";
		}
		cout << endl;
	}
	cout << "********************NCSG图****************" << endl;
	cout << "NCSG" << endl;
	int size = V.size() + 1;  //加入汇点（无穷点）
	//初始化E矩阵
	cout << 0 << ":";
	for (int j = 0; j < size; j++)
	{
		
		if (j>10)
			cout << j<<"  ";
		else
			cout << j << "   ";
	}
	cout << endl;
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		cout << i << ":";

		for (int j = 0; j < size; j++)
		{
			sum = sum + E[i][j];
			cout <<E[i][j] <<"   ";
		}
		cout << endl;
	}
	cout << "边的总数为" << sum<<endl;
	sum = 0;
	cout << "********************前向拓扑排序结果及图****************" << endl;
	cout << "forwordsortNCSG" << endl;
	//初始化E矩阵
	cout << 0 << ":";
	for (int j = 0; j < size; j++)
	{

		if (j>10)
			cout << j << "  ";
		else
			cout << j << "   ";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i << ":";

		for (int j = 0; j < size; j++)
		{
			sum = sum + topsort[i][j];
			cout << topsort[i][j] << "   ";
		}
		cout << endl;
	}
	cout << "边的总数为" << sum << endl;
	sum = 0;
	cout << "********************后向拓扑排序结果及图****************" << endl;
	cout << "backsortNCSG" << endl;
	//初始化E矩阵
	cout << 0 << ":";
	int flag = 0;
	for (int j = 0; j < size; j++)
	{
		flag = 0;
		for (int i = 0; i < delete_point_back.size(); i++)
		{
			if (delete_point_back[i] == j)
				flag = 1;

		}
		if (flag == 1)
			continue;
		if (j>10)
			cout << j << "  ";
		else
			cout << j << "   ";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		flag = 0;
		for (int k = 0; k < delete_point_back.size(); k++)
		{
			if (delete_point_back[k] == i)
				flag = 1;

		}
		if (flag == 1)
			continue;
		cout << i << ":";

		for (int j = 0; j < size; j++)
		{
			flag = 0;
			for (int k = 0; k < delete_point_back.size(); k++)
			{
				if (delete_point_back[k] == j)
					flag = 1;

			}
			if (flag == 1)
				continue;
			sum = sum + backsort[i][j];

			cout << backsort[i][j] << "   ";
		}
		cout << endl;
	}
	cout << "边的总数为" << sum << endl;
	cout << "********************前向拓扑排序每点的级别****************" << endl;
	cout << "前向级别" << endl;
	for (int i = 0; i < number_dominant; i++)
	{
		cout << k_level_forward[i]<<" ";
	}
	cout << endl;
	cout << "********************后向拓扑排序每点级别****************" << endl;
	cout << "后向级别" << endl;
	for (int i = 0; i < number_dominant; i++)
	{
		cout << k_level_backward[i] << " ";
	}
	cout << endl;
	cout << "********************后向拓扑排序删除的点****************" << endl;
	cout << "后序删除的点" << endl;
	for (int i = 0; i < delete_point_back.size(); i++)
	{
		cout << delete_point_back[i] << " ";
	}
}
NCSG::~NCSG()
{
	if (T!=nullptr)
	{
		delete[]T;
	}	
	if (k_level_forward != nullptr)
	{
		delete[]T;
	}
	if (k_level_backward != nullptr)
	{
		delete[]T;
	}
	if (state_isstack != nullptr)
	{
		delete[]state_isstack;
	}
	if (topsort != nullptr)
	{
		for (int i = 0; i < number_dominant; i++)
		{
			delete[] topsort[i];
		}
		delete[] topsort;
	}
	if (E != nullptr)
	{
		for (int i = 0; i < number_dominant; i++)
		{
			delete[] E[i];
		}
		delete[] E;
	}
	if (backsort != nullptr)
	{
		for (int i = 0; i < number_dominant; i++)
		{
			delete[] backsort[i];
		}
		delete[] backsort;
	}

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


}
