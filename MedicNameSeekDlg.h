#pragma once


// CMedicNameSeekDlg 对话框

class CMedicNameSeekDlg : public CDialog
{
	DECLARE_DYNAMIC(CMedicNameSeekDlg)

public:
	CMedicNameSeekDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMedicNameSeekDlg();

// 对话框数据
	enum { IDD = IDD_MEDIC_SEEK_NAME };
	CString m_strContent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
