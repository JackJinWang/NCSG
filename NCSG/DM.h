#pragma once
class DM{
private:
	int index;
	int *point;
	int number_T;
public:
	DM(int index, int *point,int number_T);          //���캯��
	DM();
	DM(const DM &dm);
	int getIndex();
	int * getPoint();
	~DM();
	void setIndex(int index);
	void setPoint(int *point,int number_T);
};