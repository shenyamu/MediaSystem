// MedicSet.h : CMedicSet 类的实现



// CMedicSet 实现

// 代码生成在 2014年7月22日, 16:51

#include "stdafx.h"
#include "MedicSet.h"
IMPLEMENT_DYNAMIC(CMedicSet, CRecordset)

CMedicSet::CMedicSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_MedicID = _T("");
	m_MedicName = _T("");
	m_MedicType = _T("");
	m_ProduceDate;
	m_MedicNumber = 0;
	m_MedicPrice = 0.0;
	m_GuarantPeriod = 0;
	m_ProduceCompany = _T("");
	m_nFields = 8;
	m_nDefaultType = snapshot;
}

CString CMedicSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MyDb");
}

CString CMedicSet::GetDefaultSQL()
{
	return _T("[medicine]");
}

void CMedicSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[MedicID]"), m_MedicID);
	RFX_Text(pFX, _T("[MedicName]"), m_MedicName);
	RFX_Text(pFX, _T("[MedicType]"), m_MedicType);
	RFX_Date(pFX, _T("[ProduceDate]"), m_ProduceDate);
	RFX_Int(pFX, _T("[MedicNumber]"), m_MedicNumber);
	RFX_Single(pFX, _T("[MedicPrice]"), m_MedicPrice);
	RFX_Int(pFX, _T("[GuarantPeriod]"), m_GuarantPeriod);
	RFX_Text(pFX, _T("[ProduceCompany]"), m_ProduceCompany);

}
/////////////////////////////////////////////////////////////////////////////
// CMedicSet 诊断

#ifdef _DEBUG
void CMedicSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMedicSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


