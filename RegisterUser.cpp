// RegisterUser.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "RegisterUser.h"
#include "MainFrm.h"
#include "User.h"
#include "MyTreeView.h"

// CRegisterUser 对话框

IMPLEMENT_DYNAMIC(CRegisterUserDlg, CDialog)

CRegisterUserDlg::CRegisterUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterUserDlg::IDD, pParent)
{
	Flag = FALSE;
}

CRegisterUserDlg::~CRegisterUserDlg()
{
}

void CRegisterUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_REGISTER_LIST,m_UserList);
	DDX_Text(pDX,IDC_REGISTER_ACCOUNT,m_UserAccount);
	DDX_Text(pDX,IDC_REGISTER_PWD1,m_UserPasswd);
	DDX_Text(pDX,IDC_REGISTER_PWD2,m_UserPasswd2);
	DDX_Text(pDX,IDC_REGISTER_COMBO,m_UserType);

}


BEGIN_MESSAGE_MAP(CRegisterUserDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_REGISTER_ACCOUNT, &CRegisterUserDlg::OnEnKillfocusRegisterAccount)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRegisterUser 消息处理程序

BOOL CRegisterUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  在此添加额外的初始化

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pUserSet = &pMainFrm->userSet;
	pUserSet->m_strFilter="";
	pUserSet->Requery();

	CString userColumn[]={_T("ID"),_T("用户账号"),_T("用户密码"),_T("用户角色")};
	for(int i=0;i<4;i++)
	{
		m_UserList.InsertColumn(i,userColumn[i],LVCFMT_LEFT,102,i);
	}

	CString ID;
	for(int j=0;;j++)
	{
		if(pUserSet->IsEOF())
		{
			break;
		}
		ID.Format(_T("%d"),j+1);
		m_UserList.InsertItem(j,ID);
		m_UserList.SetItemText(j,1,pUserSet->m_UserAccount);
		m_UserList.SetItemText(j,2,pUserSet->m_UserPasswd);
		m_UserList.SetItemText(j,3,pUserSet->m_UserType);
		pUserSet->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRegisterUserDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	UpdateData();
	if(m_UserAccount=="")
	{
		AfxMessageBox(_T("用户账号不能为空"));
	}
	else if(m_UserPasswd != m_UserPasswd2)
	{
		AfxMessageBox(_T("两次输入的密码不一致"));
	}
	else if(m_UserPasswd == "")
	{
		AfxMessageBox(_T("密码不可为空"));
	}
	else if(m_UserType=="")
	{
		AfxMessageBox(_T("请选择用户的角色"));
	}
	else
	{
		CUser* newUser=new CUser;
		newUser->SetAllMembers(m_UserAccount,m_UserPasswd,m_UserType);
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
		CUserSet* pUserSet = &pMainFrm->userSet;
		if(newUser->AddNewUser(pUserSet))
		{
			int number=m_UserList.GetItemCount();
			CString ID;
			ID.Format(_T("%d"),number+1);
			m_UserList.InsertItem(number,ID);
			m_UserList.SetItemText(number,1,m_UserAccount);
			m_UserList.SetItemText(number,2,m_UserPasswd);
			m_UserList.SetItemText(number,3,m_UserType);

			AfxMessageBox(_T("增加用户成功"));

			m_UserAccount=_T("");
			m_UserPasswd=_T("");
			m_UserPasswd2=_T("");
			m_UserType=_T("");
			UpdateData(FALSE);

			Flag = TRUE;
		}	
	}
}
void CRegisterUserDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	if (!Flag)
	{
		CDialog::OnCancel();
		return;
	}

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CUserSet* pUserSet = &pMainFrm->userSet;
	CUser* pUser = &pMainFrm->user;
	
	CMyTreeView* pTreeView = (CMyTreeView *)(pMainFrm->m_wndSplitterWnd).GetPane(0,0);
	CTreeCtrl* m_theTreeCtrl=pTreeView->m_TreeCtrl;
	m_theTreeCtrl->DeleteAllItems();
	HTREEITEM rootItem;
	rootItem = m_theTreeCtrl->InsertItem(_T("用户列表"),2,2,TVI_ROOT);

	CString userTreeHeader[3]={"管理员","售药员","医生"};
	HTREEITEM userItem[3];
	for(int i=0;i<3;i++)
	{
		userItem[i]=m_theTreeCtrl->InsertItem(userTreeHeader[i],2,2,rootItem);
		m_theTreeCtrl->SetItemData(userItem[i],(DWORD)i);
	}

	HTREEITEM thePoint;
	for(int i=0;i<3;i++)
	{
		pUserSet->m_strFilter = "UserType='"+userTreeHeader[i]+"'";
		pUserSet->Requery();
		for(int j=0;;j++)
		{
			if(pUserSet->IsEOF())
			{
				break;
			}	
			if(pUserSet->m_UserAccount == pUser->GetAccount())
			{
				HTREEITEM userSpecifics = m_theTreeCtrl->InsertItem(pUserSet->m_UserAccount+"(当前用户)",0,0,userItem[i]);
				m_theTreeCtrl->SetItemData(userSpecifics,(DWORD)j);
				thePoint = userSpecifics;
			}
			else
			{
				HTREEITEM userSpecifics = m_theTreeCtrl->InsertItem(pUserSet->m_UserAccount,1,1,userItem[i]);
				m_theTreeCtrl->SetItemData(userSpecifics,(DWORD)j);
			}
			pUserSet->MoveNext();
		}
	}

	m_theTreeCtrl->Select(thePoint,TVGN_CARET);

	CDialog::OnCancel();
}


void CRegisterUserDlg::OnEnKillfocusRegisterAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	if (GetFocus() == GetDlgItem(IDCANCEL))
	{
		return;
	}
	UpdateData();
	CString strFilter;
	strFilter.Format(_T("UserAccount=\'%s\'"),m_UserAccount);
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CUserSet* pUserSet = &pMainFrm->userSet;
	pUserSet->m_strFilter = strFilter;
	pUserSet->Requery();
	if(pUserSet->GetRecordCount())
	{
		AfxMessageBox(_T("该账号已经存在"));		
		GetDlgItem(IDC_REGISTER_ACCOUNT)->SetFocus();
		return;
	}
}

void CRegisterUserDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnCancel();
}
