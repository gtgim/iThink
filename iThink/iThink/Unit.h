#pragma once
class CUnit
{
public:
	CUnit(void);
	~CUnit(void);
private:
	double m_Value;
	DWORD m_TimeSeconds;
public:
	void SetValue(double value);
	void SetTimeSeconds(DWORD timeSeconds);
	double GetValue(void);
	DWORD GetTimeSeconds(void);
};

