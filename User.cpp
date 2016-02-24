#include "StdAfx.h"
#include "User.h"

CUser::CUser(void)
{
}

CUser::~CUser(void)
{
}

void CUser::SetAllMembers(CString strAccount,CString strPasswd,CString strType)
{
	m_strAccount = strAccount;
	m_strPasswd = strPasswd;
	m_strType = strType;
}


BOOL CUser::LogIn(CUserSet *userSet)
{
	CString strFilter;
	strFilter.Format(_T("UserAccount=\'%s\' and UserPasswd=\'%s\' and UserType=\'%s\'"),m_strAccount,m_strPasswd,m_strType);
  	//userSet->m_strFilter=_T("UserAccount='"+m_strAccount+"' and UserPasswd='"+m_strPasswd+"' and UserType='"+m_strType+"'");
	userSet->m_strFilter = strFilter;
	userSet->Requery();
	if(userSet->GetRecordCount())
	{
		return TRUE;
	}
	return FALSE;
}


CString CUser::GetAccount()
{
	return m_strAccount;
}


CString CUser::GetPasswd()
{
	return m_strPasswd;
}

CString CUser::GetType()
{
	return m_strType;
}

void CUser::SetPasswd( CString strPasswd )
{
	m_strPasswd = strPasswd;
}

BOOL CUser::AddNewUser(CUserSet *pUserSet)
{
	pUserSet->AddNew();
	pUserSet->m_UserAccount = m_strAccount;
	pUserSet->m_UserPasswd = m_strPasswd;
	pUserSet->m_UserType = m_strType;
	if(pUserSet->CanUpdate())
	{
		pUserSet->Update();
	}
	if(!pUserSet->IsEOF())
	{
		pUserSet->MoveLast();
	}
	
	pUserSet->Requery();

	return TRUE;
}

void CUser::ModifyPasswd( CUserSet *pUserSet )
{
	pUserSet->Edit();
	pUserSet->m_UserPasswd = m_strPasswd;
	if (pUserSet->CanUpdate())
	{
		pUserSet->Update();
	}
}

BOOL CUser::DeleteUser( CUserSet *pUserSet )
{
	pUserSet->m_strFilter = "UserAccount='"+m_strAccount+"'";
	pUserSet->Requery();
	if(!pUserSet->GetRecordCount())
	{
		AfxMessageBox("您要删除的用户不存在");
		return FALSE;
	}
	else
	{
		pUserSet->Delete();
		return TRUE;
	}
}

void CUser::SetAccount( CString strAccount )
{
	m_strAccount = strAccount;
}



BOOL CUser::SeekUserInfo(int typeRadio,CString str, CUserSet *theSet)
{
	if(typeRadio==0)
	{
		if(str=="")
		{
			AfxMessageBox("请选择要查询的用户角色");
			return FALSE;
		}
		else if(str=="所有角色")
		{
			theSet->m_strFilter="";
		}
		else
		{
			theSet->m_strFilter="UserType='"+str+"'";
		}
	}
	else if(typeRadio==1)
	{
		if(str=="")
		{
			AfxMessageBox("请输入要查询的用户账号");
			return FALSE;
		}
		else
		{
			theSet->m_strFilter="UserAccount='"+str+"'";
		}
	}
	theSet->Requery();
	return TRUE;
}


