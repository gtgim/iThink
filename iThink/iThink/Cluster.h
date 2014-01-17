#pragma once

#include "ListBaseQueue.h"

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
};

