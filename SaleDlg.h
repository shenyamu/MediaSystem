#pragma once

#include "Globol.h"
#include <vector>

using namespace std;

// CSaleDlg 对话框

class CSaleMedicDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaleMedicDlg)

public:
	CSaleMedicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaleMedicDlg();

// 对话框数据
	enum { IDD = IDD_MEDIC_SALE };
	vector<CSale *> m_vecSaleBills;
	CSaleSet *pSaleSet;
	CMedicSet *pMedicSet;
	CString m_strMedicType;
	CString m_strMedicName;
	int m_nMedicNumber;
	CListCtrl m_ListCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedSaleAdd();
	afx_msg void OnCbnSelchangeMedicType();
	afx_msg void OnBnClickedSaleDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedUndo();
	afx_msg void OnBnClickedCancel();
};
