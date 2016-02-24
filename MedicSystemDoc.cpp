// MedicSystemDoc.cpp : CMedicSystemDoc 类的实现
//

#include "stdafx.h"
#include "MedicSystem.h"

#include "MedicSystemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMedicSystemDoc

IMPLEMENT_DYNCREATE(CMedicSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CMedicSystemDoc, CDocument)
END_MESSAGE_MAP()


// CMedicSystemDoc 构造/析构

CMedicSystemDoc::CMedicSystemDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMedicSystemDoc::~CMedicSystemDoc()
{
}

BOOL CMedicSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMedicSystemDoc 序列化

void CMedicSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMedicSystemDoc 诊断

#ifdef _DEBUG
void CMedicSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMedicSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMedicSystemDoc 命令
