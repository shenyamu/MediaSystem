#pragma once


// CMedicIDSeekDlg 对话框

class CMedicIDSeekDlg : public CDialog
{
	DECLARE_DYNAMIC(CMedicIDSeekDlg)

public:
	CMedicIDSeekDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMedicIDSeekDlg();

// 对话框数据
	enum { IDD = IDD_MEDIC_SEEK_ID };
	CString m_strContent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
