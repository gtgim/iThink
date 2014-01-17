#pragma once

#include "Unit.h"

typedef CUnit Data;

class CNode
{
private:
	Data data;
	CNode* next;
public:
	void SetData(Data data);
	void SetNext(CNode* pNext);
	Data GetData(void);
	CNode* GetNext(void);
};


class CListBaseQueue
{
public:
	CListBaseQueue(void);
	~CListBaseQueue(void);
private:
	CNode* front;
	CNode* rear;
public:
	void QueueInit(CListBaseQueue* pq);
	int QIsEmpty(CListBaseQueue* pq);
	void Enqueue(CListBaseQueue* pq, Data data);
	Data Dequeue(CListBaseQueue* pq);
	Data QPeek(CListBaseQueue* pq);
};

