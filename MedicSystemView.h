// MedicSystemView.h : CMedicSystemView 类的接口
//


#pragma once


class CMedicSystemView : public CView
{
protected: // 仅从序列化创建
	CMedicSystemView();
	DECLARE_DYNCREATE(CMedicSystemView)

// 属性
public:
	CMedicSystemDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMedicSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MedicSystemView.cpp 中的调试版本
inline CMedicSystemDoc* CMedicSystemView::GetDocument() const
   { return reinterpret_cast<CMedicSystemDoc*>(m_pDocument); }
#endif

