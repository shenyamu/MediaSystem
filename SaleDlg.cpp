// SaleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "SaleDlg.h"

// CSaleDlg 对话框

IMPLEMENT_DYNAMIC(CSaleMedicDlg, CDialog)

CSaleMedicDlg::CSaleMedicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaleMedicDlg::IDD, pParent)
{
	m_strMedicName = "";
	m_strMedicType = "";
	m_nMedicNumber = 0;
	m_vecSaleBills.clear();
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pSaleSet = &pMainFrm->saleSet;
	pMedicSet = &pMainFrm->medicSet;
}

CSaleMedicDlg::~CSaleMedicDlg()
{
}

void CSaleMedicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_ListCtrl);
	DDX_Text(pDX,IDC_MEDIC_NAME,m_strMedicName);
	DDX_Text(pDX,IDC_MEDIC_TYPE,m_strMedicType);
	DDX_Text(pDX,IDC_MEDIC_NUMBER,m_nMedicNumber);
}


BEGIN_MESSAGE_MAP(CSaleMedicDlg, CDialog)
	ON_BN_CLICKED(IDC_SALE_ADD, &CSaleMedicDlg::OnBnClickedSaleAdd)
	ON_CBN_SELCHANGE(IDC_MEDIC_TYPE, &CSaleMedicDlg::OnCbnSelchangeMedicType)
	ON_BN_CLICKED(IDC_SALE_DEL, &CSaleMedicDlg::OnBnClickedSaleDel)
	ON_BN_CLICKED(IDOK, &CSaleMedicDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDUNDO, &CSaleMedicDlg::OnBnClickedUndo)
	ON_BN_CLICKED(IDCANCEL, &CSaleMedicDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSaleDlg 消息处理程序

BOOL CSaleMedicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CString strSale[] = {"药品编号","药品名称","出售数量","药品单价","总金额"};
	for (int i = 0;i < 5;i++)
	{
		m_ListCtrl.InsertColumn(i,strSale[i],LVCFMT_LEFT,86);
	}
	
	if (!pSaleSet->IsOpen())
	{
		pSaleSet->Open();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSaleMedicDlg::OnCbnSelchangeMedicType()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CComboBox *pName = (CComboBox *)GetDlgItem(IDC_MEDIC_NAME);
	pName->ResetContent();
	pMedicSet->m_strFilter = "MedicType= '"+m_strMedicType+"'";
	pMedicSet->Requery();
	while(!pMedicSet->IsEOF())
	{
		pName->AddString(pMedicSet->m_MedicName);
		pMedicSet->MoveNext();
	}
}


//添加按钮响应事件函数
void CSaleMedicDlg::OnBnClickedSaleAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if ("" == m_strMedicType)
	{
		AfxMessageBox("请选择药品类型");
		return;
	}
	if ("" == m_strMedicName)
	{
		AfxMessageBox("请选择药品名称");
		return;
	}

	CSale *bufSale;
	vector<CSale *>::iterator it = m_vecSaleBills.begin();
	for (;it != m_vecSaleBills.end();++it)
	{
		bufSale = *it;
		if (bufSale->m_MedicName == m_strMedicName)
		{
			AfxMessageBox("此药品已在本次出售单中，请先删除");
			return;
		}
	}
	
	pMedicSet->m_strFilter = "MedicName='"+m_strMedicName+"'";
	pMedicSet->Requery();

	if (0 == m_nMedicNumber)
	{
		AfxMessageBox("请输入正确的出售数量");
		return;
	}
	else if (m_nMedicNumber > pMedicSet->m_MedicNumber)
	{
		CString str;
		str.Format("库存数量不足，当前数量为%d",pMedicSet->m_MedicNumber);
		AfxMessageBox(str);
		return;
	}

	//判断是否过期
	CMedicManage medicManage;
	medicManage.SetMedicSet(pMedicSet);
	CTime OutTime = medicManage.GetOutDateTime();
	CTime CurTime = CTime::GetCurrentTime();
	if (OutTime < CurTime)
	{
		AfxMessageBox("所选择的药品已过期，请重新选择");
		return;
	}

	int number=m_ListCtrl.GetItemCount();
	CString str;
	str.Format("%d",m_nMedicNumber);
	m_ListCtrl.InsertItem(number,pMedicSet->m_MedicID);
	m_ListCtrl.SetItemText(number,1,pMedicSet->m_MedicName);
	m_ListCtrl.SetItemText(number,2,str);
	str.Format("%.2f",pMedicSet->m_MedicPrice);
	m_ListCtrl.SetItemText(number,3,str);
	str.Format("%.2f",pMedicSet->m_MedicPrice*m_nMedicNumber);
	m_ListCtrl.SetItemText(number,4,str);

	CSale *pSale = new CSale;
	pSale->m_MedicID = pMedicSet->m_MedicID;
	pSale->m_MedicName = pMedicSet->m_MedicName;
	pSale->m_MedicNumber = m_nMedicNumber;
	pSale->m_MedicPrice = pMedicSet->m_MedicPrice;
	pSale->m_TotalMoney = pMedicSet->m_MedicPrice*m_nMedicNumber;
	m_vecSaleBills.push_back(pSale);//添加未结算的销售单到容器中
	
	CComboBox *pType = (CComboBox *)GetDlgItem(IDC_MEDIC_TYPE);
	pType->SetCurSel(-1);
	CComboBox *pName = (CComboBox *)GetDlgItem(IDC_MEDIC_NAME);
	pName->SetCurSel(-1);
	pName->ResetContent();

	m_nMedicNumber = 0;
	UpdateData(FALSE);

}

//删除按钮响应事件函数
void CSaleMedicDlg::OnBnClickedSaleDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if ("" == m_strMedicType)
	{
		AfxMessageBox("请选择药品类型");
		return;
	}
	if ("" == m_strMedicName)
	{
		AfxMessageBox("请选择药品名称");
		return;
	}

	CSale *bufSale;
	vector<CSale *>::iterator it = m_vecSaleBills.begin();
	for (;it != m_vecSaleBills.end();)
	{
		bufSale = *it;
		if (bufSale->m_MedicName == m_strMedicName)
		{
			it = m_vecSaleBills.erase(it);
			break;
		}
		else
			++it;
	}

	if (it == m_vecSaleBills.end())
	{
		AfxMessageBox("选择的药品不在本次出售单中，请重新选择");
		return;
	}

	CString str;
	str.Format("删除出售单中的药品%s成功",m_strMedicName);
	AfxMessageBox(str);

	int nCounts = m_ListCtrl.GetItemCount();
	for (int i = 0;i < nCounts;i++)
	{
		if (m_ListCtrl.GetItemText(i,1) == m_strMedicName)
		{
			m_ListCtrl.DeleteItem(i);
			//m_ListCtrl.RedrawItems(0,nCounts);
			break;
		}
	}
	
}

void CSaleMedicDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	if (m_vecSaleBills.empty())
	{
		AfxMessageBox("当前未添加任何药品");
		return;
	}

	CSale *bufSale;
	float fMoney = 0;
	vector<CSale *>::iterator it = m_vecSaleBills.begin();
	for (;it != m_vecSaleBills.end();it++)
	{
		bufSale = *it;
		pSaleSet->AddNew();
		pSaleSet->m_MedicID = bufSale->m_MedicID;
		pSaleSet->m_MedicName = bufSale->m_MedicName;
		pSaleSet->m_MedicNumber = bufSale->m_MedicNumber;
		pSaleSet->m_MedicPrice = bufSale->m_MedicPrice;
		pSaleSet->m_TotalMoney = bufSale->m_TotalMoney;
		if (pSaleSet->CanUpdate())
		{
			pSaleSet->Update();
		}
		fMoney += bufSale->m_TotalMoney;
	}

	CString str;
	str.Format("结算成功，请支付%.1f元",fMoney);
	AfxMessageBox(str);

	m_vecSaleBills.clear();
	m_ListCtrl.DeleteAllItems();
}

void CSaleMedicDlg::OnBnClickedUndo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_vecSaleBills.size())
	{
		if (AfxMessageBox("确定撤销所有出售单药品？",MB_YESNO) == IDYES)
		{
			m_vecSaleBills.clear();
			m_ListCtrl.DeleteAllItems();
		}
	}
	else
		AfxMessageBox("当前未添加任何药品");
	
}

void CSaleMedicDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_vecSaleBills.size())
	{
		AfxMessageBox("退出之前请先结算或撤销");
		return;
	}
	OnCancel();
}
