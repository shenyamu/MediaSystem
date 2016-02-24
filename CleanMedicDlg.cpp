// CleanMedicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "CleanMedicDlg.h"
#include "Globol.h"

// CCleanMedicDlg 对话框

IMPLEMENT_DYNAMIC(CCleanMedicDlg, CDialog)

CCleanMedicDlg::CCleanMedicDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCleanMedicDlg::IDD, pParent),m_nCleanType(-1),m_bFlag(FALSE)
{

}

CCleanMedicDlg::~CCleanMedicDlg()
{
}

void CCleanMedicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_ListCtrl);
	DDX_Radio(pDX,IDC_RADIO_ZERO,m_nCleanType);
}


BEGIN_MESSAGE_MAP(CCleanMedicDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_ZERO, &CCleanMedicDlg::OnBnClickedRadioZero)
	ON_BN_CLICKED(IDC_RADIO_OUTDATE, &CCleanMedicDlg::OnBnClickedRadioOutdate)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCleanMedicDlg 消息处理程序

BOOL CCleanMedicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMedicManage manageMedic;
	CString header[]={"药品编号","药品名称","库存数量","是否过期"};
	for(int i=0;i<4;i++)
	{
		m_ListCtrl.InsertColumn(i,header[i],LVCFMT_LEFT,90);
	}
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMedicSet = &pMainFrm->medicSet;
	pMedicSet->m_strFilter = _T("");
	pMedicSet->Requery();
	for(int i = 0;;i++)
	{
		if(pMedicSet->IsEOF())
		{
			break;
		}
		m_ListCtrl.InsertItem(i,pMedicSet->m_MedicID);
		m_ListCtrl.SetItemText(i,1,pMedicSet->m_MedicName);
		CString str;
		str.Format("%d",pMedicSet->m_MedicNumber);
		m_ListCtrl.SetItemText(i,2,str);
		manageMedic.SetMedicSet(pMedicSet);
		CTime timeAfter=manageMedic.GetOutDateTime();
		CTime timeNow=CTime::GetCurrentTime();
		CString strfool;
		if(timeAfter>timeNow)
		{
			strfool="否";
		}
		else
		{
			strfool="是";
		}
		m_ListCtrl.SetItemText(i,3,strfool);
		pMedicSet->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCleanMedicDlg::OnBnClickedRadioZero()
{
	// TODO: 在此添加控件通知处理程序代码

	pMedicSet->m_strFilter = _T("MedicNumber=0");
	pMedicSet->Requery();
	CMedicManage manageMedic;
	m_ListCtrl.DeleteAllItems();
	for(int i = 0;;i++)
	{
		if(pMedicSet->IsEOF())
		{
			break;
		}
		m_ListCtrl.InsertItem(i,pMedicSet->m_MedicID);
		m_ListCtrl.SetItemText(i,1,pMedicSet->m_MedicName);
		CString str;
		str.Format("%d",pMedicSet->m_MedicNumber);
		m_ListCtrl.SetItemText(i,2,str);
		manageMedic.SetMedicSet(pMedicSet);
		CTime timeAfter=manageMedic.GetOutDateTime();
		CTime timeNow=CTime::GetCurrentTime();
		CString strFlag;
		if(timeAfter > timeNow)
		{
			strFlag="否";
		}
		else
		{
			strFlag="是";
		}
		m_ListCtrl.SetItemText(i,3,strFlag);
		pMedicSet->MoveNext();
	}
}

void CCleanMedicDlg::OnBnClickedRadioOutdate()
{
	// TODO: 在此添加控件通知处理程序代码
	CMedicManage manageMedic;
	pMedicSet->m_strFilter = "";
	pMedicSet->Requery();
	m_ListCtrl.DeleteAllItems();
	for(int i=0;;i++)
	{
		if(pMedicSet->IsEOF())
		{
			break;
		}
		manageMedic.SetMedicSet(pMedicSet);
		CTime OutTime = manageMedic.GetOutDateTime();
		CTime CurTime = CTime::GetCurrentTime();
		if(OutTime < CurTime)
		{
			m_ListCtrl.InsertItem(i,pMedicSet->m_MedicID);
			m_ListCtrl.SetItemText(i,1,pMedicSet->m_MedicName);
			CString str;
			str.Format("%d",pMedicSet->m_MedicNumber);
			m_ListCtrl.SetItemText(i,2,str);
			m_ListCtrl.SetItemText(i,3,"是");
		}
		else
		{
			i=i-1;
		}
		pMedicSet->MoveNext();
	}
}


void CCleanMedicDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData();
	if (m_nCleanType == -1)
	{
		AfxMessageBox("请选择要清理的类型");
		return;
	}
	CMedicManage manageMedic;
	manageMedic.SetMedicSet(pMedicSet);
	if(m_nCleanType == 0)
	{
		if(manageMedic.DelMedicZeroNumber())
		{
			m_bFlag = TRUE;
			AfxMessageBox("数量为0的药品清理完毕");
		}
		else
			AfxMessageBox("数量为0的药品不存在");
	}
	else
	{
		if(manageMedic.DelMedicOutDate())
		{
			m_bFlag = TRUE;
			AfxMessageBox("过期的药品清理完毕");
		}
		else
			AfxMessageBox("暂无过期的药品可清理");	
	}
	
	pMedicSet->m_strFilter = "";
	pMedicSet->Requery();
	m_ListCtrl.DeleteAllItems();
	for(int i=0;;i++)
	{
		if(pMedicSet->IsEOF())
		{
			break;
		}
		m_ListCtrl.InsertItem(i,pMedicSet->m_MedicID);
		m_ListCtrl.SetItemText(i,1,pMedicSet->m_MedicName);
		CString str;
		str.Format("%d",pMedicSet->m_MedicNumber);
		m_ListCtrl.SetItemText(i,2,str);
		manageMedic.SetMedicSet(pMedicSet);
		CTime timeAfter=manageMedic.GetOutDateTime();
		CTime timeNow=CTime::GetCurrentTime();
		CString strFlag;
		if(timeAfter > timeNow)
		{
			strFlag="否";
		}
		else
		{
			strFlag="是";
		}
		m_ListCtrl.SetItemText(i,3,strFlag);
		pMedicSet->MoveNext();
	}

	m_nCleanType = -1;
	UpdateData(FALSE);
}


void CCleanMedicDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!m_bFlag)
	{
		CDialog::OnCancel();
		return;
	}
	
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &pMainFrm->medicSet;
	pMedicSet->m_strFilter = "";
	pMedicSet->Requery();

	CMedic::RefreshReport(pMedicSet);

	CDialog::OnCancel();
}


void CCleanMedicDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CCleanMedicDlg::OnCancel();
}
