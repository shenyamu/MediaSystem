// UserSet.h : CUserSet 类的实现



// CUserSet 实现

// 代码生成在 2014年7月21日, 9:11

#include "stdafx.h"
#include "UserSet.h"

IMPLEMENT_DYNAMIC(CUserSet, CRecordset)

CUserSet::CUserSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_UserAccount = _T("");
	m_UserPasswd = _T("");
	m_UserType = _T("");
	m_nFields = 3;
	m_nDefaultType = snapshot;
}


CString CUserSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MyDb");
}

CString CUserSet::GetDefaultSQL()
{
	return _T("[user]");
}

void CUserSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[UserAccount]"), m_UserAccount);
	RFX_Text(pFX, _T("[UserPasswd]"), m_UserPasswd);
	RFX_Text(pFX, _T("[UserType]"), m_UserType);

}
/////////////////////////////////////////////////////////////////////////////
// CUserSet 诊断

#ifdef _DEBUG
void CUserSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


