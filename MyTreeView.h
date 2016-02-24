#pragma once


// CMyTreeView 视图

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyTreeView();
public:
	CTreeCtrl *m_TreeCtrl;
	CImageList m_imgList;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


