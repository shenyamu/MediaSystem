#pragma once


// CMedicTypeSeekDlg 对话框

class CMedicTypeSeekDlg : public CDialog
{
	DECLARE_DYNAMIC(CMedicTypeSeekDlg)

public:
	CMedicTypeSeekDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMedicTypeSeekDlg();

// 对话框数据
	enum { IDD = IDD_MEDIC_SEEK_TYPE };
	CString m_strContent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
//	virtual BOOL OnInitDialog();
};
