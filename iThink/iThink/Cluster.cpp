#include "StdAfx.h"
#include "Cluster.h"


CCluster::CCluster(void)
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
