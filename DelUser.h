#pragma once

#include "UserSet.h"
#include "User.h"

// CDelUser 对话框

class CDelUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CDelUserDlg)

public:
	CDelUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDelUserDlg();

// 对话框数据
	enum { IDD = IDD_USER_DEL };
	CUserSet *pUserSet;

	CComboBox m_wndUserType;
	CListCtrl m_UserList;
	CString m_strUserAccount;
	BOOL Flag;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCbnSelchangeCombo1();
protected:
	virtual void OnCancel();
};
