
// iThink.h : iThink ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CiThinkApp:
// �� Ŭ������ ������ ���ؼ��� iThink.cpp�� �����Ͻʽÿ�.
//

class CiThinkApp : public CWinApp
{
public:
	CiThinkApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CiThinkApp theApp;
