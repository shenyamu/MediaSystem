// MedicTypeSeekDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "MedicTypeSeekDlg.h"
#include "Globol.h"

// CMedicTypeSeekDlg 对话框

IMPLEMENT_DYNAMIC(CMedicTypeSeekDlg, CDialog)

CMedicTypeSeekDlg::CMedicTypeSeekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedicTypeSeekDlg::IDD, pParent)
{
	m_strContent = "";
}

CMedicTypeSeekDlg::~CMedicTypeSeekDlg()
{
}

void CMedicTypeSeekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX,IDC_EDIT1,m_strContent);
}


BEGIN_MESSAGE_MAP(CMedicTypeSeekDlg, CDialog)
END_MESSAGE_MAP()


// CMedicTypeSeekDlg 消息处理程序

void CMedicTypeSeekDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类


	UpdateData();
	if (m_strContent == "")
	{
		AfxMessageBox(_T("请选择要查找的药品类型"));
	}
	else
	{
		CMedicSet *pMedicSet = &((CMainFrame *)AfxGetMainWnd())->medicSet;
		CMedic::MedicSearch(pMedicSet,m_strContent,2);
		CDialog::OnOK();
	}
	
}

//BOOL CMedicTypeSeekDlg::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//	CMedicSet *pMedicSet = &((CMainFrame *)AfxGetMainWnd())->medicSet;
//	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_EDIT1);
//	pMedicSet->m_strFilter = "";
//	pMedicSet
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常: OCX 属性页应返回 FALSE
//}
