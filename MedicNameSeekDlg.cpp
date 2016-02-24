// MedicNameSeekDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "MedicNameSeekDlg.h"
#include "Globol.h"

// CMedicNameSeekDlg 对话框

IMPLEMENT_DYNAMIC(CMedicNameSeekDlg, CDialog)

CMedicNameSeekDlg::CMedicNameSeekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedicNameSeekDlg::IDD, pParent)
{

}

CMedicNameSeekDlg::~CMedicNameSeekDlg()
{
}

void CMedicNameSeekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT1,m_strContent);
}


BEGIN_MESSAGE_MAP(CMedicNameSeekDlg, CDialog)
END_MESSAGE_MAP()


// CMedicNameSeekDlg 消息处理程序

void CMedicNameSeekDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	UpdateData();
	if (m_strContent == "")
	{
		AfxMessageBox(_T("请输入要查找的药品名称"));
	}
	else
	{		
		CMedicSet *pMedicSet = &((CMainFrame *)AfxGetMainWnd())->medicSet;
		CMedic::MedicSearch(pMedicSet,m_strContent,1);
		CDialog::OnOK();
	}
}
