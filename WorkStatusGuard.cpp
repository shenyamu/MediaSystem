
#include "stdafx.h"
#include "WorkStatusGuard.h"

const TCHAR CWorkStatusGuard::ZEMR_WAITING_TIP[] = _T("zzzLoading");

IMPLEMENT_DYNAMIC(CWorkStatusGuard, CWnd)

CWorkStatusGuard::CWorkStatusGuard(LPCTSTR pszMessage, CWnd * pParentWnd/* = NULL*/)
	: m_stopEvent(NULL, TRUE, NULL, NULL)
{
	m_bIsRanderThreadStart = FALSE;
	m_bStop = FALSE;
	m_nIconIdx = 0;
	RegisterWindowClass();
	m_pParentWnd = pParentWnd;
	BOOL bCreate = Create(pParentWnd ? pParentWnd : AfxGetMainWnd());
	//BOOL bCreate = CWnd::Create(ZEMR_WAITING_TIP,L"", );
	if(!bCreate)
	{
		return;
	}

	ShowNewMessages(pszMessage);

	NONCLIENTMETRICS nm;
	nm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0);

	m_captionFont.CreateFontIndirect(&nm.lfSmCaptionFont);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_WAITING_ZDLG);

	m_imgList.Create(ICON_SIZE, ICON_SIZE, ILC_COLOR24, 8, 1);
	m_imgList.Add(&bmp, RGB(0, 0, 0));

	//HANDLE Thread;
	DWORD dwThreadId;
	::CreateThread(NULL,0,&CWorkStatusGuard::ThreadProc,this,0,&dwThreadId);
}

 DWORD WINAPI CWorkStatusGuard::ThreadProc (PVOID pParam)
{
	CWorkStatusGuard* pWork = (CWorkStatusGuard*)pParam;
	while(!pWork->m_bStop)
	{
		pWork->Render();
		::Sleep(80);
	}

	pWork->m_stopEvent.SetEvent();
	return 0;
}

CWorkStatusGuard::~CWorkStatusGuard()
{
	if(m_captionFont.m_hObject)
	{
		m_captionFont.DeleteObject();
	}
	DestroyWindow();
}

BOOL CWorkStatusGuard::RegisterWindowClass(HINSTANCE hInstance /*= NULL*/)
{
	WNDCLASS wndcls;
	if(hInstance == NULL) hInstance = AfxGetInstanceHandle();

	if(!(::GetClassInfo(hInstance, ZEMR_WAITING_TIP, &wndcls)))
	{
		wndcls.style = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInstance;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = ZEMR_WAITING_TIP;

		if(!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

// 2012.08.01 wfj create 3.0.00010.0 封装创建过程，只创建固定的样式
// 2012.08.31 wfj modify 3.0.0010.0 修改样式, 去掉WS_EX_TOPMOST, 防止处于所有程序窗口的顶层, 影响视觉
BOOL CWorkStatusGuard::Create(CWnd* pParent)
{
	CRect rcDesktop = GetDesktopWorkAreaRect();
	//if(pParent->GetSafeHwnd() == NULL)
	{
		pParent = GetDesktopWindow();
	}

	int nWidth = MIN_WIDTH;
	int nHeight = MIN_HEIGHT;
	int nLeft = (rcDesktop.Width()  - nWidth) / 2;
	int nTop = (rcDesktop.Height()  - nHeight) / 2;

	DWORD dwStyle = WS_VISIBLE  | WS_POPUP ;

	return CreateEx(WS_EX_TOOLWINDOW, ZEMR_WAITING_TIP, _T("Waiting"), 
		dwStyle, CRect(nLeft, nTop, nLeft + nWidth, nTop + nHeight), pParent, 0);
}

// 2012.08.01 wfj create 3.0.00010.0 设置要显示的消息。设置之前，必须已经创建窗口
void CWorkStatusGuard::ShowNewMessages(LPCTSTR strMsg)
{
	if(this->GetSafeHwnd() == NULL) return;

	ASSERT(::IsWindow(m_hWnd));
	m_dwTimeStart = ::GetTickCount();
	m_strMsg = strMsg;
	if(m_strMsg.IsEmpty()) m_strMsg = L"";

	// 窗口宽度 = 边距 + 图标 + 文本后，这些内容占据窗口的宽度
	CDC* pDC = GetDC();
	CSize szText = pDC->GetTextExtent(m_strMsg);

	int nExpectWidth = MARGIN_HOR * 3 + szText.cx + ICON_SIZE;
	if(nExpectWidth < MIN_WIDTH)
	{
		nExpectWidth = MIN_WIDTH;
	}

	// 设置窗口大小
	CRect rcDesktop = GetDesktopWorkAreaRect();
	int nWidth = nExpectWidth;
	int nHeight = MIN_HEIGHT;
	int nLeft = (rcDesktop.Width()  - nWidth) / 2;
	int nTop = (rcDesktop.Height()  - nHeight) / 2;

	if(m_pParentWnd != NULL)
	{
		CRect rcW;
		m_pParentWnd->GetWindowRect(&rcW);
		if(nWidth < rcW.Width() && nHeight < rcW.Height())
		{
			nLeft = rcW.left + (rcW.Width()  - nWidth) / 2;
			nTop = rcW.top + (rcW.Height()  - nHeight) / 2;
		}
	}

	HRGN rgn = CreateRoundRectRgn(nLeft, nTop,nLeft+ nWidth,nTop+ nHeight, 30, 30);
	SetWindowRgn(rgn, TRUE);
	
	//SetWindowPos(NULL, nLeft, nTop, nWidth, nHeight, SWP_NOZORDER);
}

// 2012.08.02 wfj create 3.0.00010.0 获取桌面除任务栏之外的区域大小
CRect CWorkStatusGuard::GetDesktopWorkAreaRect()
{
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);

	return rcWorkArea;
}

void CWorkStatusGuard::Show()
{
	ShowWindow(SW_SHOW);
}

void CWorkStatusGuard::Hide()
{
	ShowWindow(SW_HIDE);
}

void CWorkStatusGuard::OnPaint()
{
	//CWnd::OnPaint();
	///*Render();*/
	CDC* dc = GetDC();
	//CBrush brush(RGB(255,255,255));
	//CPen pen(PS_SOLID, 2, RGB(255,0,0));
	////CBrush *oldPen = dc.SelectObject(&brush);
	//CPen* odlPen = dc->SelectObject(&pen);

	CRect rect;
	GetClientRect(&rect);
	dc->RoundRect(&rect,CPoint(30,30));

	CBrush brush(BGCLR);
	CRgn rgn;
	rgn.CreateRoundRectRgn(rect.left+1,rect.top+1,rect.Width(),rect.Height(), 30, 30);
	dc->FillRgn(&rgn,&brush);

	////CPen *oldPen=pDC->SelectObject(&m_pen[0]);
	//
	//{
	//	//rect.OffsetRect(80,0);//每次绘图右移80个像素
	//	//pDC->SelectObject(&m_pen[i]);
	//	
	//	
	//}
	//
	//dc->SelectObject(odlPen);
	ReleaseDC(dc);
}

BEGIN_MESSAGE_MAP(CWorkStatusGuard, CWnd)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
//	ON_WM_NCPAINT()
//ON_WM_NCPAINT()
END_MESSAGE_MAP()

// CWorkStatusGuard message handlers
void CWorkStatusGuard::Render()
{
	if(!::IsWindow(m_hWnd) || !IsWindowVisible()) return;

	CDC* pDC = GetDC();

	try
	{
		if(pDC == NULL || pDC->GetSafeHdc() == NULL || m_imgList.m_hImageList == NULL)
		{
			ReleaseDC(pDC);
			return;
		}

		CRect rcClient;
		GetClientRect(&rcClient);
	

		CBitmap bmpCache;
		bmpCache.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		if(!memDC.GetSafeHdc())
		{
			ReleaseDC(pDC);
			return;
		}

		CBitmap* pOldBitmap = memDC.SelectObject(&bmpCache);
		CFont* pOldFont = memDC.SelectObject(&m_captionFont);

		
		CRect rect;
		GetClientRect(&rect);

		memDC.RoundRect(&rcClient, CPoint(30, 30));

		// 背景
		//memDC.FillSolidRect(rcClient, BGCLR);
		CBrush brush(BGCLR);
		CRgn rgn;
		rgn.CreateRoundRectRgn(rect.left+1,rect.top+1,rect.Width(),rect.Height(), 30, 30);
		memDC.FillRgn(&rgn,&brush);
	
	
	

		// 绘制图标
		CSize szText = memDC.GetTextExtent(m_strMsg);
		int nLeft = MARGIN_HOR;
		int nTop = (rcClient.Height() - ICON_SIZE) / 2;

		m_imgList.Draw(&memDC, m_nIconIdx, CPoint(nLeft, nTop), ILD_IMAGE);

		++m_nIconIdx;
		if(m_nIconIdx > 7) m_nIconIdx = 0;

		// 绘制文本
		int nBkMode = memDC.SetBkMode(TRANSPARENT);
		if(!m_strMsg.IsEmpty())
		{
			nLeft = MARGIN_HOR * 2 + ICON_SIZE;
			nTop = (rcClient.Height() - szText.cy) / 2;
			memDC.DrawText(m_strMsg, CRect(nLeft, nTop, nLeft + szText.cx, rcClient.Height()), DT_LEFT);

			DWORD dwTimeCount = ::GetTickCount();
			DWORD dwTimeSpan = (dwTimeCount - m_dwTimeStart) / 1000;
			wostringstream osT;
			osT << dwTimeSpan << _T(" 秒");
			
			int iTWidth = TIME_WIDTH;
			int iTHeight = TIME_HEIGHT;
			int iTX = rcClient.Width() - iTWidth;
			int iTY = rcClient.Height() - iTHeight;
			CRect rTime(iTX, iTY, iTX + iTWidth, iTY + iTHeight);
			
			//memDC.DrawText(W2A(osT.str().c_str()), rTime, DT_CENTER);
		}

	
		// 将缓存绘制上去
		pDC->BitBlt(0, 0, rcClient.right, rcClient.bottom, &memDC, 0, 0, SRCCOPY);
		memDC.SetBkMode(nBkMode);

		memDC.SelectObject(pOldBitmap);
		memDC.SelectObject(pOldFont);
	}
	catch(...)
	{}

	ReleaseDC(pDC);
}

void CWorkStatusGuard::OnTimer(UINT_PTR nIDEvent)
{
}

int CWorkStatusGuard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	return 0;
}

void CWorkStatusGuard::OnDestroy()
{
	if(m_bIsRanderThreadStart)
	{
		m_bStop = TRUE;
		m_stopEvent.Lock();
	}

	CWnd::OnDestroy();
}

void CWorkStatusGuard::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		if(!m_bIsRanderThreadStart)
		{
			m_bIsRanderThreadStart = TRUE;			
//			m_thRender.start(m_runnable);
		}

	}
	else
	{
		if(m_bIsRanderThreadStart)
		{
			m_bStop = TRUE;
			m_stopEvent.Lock();
		}

		m_bStop = FALSE;
		m_bIsRanderThreadStart = FALSE;
		m_stopEvent.ResetEvent();
	}

}

void CWorkStatusGuard::RenderWindow()
{
	while(!this->m_bStop) 
	{
		this->Render();
		::Sleep(80);
	}

	this->m_stopEvent.SetEvent();
}


