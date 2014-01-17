#include "StdAfx.h"
#include "Unit.h"


CUnit::CUnit(void)
	: m_Value(0)
	, m_TimeSeconds(0)
{
}


CUnit::~CUnit(void)
{
}


void CUnit::SetValue(double value)
{
	m_Value = value;
}


void CUnit::SetTimeSeconds(DWORD timeSeconds)
{
	m_TimeSeconds = timeSeconds;
}


double CUnit::GetValue(void)
{
	return m_Value;
}


DWORD CUnit::GetTimeSeconds(void)
{
	return m_TimeSeconds;
}
