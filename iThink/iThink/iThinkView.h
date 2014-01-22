
// iThinkView.h : CiThinkView 클래스의 인터페이스
//

#pragma once
#include "afxext.h"

#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include "C:\\Users\\gtgim\\Desktop\\examples\\include\\edk.h"
#include "C:\\Users\\gtgim\\Desktop\\examples\\include\\edkErrorCode.h"
#include "C:\\Users\\gtgim\\Desktop\\examples\\include\\EmoStateDLL.h"
#include "gdiplusheaders.h"

#pragma comment(lib, "C:\\Users\\gtgim\\Desktop\\examples\\lib\\edk.lib")
#pragma comment(lib, "C:\\Users\\gtgim\\Desktop\\examples\\lib\\edk_utils.lib")

#include "Cluster.h"

#define USR_DEFWINPROC

#define PI 3.1418

class CiThinkView : public CView
{
protected: // serialization에서만 만들어집니다.
	CiThinkView();
	DECLARE_DYNCREATE(CiThinkView)

// 특성입니다.
public:
	CiThinkDoc* GetDocument() const;

// 작업입니다.
public:
	RECT   m_areaWinView;
	SIZE   m_szWinView;

	RECT   m_areaTitleBar;

	//CRect  m_arOkBtn;

//#define BTNID_OK   101

	//CButton m_BtnOK;

	CBrush m_tlBarBrush; //RGB(100, 50,50));
	//CBrush m_clientBrush; //RGB(200, 250,200));

	void  CloseElem();


	/// Mouse /////////////////////
	int m_stWinMove;
	POINT m_stMove;


	TCHAR  m_buff[256];

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CiThinkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	CBitmapButton m_ButtonClose;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CBitmapButton m_ButtonTraining;
	CBitmapButton m_ButtonCalibration;
	CBitmapButton m_ButtonStart;
public:
	afx_msg void OnPaint();
private:
	CBitmapButton m_ButtonAcquiring;
	CBitmapButton m_ButtonDelete;
	ULONG m_GdiplusToken;
	EmoEngineEventHandle eEvent;
	EmoStateHandle eState;
	unsigned int userID;
	int state;
public:
	void Emotiv(void);
private:
	int m_CGCAction;
	int m_CGCActionPower;
public:
	static UINT ThreadOne(LPVOID pParam);
private:
	int m_FlagClose;
	EE_EEG_ContactQuality_t m_ContactQuality[18];
	Image* imageCircleBlack;
	Image* imageCircleRed;
	Image* imageCircleOrange;
	Image* imageCircleYellow;
	Image* imageCircleGreen;
public:
	Image* SetImageCircleColor(EE_EEG_ContactQuality_t* pCQ);
private:
	CString m_Account;
	int m_ChargeLevel;
	int m_MaxChargeLevel;
	int m_WirelessLevel;
private:
	bool oneTime;
	bool outOfBound;
	float currX,currY;
	double maxRadius;
	float xmax, ymax;
	float preX, preY;
	int incOrDec;
	float oldXVal, oldYVal;
	unsigned long pass,globalElapsed;
	int count;
	float x;
public:
	void changeXY(int x);
	void updateDisplay(void);
private:
	Image* imageComment;
	CString m_Comment;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_FlagTimeOld;
	DWORD m_TimeOld;
	int m_FlagComment;
public:
	void SetCognitiv(void);
private:
	int m_FlagSetCognitiv;
	HWND m_Game;
public:
	void ControlGame(void);
private:
	float xmaxOld;
	CCluster m_Cluster;
public:
	void logAffectivScore(EmoStateHandle  eState);
	void CaculateScale(double& rawScore, double& maxScale, double& minScale, double& scaledScore);
private:
	double m_ScaledScore;
	int m_SelectButton;
};

#ifndef _DEBUG  // iThinkView.cpp의 디버그 버전
inline CiThinkDoc* CiThinkView::GetDocument() const
   { return reinterpret_cast<CiThinkDoc*>(m_pDocument); }
#endif

