// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "MedicSet.h"
#include "User.h"
#include "UserSet.h"
#include "ReportSeek.h"
#include "SaleSet.h"

class CMainFrame : public CXTPFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CXTPStatusBar  m_wndStatusBar;
	UINT m_nRibbonStyle;
	UINT m_nFont;
	UINT m_nSkin;
	CDialogBar m_wndFieldChooser;
public:
	CSplitterWnd m_wndSplitterWnd;
	CXTPReportControl *m_wndReportCtrl;
	CReportSeekDlg *pSeek;
	CUser user;
	CUserSet userSet;
	CMedicSet medicSet;
	CSaleSet saleSet;

public:
	void InitReport(void);
	void CreateRibbonBar(void);
	void CreateDataSource();
// 生成的消息映射函数
//protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnToggleRibbonBars();
	afx_msg void OnRegisterUser();
	afx_msg void OnDelUser();
	afx_msg void OnSeekUser();
	afx_msg void OnModUserPasswd();
	afx_msg void OnChangeUser();
	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnChangeFont(UINT nFont);
	afx_msg void OnSelectSkin(UINT nSkin);
	afx_msg void OnReportFind();
	afx_msg void OnReportSet();
	afx_msg void OnMedicSeekID();
	afx_msg void OnMedicSeekName();
	afx_msg void OnMedicSeekType();
	afx_msg void OnMedicSearchAll();
	afx_msg void OnMedicSearchZeroNumber();
	afx_msg void OnMedicSearchOutDate();
	afx_msg void OnMedicStore();
	afx_msg void OnMedicClean();
	afx_msg void OnMedicSale();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateRibbonMinimize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRibbonExpand(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUserManger(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFonts(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSkin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNormalButton(CCmdUI* pCmdUI);

};


