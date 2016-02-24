// LogInDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicSystem.h"
#include "LogInDlg.h"
#include "MainFrm.h"

// CLogInDlg 对话框

IMPLEMENT_DYNAMIC(CLogInDlg, CDialog)

CLogInDlg::CLogInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogInDlg::IDD, pParent)
{
	m_userAccount = _T("admin");
	m_userPasswd = _T("admin");
	m_userType = _T("管理员");
	m_PreUserAccount = _T("");
}

CLogInDlg::~CLogInDlg()
{
}

void CLogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_ACCOUNT,m_userAccount);
	DDX_Text(pDX,IDC_EDIT_PASSWD,m_userPasswd);
	DDX_CBString(pDX,IDC_COMBO_TYPE,m_userType);
}


BEGIN_MESSAGE_MAP(CLogInDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_ACCOUNT, &CLogInDlg::OnEnKillfocusEditAccount)
END_MESSAGE_MAP()


// CLogInDlg 消息处理程序

BOOL CLogInDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始

	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,0,460,300,SWP_NOZORDER);//设置对话框大小和位置
	CenterWindow();

	AnimateWindow(500,AW_VER_POSITIVE | AW_HOR_POSITIVE);
	/*HINSTANCE instance = LoadLibrary(_T("User32.DLL");
	typedef BOOL(WINAPI myFun(HWND,DWORD,WORD));
	myFun *Animate;
	Animate = (myFun *)::GetProcAddress(instance,_T("AnimateWindow");
	Animate(this->m_hWnd,2000,AW_CENTER);
	FreeLibrary(instance);*/

	//CButton *pLogIn = (CButton *)GetDlgItem(IDOK);
	//m_btnOK.SetBitmap(CSize(20,20),IDB_HEAD);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLogInDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	ExitProcess(1);
}

void CLogInDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	UpdateData(TRUE);//更新控件里的数据到成员对象中
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	CUser *pUser = &pMainWnd->user;
	pUser->SetAllMembers(m_userAccount,m_userPasswd,m_userType);
	CUserSet *pUserSet = &pMainWnd->userSet;
	BOOL flag = pUser->LogIn(pUserSet);
	if (flag)
	{
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox(_T("登录信息有误，请重新输入"));
		m_userAccount = _T("");
		m_userPasswd = _T("");
		UpdateData(FALSE);//更新成员变量的数据到控件中
		
 	    (CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
	}
}

void CLogInDlg::OnEnKillfocusEditAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (GetFocus() == GetDlgItem(IDCANCEL) || m_PreUserAccount == m_userAccount
		 || "" == m_userAccount )
	{
		return;
	}
	CMainFrame *pMainWnd = (CMainFrame *)AfxGetMainWnd();
	CUserSet *pUserSet = &pMainWnd->userSet;
	pUserSet->m_strFilter = "UserAccount='"+m_userAccount+"'";
	pUserSet->Requery();
	if (!pUserSet->GetRecordCount())
	{
		AfxMessageBox("无效的用户名！");
		(CEdit *)GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
		m_PreUserAccount = m_userAccount;
	}
}
