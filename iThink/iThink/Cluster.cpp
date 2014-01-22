#include "StdAfx.h"
#include "Cluster.h"

#include <cmath>

CCluster::CCluster(void)
	: m_CountIndexQueuePush(0)
	, m_DynamicArrayPush(NULL)
	, m_CountIndexQueueGroupClassOne(0)
	, m_CountIndexQueueGroupClassTwo(0)
	, m_FlagKMeans(0)
	, m_LevelSensitivity(0)
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


void CCluster::SetUnitClass(void)
{
	CUnit unitExcitement;
	CUnit unitPush;

	for (int i=0;i<m_CountIndexQueuePush;i++)
	{
		if (!(m_QueuePush.QIsEmpty(GetQueuePush())) && !(m_QueueExcitement.QIsEmpty(GetQueueExcitement())))
		{
			unitExcitement = m_QueueExcitement.Dequeue(GetQueueExcitement());
			unitPush = m_QueuePush.Dequeue(GetQueuePush());			

			if (unitExcitement.GetValue() > 0 && unitPush.GetValue() > 50)
			{
				m_UnitClassTwo = unitPush;
			}

			if (unitExcitement.GetValue() == 0 && unitPush.GetValue() <= 50)
			{
				m_UnitClassOne = unitPush;
			}
		}		

		m_QueueExcitement.Enqueue(GetQueueExcitement(), unitExcitement);
		m_QueuePush.Enqueue(GetQueuePush(), unitPush);
	}
}


void CCluster::EuclideanDistance(void)
{
	CUnit unitDistanceClassOne;
	CUnit unitDistanceClassTwo;

	m_QueueDistanceClassOne.QueueInit(&m_QueueDistanceClassOne);
	m_QueueDistanceClassTwo.QueueInit(&m_QueueDistanceClassTwo);

	for (int i=0;i<m_CountIndexQueuePush;i++)
	{
		unitDistanceClassOne.SetValue(
			sqrt(
			pow(m_UnitClassOne.GetValue() - m_DynamicArrayPush[i].GetValue(), 2) + 
			powl((long double)m_UnitClassOne.GetTimeSeconds() - m_DynamicArrayPush[i].GetTimeSeconds(), 2)
			)
		);

		m_QueueDistanceClassOne.Enqueue(&m_QueueDistanceClassOne, unitDistanceClassOne);

		unitDistanceClassTwo.SetValue(
			sqrt(
			pow(m_UnitClassTwo.GetValue() - m_DynamicArrayPush[i].GetValue(), 2) + 
			powl((long double)m_UnitClassTwo.GetTimeSeconds() - m_DynamicArrayPush[i].GetTimeSeconds(), 2)
			)
		);

		m_QueueDistanceClassTwo.Enqueue(&m_QueueDistanceClassTwo, unitDistanceClassTwo);
	}
}


void CCluster::SetQueueGroupClass(void)
{
	CUnit unitDistanceClassOne;
	CUnit unitDistanceClassTwo;

	CUnit unitGroupClassOne;
	CUnit unitGroupClassTwo;

	m_QueueGroupClassOne.QueueInit(&m_QueueGroupClassOne);
	m_QueueGroupClassTwo.QueueInit(&m_QueueGroupClassTwo);

	for (int i=0;i<m_CountIndexQueuePush;i++)
	{
		if (!(m_QueueDistanceClassOne.QIsEmpty(&m_QueueDistanceClassOne)) && !(m_QueueDistanceClassTwo.QIsEmpty(&m_QueueDistanceClassTwo)))
		{
			unitDistanceClassOne = m_QueueDistanceClassOne.Dequeue(&m_QueueDistanceClassOne);
			unitDistanceClassTwo = m_QueueDistanceClassTwo.Dequeue(&m_QueueDistanceClassTwo);

			if (unitDistanceClassOne.GetValue() > unitDistanceClassTwo.GetValue())
			{
				unitGroupClassOne.SetValue(i);

				m_QueueGroupClassOne.Enqueue(&m_QueueGroupClassOne, unitGroupClassOne);

				m_CountIndexQueueGroupClassOne++;
			}

			if (unitDistanceClassOne.GetValue() < unitDistanceClassTwo.GetValue())
			{
				unitGroupClassTwo.SetValue(i);

				m_QueueGroupClassTwo.Enqueue(&m_QueueGroupClassTwo, unitGroupClassTwo);

				m_CountIndexQueueGroupClassTwo++;
			}
		}		
	}
}


void CCluster::SetUnitNewClass(void)
{
	CUnit unitGroupClassOne;
	int valueQueueGroupClassOne;
	double caseOneSumValueDynamicArrayPush = 0.0;
	DWORD caseOneSumTimeSecondsDynamicArrayPush = 0;

	CUnit unitGroupClassTwo;
	int valueQueueGroupClassTwo;
	double caseTwoSumValueDynamicArrayPush = 0.0;
	DWORD caseTwoSumTimeSecondsDynamicArrayPush = 0;
	
	for (int i=0;i<m_CountIndexQueueGroupClassOne;i++)
	{
		if (!(m_QueueGroupClassOne.QIsEmpty(&m_QueueGroupClassOne)))
		{
			unitGroupClassOne = m_QueueGroupClassOne.Dequeue(&m_QueueGroupClassOne);

			valueQueueGroupClassOne = unitGroupClassOne.GetValue();

			caseOneSumValueDynamicArrayPush += m_DynamicArrayPush[valueQueueGroupClassOne].GetValue();
			caseOneSumTimeSecondsDynamicArrayPush += m_DynamicArrayPush[valueQueueGroupClassOne].GetTimeSeconds();

			m_QueueGroupClassOne.Enqueue(&m_QueueGroupClassOne, unitGroupClassOne);
		}		
	}

	for (int i=0;i<m_CountIndexQueueGroupClassTwo;i++)
	{
		if (!(m_QueueGroupClassTwo.QIsEmpty(&m_QueueGroupClassTwo)))
		{
			unitGroupClassTwo = m_QueueGroupClassTwo.Dequeue(&m_QueueGroupClassTwo);

			valueQueueGroupClassTwo = unitGroupClassTwo.GetValue();

			caseTwoSumValueDynamicArrayPush += m_DynamicArrayPush[valueQueueGroupClassTwo].GetValue();
			caseTwoSumTimeSecondsDynamicArrayPush += m_DynamicArrayPush[valueQueueGroupClassTwo].GetTimeSeconds();

			m_QueueGroupClassTwo.Enqueue(&m_QueueGroupClassTwo, unitGroupClassTwo);
		}		
	}
	
	m_UnitNewClassOne.SetValue(caseOneSumValueDynamicArrayPush / m_CountIndexQueueGroupClassOne);
	m_UnitNewClassOne.SetTimeSeconds(caseOneSumTimeSecondsDynamicArrayPush / m_CountIndexQueueGroupClassOne);

	m_UnitNewClassTwo.SetValue(caseTwoSumValueDynamicArrayPush / m_CountIndexQueueGroupClassTwo);
	m_UnitNewClassTwo.SetTimeSeconds(caseTwoSumTimeSecondsDynamicArrayPush / m_CountIndexQueueGroupClassTwo);
}


void CCluster::CompareClass(void)
{
	if (
		(int)m_UnitClassOne.GetValue() == (int)m_UnitNewClassOne.GetValue() &&
		m_UnitClassOne.GetTimeSeconds() == m_UnitNewClassOne.GetTimeSeconds() &&
		(int)m_UnitClassTwo.GetValue() == (int)m_UnitNewClassTwo.GetValue() &&
		m_UnitClassTwo.GetTimeSeconds() == m_UnitNewClassTwo.GetTimeSeconds()
		)
	{
		m_FlagKMeans = 1;
	}
	else
	{
		m_UnitClassOne = m_UnitNewClassOne;
		m_UnitClassTwo = m_UnitNewClassTwo;
	}
}


void CCluster::KMeans(DWORD timeSeconds)
{
	SetCountIndexQueuePush(timeSeconds);
	NewDynamicArrayPush();			
	SetDynamicArrayPush();
	SetUnitClass();

	for (int i=0;i<timeSeconds;i++)
	{
		EuclideanDistance();			
		SetQueueGroupClass();
		SetUnitNewClass();
		CompareClass();
	}	

	SetLevelSensitivity();
	DeleteDynamicArrayPush();
}


void CCluster::SetLevelSensitivity(void)
{
	//
}


int CCluster::GetLevelSensitivity(void)
{
	return m_LevelSensitivity;
}
