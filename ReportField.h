#pragma once


// CReportField 对话框

class CReportField : public CDialog
{
	DECLARE_DYNAMIC(CReportField)

public:
	CReportField(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportField();

// 对话框数据
	enum { IDD = IDD_FIELDCHOOSER };
	CXTPReportSubListControl m_wndReportSubList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnClose();
};
