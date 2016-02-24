// SaleSet.h : CSaleSet 类的实现



// CSaleSet 实现

// 代码生成在 2014年8月13日, 16:43

#include "stdafx.h"
#include "SaleSet.h"
IMPLEMENT_DYNAMIC(CSaleSet, CRecordset)

CSaleSet::CSaleSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_MedicID = L"";
	m_MedicName = L"";
	m_MedicPrice = 0.0;
	m_MedicNumber = 0;
	m_TotalMoney = 0.0;
	m_nFields = 5;
	m_nDefaultType = snapshot;
}

CString CSaleSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MyDb");
}

CString CSaleSet::GetDefaultSQL()
{
	return _T("[saleTable]");
}

void CSaleSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[MedicID]"), m_MedicID);
	RFX_Text(pFX, _T("[MedicName]"), m_MedicName);
	RFX_Single(pFX, _T("[MedicPrice]"), m_MedicPrice);
	RFX_Int(pFX, _T("[MedicNumber]"), m_MedicNumber);
	RFX_Single(pFX, _T("[TotalMoney]"), m_TotalMoney);

}
/////////////////////////////////////////////////////////////////////////////
// CSaleSet 诊断

#ifdef _DEBUG
void CSaleSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSaleSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


