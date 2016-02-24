// MedicIDSeekDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "MedicIDSeekDlg.h"
#include "Globol.h"

// CMedicIDSeekDlg 对话框

IMPLEMENT_DYNAMIC(CMedicIDSeekDlg, CDialog)

CMedicIDSeekDlg::CMedicIDSeekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedicIDSeekDlg::IDD, pParent)
{

}

CMedicIDSeekDlg::~CMedicIDSeekDlg()
{
}

void CMedicIDSeekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT1,m_strContent);
}


BEGIN_MESSAGE_MAP(CMedicIDSeekDlg, CDialog)
END_MESSAGE_MAP()


// CMedicIDSeekDlg 消息处理程序

void CMedicIDSeekDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	UpdateData();
	if (m_strContent == "")
	{
		AfxMessageBox("请输入要查找的药品编号");
	}
	else
	{
		CMedicSet *pMedicSet = &((CMainFrame *)AfxGetMainWnd())->medicSet;
		CMedic::MedicSearch(pMedicSet,m_strContent,0);
		CDialog::OnOK();
	}
	
}
