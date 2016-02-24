// ReportField.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "ReportField.h"
#include "Globol.h"

// CReportField 对话框

IMPLEMENT_DYNAMIC(CReportField, CDialog)

CReportField::CReportField(CWnd* pParent /*=NULL*/)
	: CDialog(CReportField::IDD, pParent)
{

}

CReportField::~CReportField()
{
}

void CReportField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_wndReportSubList);
}


BEGIN_MESSAGE_MAP(CReportField, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CReportField 消息处理程序

BOOL CReportField::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CXTPReportControl *pReportCtrl = pMainFrm->m_wndReportCtrl;
	pReportCtrl->GetReportHeader()->SetSubListCtrl(&m_wndReportSubList);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReportField::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}
