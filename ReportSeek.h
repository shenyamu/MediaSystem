#pragma once


// CReportSeek 对话框

class CReportSeekDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportSeekDlg)

public:
	CReportSeekDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportSeekDlg();
// 对话框数据
	enum { IDD =  NULL};
	//CString m_strFilter;
	CXTPReportFilterEditControl m_wndFilterEditCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	//virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
};
