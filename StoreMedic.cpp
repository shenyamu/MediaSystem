// StoreMedic.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "StoreMedic.h"
#include "Globol.h"

// CStoreMedic 对话框

IMPLEMENT_DYNAMIC(CStoreMedicDlg, CDialog)

CStoreMedicDlg::CStoreMedicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStoreMedicDlg::IDD, pParent),m_bFlag(FALSE),m_bNumber(FALSE)
{
	
}

CStoreMedicDlg::~CStoreMedicDlg()
{
}

void CStoreMedicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_DATE,m_wndDateTime);
	DDX_Text(pDX,IDC_EDIT_ID,m_strMedicID);
	DDX_Text(pDX,IDC_EDIT_NAME,m_strMedicName);
	DDX_CBString(pDX,IDC_EDIT_TYPE,m_strMedicType);
	DDX_Text(pDX,IDC_EDIT_NUMBER,m_strMedicNumber);
	DDX_Text(pDX,IDC_EDIT_KEEP,m_strGuarantPeriod);
	DDX_Text(pDX,IDC_EDIT_PRICE,m_strMedicPrice);
	DDX_Text(pDX,IDC_EDIT_COMPANY,m_strProduceCompany);

}


BEGIN_MESSAGE_MAP(CStoreMedicDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_ID, &CStoreMedicDlg::OnEnKillfocusEditId)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CStoreMedicDlg::OnEnKillfocusEditName)
END_MESSAGE_MAP()


// CStoreMedic 消息处理程序

BOOL CStoreMedicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	COleDateTime OleTiem;
	OleTiem.SetDate(2010,1,1);
	m_wndDateTime.SetTime(OleTiem);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CStoreMedicDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMedicManage manageMedic;
	CMedic medic;
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &pMain->medicSet;
	manageMedic.SetMedicSet(pMedicSet);
	manageMedic.SetMedic(&medic);

	UpdateData();

	if (m_bNumber)//只添加存在药品的数量
	{
		medic.m_strMedicNumber = _ttoi(m_strMedicNumber);
		if(manageMedic.Storage(m_bNumber))
		{
			AfxMessageBox("药品添加成功");
			m_bFlag = TRUE;
		}
	}
	else//添加新的药品
	{
		if(m_strMedicName=="")
		{
			AfxMessageBox("请输入药品名称");
			return;
		}
		if(m_strMedicType=="")
		{
			AfxMessageBox("请选择药品类别");
			return;
		}
		if (m_strMedicNumber == "")
		{
			AfxMessageBox("请输入药品数量");
			return;
		}
		if (m_strMedicPrice == "")
		{
			AfxMessageBox("请输入药品单价");
			return;
		}
		if (m_strGuarantPeriod == "")
		{
			AfxMessageBox("请输入药品保质期");
			return;
		}

		medic.m_strMedicID = m_strMedicID;
		medic.m_strMedicName = m_strMedicName;
		medic.m_strMedicType = m_strMedicType;
		medic.m_strMedicNumber = _ttoi(m_strMedicNumber);
		medic.m_strMedicPrice = _tstof(m_strMedicPrice);
		medic.m_strGuarantPeriod = _ttoi(m_strGuarantPeriod);
		medic.m_ProduceCompany = m_strProduceCompany;

		CTime produceTime;
		m_wndDateTime.GetTime(produceTime);
		medic.m_strProduceDate = produceTime;
		if (manageMedic.Storage(m_bNumber))
		{
			AfxMessageBox("药品添加成功");
			m_bFlag = TRUE;
		}
	}
	
	if (m_bNumber)
	{
		((CEdit *)GetDlgItem(IDC_EDIT_NAME))->EnableWindow(TRUE);
		((CEdit *)GetDlgItem(IDC_EDIT_TYPE))->EnableWindow(TRUE);
		((CEdit *)GetDlgItem(IDC_EDIT_KEEP))->EnableWindow(TRUE);
		((CEdit *)GetDlgItem(IDC_EDIT_PRICE))->EnableWindow(TRUE);
		((CEdit *)GetDlgItem(IDC_EDIT_COMPANY))->EnableWindow(TRUE);
		((CDateTimeCtrl *)GetDlgItem(IDC_EDIT_DATE))->EnableWindow(TRUE);
		m_bNumber = FALSE;
	}

	m_strMedicID = "";
	m_strMedicName = "";
	m_strMedicNumber = "";
	m_strMedicPrice = "";
	m_strGuarantPeriod = "";
	m_strProduceCompany = "";
	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetFocus();

	UpdateData(FALSE);
}


void CStoreMedicDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!m_bFlag)
	{
		CDialog::OnCancel();
		return;
	}
	
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &pMain->medicSet;
	pMedicSet->m_strFilter = _T("");
	pMedicSet->Requery();

	CMedic::RefreshReport(pMedicSet);

	CDialog::OnCancel();
}


void CStoreMedicDlg::OnEnKillfocusEditId()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &pMain->medicSet;
	pMedicSet->m_strFilter="MedicID='"+m_strMedicID+"'";
	pMedicSet->Requery();
	if (pMedicSet->GetRecordCount())
	{
		BOOL Ret = AfxMessageBox("该编号的药品已存在，是否增加数量？",MB_OKCANCEL);
		if (Ret == IDCANCEL)
		{
			m_strMedicID = "";
			UpdateData(FALSE);
		}
		else
		{
			((CEdit *)GetDlgItem(IDC_EDIT_NAME))->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_EDIT_TYPE))->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_EDIT_KEEP))->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_EDIT_PRICE))->EnableWindow(FALSE);
			((CEdit *)GetDlgItem(IDC_EDIT_COMPANY))->EnableWindow(FALSE);
			((CDateTimeCtrl *)GetDlgItem(IDC_EDIT_DATE))->EnableWindow(FALSE);
			m_bNumber = TRUE;
		}		
	}

}

void CStoreMedicDlg::OnEnKillfocusEditName()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &pMain->medicSet;
	pMedicSet->m_strFilter="MedicName='"+m_strMedicName+"'";
	pMedicSet->Requery();
	if (pMedicSet->GetRecordCount())
	{
		AfxMessageBox("药品名称已存在，请重新输入");
		m_strMedicName = "";
		UpdateData(FALSE);

		CEdit *pName = (CEdit *)GetDlgItem(IDC_EDIT_NAME);
		pName->SetFocus();
	}

}
