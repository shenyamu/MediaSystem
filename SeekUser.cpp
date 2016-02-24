// SeekUser.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "SeekUser.h"

// CSeekUser 对话框

IMPLEMENT_DYNAMIC(CSeekUserDlg, CDialog)

CSeekUserDlg::CSeekUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeekUserDlg::IDD, pParent)
{
	m_strAccount = _T("");
	m_strUsertype = _T("");
	m_ntypeRadio = -1;
}

CSeekUserDlg::~CSeekUserDlg()
{
}

void CSeekUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_SEEK_LIST,m_UserList);
	DDX_Text(pDX,IDC_SEEK_EDIT,m_strAccount);
	DDX_CBString(pDX,IDC_SEEK_COMBO,m_strUsertype);
	DDX_Radio(pDX,IDC_SEEK_RADIO1,m_ntypeRadio);
}


BEGIN_MESSAGE_MAP(CSeekUserDlg, CDialog)
END_MESSAGE_MAP()


// CSeekUser 消息处理程序

BOOL CSeekUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ntypeRadio=0;
	UpdateData(FALSE);
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

	//CString ID;
	//for(int j=0;;j++)
	//{
	//	if(pUserSet->IsEOF())
	//	{
	//		break;
	//	}
	//	ID.Format(_T("%d"),j+1);
	//	m_UserList.InsertItem(j,ID);
	//	m_UserList.SetItemText(j,1,pUserSet->m_UserAccount);
	//	m_UserList.SetItemText(j,2,pUserSet->m_UserPasswd);
	//	m_UserList.SetItemText(j,3,pUserSet->m_UserType);
	//	pUserSet->MoveNext();
	//}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSeekUserDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	UpdateData(TRUE);
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CUser* theUser=&pMainFrm->user;

	CString str;
	if(m_ntypeRadio==0)
	{
		str = m_strUsertype;
	}
	else
	{
		str=m_strAccount;
	}

	if(!theUser->SeekUserInfo(m_ntypeRadio,str,pUserSet))
		return;
	
	m_UserList.DeleteAllItems();

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
		m_UserList.SetItemText(j,2,"******");
		m_UserList.SetItemText(j,3,pUserSet->m_UserType);
		pUserSet->MoveNext();
	}
	//CDialog::OnOK();
}
