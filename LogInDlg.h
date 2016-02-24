#pragma once


// CLogInDlg 对话框

class CLogInDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogInDlg)

public:
	CLogInDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogInDlg();

// 对话框数据
	enum { IDD = IDD_USER_LOGIN };
	CString m_userAccount;
	CString m_userPasswd;
	CString m_userType;
	CString m_PreUserAccount;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnEnKillfocusEditAccount();
};
