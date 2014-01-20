
// iThinkView.cpp : CiThinkView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "iThink.h"
#endif

#include "iThinkDoc.h"
#include "iThinkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "BufferDC.h"
#include <atlimage.h>


// CiThinkView

IMPLEMENT_DYNCREATE(CiThinkView, CView)

BEGIN_MESSAGE_MAP(CiThinkView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CiThinkView 생성/소멸

CiThinkView::CiThinkView()
	: m_GdiplusToken(0)
	, userID(0)
	, state(0)
	, m_CGCAction(0)
	, m_CGCActionPower(0)
	, m_FlagClose(0)
	, imageCircleBlack(NULL)
	, imageCircleRed(NULL)
	, imageCircleOrange(NULL)
	, imageCircleYellow(NULL)
	, imageCircleGreen(NULL)
	, m_Account(_T(""))
	, m_ChargeLevel(0)
	, m_MaxChargeLevel(0)
	, m_WirelessLevel(0)
	, imageComment(NULL)
	, m_Comment(_T(""))
	, m_FlagTimeOld(0)
	, m_TimeOld(0)
	, m_FlagComment(0)
	, m_FlagSetCognitiv(0)
	, xmaxOld(0)
	, m_ScaledScore(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_stWinMove = 0;

	oneTime = true;
	outOfBound = false;
	currX = 0,currY = 0;
	maxRadius = 10000;
	xmax = 0, ymax = 0;
	preX = 0, preY = 0;
	incOrDec = 10;
	oldXVal =0, oldYVal = 0;
	pass = 0,globalElapsed = 0;
	count = 0;
	x;
}

CiThinkView::~CiThinkView()
{
}

BOOL CiThinkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CiThinkView 그리기

void CiThinkView::OnDraw(CDC* pDC)
{
	CiThinkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.	
}


// CiThinkView 진단

#ifdef _DEBUG
void CiThinkView::AssertValid() const
{
	CView::AssertValid();
}

void CiThinkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CiThinkDoc* CiThinkView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CiThinkDoc)));
	return (CiThinkDoc*)m_pDocument;
}
#endif //_DEBUG


// CiThinkView 메시지 처리기


void CiThinkView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	ModifyStyle(0, WS_CLIPCHILDREN);

	GetClientRect( &m_areaWinView );

	m_szWinView.cx = m_areaWinView.right - m_areaWinView.left + 1;
	m_szWinView.cy = m_areaWinView.bottom - m_areaWinView.top + 1;

	m_areaTitleBar.left = 950;
	m_areaTitleBar.top = 10;
	//m_areaTitleBar.right = m_areaWinView.right-m_areaWinView.left-40;
	m_areaTitleBar.right = 975;
	m_areaTitleBar.bottom = 35;

	/*m_arOkBtn.left = 980;
	m_arOkBtn.top = 10;
	m_arOkBtn.right = m_areaWinView.right-m_areaWinView.left-10;
	m_arOkBtn.bottom = m_arOkBtn.top + 70;*/
	

	m_tlBarBrush.CreateSolidBrush( RGB(65, 83,95) );
	//m_clientBrush.CreateSolidBrush( RGB(255, 255,255) );


	/*m_BtnOK.Create(_T("OK"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		m_arOkBtn, this, BTNID_OK);*/
}


BOOL CiThinkView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	TRACE( L"CSdiNoFrameView::OnCommand()\n");

	if (wParam == 1000) {

		CloseElem();

		CWnd *pWnd = AfxGetMainWnd();

		pWnd->SendMessage(WM_CLOSE);
		TRACE( L"- End pWnd->SendMessage(WM_CLOSE)\n");


		//pWnd->DestroyWindow();
		//TRACE( L"- End pWnd->DestroyWindow()\n");

		return TRUE;
	}

	if (wParam == 1004)
	{
		if (SetTimer(10,1000,NULL)!=10)
		{
			AfxMessageBox(TEXT("ERROR:Failed to set timer!"));
		}

		srand((unsigned)time(NULL));

		return TRUE;
	}

	if (wParam == 1003)
	{
		::WinExec("C:\\Users\\gtgim\\Desktop\\test.exe", SW_SHOW);
		m_Game = ::FindWindow(_T("UnityWndClass"), NULL);

		return TRUE;
	}

	if (wParam == 1002)
	{
		if (SetTimer(11,1000,NULL)!=11)
		{
			AfxMessageBox(TEXT("ERROR:Failed to set timer!"));
		}

		srand((unsigned)time(NULL));

		return TRUE;
	}

	BOOL res =  CView::OnCommand(wParam, lParam);

	TRACE( L"- End CView::OnCommand() => %d\n", res);

	return res;
}

void CiThinkView::CloseElem()
{

	//m_BtnOK.DestroyWindow();
	m_tlBarBrush.DeleteObject();
	//m_clientBrush.DeleteObject();
	
	m_ButtonClose.DestroyWindow();
	m_ButtonTraining.DestroyWindow();
	m_ButtonCalibration.DestroyWindow();
	m_ButtonStart.DestroyWindow();
	m_ButtonAcquiring.DestroyWindow();
	m_ButtonDelete.DestroyWindow();

	GdiplusShutdown(m_GdiplusToken);

	m_FlagClose = 1;
	EE_EngineDisconnect();
	EE_EmoStateFree(eState);
	EE_EmoEngineEventFree(eEvent);
}

void CiThinkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_areaTitleBar.left <= point.x && m_areaTitleBar.top <= point.y) {
		if (m_areaTitleBar.right >= point.x && m_areaTitleBar.bottom >= point.y) {
			TRACE( L"Move Start (%d,%d)\n", point.x, point.y );

#ifdef USR_DEFWINPROC 
			CWnd *pWnd = AfxGetMainWnd();
			HWND hUIWnd = pWnd->m_hWnd;
			::DefWindowProc(hUIWnd, WM_SYSCOMMAND, SC_MOVE+1,MAKELPARAM(point.x,point.y));
#else
			m_stWinMove = 1;
			m_stMove.x = point.x;
			m_stMove.y = point.y;
#endif
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


int CiThinkView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	m_ButtonClose.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(980,0,1023,43), this, 1000);
	m_ButtonClose.LoadBitmaps(IDB_BITMAP1,IDB_BITMAP1,IDB_BITMAP1,IDB_BITMAP1);
	//m_ButtonClose.SizeToContent();

	m_ButtonTraining.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(10,10,110,60), this, 1001);
	m_ButtonTraining.LoadBitmaps(IDB_BITMAP2,IDB_BITMAP2,IDB_BITMAP2,IDB_BITMAP2);

	m_ButtonCalibration.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(120,10,220,60), this, 1002);
	m_ButtonCalibration.LoadBitmaps(IDB_BITMAP3,IDB_BITMAP3,IDB_BITMAP3,IDB_BITMAP3);

	m_ButtonStart.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(230,10,330,60), this, 1003);
	m_ButtonStart.LoadBitmaps(IDB_BITMAP4,IDB_BITMAP4,IDB_BITMAP4,IDB_BITMAP4);

	m_ButtonAcquiring.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(740,510,840,560), this, 1004);
	m_ButtonAcquiring.LoadBitmaps(IDB_BITMAP5,IDB_BITMAP5,IDB_BITMAP5,IDB_BITMAP5);

	m_ButtonDelete.Create(NULL, WS_CHILD|WS_VISIBLE|BS_OWNERDRAW, 
		CRect(870,510,970,560), this, 1005);
	m_ButtonDelete.LoadBitmaps(IDB_BITMAP6,IDB_BITMAP6,IDB_BITMAP6,IDB_BITMAP6);

	GdiplusStartupInput GdiplusStartupInput;
	GdiplusStartup(&m_GdiplusToken, &GdiplusStartupInput, NULL);
		
	imageCircleBlack = Image::FromFile(L"C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\CircleBlack.png");
	imageCircleRed = Image::FromFile(L"C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\CircleRed.png");
	imageCircleOrange = Image::FromFile(L"C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\CircleOrange.png");
	imageCircleYellow = Image::FromFile(L"C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\CircleYellow.png");
	imageCircleGreen = Image::FromFile(L"C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\CircleGreen.png");


	eEvent = EE_EmoEngineEventCreate();
	eState = EE_EmoStateCreate();

	/*if (EE_EngineConnect() != EDK_OK) {
		AfxMessageBox(TEXT("Emotiv Engine start up failed."));		
	}*/

	if (EE_EngineRemoteConnect("127.0.0.1", 3008) != EDK_OK) {
		AfxMessageBox(TEXT("Emotiv Engine start up failed."));
	}
	else {
		AfxMessageBox((TEXT("Emotiv Engine started!")));
	}


	CWinThread* pThread1 = AfxBeginThread(ThreadOne,this);
	if (pThread1 == NULL)
	{
		AfxMessageBox(TEXT("ERROR:Failed to begin worker- thread!"));
	}

	TCHAR strAccount[MAX_PATH];
	DWORD len;
	GetUserName(strAccount,&len);
	m_Account.Format(_T("%s"), strAccount);

	imageComment = Image::FromFile(L"C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\Comment.png");	

	return 0;
}


void CiThinkView::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages

	CBufferDC dc(this);

	CString strImageBackground = TEXT("C:\\Users\\gtgim\\Documents\\Visual Studio 2010\\Projects\\iThink\\iThink\\Background.png");
	CImage ImageBackground;
	HRESULT hResultBackground = ImageBackground.Load(strImageBackground);
	ImageBackground.BitBlt(dc.m_hDC,0,0);

	//dc.FillRect(&m_areaWinView, &m_clientBrush);
	dc.FillRect(&m_areaTitleBar, &m_tlBarBrush);

	Graphics graphics(dc.m_hDC);

	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[3]), 100, 150, (SetImageCircleColor(&m_ContactQuality[3]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[3]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[16]), 195, 150, (SetImageCircleColor(&m_ContactQuality[16]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[16]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[4]), 50, 200, (SetImageCircleColor(&m_ContactQuality[4]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[4]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[5]), 120, 200, (SetImageCircleColor(&m_ContactQuality[5]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[5]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[14]), 180, 200, (SetImageCircleColor(&m_ContactQuality[14]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[14]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[15]), 245, 200, (SetImageCircleColor(&m_ContactQuality[15]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[15]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[6]), 80, 240, (SetImageCircleColor(&m_ContactQuality[6]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[6]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[13]), 210, 240, (SetImageCircleColor(&m_ContactQuality[13]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[13]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[7]), 20, 265, (SetImageCircleColor(&m_ContactQuality[7]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[7]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[12]), 275, 265, (SetImageCircleColor(&m_ContactQuality[12]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[12]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[0]), 40, 305, (SetImageCircleColor(&m_ContactQuality[0]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[0]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[1]), 255, 305, (SetImageCircleColor(&m_ContactQuality[1]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[1]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[8]), 70, 345, (SetImageCircleColor(&m_ContactQuality[8]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[8]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[11]), 225, 345, (SetImageCircleColor(&m_ContactQuality[11]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[11]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[9]), 100, 380, (SetImageCircleColor(&m_ContactQuality[9]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[9]))->GetHeight());
	graphics.DrawImage(SetImageCircleColor(&m_ContactQuality[10]), 195, 380, (SetImageCircleColor(&m_ContactQuality[10]))->GetWidth(), (SetImageCircleColor(&m_ContactQuality[10]))->GetHeight());
	
	Font F(L"Myriad Pro" , 18, FontStyleRegular,UnitPixel) ;
	SolidBrush B(Color(255,255,255));
	graphics.SetTextRenderingHint( Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias );
	graphics.DrawString(m_Account, -1, &F, PointF(200,498), &B);

	CString strChargeLevel;
	strChargeLevel.Format(_T("%d%%"), m_ChargeLevel * 25);
	graphics.DrawString(strChargeLevel, -1, &F, PointF(200,530), &B);

	CString strWirelessLevel;
	if (m_WirelessLevel == 0)
	{
		strWirelessLevel.Format(_T("No signal"));
	}
	if (m_WirelessLevel == 1)
	{
		strWirelessLevel.Format(_T("Low"));
	}
	if (m_WirelessLevel == 2)
	{
		strWirelessLevel.Format(_T("High"));
	}
	graphics.DrawString(strWirelessLevel, -1, &F, PointF(200,560), &B);

	graphics.DrawString(L"Active", -1, &F, PointF(200,598), &B);

	if (m_CGCAction == 1)
	{
		graphics.DrawString(L"0%", -1, &F, PointF(540,498), &B);
		graphics.DrawString(L"0%", -1, &F, PointF(540,530), &B);
	}
	if (m_CGCAction == 2)
	{
		CString strCGCActionPower;
		strCGCActionPower.Format(_T("%d%%"), m_CGCActionPower);
		graphics.DrawString(strCGCActionPower, -1, &F, PointF(540,498), &B);
		graphics.DrawString(L"0%", -1, &F, PointF(540,530), &B);
	}
	if (m_CGCAction == 4)
	{
		graphics.DrawString(L"0%", -1, &F, PointF(540,498), &B);
		CString strCGCActionPower;
		strCGCActionPower.Format(_T("%d%%"), m_CGCActionPower);
		graphics.DrawString(strCGCActionPower, -1, &F, PointF(540,530), &B);
	}

	int tempXMax = xmax;
	tempXMax = (tempXMax/100) * 2;
	CString strXMax;
	if (tempXMax < 0)
	{
		strXMax.Format(_T("%d%%"), ~tempXMax);
		if (~tempXMax > 100)
		{
			strXMax.Format(_T("100%%"));
		}
		graphics.DrawString(strXMax, -1, &F, PointF(540,565), &B);
		graphics.DrawString(L"0%", -1, &F, PointF(540,600), &B);
	}
	if (tempXMax > 0)
	{
		graphics.DrawString(L"0%", -1, &F, PointF(540,565), &B);
		strXMax.Format(_T("%d%%"), tempXMax);
		if (tempXMax > 100)
		{
			strXMax.Format(_T("100%%"));
		}
		graphics.DrawString(strXMax, -1, &F, PointF(540,600), &B);
	}
	if (tempXMax == 0)
	{
		strXMax.Format(_T("0%%"));
		graphics.DrawString(strXMax, -1, &F, PointF(540,565), &B);
		graphics.DrawString(strXMax, -1, &F, PointF(540,600), &B);
	}

	graphics.DrawImage(imageComment, 350, 200, imageComment->GetWidth(), imageComment->GetHeight());
	if (m_FlagComment == 0)
	{
		m_Comment.Format(_T("iThink waiting for command."));
	}
	if (m_FlagComment == 1)
	{
		m_Comment.Format(_T("After a while, iThink will acquire\nNeutral data."));
	}
	if (m_FlagComment == 2)
	{
		m_Comment.Format(_T("iThink acquiring Neutral data.\n\nConcentrate at 8 Seconds."));
	}
	if (m_FlagComment == 3)
	{
		m_Comment.Format(_T("Neutral data is acquired.\n\nAfter a while, iThink will acquire\nPush data."));
	}
	if (m_FlagComment == 4)
	{
		m_Comment.Format(_T("iThink acquiring Push data.\n\nConcentrate at 8 Seconds."));
	}
	if (m_FlagComment == 5)
	{
		m_Comment.Format(_T("Push data is acquired.\n\nAfter a while, iThink will acquire\nPull data."));
	}
	if (m_FlagComment == 6)
	{
		m_Comment.Format(_T("iThink acquiring Pull data.\n\nConcentrate at 8 Seconds."));
	}
	if (m_FlagComment == 7)
	{
		m_Comment.Format(_T("Pull data is acquired.\n\nPlease wait a moment."));
	}	
	graphics.DrawString(m_Comment, -1, &F, PointF(400,215), &B);
}


void CiThinkView::Emotiv(void)
{
	state = EE_EngineGetNextEvent(eEvent);

	ES_GetBatteryChargeLevel(eState,&m_ChargeLevel,&m_MaxChargeLevel);
	m_WirelessLevel = ES_GetWirelessSignalStatus(eState);

	if (state == EDK_OK)
	{
		EE_Event_t eventType = EE_EmoEngineEventGetType(eEvent);		
		EE_EmoEngineEventGetUserId(eEvent, &userID);

		ES_GetContactQualityFromAllChannels(eState,m_ContactQuality,18);
		
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(eEvent, eState);				

			m_CGCAction = static_cast<int>(ES_CognitivGetCurrentAction(eState));
			m_CGCActionPower = static_cast<int>(ES_CognitivGetCurrentActionPower(eState)*100.0f);

			logAffectivScore(eState);
		}
		if (eventType == EE_CognitivEvent)
		{
			EE_CognitivEvent_t eventType = EE_CognitivEventGetType(eEvent);

			if (eventType == EE_CognitivTrainingStarted)
			{									
			}
			if (eventType == EE_CognitivTrainingSucceeded)
			{
				EE_CognitivSetTrainingControl(userID, COG_ACCEPT);
			}
			if (eventType == EE_CognitivTrainingCompleted)
			{
				EE_CognitivSetTrainingControl(userID, COG_ACCEPT);
			}
		}
	}	
}


UINT CiThinkView::ThreadOne(LPVOID pParam)
{
	CiThinkView* pView = (CiThinkView*)pParam;
	
	while (pView->m_FlagClose == 0)
	{
		pView->Emotiv();
		pView->updateDisplay();
		pView->SetCognitiv();
		pView->RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW);
		pView->ControlGame();
		Sleep(1);
	}	

	return 0;
}


Image* CiThinkView::SetImageCircleColor(EE_EEG_ContactQuality_t* pCQ)
{
	if (*pCQ == 4)
	{
		return imageCircleGreen;
	}
	if (*pCQ == 3)
	{
		return imageCircleYellow;
	}
	if (*pCQ == 2)
	{
		return imageCircleOrange;
	}
	if (*pCQ == 1)
	{
		return imageCircleRed;
	}

	return imageCircleBlack;
}


void CiThinkView::changeXY(int x)
{
	if( currX >0 )
	{
		float temp = currY/currX;					
		currX -= incOrDec;
		currY = temp*currX;
	}
	else if( currX < 0)
	{ 
		float temp = currY/currX;		
		currX += incOrDec;
		currY = temp*currX;
	}
	else 
	{
		if( currY > 0 ) currY -= incOrDec;
		else if( currY <0 ) currY += incOrDec;
	}				
	if( x == 0)
	{
		if( (abs(currX) <= incOrDec) && (abs(currY) <= incOrDec))
		{
			xmax = 0;
			ymax = 0;
		}
		else
		{
			xmax = currX;
			ymax = currY;
		}
	}
	else
	{
		if( (abs(currX) <= incOrDec) && (abs(currY) <= incOrDec))
		{
			xmax = 0;
			ymax = 0;
		}
	}
}


void CiThinkView::updateDisplay(void)
{
	int gyroX = 0,gyroY = 0;
	EE_HeadsetGetGyroDelta(0,&gyroX,&gyroY);
	xmax += gyroX;
	ymax += gyroY;

	if( outOfBound )
	{
		if( preX != gyroX && preY != gyroY )
		{
			xmax = currX;
			ymax = currY;
		}
	}

	double val = sqrt((float)(xmax*xmax + ymax*ymax));

	//std::cout <<"xmax : " << xmax <<" ; ymax : " << ymax << std::endl;


	if( val >= maxRadius )
	{
		changeXY(1);	
		outOfBound = true;
		preX = gyroX;
		preY = gyroY;
	}
	else
	{		
		outOfBound = false;
		if(oldXVal == gyroX && oldYVal == gyroY)
		{
			++count;
			if( count > 10 )
			{									
				changeXY(0);
			}
		}
		else
		{
			count = 0;
			currX = xmax;
			currY = ymax;
			oldXVal = gyroX;
			oldYVal = gyroY;			
		}
	}
	Sleep(15);
}


void CiThinkView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == 10)
	{
		if (m_FlagTimeOld == 0)
		{
			m_TimeOld = GetTickCount();
			m_FlagTimeOld = 1;
		}
		DWORD timeNew = GetTickCount();

		DWORD timeSeconds = (timeNew - m_TimeOld) / 1000;

		if (timeSeconds >= 0 && timeSeconds <= 8)
		{
			m_FlagComment = 1;
		}
		if (timeSeconds >= 9 && timeSeconds <= 17)
		{
			m_FlagComment = 2;			
		}
		if (timeSeconds >= 18 && timeSeconds <= 26)
		{
			m_FlagComment = 3;
		}
		if (timeSeconds >= 27 && timeSeconds <= 35)
		{
			m_FlagComment = 4;			
		}
		if (timeSeconds >= 36 && timeSeconds <= 44)
		{
			m_FlagComment = 5;
		}
		if (timeSeconds >= 45 && timeSeconds <= 53)
		{
			m_FlagComment = 6;			
		}
		if (timeSeconds >= 54 && timeSeconds <= 62)
		{
			m_FlagComment = 7;
		}
		if (timeSeconds >= 63 && timeSeconds <= 71)
		{
			m_FlagComment = 0;
			KillTimer(10);
			m_FlagTimeOld = 0;			
		}
	}

	if (nIDEvent == 11)
	{
		// Queue의 생성 및 초기화 ///////
		//Queue q;
		/*CListBaseQueue q;
		//QueueInit(&q);
		q.QueueInit(&q);*/

		// 데이터 넣기 ///////
		/*Enqueue(&q, 1);  Enqueue(&q, 2);
		Enqueue(&q, 3);  Enqueue(&q, 4);
		Enqueue(&q, 5);*/
		/*q.Enqueue(&q, 1); q.Enqueue(&q, 2);
		q.Enqueue(&q, 3); q.Enqueue(&q, 4);
		q.Enqueue(&q, 5);*/

		// 데이터 꺼내기 ///////
		/*while(!QIsEmpty(&q))
		printf("%d ", Dequeue(&q));*/
		/*while (!(q.QIsEmpty(&q)))
		{
			CString test;
			test.Format(_T("%d\n"), q.Dequeue(&q));
			TRACE(test);
		}*/

		if (m_FlagTimeOld == 0)
		{
			m_TimeOld = GetTickCount();
			m_FlagTimeOld = 1;

			m_Cluster.GetQueuePush()->QueueInit(m_Cluster.GetQueuePush());
			m_Cluster.GetQueueExcitement()->QueueInit(m_Cluster.GetQueueExcitement());
		}
		DWORD timeNew = GetTickCount();

		DWORD timeSeconds = (timeNew - m_TimeOld) / 1000;

		if (timeSeconds < 10)
		{
			CUnit unitPush;
			if (m_CGCAction == 2)
			{
				unitPush.SetValue(m_CGCActionPower);				
			}
			unitPush.SetTimeSeconds(timeSeconds);

			m_Cluster.GetQueuePush()->Enqueue(m_Cluster.GetQueuePush(), unitPush);

			CUnit unitExcitement;
			unitExcitement.SetValue(m_ScaledScore);
			unitExcitement.SetTimeSeconds(timeSeconds);

			m_Cluster.GetQueueExcitement()->Enqueue(m_Cluster.GetQueueExcitement(), unitExcitement);
		}
		else
		{
			/*while (!(m_Cluster.GetQueuePush()->QIsEmpty(m_Cluster.GetQueuePush())))
			{
				CString test;
				test.Format(_T("%lf\n"), m_Cluster.GetQueuePush()->Dequeue(m_Cluster.GetQueuePush()).GetValue());
				TRACE(test);
			}

			TRACE("^^\n");

			while (!(m_Cluster.GetQueueExcitement()->QIsEmpty(m_Cluster.GetQueueExcitement())))
			{
				CString test;
				test.Format(_T("%lf\n"), m_Cluster.GetQueueExcitement()->Dequeue(m_Cluster.GetQueueExcitement()).GetValue());
				TRACE(test);
			}*/

			m_Cluster.SetCountIndexQueuePush(10);
			m_Cluster.NewDynamicArrayPush();			
			m_Cluster.SetDynamicArrayPush();
			m_Cluster.SetUnitClass();
			m_Cluster.EuclideanDistance();
			m_Cluster.DeleteDynamicArrayPush();
			m_Cluster.SetQueueGroupClass();

			KillTimer(11);
			m_FlagTimeOld = 0;
		}
	}

	CView::OnTimer(nIDEvent);
}


void CiThinkView::SetCognitiv(void)
{
	if (m_FlagComment == 2 && m_FlagSetCognitiv == 0)
	{
		unsigned long activeActions = 6; // EE_CognitivAction_t 비트 연산

		EE_CognitivSetActiveActions(userID, activeActions);

		EE_CognitivSetTrainingAction(userID, COG_NEUTRAL);
		EE_CognitivSetTrainingControl(userID, COG_START);

		m_FlagSetCognitiv = 1;
	}
	if (m_FlagComment == 4 && m_FlagSetCognitiv == 1)
	{
		EE_CognitivSetTrainingAction(userID, COG_PUSH);
		EE_CognitivSetTrainingControl(userID, COG_START);

		m_FlagSetCognitiv = 2;
	}
	if (m_FlagComment == 6 && m_FlagSetCognitiv == 2)
	{
		EE_CognitivSetTrainingAction(userID, COG_PULL);
		EE_CognitivSetTrainingControl(userID, COG_START);

		m_FlagSetCognitiv = 0;
	}
}


void CiThinkView::ControlGame(void)
{
	if (m_Game != NULL && m_CGCAction == 2)
	{
		::PostMessage(m_Game, WM_KEYDOWN, 0x00000057, 0x00110001);
		::PostMessage(m_Game, WM_KEYUP, 0x00000057, 0xC0110001);
	}
	if (m_Game != NULL && m_CGCAction == 4)
	{
		::PostMessage(m_Game, WM_KEYDOWN, 0x00000053, 0x001F0001);
		::PostMessage(m_Game, WM_KEYUP, 0x00000053, 0xC01F0001);
	}
	if (m_Game != NULL && xmax < -1)
	{
		if (xmax != xmaxOld && xmax < xmaxOld)
		{
			::PostMessage(m_Game, WM_KEYDOWN, 0x00000041, 0x001E0001);
			::PostMessage(m_Game, WM_KEYUP, 0x00000041, 0xC01E0001);
		}
	}
	if (m_Game != NULL && xmax > 1)
	{
		if (xmax != xmaxOld && xmax > xmaxOld)
		{
			::PostMessage(m_Game, WM_KEYDOWN, 0x00000044, 0x00200001);
			::PostMessage(m_Game, WM_KEYUP, 0x00000044, 0xC0200001);
		}
	}

	xmaxOld = xmax;
}


void CiThinkView::logAffectivScore(EmoStateHandle  eState)
{
	// Affectiv results
	double rawScore=0;
	double minScale=0;
	double maxScale=0;	
	double scaledScore=0;

	ES_AffectivGetExcitementShortTermModelParams(eState,&rawScore,&minScale,&maxScale);
	if (minScale==maxScale)
	{
		//os << "undefined" << ",";
	}
	else{
		CaculateScale(rawScore,maxScale, minScale,scaledScore);
		//os << scaledScore << ",";

		m_ScaledScore = scaledScore;
	}
}


void CiThinkView::CaculateScale(double& rawScore, double& maxScale, double& minScale, double& scaledScore)
{
	if (rawScore<minScale)
	{
		scaledScore =0;
	}else if (rawScore>maxScale)
	{
		scaledScore = 1;
	}
	else{
		scaledScore = (rawScore-minScale)/(maxScale-minScale);
	}
}
