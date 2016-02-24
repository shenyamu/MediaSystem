
#pragma once


#include "UserSet.h"

class CUser
{
public:
	CUser(void);
	~CUser(void);
	BOOL AddNewUser(CUserSet *pUserSet);
	BOOL DeleteUser(CUserSet *pUserSet);
	void ModifyPasswd(CUserSet *pUserSet);
	BOOL SeekUserInfo(int typeRadio,CString str, CUserSet *theSet);
	void SetAllMembers(CString strAccount,CString strPasswd,CString strType);
	void SetPasswd(CString strPasswd);
	void SetAccount(CString strAccount);
	BOOL LogIn(CUserSet *userSet);
	CString GetAccount();
	CString GetPasswd();
	CString GetType();
private:
	CString m_strAccount;
	CString m_strPasswd;
	CString m_strType;
};
