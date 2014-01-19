#include "StdAfx.h"
#include "Cluster.h"


CCluster::CCluster(void)
	: m_CountIndexQueuePush(0)
	, m_DynamicArrayPush(NULL)
{
}


CCluster::~CCluster(void)
{
}


CListBaseQueue* CCluster::GetQueueExcitement(void)
{
	return &m_QueueExcitement;
}


CListBaseQueue* CCluster::GetQueuePush(void)
{
	return &m_QueuePush;
}


void CCluster::SetCountIndexQueuePush(int countIndexQueuePush)
{
	m_CountIndexQueuePush = countIndexQueuePush;
}


void CCluster::NewDynamicArrayPush(void)
{
	m_DynamicArrayPush = new CUnit[m_CountIndexQueuePush];
}


void CCluster::DeleteDynamicArrayPush(void)
{
	delete[] m_DynamicArrayPush;
}


void CCluster::SetDynamicArrayPush(void)
{
	for (int i=0;i<m_CountIndexQueuePush;i++)
	{
		if (!(m_QueuePush.QIsEmpty(GetQueuePush())))
		{
			m_DynamicArrayPush[i] = m_QueuePush.Dequeue(GetQueuePush());
		}		

		m_QueuePush.Enqueue(GetQueuePush(), m_DynamicArrayPush[i]);
	}
}
