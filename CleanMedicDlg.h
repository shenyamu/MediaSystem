#pragma once

#include "MedicSet.h"
// CCleanMedicDlg 对话框

class CCleanMedicDlg : public CDialog
{
	DECLARE_DYNAMIC(CCleanMedicDlg)

public:
	CCleanMedicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCleanMedicDlg();
	CMedicSet *pMedicSet;
// 对话框数据
	enum { IDD = IDD_MEDIC_CLEAN };
	CListCtrl m_ListCtrl;
	int m_nCleanType;
	BOOL m_bFlag;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedRadioZero();
	afx_msg void OnBnClickedRadioOutdate();
};
