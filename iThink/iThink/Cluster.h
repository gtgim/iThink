#pragma once

#include "ListBaseQueue.h"
#include "Unit.h"

class CCluster
{
public:
	CCluster(void);
	~CCluster(void);
private:
	CListBaseQueue m_QueueExcitement;
	CListBaseQueue m_QueuePush;
public:
	CListBaseQueue* GetQueueExcitement(void);
	CListBaseQueue* GetQueuePush(void);
private:
	int m_CountIndexQueuePush;
	CUnit* m_DynamicArrayPush;
public:
	void SetCountIndexQueuePush(int countIndexQueuePush);
	void NewDynamicArrayPush(void);
	void DeleteDynamicArrayPush(void);
	void SetDynamicArrayPush(void);
private:
	CUnit m_UnitClassOne;
	CUnit m_UnitClassTwo;
public:
	void SetUnitClass(void);
private:
	CListBaseQueue m_QueueDistanceClassOne;
	CListBaseQueue m_QueueDistanceClassTwo;
public:
	void EuclideanDistance(void);
private:
	CListBaseQueue m_QueueGroupClassOne;
	CListBaseQueue m_QueueGroupClassTwo;
public:
	void SetQueueGroupClass(void);
};

