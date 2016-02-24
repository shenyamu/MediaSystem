#include "StdAfx.h"
#include "MedicManage.h"

CMedicManage::CMedicManage(void)
{
	m_theMedic = NULL;
	m_theMedicSet = NULL;
}

CMedicManage::~CMedicManage(void)
{
}

void CMedicManage::SetMedicSet( CMedicSet* theMedicSet )
{
	m_theMedicSet = theMedicSet;
}

void CMedicManage::SetMedic( CMedic* theMedic )
{
	m_theMedic = theMedic;
}


CTime CMedicManage::GetOutDateTime()
{
	CTime timeProduce = m_theMedicSet->m_ProduceDate;
	int quelity = m_theMedicSet->m_GuarantPeriod;
	int month = (timeProduce.GetMonth()+quelity) % 12;//12月份特殊考虑
	if(0 == month)
	{
		month = 12;
	}
	int year = (timeProduce.GetMonth()+quelity)/12+timeProduce.GetYear();
	if(12 == month)
	{
		year=year-1;//过期月份为12月，则年份减一
	}
	int day = timeProduce.GetDay();
	CTime OutDate(year,month,day,0,0,0);	
	return OutDate;
}


BOOL CMedicManage::Storage(BOOL bFlag)
{
	if(bFlag)//判断是否单纯添加某一存在药品的数量
	{
		if (m_theMedic->m_strMedicNumber == 0)
		{
			AfxMessageBox("药品数量输入不正确");
			return FALSE;
		}
		m_theMedicSet->Edit();
		m_theMedicSet->m_MedicNumber += m_theMedic->m_strMedicNumber;
		if(m_theMedicSet->CanUpdate())
		{
			m_theMedicSet->Update();
		}
	}
	else
	{
		//m_theMedicSet->MoveLast();
		m_theMedicSet->AddNew();
		m_theMedicSet->m_MedicID = m_theMedic->m_strMedicID;
		m_theMedicSet->m_MedicName = m_theMedic->m_strMedicName;
		m_theMedicSet->m_MedicType = m_theMedic->m_strMedicType;
		m_theMedicSet->m_ProduceCompany = m_theMedic->m_ProduceCompany;
		m_theMedicSet->m_ProduceDate = m_theMedic->m_strProduceDate;
		m_theMedicSet->m_MedicNumber=m_theMedic->m_strMedicNumber;
		m_theMedicSet->m_GuarantPeriod=m_theMedic->m_strGuarantPeriod;
		m_theMedicSet->m_MedicPrice = m_theMedic->m_strMedicPrice;
		if(m_theMedicSet->CanUpdate())
		{
			m_theMedicSet->Update();
		}
	}
	return TRUE;
}
//删除药品数量为0的药品
BOOL CMedicManage::DelMedicZeroNumber()
{
	BOOL bFlag = FALSE;
	m_theMedicSet->m_strFilter = _T("MedicNumber=0");
	m_theMedicSet->Requery();
	if (m_theMedicSet->GetRecordCount())
	{
		bFlag = TRUE;
	}

	while(!m_theMedicSet->IsEOF())
	{
		m_theMedicSet->Delete();
		m_theMedicSet->MoveNext();
	}
	return bFlag;
}
//删除过期药品
BOOL CMedicManage::DelMedicOutDate()
{
	BOOL bFlag = FALSE;
	m_theMedicSet->m_strFilter = _T("");
	m_theMedicSet->Requery();
	while(!m_theMedicSet->IsEOF())
	{
		CTime CurTime = CTime::GetCurrentTime();
		CTime OutTime = GetOutDateTime();
		if (OutTime < CurTime)
		{
			m_theMedicSet->Delete();
			bFlag = TRUE;
		}
		m_theMedicSet->MoveNext();
	}
	return bFlag;
}
