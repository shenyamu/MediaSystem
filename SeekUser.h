#pragma once

#include "Globol.h"

// CSeekUser 对话框

class CSeekUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CSeekUserDlg)

public:
	CSeekUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSeekUserDlg();

// 对话框数据
	enum { IDD = IDD_USER_SEEK };
	CUserSet	*pUserSet;
	CListCtrl	m_UserList;
	CString		m_strAccount;
	CString		m_strUsertype;
	int			m_ntypeRadio;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
