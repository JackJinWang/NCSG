#include"DM.h"
DM::DM(int index,int *point,int number_T)
{
	this->index = index;
	this->number_T = number_T;
	this->point = new int[number_T];
	for (int i = 0; i < number_T; i++)
	{
		this->point[i] = point[i];
	}
	
}
DM::DM()
{
	this->index = 0;
	this->point = nullptr;
}
DM::DM(const DM &dm)
{
	this->index = dm.index;
	this->point = dm.point;
	this->number_T = dm.number_T;
}
void DM::setIndex(int index)
{
	this->index = index;
}
void DM::setPoint(int *point,int number_T)
{
	this->number_T = number_T;
	this->point = new int[number_T];
	for (int i = 0; i < number_T; i++)
	{
		this->point[i] = point[i];
	}
}
int DM::getIndex()
{
	return this->index;
}
int *DM::getPoint()
{
	return this->point;
}
DM::~DM()
{
//	if (point != nullptr)
//		delete []point;
}