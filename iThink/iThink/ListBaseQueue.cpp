#include "StdAfx.h"
#include "ListBaseQueue.h"

void CNode::SetData(Data data)
{
	this->data = data;
}

void CNode::SetNext(CNode* pNext)
{
	this->next = pNext;
}

Data CNode::GetData(void)
{
	return data;
}

CNode* CNode::GetNext(void)
{
	return next;
}


CListBaseQueue::CListBaseQueue(void)
	: front(NULL)
	, rear(NULL)
{
}


CListBaseQueue::~CListBaseQueue(void)
{
}


void CListBaseQueue::QueueInit(CListBaseQueue* pq)
{
	pq->front = NULL;
	pq->rear = NULL;
}


int CListBaseQueue::QIsEmpty(CListBaseQueue* pq)
{
	if(pq->front == NULL)
		return TRUE;
	else
		return FALSE;
}


void CListBaseQueue::Enqueue(CListBaseQueue* pq, Data data)
{
	//Node * newNode = (Node*)malloc(sizeof(Node));
	CNode * newNode = new CNode;
	//newNode->next = NULL;
	newNode->SetNext(NULL);
	//newNode->data = data;
	newNode->SetData(data);

	if(QIsEmpty(pq))
	{
		pq->front = newNode;
		pq->rear = newNode;
	}
	else
	{
		//pq->rear->next = newNode;
		pq->rear->SetNext(newNode);
		pq->rear = newNode;
	}
}


Data CListBaseQueue::Dequeue(CListBaseQueue* pq)
{
	//Node * delNode;
	CNode * delNode;
	Data retData;

	if(QIsEmpty(pq))
	{
		//printf("Queue Memory Error!");
		AfxMessageBox(_T("Queue Memory Error!"));
		exit(-1);
	}

	delNode = pq->front;
	//retData = delNode->data;
	retData = delNode->GetData();
	//pq->front = pq->front->next;
	pq->front = pq->front->GetNext();

	//free(delNode);
	delete delNode;
	return retData;
}


Data CListBaseQueue::QPeek(CListBaseQueue* pq)
{
	if(QIsEmpty(pq))
	{
		//printf("Queue Memory Error!");
		AfxMessageBox(_T("Queue Memory Error!"));
		exit(-1);
	}

	//return pq->front->data;
	return pq->front->GetData();
}
