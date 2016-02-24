// test.h : CTestuser 类的实现



// CTestuser 实现

// 代码生成在 2014年8月4日, 14:53

#include "stdafx.h"
#include "test.h"
IMPLEMENT_DYNAMIC(CTestuser, CRecordset)

CTestuser::CTestuser(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_UserAccount = L"";
	m_UserPasswd = L"";
	m_UserType = L"";
	m_nFields = 3;
	m_nDefaultType = snapshot;
}

CString CTestuser::GetDefaultConnect()
{
	return _T("DSN=MyDb;DBQ=C:\\USERS\\ADMINISTRATOR\\DESKTOP\\MedicSystem\\db\\mydb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CTestuser::GetDefaultSQL()
{
	return _T("[user]");
}

void CTestuser::DoFieldExchange(CFieldExchange* pFX)
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
// CTestuser 诊断

#ifdef _DEBUG
void CTestuser::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTestuser::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


