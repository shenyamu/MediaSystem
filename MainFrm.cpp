// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MedicSystem.h"

#include "MainFrm.h"
#include "MyTreeView.h"
#include "MedicSystemDoc.h"
#include "RegisterUser.h"
#include "DelUser.h"
#include "SeekUser.h"
#include "ChangeUserDlg.h"
#include "ModifyPasswdDlg.h"

#include "MedicIDSeekDlg.h"
#include "MedicNameSeekDlg.h"
#include "MedicTypeSeekDlg.h"
#include "StoreMedic.h"
#include "CleanMedicDlg.h"
#include "SaleDlg.h"
#include "ReportField.h"
#include "WorkStatusGuard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()	//处理框架窗口关闭响应消息
	ON_COMMAND(ID_USER_ADD,OnRegisterUser)
	ON_COMMAND(ID_USER_DEL,OnDelUser)
	ON_COMMAND(ID_USER_SEEK,OnSeekUser)
	ON_COMMAND(ID_USER_MODPWD,OnModUserPasswd)
	ON_COMMAND(ID_USER_CHANGE,OnChangeUser)
	ON_COMMAND(ID_USER_LOGOUT,OnClose)

	ON_COMMAND(ID_SEEK_NUMBER,OnMedicSeekID)
	ON_COMMAND(ID_SEEK_NAME,OnMedicSeekName)
	ON_COMMAND(ID_SEEK_TYPE,OnMedicSeekType)

	ON_COMMAND(ID_SEEK_ALL,OnMedicSearchAll)
	ON_COMMAND(ID_SEEK_ZERO,OnMedicSearchZeroNumber)
	ON_COMMAND(ID_SEEK_OUTDATE,OnMedicSearchOutDate)
	
	ON_COMMAND(ID_MEDIC_ADD,OnMedicStore)
	ON_COMMAND(ID_MEDIC_CLEAN,OnMedicClean)
	ON_COMMAND(ID_MEDIC_SALE,OnMedicSale)

	//ON_UPDATE_COMMAND_UI_RANGE(ID_SEEK_NUMBER,ID_SEEK_OUTDATE,OnUpdateNormalButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MEDIC_ADD,ID_MEDIC_CLEAN,OnUpdateNormalButton)

	ON_COMMAND(ID_SEEK_FILTER,OnReportFind)
	ON_COMMAND(ID_REPORT_SET,OnReportSet)
	//ON_UPDATE_COMMAND_UI(ID_SEEK_FILTER,OnUpdateNormalButton)

	ON_UPDATE_COMMAND_UI_RANGE(ID_USER_ADD,ID_USER_SEEK,OnUpdateUserManger)
	ON_UPDATE_COMMAND_UI_RANGE(ID_USER_CHANGE,ID_USER_LOGOUT,OnUpdateUserManger)

	ON_COMMAND(ID_RIBBON_MINIMIZE, OnToggleRibbonBars)
	ON_COMMAND(ID_RIBBON_EXPAND, OnToggleRibbonBars)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_MINIMIZE, OnUpdateRibbonMinimize)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_EXPAND, OnUpdateRibbonExpand)

	ON_COMMAND_RANGE(ID_STYLES_OFFICE2007BLUE,ID_STYLES_OFFICE2010BLACK,OnOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_STYLES_OFFICE2007BLUE,ID_STYLES_OFFICE2010BLACK,OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI(ID_STYLE_POPBTN,OnUpdateOptionsStyle)

	ON_COMMAND_RANGE(ID_STYLE_FONT1,ID_STYLE_FONT4,OnChangeFont)
	ON_UPDATE_COMMAND_UI_RANGE(ID_STYLE_FONT1,ID_STYLE_FONT4,OnUpdateFonts)
	ON_UPDATE_COMMAND_UI(ID_STYLE_FONT,OnUpdateFonts)
	
	ON_COMMAND_RANGE(ID_SKIN1,ID_SKIN5,OnSelectSkin)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SKIN1,ID_SKIN5,OnUpdateSkin)
	ON_UPDATE_COMMAND_UI(ID_STYLE_SKIN,OnUpdateSkin)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	m_nRibbonStyle = ID_STYLES_OFFICE2007BLUE;
	m_nFont = ID_STYLE_FONT1;
	m_nSkin = ID_SKIN1;
	pSeek = NULL;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
 	if (!m_wndStatusBar.Create(this) ||
 		!m_wndStatusBar.SetIndicators(indicators,
 		  sizeof(indicators)/sizeof(UINT)))
 	{
 		TRACE0("未能创建状态栏\n");
 		return -1;
 	}
	
	InitCommandBars();// 初始化命令工具栏
	CreateRibbonBar();

	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics | xtpSkinApplyFrame);

	OnOptionsStyle(ID_STYLES_WINDOWS7SCENIC);
	//OnChangeFont(ID_STYLE_FONT1);
	CXTPPaintManager::SetTheme(xtpThemeOffice2007);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	
	m_wndSplitterWnd.CreateStatic(this,1,2);
	m_wndSplitterWnd.CreateView(0,0,RUNTIME_CLASS(CMyTreeView),CSize(200,600),pContext);
	m_wndSplitterWnd.CreateView(0,1,RUNTIME_CLASS(CXTPReportControl),CSize(700,600),pContext);

	InitReport();
	
	return TRUE;
	
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(),cs.lpszClass,CS_DBLCLKS,
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG



void CMainFrame::InitReport(void)
{
	if (medicSet.IsOpen())
	{
		medicSet.Close();
	}
	medicSet.Open();

	CXTPReportColumn* pColumn;
	m_wndReportCtrl = (CXTPReportControl *)m_wndSplitterWnd.GetPane(0,1);
	
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(0,_T("药品ID"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(1,_T("药品名称"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(2,_T("药品类型"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(3,_T("生产日期"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(4,_T("库存数量"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(5,_T("单价"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(6,_T("保质期(月)"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	pColumn = m_wndReportCtrl->AddColumn(new CXTPReportColumn(7,_T("生产地"),15));
	pColumn->SetHeaderAlignment(DT_CENTER);
	pColumn->SetAlignment(DT_CENTER);
	
	m_wndReportCtrl->ShowGroupBy(TRUE);//显示可按列分组的一个Group Box
	//m_wndReportCtrl->GetColumns()->GetGroupsOrder()->Add(m_wndReportCtrl->GetColumns()->GetAt(0));

	CMedicSet *pMedicSet = &(this->medicSet);
	pMedicSet->m_strFilter = _T("");
	pMedicSet->Requery();
	CXTPReportRecord *pRecord;
	CXTPReportRecordItem *pRecordItem;
	CTime ProduceData;
	CString strPrice;
	while(!pMedicSet->IsEOF())
	{
		pRecord = new CXTPReportRecord();
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicID));
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicName));
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_MedicType));
		ProduceData = pMedicSet->m_ProduceDate;
		//ProduceData.Format(_T("%B %d,%Y");
		pRecord->AddItem(new CXTPReportRecordItemText(ProduceData.Format(_T("%Y-%m-%d"))));
		if (pMedicSet->m_MedicNumber == 0)
		{
			pRecordItem = new CXTPReportRecordItemNumber(pMedicSet->m_MedicNumber);
			//pRecordItem->SetBackgroundColor(RGB(250,0,0));
			pRecordItem->SetBackgroundColor(RGB(255,0,0));
			pRecord->AddItem(pRecordItem);
		}
		else
			pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_MedicNumber));
		strPrice.Format("%.2f",pMedicSet->m_MedicPrice);
		pRecord->AddItem(new CXTPReportRecordItemText(strPrice));
		pRecord->AddItem(new CXTPReportRecordItemNumber(pMedicSet->m_GuarantPeriod));
		pRecord->AddItem(new CXTPReportRecordItemText(pMedicSet->m_ProduceCompany));
		m_wndReportCtrl->AddRecord(pRecord);
		pMedicSet->MoveNext();
	}
	
	m_wndReportCtrl->SetGridColor(RGB(0,0,255));
	m_wndReportCtrl->SetGridStyle(FALSE,xtpReportGridSolid);
	m_wndReportCtrl->SetGridStyle(TRUE,xtpReportGridSolid);
	m_wndReportCtrl->GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2007);
	m_wndReportCtrl->SetGroupRowsBold(TRUE);
	//m_wndReportCtrl->ShadeGroupHeadings(TRUE);分组的头行显示背景
	
	m_wndReportCtrl->Populate();
}


void CMainFrame::CreateRibbonBar(void)
{
	CXTPCommandBars *pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

	CXTPRibbonBar *pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"),xtpBarTop,RUNTIME_CLASS(CXTPRibbonBar));
	pRibbonBar->EnableDocking(0);
	
	CXTPControl* pControlExpand = pRibbonBar->GetControls()->Add(xtpControlButton,ID_RIBBON_EXPAND);
	pControlExpand->SetFlags(xtpFlagRightAlign);

	CXTPControl* pControlMinimize = pRibbonBar->GetControls()->Add(xtpControlButton,ID_RIBBON_MINIMIZE);
	pControlMinimize->SetFlags(xtpFlagRightAlign);

	UINT uiRibbonMini[] = {ID_RIBBON_MINIMIZE, ID_RIBBON_EXPAND};
	pCommandBars->GetImageManager()->SetIcons(IDR_PNG_MINI,uiRibbonMini, _countof(uiRibbonMini), CSize(16, 16));

	//CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(IDR_PNG_SYSICON);
 //	pControlFile->SetCommandBar(menu.GetSubMenu(0));
 //	//pControlFile->GetCommandBar()->SetIconSize(CSize(0, 0));
//pCommandBars->GetImageManager()->SetIcons(IDR_PNG_SYSICON);
 //pControlFile->SetCaption(_T("&File"));
 //pControlFile->SetIconId(IDR_PNG_SYSICON);

//  	UINT uCommand = {IDR_PNG_SYSICON};
//  	pCommandBars->GetImageManager()->SetIcons(IDR_PNG_SYSICON, &uCommand, 1, CSize(0, 0), xtpImageNormal);
	
	CXTPRibbonTab *pTab1 = pRibbonBar->AddTab(ID_TAB_START);
	if (pTab1)
	{
		CXTPControl *pControl;
		
		CXTPRibbonGroup* pGroup = pTab1->AddGroup(ID_GROUP_USER);
		pGroup->ShowOptionButton(FALSE);
		
		pControl = pGroup->Add(xtpControlButton,ID_USER_ADD);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_USER_DEL);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_USER_SEEK);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

  		UINT nIDs[] = {ID_USER_ADD,ID_USER_DEL,ID_USER_SEEK};
  		pCommandBars->GetImageManager()->SetIcons(IDB_USER_RIBBON, nIDs, _countof(nIDs), CSize(32, 32));
 	
 		pGroup = pTab1->AddGroup(ID_GROUP_SYSTEM);
 
 		pControl = pGroup->Add(xtpControlButton,ID_USER_MODPWD);
 		pControl->SetStyle(xtpButtonIconAndCaptionBelow);
 
 		pControl = pGroup->Add(xtpControlButton,ID_USER_CHANGE);
 		pControl->SetStyle(xtpButtonIconAndCaptionBelow);
 
 		pControl = pGroup->Add(xtpControlButton,ID_USER_LOGOUT);
 		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		nIDs[0] = ID_USER_MODPWD;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_MODPWD, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_USER_CHANGE;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_CHANGE, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_USER_LOGOUT;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_EXIT, nIDs, _countof(nIDs), CSize(32, 32));
 	}

	CXTPRibbonTab *pTab2 = pRibbonBar->AddTab(ID_TAB_SEEK);
	if (pTab2)
	{
		CXTPControl *pControl;
		CXTPRibbonGroup* pGroup = pTab2->AddGroup(ID_GROUP_SEEK);
		pGroup->ShowOptionButton(FALSE);

		pControl = pGroup->Add(xtpControlButton,ID_SEEK_NUMBER);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_SEEK_NAME);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_SEEK_TYPE);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		UINT nIDs[] = {ID_SEEK_NUMBER};
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_SEEK, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_SEEK_NAME;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_SEEK, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_SEEK_TYPE;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_SEEK, nIDs, _countof(nIDs), CSize(32, 32));

		pGroup = pTab2->AddGroup(ID_GROUP_OTHERS);

		pControl = pGroup->Add(xtpControlButton,ID_SEEK_ALL);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_SEEK_ZERO);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_SEEK_OUTDATE);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		nIDs[0] = ID_SEEK_ALL;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_DEFAULT, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_SEEK_ZERO;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_DEFAULT, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_SEEK_OUTDATE;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_DEFAULT, nIDs, _countof(nIDs), CSize(32, 32));

		pGroup = pTab2->AddGroup(ID_GROUP_REPOTR);
		pControl = pGroup->Add(xtpControlButton,ID_SEEK_FILTER);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_REPORT_SET);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		nIDs[0] = ID_SEEK_FILTER;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_FIND, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_REPORT_SET;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_DEFAULT, nIDs, _countof(nIDs), CSize(32, 32));
	}

	CXTPRibbonTab *pTab3 = pRibbonBar->AddTab(ID_TAB_MANAGER);
	if (pTab3)
	{
		CXTPControl *pControl;
		CXTPRibbonGroup* pGroup = pTab3->AddGroup(ID_GROUP_MEDIC);
		pGroup->ShowOptionButton(FALSE);

		pControl = pGroup->Add(xtpControlButton,ID_MEDIC_ADD);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_MEDIC_SALE);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton,ID_MEDIC_CLEAN);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		UINT nIDs[] = {ID_MEDIC_ADD};
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_MEDIC, nIDs, _countof(nIDs), CSize(32, 24));
		nIDs[0] = ID_MEDIC_SALE;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_DEFAULT, nIDs, _countof(nIDs), CSize(32, 32));
		nIDs[0] = ID_MEDIC_CLEAN;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_CLEAN, nIDs, _countof(nIDs), CSize(32, 32));
	}

	CXTPRibbonTab *pTab4 = pRibbonBar->AddTab(ID_TAB_THEME);
	if (pTab4)
	{
		CXTPControl *pControl;
		CXTPRibbonGroup* pGroup = pTab4->AddGroup(ID_GROUP_STYLE);
		pGroup->ShowOptionButton(FALSE);

		pControl = pGroup->Add(xtpControlButtonPopup,ID_STYLE_POPBTN);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		UINT nID = ID_STYLE_POPBTN;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_THEME, &nID, 1, CSize(32, 32));

		pGroup = pTab4->AddGroup(ID_GROUP_FONT);
		pControl = pGroup->Add(xtpControlButtonPopup,ID_STYLE_FONT);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		nID = ID_STYLE_FONT;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_FONT, &nID, 1, CSize(32, 32));

		pGroup = pTab4->AddGroup(ID_GROUP_SKIN);
		pControl = pGroup->Add(xtpControlButtonPopup,ID_STYLE_SKIN);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		nID = ID_STYLE_SKIN;
		pCommandBars->GetImageManager()->SetIcons(IDR_PNG_DEFAULT, &nID, 1, CSize(32, 32));
	}
	
	pRibbonBar->EnableFrameTheme();
}

// CMainFrame 消息处理程序


void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	if (pCmdUI->m_nID == ID_STYLE_POPBTN)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);
}


void CMainFrame::OnOptionsStyle(UINT nStyle)
{
	GetCommandBars()->SetTheme(xtpThemeRibbon);

	HMODULE hModule = AfxGetInstanceHandle();

	LPCTSTR lpszIniFile = 0;
	switch (nStyle)
	{
	case ID_STYLES_OFFICE2007BLUE: 
		lpszIniFile = _T("OFFICE2007BLUE.INI"); 
		//XTPPaintManager()->SetTheme(xtpThemeOffice2007);
		break;

	case ID_STYLES_OFFICE2007BLACK: 
		hModule = LoadLibrary(_T("Styles/Office2007.dll"));
		lpszIniFile = _T("OFFICE2007BLACK.INI"); 
		break;

	case ID_STYLES_OFFICE2007SILVER: 
		hModule = LoadLibrary(_T("Styles/Office2007.dll"));
		lpszIniFile = _T("OFFICE2007SILVER.INI"); 
		break;

	case ID_STYLES_WINDOWS7SCENIC: 
		hModule = LoadLibrary(_T("Styles/Windows7.dll"));
		lpszIniFile = _T("WINDOWS7BLUE.INI"); 
		//XTPPaintManager()->SetTheme(xtpThemeVisualStudio6);
		break;

	case ID_STYLES_OFFICE2010SILVER: 
		hModule = LoadLibrary(_T("Styles/Office2010.dll"));
		lpszIniFile = _T("OFFICE2010SILVER.INI"); 
		//XTPPaintManager()->SetTheme(xtpThemeVisualStudio2010);
		break;

	case ID_STYLES_OFFICE2010BLUE: 
		hModule = LoadLibrary(_T("Styles/Office2010.dll"));
		lpszIniFile = _T("OFFICE2010BLUE.INI"); 
		break;

	case ID_STYLES_OFFICE2010BLACK: 
		hModule = LoadLibrary(_T("Styles/Office2010.dll"));
		lpszIniFile = _T("OFFICE2010BLACK.INI"); 
		break;

	}

	if (hModule != 0)
	{
		((CXTPOffice2007Theme*)GetCommandBars()->GetPaintManager())->SetImageHandle(hModule, lpszIniFile);
	}
	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);
	//RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE|RDW_ALLCHILDREN);
	OnChangeFont(m_nFont);
	m_nRibbonStyle = nStyle;
}

void CMainFrame::OnToggleRibbonBars()
{
	CXTPRibbonBar *pRibbon = (CXTPRibbonBar *)GetCommandBars()->GetAt(0);
	pRibbon->SetRibbonMinimized(!pRibbon->IsRibbonMinimized());
}

void CMainFrame::OnUpdateRibbonMinimize(CCmdUI* pCmdUI)
{
	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);
	if (pControl)
	{
		CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
		pControl->SetVisible(!pRibbonBar->IsRibbonMinimized());
	}
}

void CMainFrame::OnUpdateRibbonExpand(CCmdUI* pCmdUI)
{
	CXTPControl* pControl = CXTPControl::FromUI(pCmdUI);
	if (pControl)
	{
		CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();
		pControl->SetVisible(pRibbonBar->IsRibbonMinimized());
	}
}


void CMainFrame::OnUpdateUserManger(CCmdUI* pCmdUI)
{
	int nId = pCmdUI->m_nID;
	if (user.GetType() == _T("管理员"))
	{
		pCmdUI->Enable(TRUE);
	}
	else if (nId >= ID_USER_ADD && nId <= ID_USER_SEEK)
	{
		pCmdUI->Enable(FALSE);
	}
	else
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnRegisterUser()
{
 	CRegisterUserDlg dlgAdd;
 	dlgAdd.DoModal();
}

void CMainFrame::OnDelUser()
{
	CDelUserDlg dlgDel;
	dlgDel.DoModal();
}

void CMainFrame::OnSeekUser()
{
	CSeekUserDlg dlgSeek;
	dlgSeek.DoModal();
}

void CMainFrame::OnChangeUser()
{
	ShowWindow(SW_HIDE);
	CChangeUserDlg ChangeDlg;
	ChangeDlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CMainFrame::OnModUserPasswd()
{
	CModifyPasswdDlg dlgModify;
	CUser *pUser = &((CMainFrame *)AfxGetMainWnd())->user;
	dlgModify.m_strAccount = pUser->GetAccount();
	dlgModify.DoModal();
}


void CMainFrame::OnUpdateFonts(CCmdUI* pCmdUI)
{
	if (pCmdUI->m_nID == ID_STYLE_FONT)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(pCmdUI->m_nID == m_nFont ? 1:0 );
	}
}



void CMainFrame::OnChangeFont(UINT nFont)
{
	UINT size[] = {14, 15, 16, 17};
	UINT nFontHeight;
	if (nFont == ID_STYLE_FONT4)
	{
		nFontHeight = size[3];
	}
	else
		nFontHeight = size[nFont - ID_STYLE_FONT1];

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);
	pRibbonBar->SetFontHeight(nFontHeight);

	m_nFont = nFont;
}

void CMainFrame::OnReportFind()
{
	if (NULL == pSeek)
	{
		pSeek = new CReportSeekDlg();//创建一个非模式对话框
		pSeek->Create(IDD_REPORT_SEEK);
		pSeek->CenterWindow();
		pSeek->ShowWindow(SW_NORMAL);
		pSeek->UpdateWindow();
	}
	else
		pSeek->SetFocus();
}

void CMainFrame::OnUpdateNormalButton( CCmdUI* pCmdUI )
{
	int nId = pCmdUI->m_nID;
	if (nId >= ID_MEDIC_ADD && nId <= ID_MEDIC_CLEAN)
	{
		if (user.GetType() == "售药员" && nId != ID_MEDIC_SALE)
			pCmdUI->Enable(FALSE);
		else if (user.GetType() == "医生")
			pCmdUI->Enable(FALSE);
	}
}


void CMainFrame::OnClose()
{
	int flag = AfxMessageBox("确定要退出系统吗?",MB_OKCANCEL);
	if(flag == IDOK)
	{
		CFrameWnd::OnClose();
	}
}

void CMainFrame::OnMedicSeekID()
{
	CMedicIDSeekDlg IDDlg;
	IDDlg.DoModal();
}

void CMainFrame::OnMedicSeekName()
{
	CMedicNameSeekDlg NameDlg;
	NameDlg.DoModal();
}

void CMainFrame::OnMedicSeekType()
{
	CMedicTypeSeekDlg TypeDlg;
	TypeDlg.DoModal();
}

void CMainFrame::OnMedicSearchAll()
{
	CMedic::MedicSearchAll();
}

void CMainFrame::OnMedicSearchZeroNumber()
{
	CMedic::MedicSearchZeroNumber();
}

void CMainFrame::OnMedicSearchOutDate()
{
	CMedic::MedicSearchOutDate();
}

void CMainFrame::OnMedicStore()
{
	CStoreMedicDlg dlgStore;
	dlgStore.DoModal();
}

void CMainFrame::OnMedicClean()
{
	CCleanMedicDlg dlgClean;
	dlgClean.DoModal();
}

void CMainFrame::OnMedicSale()
{
	CSaleMedicDlg dlgSale;
	dlgSale.DoModal();
}

void CMainFrame::OnReportSet()
{
	static CReportField *dlgReportField = NULL;
	if (!dlgReportField)
	{
		dlgReportField = new CReportField();
		dlgReportField->Create(IDD_FIELDCHOOSER);
		dlgReportField->CenterWindow();
		dlgReportField->ShowWindow(SW_NORMAL);
		dlgReportField->UpdateWindow();
	}
	else
		dlgReportField->ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateSkin( CCmdUI* pCmdUI )
{
	if (pCmdUI->m_nID == ID_STYLE_SKIN)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(pCmdUI->m_nID == m_nSkin ? 1:0);
	}
}

void CMainFrame::OnSelectSkin( UINT nSkin )
{
	if (ID_SKIN1 == nSkin)
	{
		XTPSkinManager()->LoadSkin(NULL);
	}
	else if (ID_SKIN2 == nSkin)
	{
		XTPSkinManager()->LoadSkin(_T("Styles/Codejock.cjstyles"));
	}
	else if (ID_SKIN3 == nSkin)
	{
		XTPSkinManager()->LoadSkin(_T("Styles/Vista.cjstyles"));
	}
	else if (ID_SKIN4 == nSkin)
	{
		XTPSkinManager()->LoadSkin(_T("Styles/Office2007.cjstyles"));
	}
	else if (ID_SKIN5 == nSkin)
	{
		XTPSkinManager()->LoadSkin(_T("Styles/WinXP.Luna.cjstyles"));
	}

	m_nSkin = nSkin;
}
