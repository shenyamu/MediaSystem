// MedicSystemView.cpp : CMedicSystemView 类的实现
//

#include "stdafx.h"
#include "MedicSystem.h"

#include "MedicSystemDoc.h"
#include "MedicSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMedicSystemView

IMPLEMENT_DYNCREATE(CMedicSystemView, CView)

BEGIN_MESSAGE_MAP(CMedicSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMedicSystemView 构造/析构

CMedicSystemView::CMedicSystemView()
{
	// TODO: 在此处添加构造代码

	XTPSkinManager()->LoadSkin(_T("Styles/WinXP.Royale.cjstyles"));
}

CMedicSystemView::~CMedicSystemView()
{
}

BOOL CMedicSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMedicSystemView 绘制

void CMedicSystemView::OnDraw(CDC* pDC)
{
	CMedicSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP3);
	dcCompatible.SelectObject(&bmp);
	CRect rect;
	GetClientRect(&rect);
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
//  	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
//  		0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);

	// TODO: 在此处为本机数据添加绘制代码
}


// CMedicSystemView 打印

BOOL CMedicSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMedicSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMedicSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CMedicSystemView 诊断

#ifdef _DEBUG
void CMedicSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CMedicSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMedicSystemDoc* CMedicSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMedicSystemDoc)));
	return (CMedicSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CMedicSystemView 消息处理程序
