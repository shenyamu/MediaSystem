// ReportSeek.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "ReportSeek.h"
#include "Globol.h"

// CReportSeek 对话框

IMPLEMENT_DYNAMIC(CReportSeekDlg, CDialog)

CReportSeekDlg::CReportSeekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportSeekDlg::IDD, pParent)
{

}

CReportSeekDlg::~CReportSeekDlg()
{
}

void CReportSeekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Text(pDX,IDC_EDIT_FILTER,m_strFilter);
	DDX_Control(pDX,IDC_EDIT_FILTER,m_wndFilterEditCtrl);
}


BEGIN_MESSAGE_MAP(CReportSeekDlg, CDialog)
END_MESSAGE_MAP()


// CReportSeek 消息处理程序

//void CReportSeekDlg::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	UpdateData(TRUE);
//	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
//	pMainFrm->m_wndReportCtrl->SetFilterText(m_strFilter);
//	pMainFrm->m_wndReportCtrl->Populate();
//	pMainFrm->m_wndReportCtrl->SetFilterText("");
//	//CDialog::OnOK();
//}

void CReportSeekDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CWnd::DestroyWindow();
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->m_wndReportCtrl->SetFilterText("");
	pMainFrm->pSeek = NULL;
}

BOOL CReportSeekDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CXTPReportControl *pReportCtrl = pMainFrm->m_wndReportCtrl;
	pReportCtrl->GetReportHeader()->SetFilterEditCtrl(&m_wndFilterEditCtrl);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
