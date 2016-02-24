#pragma once


// CStoreMedic 对话框

class CStoreMedicDlg : public CDialog
{
	DECLARE_DYNAMIC(CStoreMedicDlg)

public:
	CStoreMedicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStoreMedicDlg();

// 对话框数据
	enum { IDD = IDD_MEDIC_STORE };
	BOOL m_bFlag;
	BOOL m_bNumber;
	CString	m_strMedicID;
	CString	m_strMedicName;
	CString	m_strMedicType;
	CString	m_strMedicNumber;
	CString	m_strMedicPrice;
	CString	m_strGuarantPeriod;
	CString	m_strProduceCompany;
	CDateTimeCtrl m_wndDateTime;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnEnKillfocusEditId();
public:
	afx_msg void OnEnKillfocusEditName();
};
