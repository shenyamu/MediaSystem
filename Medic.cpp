#include "StdAfx.h"
#include "Medic.h"
#include "Globol.h"
#include "MedicManage.h"

CMedic::CMedic(void)
{
}

CMedic::~CMedic(void)
{
}


void CMedic::MedicSearch(CMedicSet *pMedicSet, CString str1, int flag)
{
	if(flag==0)
	{
		pMedicSet->m_strFilter="MedicID='"+str1+"'";
	}
	else if(flag==1)
	{
		pMedicSet->m_strFilter="MedicName='"+str1+"'";
	}
	else if(flag==2)
	{
		pMedicSet->m_strFilter="MedicType='"+str1+"'";
	}
	else
	{
		return;
	}
	pMedicSet->Requery();
	RefreshReport(pMedicSet);
}


void CMedic::MedicSearchAll()
{
	CMainFrame *p = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &p->medicSet;
	pMedicSet->m_strFilter = "";
	pMedicSet->Requery();
	RefreshReport(pMedicSet);
}


void CMedic::MedicSearchZeroNumber()
{
	CMainFrame *p = (CMainFrame *)AfxGetMainWnd();
	CMedicSet *pMedicSet = &p->medicSet;
	pMedicSet->m_strFilter = "MedicNumber=0";
	pMedicSet->Requery();
	RefreshReport(pMedicSet);
}

void CMedic::MedicSearchOutDate()
{
	CMainFrame *p = (CMainFrame *)AfxGetMainWnd();
	CXTPReportControl *pReport = p->m_wndReportCtrl;
	CXTPReportRecords *pRecords = pReport->GetRecords();
	pRecords->RemoveAll();
	

	CXTPReportRecord *pRecord;

	CMedicSet *pMedicSet = &p->medicSet;
	pMedicSet->m_strFilter = "";
	pMedicSet->Requery();
	CMedicManage ManMedic;
	CTime CurDate = CTime::GetCurrentTime();
	CString strPrice;
	while(!pMedicSet->IsEOF())
	{
		ManMedic.SetMedicSet(pMedicSet);
		CTime OutDate = ManMedic.GetOutDateTime();
		/*CString k = OutDate.Format(_T("%Y-%m-%d"));*/
		
		if (OutDate < CurDate)
		{
			pRecord = new CXTPReportRecord();
			pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicID));
			pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicName));
			pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicType));
			CTime ProduceData = pMedicSet->m_ProduceDate;
			pRecord->AddItem(new CXTPReportRecordItemText(ProduceData.Format(_T("%Y-%m-%d"))));
			pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_MedicNumber));
			strPrice.Format("%.2f",pMedicSet->m_MedicPrice);
			pRecord->AddItem(new CXTPReportRecordItemText(strPrice));
			pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_GuarantPeriod));
			pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_ProduceCompany));
			pReport->AddRecord(pRecord);
		}
		pMedicSet->MoveNext();
	}
	pReport->Populate();
}


void CMedic::RefreshReport( CMedicSet *pMedicSet )
{
	CMainFrame *p = (CMainFrame *)AfxGetMainWnd();
	CXTPReportControl *pReport = p->m_wndReportCtrl;
	CXTPReportRecords *pRecords = pReport->GetRecords();
	pRecords->RemoveAll();

	CXTPReportRecord *pRecord;
	CXTPReportRecordItem *pItem;
	CString strPrice;
	while(!pMedicSet->IsEOF())
	{
		pRecord = new CXTPReportRecord();
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicID));
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicName));
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicType));
		CTime ProduceData = pMedicSet->m_ProduceDate;
		pRecord->AddItem(new CXTPReportRecordItemText(ProduceData.Format(_T("%Y-%m-%d"))));
		if (0 == pMedicSet->m_MedicNumber)
		{
			pItem = pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_MedicNumber));
			pItem->SetBackgroundColor(RGB(255,0,0));
		}
		else
			pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_MedicNumber));
		strPrice.Format("%.2f",pMedicSet->m_MedicPrice);
		pRecord->AddItem(new CXTPReportRecordItemText(strPrice));
		pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_GuarantPeriod));
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_ProduceCompany));
		pReport->AddRecord(pRecord);
		pMedicSet->MoveNext();
	}
	pReport->Populate();
	
}
