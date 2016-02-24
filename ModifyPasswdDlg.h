#pragma once


// CModifyPasswdDlg 对话框

class CModifyPasswdDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyPasswdDlg)

public:
	CModifyPasswdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModifyPasswdDlg();

// 对话框数据
	enum { IDD = IDD_USER_MODPW };
	CString m_strAccount;
	CString m_strOldPasswd;
	CString m_strPasswd;
	CString m_strPasswd1;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
