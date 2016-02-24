#pragma once

#include "Globol.h"

// CChangeUserDlg 对话框

class CChangeUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangeUserDlg)

public:
	CChangeUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeUserDlg();

// 对话框数据
	enum { IDD = IDD_USER_CHANGE };
	CString m_strUserAccount;
	CString m_strPasswd;
	CString m_strUserType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
