#include "stdafx.h"
#include <math.h>
#include "Billiard.h"
#include "BilliardDlg.h"
#include "HyperLink.h"
#include "Math.h"
#include "afxwin.h"
#include "MinimizeToTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 目标袋口，1：左上 2：中上 3：右上 4：左下 5：中下 6：右下
#define		GOAL_LU		1
#define		GOAL_MU		2
#define		GOAL_RU		3
#define		GOAL_LD		4
#define		GOAL_MD		5
#define		GOAL_RD		6
// 定时器
#define		TIMER_CANVAS	1
#define		TIMER_LINES		2
#define		TIMER_REFLECT	3
#define		TIMER_NONE		-1
#define		TIMER_CANVAS_INTERVAL	500
#define		TIMER_LINES_INTERVAL	500
#define		TIMER_REFLECT_INTERVAL	200
// 放大倍数
#define		ZOOM_MAX	3
#define		ZOOM_MIN	1
// 自定义消息
#define		MYMSG_NOTIFYICON		(WM_APP + 100)

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_linkUrl;
	CHyperLink	m_linkMail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CSkinButton m_btnOK;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_btnOK.m_nXPos=10;
	m_btnOK.m_nYPos=9;
	m_btnOK.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;
	m_btnOK.m_nFocusBitmapResID=IDB_BITMAPFOCUS;
	m_btnOK.m_nHoverBitmapResID=0;
	m_btnOK.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;
	m_btnOK.m_bEnableStretch=TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATIC_URL, m_linkUrl);
	DDX_Control(pDX, IDC_STATIC_MAIL, m_linkMail);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_linkUrl.SetURL(_T("http://antiboss.googlepages.com/billiardassist"));
	m_linkUrl.ModifyLinkStyle(0, CHyperLink::StyleUseHover);
	m_linkUrl.SetWindowText(_T("http://antiboss.googlepages.com/billiardassist"));

	m_linkMail.SetURL(_T("antiboss@gmail.com"));
	m_linkMail.ModifyLinkStyle(0, CHyperLink::StyleDownClick);
	m_linkMail.SetWindowText(_T("antiboss@gmail.com"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBilliardDlg dialog

CBilliardDlg::CBilliardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBilliardDlg::IDD, pParent)
	, m_nCanvasWidth(580)
	, m_nCanvasHeight(284)
	, m_nBallDiameter(20)
	, m_nHoleRadius(20)
	, m_nCanvasXPos(200)
	, m_nCanvasYPos(200)
	, m_nZoomValue(2)
	, m_nShowCanvas(BST_UNCHECKED)
	, m_nShowLine(BST_UNCHECKED)
	, m_nShowZoom(BST_UNCHECKED)
	, m_nHotkey(BST_UNCHECKED)
	, m_bStayOnTop(BST_UNCHECKED)
	, m_nForceRefresh(BST_CHECKED)
{
	//{{AFX_DATA_INIT(CBilliardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_nBallRadius = (float)m_nBallDiameter/2;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hMenu = NULL;
	// 默认不显示参数设定
	m_bMore = FALSE;
	// 第一次显示放大镜，停靠在对话框的右侧
	m_bFirstZoom = TRUE;
	// 默认瞄准袋口，左上
	m_nGoal = GOAL_LU;
	// 瞄准线颜色
	m_crLine = RGB(180,174,251);
	// 桌布外轮廓颜色
	m_crCanvasOut = RGB(196,194,231);
	// 桌布内轮廓颜色
	m_crLineCanvasIn = RGB(0,255,255);
	// 反射线颜色
	m_crReflect = RGB(0, 0, 255);
	// 预览对话框默认大小
	m_nSize = int(m_nZoomValue*m_nBallRadius*8);
	// 初始化热键
	m_nHOTKEY_A      = -1;			// 热键A
	m_nHOTKEY_S      = -1;			// 热键S
	m_nHOTKEY_D      = -1;			// 热键D
	m_nHOTKEY_Z      = -1;			// 热键Z
	m_nHOTKEY_X      = -1;			// 热键X
	m_nHOTKEY_C      = -1;			// 热键C
	m_nHOTKEY_LEFT   = -1;			// 热键LEFT
	m_nHOTKEY_RIGHT  = -1;			// 热键RIGHT
	m_nHOTKEY_UP     = -1;			// 热键UP
	m_nHOTKEY_DOWN   = -1;			// 热键DOWN
	m_nHOTKEY_WHITE  = -1;			// 热键定位白球
	m_nHOTKEY_GOAL	 = -1;			// 热键定位目标球
	m_nHOTKEY_RESET  = -1;			// 热键取消定位
	// 初始化DC
	m_dc.m_hDC = (HDC)0;
	m_dcLine.m_hDC = (HDC)0;
	m_dcReflect.m_hDC = (HDC)0;
	// 反射条件初始化
	m_bGoalBallPointSet = FALSE;
	m_bWhiteBallPointSet = FALSE;
	m_ptGoalBallCenter = CPoint(0, 0);
	m_ptWhiteBallCenter = CPoint(0, 0);

	// 设置按钮的皮肤。
	m_btnParam.m_nXPos=10;
	m_btnParam.m_nYPos=9;
	m_btnParam.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;
	m_btnParam.m_nFocusBitmapResID=IDB_BITMAPFOCUS;
	m_btnParam.m_nHoverBitmapResID=0;
	m_btnParam.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;
	m_btnParam.m_bEnableStretch=TRUE;

	m_btnCfgDefault.m_nXPos=10;
	m_btnCfgDefault.m_nYPos=9;
	m_btnCfgDefault.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;
	m_btnCfgDefault.m_nFocusBitmapResID=IDB_BITMAPFOCUS;
	m_btnCfgDefault.m_nHoverBitmapResID=0;
	m_btnCfgDefault.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;
	m_btnCfgDefault.m_bEnableStretch=TRUE;

	m_btnCfgSave.m_nXPos=10;
	m_btnCfgSave.m_nYPos=9;
	m_btnCfgSave.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;
	m_btnCfgSave.m_nFocusBitmapResID=IDB_BITMAPFOCUS;
	m_btnCfgSave.m_nHoverBitmapResID=0;
	m_btnCfgSave.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;
	m_btnCfgSave.m_bEnableStretch=TRUE;

	m_btnCfgLoad.m_nXPos=10;
	m_btnCfgLoad.m_nYPos=9;
	m_btnCfgLoad.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;
	m_btnCfgLoad.m_nFocusBitmapResID=IDB_BITMAPFOCUS;
	m_btnCfgLoad.m_nHoverBitmapResID=0;
	m_btnCfgLoad.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;
	m_btnCfgLoad.m_bEnableStretch=TRUE;

	m_btnAdv.m_nXPos=10;
	m_btnAdv.m_nYPos=9;
	m_btnAdv.m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;
	m_btnAdv.m_nFocusBitmapResID=IDB_BITMAPFOCUS;
	m_btnAdv.m_nHoverBitmapResID=0;
	m_btnAdv.m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;
	m_btnAdv.m_bEnableStretch=TRUE;

	m_pPtList = new CList<CPoint, CPoint&>;
	m_pPtListOld = new CList<CPoint, CPoint&>;
}

void CBilliardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBilliardDlg)
	DDX_Control(pDX, IDC_PARAM, m_btnParam);
	DDX_Control(pDX, IDC_CHECK_TOP, m_btnTop);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nCanvasWidth);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nCanvasHeight);
	DDX_Text(pDX, IDC_EDIT_BALL_RADIUS, m_nBallDiameter);
	DDX_Text(pDX, IDC_EDIT_HOLE_RADIUS, m_nHoleRadius);
	DDX_Text(pDX, IDC_EDIT_XPOS, m_nCanvasXPos);
	DDX_Text(pDX, IDC_EDIT_YPOS, m_nCanvasYPos);
	DDX_Check(pDX, IDC_CHECK_SHOWCANVAS, m_nShowCanvas);
	DDX_Check(pDX, IDC_CHECK_SHOWLINE, m_nShowLine);
	DDX_Check(pDX, IDC_CHECK_ZOOM, m_nShowZoom);
	DDX_Check(pDX, IDC_CHECK_TOP, m_bStayOnTop);
	DDX_Control(pDX, IDC_SAVE, m_btnCfgDefault);
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_nZoomValue);
	DDV_MinMaxInt(pDX, m_nZoomValue, 1, 3);
	DDX_Control(pDX, IDC_PIC_GOAL, m_picDesk);
	DDX_Control(pDX, IDC_CFG_SAVE, m_btnCfgSave);
	DDX_Control(pDX, IDC_CFG_LOAD, m_btnCfgLoad);
	DDX_Control(pDX, IDC_ADVANCE, m_btnAdv);
	DDX_Check(pDX, IDC_CHECK_HOTKEY, m_nHotkey);
	DDX_Check(pDX, IDC_CHECK_FORCE_REFRESH, m_nForceRefresh);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBilliardDlg, CDialog)
	//{{AFX_MSG_MAP(CBilliardDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PARAM, &CBilliardDlg::OnBnClickedParam)
	ON_BN_CLICKED(IDC_CHECK_TOP, &CBilliardDlg::OnBnClickedCheckTop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SHOWCANVAS, &CBilliardDlg::OnBnClickedCheckShowcanvas)
	ON_BN_CLICKED(IDC_CHECK_SHOWLINE, &CBilliardDlg::OnBnClickedCheckShowline)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_WIDTH, &CBilliardDlg::OnDeltaposSpinWidth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HEIGHT, &CBilliardDlg::OnDeltaposSpinHeight)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BALL_RADIUS, &CBilliardDlg::OnDeltaposSpinBallRadius)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HOLE_RADIUS, &CBilliardDlg::OnDeltaposSpinHoleRadius)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_XPOS, &CBilliardDlg::OnDeltaposSpinXpos)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_YPOS, &CBilliardDlg::OnDeltaposSpinYpos)
	ON_BN_CLICKED(IDC_SAVE, &CBilliardDlg::OnBnClickedCfgDefault)
	ON_BN_CLICKED(IDC_CFG_SAVE, &CBilliardDlg::OnBnClickedCfgSave)
	ON_BN_CLICKED(IDC_CFG_LOAD, &CBilliardDlg::OnBnClickedCfgLoad)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CHECK_ZOOM, &CBilliardDlg::OnBnClickedCheckZoom)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ZOOM, &CBilliardDlg::OnDeltaposSpinZoom)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CBilliardDlg::OnEnChangeEditWidth)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CBilliardDlg::OnEnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_XPOS, &CBilliardDlg::OnEnChangeEditXPos)
	ON_EN_CHANGE(IDC_EDIT_YPOS, &CBilliardDlg::OnEnChangeEditYPos)
	ON_EN_CHANGE(IDC_EDIT_BALL_RADIUS, &CBilliardDlg::OnEnChangeEditBallRadius)
	ON_EN_CHANGE(IDC_EDIT_HOLE_RADIUS, &CBilliardDlg::OnEnChangeEditHoleRadius)
	ON_EN_CHANGE(IDC_EDIT_ZOOM, &CBilliardDlg::OnEnChangeEditZoom)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_BN_CLICKED(IDC_ADVANCE, &CBilliardDlg::OnBnClickedAdvance)
	ON_BN_CLICKED(IDC_CHECK_HOTKEY, &CBilliardDlg::OnBnClickedCheckHotkey)
	ON_MESSAGE(MYMSG_NOTIFYICON,OnTrayNotification)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_EXIT, &CBilliardDlg::OnFileExit)
	ON_COMMAND(ID_TRAYICON_SHOWWINDOW, &CBilliardDlg::OnTrayiconShowwindow)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_FORCE_REFRESH, &CBilliardDlg::OnBnClickedCheckForceRefresh)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBilliardDlg message handlers

BOOL CBilliardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	g_SkinDialog.SubClassDialog(m_hWnd);
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//
	// 读入配置
	char szPath[256];
	GetExePath(szPath);
	CString str = szPath;
	ReadConfig(str);
	UpdateData(FALSE);
	// 默认瞄准袋口，左上
	SwitchDesk(IDB_BITMAP_LT);
	//
	// 隐藏参数设定
	OnBnClickedParam();
	//
	// 前端显示设定
	ShowTopWindow();
	// Hotkey
	SetHotKey(m_nHotkey == BST_CHECKED ? TRUE : FALSE);
	//
	// 启动定时器
	if (m_nShowCanvas == BST_CHECKED) {
		m_nTimerCanvas = SetTimer(TIMER_CANVAS, TIMER_CANVAS_INTERVAL, 0);
	}
	m_nTimerLine   = SetTimer(TIMER_LINES, TIMER_LINES_INTERVAL, 0);
	m_nTimerReflect = SetTimer(TIMER_REFLECT, TIMER_REFLECT_INTERVAL, 0);
	// 预览对话框默认大小
	m_nSize = (int)(m_nZoomValue*m_nBallRadius*8+0.5);
	//
	// 显示预览对话框
	if (m_nShowZoom == BST_CHECKED) {
		ShowPreviewDlg(TRUE);
	}
	// 
	// 显示托盘
	AddTrayIcon(NIM_ADD, 0);
	// 装载右键菜单
	if (m_hMenu == NULL) {
		HMENU hMenu = NULL;
		if ((hMenu = ::LoadMenu(AfxGetInstanceHandle(), (LPCTSTR) MAKEINTRESOURCE(IDR_MENU_TRAY)))) {
			m_hMenu = ::GetSubMenu(hMenu, 0);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBilliardDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBilliardDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBilliardDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/**
 * Function Name:DestroyWindow
 * Usage:
 * 窗口销毁函数
*/
BOOL CBilliardDlg::DestroyWindow() 
{
	// 去掉托盘图标
	AddTrayIcon(NIM_DELETE, 0);
	// 取消子类化
	g_SkinDialog.RemoveSubClass();
	// 关闭定时器
	KillOwnTimer();
	// 等待绘制完成
	Sleep(500);
	// 释放资源
	if (m_dc.m_hDC != (HDC)0) {
		m_dc.DeleteDC();
	}
	if (m_dcLine.m_hDC != (HDC)0) {
		m_dcLine.DeleteDC();
	}
	if (m_dcReflect.m_hDC != (HDC)0) {
		m_dcReflect.DeleteDC();
	}

	// 刷新整个屏幕
	RefreshAll();
	// Hotkey
	SetHotKey(FALSE);
	//
	if(m_hIcon)
		DestroyIcon(m_hIcon);
	// Bitmap
	HBITMAP hBitmap = m_picDesk.GetBitmap();
	if (GetObjectType(hBitmap) == OBJ_BITMAP) {
		::DeleteObject(hBitmap);
	}
	// Menu
	if (m_hMenu != NULL) {
		DestroyMenu(m_hMenu);
	}
	// Point list
	m_pPtListOld->RemoveAll();
	delete m_pPtListOld;
	m_pPtListOld = NULL;
	m_pPtList->RemoveAll();
	delete m_pPtList;
	m_pPtList = NULL;

	return CDialog::DestroyWindow();
}

/**
 * Function Name:OnBnClickedParam
 * Usage:
 * 参数设定按钮的响应，用来设定相关的参数
*/
void CBilliardDlg::OnBnClickedParam()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect1, rect2;
	CWnd* pWnd1 = GetDlgItem(IDC_STATIC_BREAK);
	pWnd1->GetWindowRect(&rect1);

	CWnd* pWnd2 = GetDlgItem(IDC_STATIC_BREAK2);
	pWnd2->GetWindowRect(&rect2);

	CRect rectSelf;
	this->GetWindowRect(&rectSelf);
	char szBuf[100];
	if(m_bMore)
	{
		rectSelf.bottom = rect2.bottom;
		LoadStr(IDS_SET_LESS, szBuf);
	}
	else
	{
		rectSelf.bottom = rect1.bottom;
		LoadStr(IDS_SET_MORE, szBuf);
	}
	m_btnParam.SetWindowText(szBuf);
	this->MoveWindow(&rectSelf);
	m_bMore = !m_bMore;
}

/**
 * Function Name:ShowTopWindow
 * Usage:
 * 前端显示设定消息响应
*/
void CBilliardDlg::OnBnClickedCheckTop()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowTopWindow();
}

/**
 * Function Name:ShowTopWindow
 * Usage:
 * 前端显示设定函数
*/
void CBilliardDlg::ShowTopWindow() 
{
	m_bStayOnTop = (m_bStayOnTop==BST_CHECKED)?BST_UNCHECKED:BST_CHECKED;
	UpdateData(FALSE);
	if(m_bStayOnTop == BST_UNCHECKED) {
	    this->SetWindowPos(&wndNoTopMost , 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
	} else {
		this->SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
	}
	UpdateMenuItemStatus(IDC_CHECK_TOP);
}

/**
 * Function Name:OnTimer
 * Usage:
 * 定时器消息函数，用来绘制模拟桌布和瞄准线
*/
void CBilliardDlg::OnTimer(UINT_PTR nIDEvent)
{
	BOOL bChanged = FALSE;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TIMER_CANVAS) {
		// 绘制模拟桌布
		// 创建画笔
		//
		// 获得Device context
		m_dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
		CPen pen(PS_SOLID, 1, m_crLine);  // Solid black pen.
		CPen* pOldPen = m_dc.SelectObject(&pen);
		int ropOld = m_dc.GetROP2();
		// 只有桌布尺寸发生变化了，才擦掉重新绘制
		if (IsCanvasChanged()) {
			bChanged = TRUE;
			ropOld = m_dc.SetROP2(R2_NOTXORPEN);
			DrawCanvas(TRUE);
		}
		DrawCanvas(FALSE);
		m_dc.SetROP2(ropOld);
		m_dc.SelectObject(pOldPen);
		if (bChanged) {
			RefreshAll();
		}
		m_dc.DeleteDC();
		m_dc.m_hDC = (HDC)0;
	} else if (nIDEvent == TIMER_LINES) {
		// 瞄准线
		// 只有瞄准线尺寸发生变化了，才擦掉重新绘制
		if (m_nShowLine == BST_CHECKED) {
			//
			// 获得Device context
			m_dcLine.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
			CPen pen(PS_SOLID, 1, m_crLineCanvasIn);  // Solid Green pen.
			CPen *pOldPen = m_dcLine.SelectObject(&pen);
			int nRopOld = m_dcLine.GetROP2();
			if (IsLineChanged()) {
				bChanged = TRUE;
				nRopOld = m_dcLine.SetROP2(R2_NOTXORPEN);
				DrawLine(TRUE);
			}
			// 原则上同一位置不要重画，但是强制刷新除外
			if ((m_nForceRefresh == BST_CHECKED) || bChanged) {
				DrawLine(FALSE);
			}
			m_dcLine.SetROP2(nRopOld);
			m_dcLine.SelectObject(pOldPen);
			m_dcLine.DeleteDC();
			m_dcLine.m_hDC = (HDC)0;
		}
		DrawPreview();
	} else if (nIDEvent == TIMER_REFLECT) {
		if (m_bGoalBallPointSet && m_bWhiteBallPointSet) {
			TRACE("@@@@@@@@@@@@@@@@@@@@@@@@@TIMER_REFLECT@@@@@@@@@@@@@@@@@@@@@@\n");
			//
			// 获得Device context
			m_dcReflect.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
			CPen pen(PS_DOT, 1, m_crReflect);  // Solid Green pen.
			CPen *pOldPen = m_dcReflect.SelectObject(&pen);
			int nRopOld = m_dcReflect.GetROP2();
			CPoint ptCursor;
			GetCursorPos(&ptCursor);
			DrawVirtualLine(ptCursor, FALSE);
			if (IsReflectChanged(ptCursor)) {
				bChanged = TRUE;
				nRopOld = m_dcReflect.SetROP2(R2_NOTXORPEN);
				DrawVirtualCircle(ptCursor, TRUE);
			}
			// 原则上同一位置不要重画，但是强制刷新除外
			if ((m_nForceRefresh == BST_CHECKED) || bChanged) {
				DrawVirtualCircle(ptCursor, FALSE);
			}
			// 绘制完毕
			m_dcReflect.SetROP2(nRopOld);
			m_dcReflect.SelectObject(pOldPen);
			m_dcReflect.DeleteDC();
			m_dcReflect.m_hDC = (HDC)0;
		}
	}
	CDialog::OnTimer(nIDEvent);
}

/**
 * Function Name:DrawCanvas
 * Usage:
 * 用来绘制模拟桌布
*/
void CBilliardDlg::DrawCanvas(BOOL bErase)
{
	// 模拟桌布布局
	//  --------
	// ①--②--③
	//||       ||
	// ⑥--⑤--④
	//  --------
	int nCanvasWidth;			// 桌布宽度
	int nCanvasHeight;			// 桌布高度
	float nBallRadius;			// 台球半径
	int nHoleRadius;			// 袋口半径
	int nCanvasXPos;			// 桌布相对于屏幕坐标的横坐标位置
	int nCanvasYPos;			// 桌布相对于屏幕坐标的纵坐标位置
	if (bErase) {
		nCanvasWidth  = m_nCanvasWidthOld;
		nCanvasHeight = m_nCanvasHeightOld;
		nBallRadius   = m_nBallRadiusOld;
		nHoleRadius   = m_nHoleRadiusOld;
		nCanvasXPos   = m_nCanvasXPosOld;
		nCanvasYPos   = m_nCanvasYPosOld;
	} else {
		nCanvasWidth  = m_nCanvasWidth;
		nCanvasHeight = m_nCanvasHeight;
		nBallRadius   = m_nBallRadius;
		nHoleRadius   = m_nHoleRadius;
		nCanvasXPos   = m_nCanvasXPos;
		nCanvasYPos   = m_nCanvasYPos;
	}
	if ((nCanvasWidth  <= 4*nHoleRadius) ||
		(nCanvasHeight <= 2*nHoleRadius)) {
		return;
	}
	int nXInterval = int((nCanvasWidth-4*nHoleRadius)/2+0.5); //Lenth of --
	// Draw |①--
	m_dc.MoveTo(nCanvasXPos, nCanvasYPos+nHoleRadius);
	m_dc.LineTo(nCanvasXPos, nCanvasYPos+nCanvasHeight-nHoleRadius);
	m_dc.MoveTo(nCanvasXPos, nCanvasYPos);
	m_dc.Arc(nCanvasXPos-nHoleRadius,nCanvasYPos-nHoleRadius,
			 nCanvasXPos+nHoleRadius,nCanvasYPos+nHoleRadius,
			 nCanvasXPos+nHoleRadius,nCanvasYPos,
			 nCanvasXPos,nCanvasYPos+nHoleRadius
			 );
	m_dc.MoveTo(nCanvasXPos+nHoleRadius, nCanvasYPos);
	m_dc.LineTo(nCanvasXPos+nHoleRadius+nXInterval, nCanvasYPos);
	// Draw ②--
	m_dc.MoveTo(nCanvasXPos+nCanvasWidth/2, nCanvasYPos);
	m_dc.Arc(nCanvasXPos+nCanvasWidth/2-nHoleRadius,nCanvasYPos-nHoleRadius,
			 nCanvasXPos+nCanvasWidth/2+nHoleRadius,nCanvasYPos+nHoleRadius,
			 nCanvasXPos+nCanvasWidth/2+nHoleRadius,nCanvasYPos,
			 nCanvasXPos+nCanvasWidth/2-nHoleRadius,nCanvasYPos
			 );
	m_dc.MoveTo(nCanvasXPos+nXInterval+3*nHoleRadius, nCanvasYPos);
	m_dc.LineTo(nCanvasXPos+nCanvasWidth-nHoleRadius, nCanvasYPos);
	// Draw ③|
	m_dc.MoveTo(nCanvasXPos+nCanvasWidth, nCanvasYPos);
	m_dc.Arc(nCanvasXPos+nCanvasWidth-nHoleRadius,nCanvasYPos-nHoleRadius,
			 nCanvasXPos+nCanvasWidth+nHoleRadius,nCanvasYPos+nHoleRadius,
			 nCanvasXPos+nCanvasWidth,nCanvasYPos+nHoleRadius,
			 nCanvasXPos+nCanvasWidth-nHoleRadius,nCanvasYPos
			 );
	m_dc.MoveTo(nCanvasXPos+nCanvasWidth, nCanvasYPos+nHoleRadius);
	m_dc.LineTo(nCanvasXPos+nCanvasWidth, nCanvasYPos+nCanvasHeight-nHoleRadius);
	// Draw ⑥--
	m_dc.MoveTo(nCanvasXPos, nCanvasYPos+nCanvasHeight);
	m_dc.Arc(nCanvasXPos-nHoleRadius,nCanvasYPos+nCanvasHeight-nHoleRadius,
			 nCanvasXPos+nHoleRadius,nCanvasYPos+nCanvasHeight+nHoleRadius,
			 nCanvasXPos,nCanvasYPos+nCanvasHeight-nHoleRadius,
			 nCanvasXPos+nHoleRadius,nCanvasYPos+nCanvasHeight
			 );
	m_dc.MoveTo(nCanvasXPos+nHoleRadius, nCanvasYPos+nCanvasHeight);
	m_dc.LineTo(nCanvasXPos+nHoleRadius+nXInterval, nCanvasYPos+nCanvasHeight);
	// Draw ⑤--
	m_dc.MoveTo(nCanvasXPos+nCanvasWidth/2, nCanvasYPos+nCanvasHeight);
	m_dc.Arc(nCanvasXPos+nCanvasWidth/2-nHoleRadius,nCanvasYPos+nCanvasHeight-nHoleRadius,
			 nCanvasXPos+nCanvasWidth/2+nHoleRadius,nCanvasYPos+nCanvasHeight+nHoleRadius,
			 nCanvasXPos+nCanvasWidth/2-nHoleRadius,nCanvasYPos+nCanvasHeight,
			 nCanvasXPos+nCanvasWidth/2+nHoleRadius,nCanvasYPos+nCanvasHeight
			 );
	m_dc.MoveTo(nCanvasXPos+nXInterval+3*nHoleRadius, nCanvasYPos+nCanvasHeight);
	m_dc.LineTo(nCanvasXPos+nCanvasWidth-nHoleRadius, nCanvasYPos+nCanvasHeight);
	// Draw ④
	m_dc.MoveTo(nCanvasXPos+nCanvasWidth, nCanvasYPos+nCanvasHeight);
	m_dc.Arc(nCanvasXPos+nCanvasWidth-nHoleRadius,nCanvasYPos+nCanvasHeight-nHoleRadius,
			 nCanvasXPos+nCanvasWidth+nHoleRadius,nCanvasYPos+nCanvasHeight+nHoleRadius,
			 nCanvasXPos+nCanvasWidth-nHoleRadius,nCanvasYPos+nCanvasHeight,
			 nCanvasXPos+nCanvasWidth,nCanvasYPos+nCanvasHeight-nHoleRadius
			 );
	// 创建画笔,绘制轮廓
	//CPen pen1(PS_SOLID, 2, m_crCanvasOut);  // Solid black pen.
	//pOldPen = m_dc.SelectObject(&pen1);
	m_dc.MoveTo(nCanvasXPos-nHoleRadius, nCanvasYPos);
	m_dc.LineTo(nCanvasXPos-nHoleRadius, nCanvasYPos+nCanvasHeight);
	m_dc.MoveTo(nCanvasXPos+nCanvasWidth+nHoleRadius, nCanvasYPos);
	m_dc.LineTo(nCanvasXPos+nCanvasWidth+nHoleRadius, nCanvasYPos+nCanvasHeight);
	m_dc.MoveTo(nCanvasXPos, nCanvasYPos-nHoleRadius);
	m_dc.LineTo(nCanvasXPos+nCanvasWidth, nCanvasYPos-nHoleRadius);
	m_dc.MoveTo(nCanvasXPos, nCanvasYPos+nCanvasHeight+nHoleRadius);
	m_dc.LineTo(nCanvasXPos+nCanvasWidth, nCanvasYPos+nCanvasHeight+nHoleRadius);		
	//m_dc.SelectObject(pOldPen);
	// 保存位置坐标
	if (bErase == FALSE) {
		m_nCanvasWidthOld  = nCanvasWidth;
		m_nCanvasHeightOld = nCanvasHeight;
		m_nBallRadiusOld   = nBallRadius;
		m_nHoleRadiusOld   = nHoleRadius;
		m_nCanvasXPosOld   = nCanvasXPos;
		m_nCanvasYPosOld   = nCanvasYPos;
	}
}

/**
 * Function Name:IsCanvasChanged()
 * Usage:
 * 判断桌布尺寸是否变化
*/
BOOL CBilliardDlg::IsCanvasChanged()
{
	if (
		m_nCanvasWidth  != m_nCanvasWidthOld ||
		m_nCanvasHeight != m_nCanvasHeightOld ||
//		m_nBallRadius   != m_nBallRadiusOld ||
		m_nHoleRadius   != m_nHoleRadiusOld ||
		m_nCanvasXPos   != m_nCanvasXPosOld ||
		m_nCanvasYPos   != m_nCanvasYPosOld) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Function Name:DrawLine
 * Usage:
 * 绘制袋口到白球之间的瞄准线
*/
void CBilliardDlg::DrawLine(BOOL bErase)
{
	// TODO: 在此添加控件通知处理程序代码
	// 获得光标坐标
	CPoint pointCursor;
	CPoint pointGoal;
	// 如果擦除，使用旧的光标位置
	if (bErase == TRUE) {
		pointCursor = m_PointCursorOld;
		pointGoal = m_PointGoalOld;
	} else {
		pointCursor = m_PointCursor;
		pointGoal = m_PointGoal;
	}
	// 如果终点在窗口内，不要绘制，或者终点在桌布外不要绘制
	RECT rect, rect2;
	this->GetWindowRect(&rect);
	rect2 = CRect(m_nCanvasXPos, m_nCanvasYPos, m_nCanvasXPos+m_nCanvasWidth, m_nCanvasYPos+m_nCanvasHeight);
	if (PtInRect(&rect, pointCursor) || PtInRect(&rect2, pointCursor) == FALSE) {
		return;
	}

	// 创建画笔,绘制轮廓
	//CPen pen(PS_SOLID, 1, m_crLineCanvasIn);  // Solid Green pen.
	//CPen *pOldPen = m_dcLine.SelectObject(&pen);
	//int nRopOld;
	//if (bErase == TRUE) {
	//	nRopOld = m_dcLine.SetROP2(R2_NOTXORPEN);
	//}
	// 中心线
	m_dcLine.MoveTo(pointCursor);
	m_dcLine.LineTo(pointGoal);
	// 目标球
	CPoint point;
	if (GetGoalPosition(pointCursor, pointGoal, &point)) {
		m_dcLine.MoveTo(point);
		if (m_nBallDiameter % 2 == 0) { // 台球直径是偶数
			int nOffset = (int)(m_nBallRadius+0.5);
			m_dcLine.Arc(point.x-nOffset, point.y-nOffset,
						 point.x+nOffset, point.y+nOffset,
						 point.x-nOffset, point.y-nOffset,
						 point.x-nOffset, point.y-nOffset
						 );
		} else { // 台球直径是奇数
			int nOffset = (int)((m_nBallDiameter-1)/2);
			DrawOddCircle(point, nOffset);
		}
	}
	// 白球
	m_dcLine.MoveTo(pointCursor);
	if (m_nBallDiameter % 2 == 0) { // 台球直径是偶数
		m_dcLine.Arc((int)(pointCursor.x-m_nBallRadius+0.5), (int)(pointCursor.y-m_nBallRadius+0.5),
					 (int)(pointCursor.x+m_nBallRadius+0.5), (int)(pointCursor.y+m_nBallRadius+0.5),
					 (int)(pointCursor.x-m_nBallRadius+0.5), (int)(pointCursor.y-m_nBallRadius+0.5),
					 (int)(pointCursor.x-m_nBallRadius+0.5), (int)(pointCursor.y-m_nBallRadius+0.5)
					 );
	} else { // 台球直径是奇数
		int nOffset = (int)((m_nBallDiameter-1)/2);
		DrawOddCircle(pointCursor, nOffset);
	}
//	m_dcLine.SelectObject(pOldPen);	
	// 保存当前位置
	if (bErase == FALSE) {
		m_PointCursorOld = pointCursor;
		m_PointGoalOld = pointGoal;
	}
}

/**
 * Function Name:DrawOddCircle()
 * Usage:
 * 绘制直径是奇数的圆
*/
BOOL CBilliardDlg::DrawOddCircle(const CPoint& point, int nOffset)
{
	CPoint pt1(point), pt2(point), pt3(point), pt4(point);
	COLORREF cr = RGB(255, 0, 0);
	m_dcLine.SetPixel(point, cr);

	for (int nIndex = 0; nIndex < nOffset; nIndex ++) {
		pt1.x -= 1;
		pt2.x += 1;
		pt3.y -= 1;
		pt4.y += 1;
		m_dcLine.SetPixel(pt1, cr);
		m_dcLine.SetPixel(pt2, cr);
		m_dcLine.SetPixel(pt3, cr);
		m_dcLine.SetPixel(pt4, cr);
	}
	return TRUE;
}

/**
 * Function Name:IsLineChanged()
 * Usage:
 * 判断瞄准线尺寸是否变化
*/
BOOL CBilliardDlg::IsLineChanged()
{
	if (!SetGoalPositon()) {
		return FALSE;
	}
	GetCursorPos(&m_PointCursor);
	if (
		m_PointCursorOld != m_PointCursor ||
		m_PointGoalOld   != m_PointGoal) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Function Name:IsReflectChanged()
 * Usage:
 * 判断反射线是否变化
*/
BOOL CBilliardDlg::IsReflectChanged(CPoint ptCursor)
{
	if (m_bGoalBallPointSet == FALSE || m_bWhiteBallPointSet == FALSE) {
		return FALSE;
	}

	CPoint ptCross;
	BOOL bRet = CMath::GetCrossPoint(m_ptGoalBallCenter, m_nBallDiameter, ptCursor, &ptCross);
	if (bRet) {
		m_ptCross = ptCross;
		if (m_ptCross != m_ptCrossOld) {
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * Function Name:GetGoalPosition
 * Usage:
 * 根据当前鼠标位置计算目标球位置
*/
BOOL CBilliardDlg::GetGoalPosition(const CPoint &ptFrom, const CPoint &ptTo, CPoint *point)
{
	double x1,y1,x2,y2,m,l;
	x1 = (double)ptFrom.x;
	y1 = (double)ptFrom.y;
	x2 = (double)ptTo.x;
	y2 = (double)ptTo.y;
	if (x1 == x2 && y1 == y2) {
		return FALSE;
	}
	l = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	m = m_nBallRadius*2;
	point->x = int((m*(x2-x1)+l*x1)/l+0.5);
	point->y = int((m*(y2-y1)+l*y1)/l+0.5);

	return TRUE;
}

/**
 * Function Name:KillOwnTimer
 * Usage:
 * 关闭定时器函数
 * Param:
 * nTimer:-1 关闭所有定时器
 *         1 只关闭模拟桌布定时器
 *         2 只关闭瞄准线定时器
*/
void CBilliardDlg::KillOwnTimer(int nTimer)
{
	if ((nTimer == TIMER_CANVAS || nTimer == TIMER_NONE) && m_nTimerCanvas != TIMER_NONE) {
		KillTimer(m_nTimerCanvas);
		m_nTimerCanvas = TIMER_NONE;
		//DrawCanvas(TRUE);
	}
	if ((nTimer == TIMER_LINES || nTimer == TIMER_NONE) && m_nTimerLine != TIMER_NONE) {
		KillTimer(m_nTimerLine);
		m_nTimerLine = TIMER_NONE;
		//DrawLine(TRUE);
	}
	if ((nTimer == TIMER_REFLECT || nTimer == TIMER_NONE) && m_nTimerReflect != TIMER_NONE) {
		KillTimer(m_nTimerReflect);
		m_nTimerReflect = TIMER_NONE;
	}
}


/**
 * Function Name:SetGoalPosition
 * Usage:
 * 根据瞄准的袋口确定对应坐标
*/
BOOL CBilliardDlg::SetGoalPositon()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nGoal == GOAL_LU) {
		m_PointGoal = CPoint(int(m_nCanvasXPos+m_nHoleRadius/2+0.5), int(m_nCanvasYPos+m_nHoleRadius/2+0.5));
	} else if (m_nGoal == GOAL_MU) {
		m_PointGoal = CPoint(int(m_nCanvasXPos+m_nCanvasWidth/2+0.5), m_nCanvasYPos);
	} else if (m_nGoal == GOAL_RU) {
		m_PointGoal = CPoint(int(m_nCanvasXPos+m_nCanvasWidth-m_nHoleRadius/2+0.5), int(m_nCanvasYPos+m_nHoleRadius/2+0.5));
	} else if (m_nGoal == GOAL_LD) {
		m_PointGoal = CPoint(int(m_nCanvasXPos+m_nHoleRadius/2+0.5), int(m_nCanvasYPos+m_nCanvasHeight-m_nHoleRadius/2+0.5));
	} else if (m_nGoal == GOAL_MD) {
		m_PointGoal = CPoint(int(m_nCanvasXPos+m_nCanvasWidth/2+0.5), m_nCanvasYPos+m_nCanvasHeight);
	} else if (m_nGoal == GOAL_RD) {
		m_PointGoal = CPoint(int(m_nCanvasXPos+m_nCanvasWidth-m_nHoleRadius/2+0.5), int(m_nCanvasYPos+m_nCanvasHeight-m_nHoleRadius/2+0.5));
	} else {
		return FALSE;
	}
	return TRUE;
}

/**
 * Function Name:OnBnClickedCheckShowcanvas
 * Usage:
 * 显示/隐藏模拟桌布
*/
void CBilliardDlg::OnBnClickedCheckShowcanvas()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nShowCanvas = (m_nShowCanvas==BST_CHECKED)?BST_UNCHECKED:BST_CHECKED;
	if (m_nShowCanvas == BST_CHECKED) {
		m_nTimerCanvas = SetTimer(TIMER_CANVAS, TIMER_CANVAS_INTERVAL, 0);
	} else {
		KillOwnTimer(TIMER_CANVAS);
		RefreshAll();
	}
	UpdateData(FALSE);
	UpdateMenuItemStatus(IDC_CHECK_SHOWCANVAS);
}

/**
 * Function Name:OnBnClickedCheckShowline
 * Usage:
 * 显示/隐藏瞄准线
*/
void CBilliardDlg::OnBnClickedCheckShowline()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nShowLine = (m_nShowLine==BST_CHECKED)?BST_UNCHECKED:BST_CHECKED;
	//if (m_nShowLine == BST_CHECKED) {
	//	m_nTimerLine = SetTimer(TIMER_LINES, TIMER_LINES_INTERVAL, 0);
	//} else {
	//	KillOwnTimer(TIMER_LINES);
	//}
	RefreshAll();
	UpdateData(FALSE);
	UpdateMenuItemStatus(IDC_CHECK_SHOWLINE);
}

/**
 * Function Name:OnBnClickedCheckShowline
 * Usage:
 * 显示/隐藏放大镜
*/
void CBilliardDlg::OnBnClickedCheckZoom()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nShowZoom = (m_nShowZoom==BST_CHECKED)?BST_UNCHECKED:BST_CHECKED;
	UpdateData(FALSE);
	ShowPreviewDlg(m_nShowZoom == BST_CHECKED ? TRUE : FALSE);
	UpdateMenuItemStatus(IDC_CHECK_ZOOM);
}

/**
 * Function Name:OnBnClickedCheckForceRefresh
 * Usage:
 * 强制刷新
*/
void CBilliardDlg::OnBnClickedCheckForceRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	RefreshAll();
}

/**
 * Function Name:PreTranslateMessage
 * Usage:
 * 通过键盘消息来切换目标袋口
*/
BOOL CBilliardDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == 'A') {//'A'
			m_nGoal = GOAL_LU;
			SwitchDesk(IDB_BITMAP_LT);
		} else if (pMsg->wParam == 'S') {//'S'
			m_nGoal = GOAL_MU;
			SwitchDesk(IDB_BITMAP_MT);
		} else if (pMsg->wParam == 'D') {//'D'
			m_nGoal = GOAL_RU;
			SwitchDesk(IDB_BITMAP_RT);
		} else if (pMsg->wParam == 'Z') {//'Z'
			m_nGoal = GOAL_LD;
			SwitchDesk(IDB_BITMAP_LB);
		} else if (pMsg->wParam == 'X') {//'X'
			m_nGoal = GOAL_MD;
			SwitchDesk(IDB_BITMAP_MB);
		} else if (pMsg->wParam == 'C') {//'C'
			m_nGoal = GOAL_RD;
			SwitchDesk(IDB_BITMAP_RB);
		} else if (pMsg->wParam == 'Q') {//LEFT
			MoveCursor(VK_LEFT);
		} else if (pMsg->wParam == 'E') {//RIGHT
			MoveCursor(VK_RIGHT);
		} else if (pMsg->wParam == '2') {//UP
			MoveCursor(VK_UP);
		} else if (pMsg->wParam == 'W') {//DOWN
			MoveCursor(VK_DOWN);
		} else if (pMsg->wParam == '1') {//DOWN
			SetWhiteBallPoint();
		} else if (pMsg->wParam == '3') {//DOWN
			SetGoalBallPoint();
		} else if (pMsg->wParam == '4') {//DOWN
			ResetReflect();
		} else if (pMsg->wParam == VK_ESCAPE) {
			// 不能ESCAPE键退出
			return 0;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

/**
 * Function Name:OnDeltaposSpinWidth
 * Usage:
 * 修改桌面宽度消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinWidth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nCanvasWidth -= pNMUpDown->iDelta;
	UpdateData(FALSE);
	*pResult = 0;
}

/**
 * Function Name:OnDeltaposSpinHeight
 * Usage:
 * 修改桌面高度消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nCanvasHeight -= pNMUpDown->iDelta;
	UpdateData(FALSE);
	*pResult = 0;
}

/**
 * Function Name:OnDeltaposSpinBallRadius
 * Usage:
 * 修改台球半径消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinBallRadius(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nBallDiameter -= pNMUpDown->iDelta;
	m_nBallRadius = (float)m_nBallDiameter/2;
	UpdateData(FALSE);
	*pResult = 0;
}

/**
 * Function Name:OnDeltaposSpinHoleRadius
 * Usage:
 * 修改袋口半径消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinHoleRadius(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nHoleRadius -= pNMUpDown->iDelta;
	UpdateData(FALSE);
	*pResult = 0;
}

/**
 * Function Name:OnDeltaposSpinXpos
 * Usage:
 * 修改桌布横坐标消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinXpos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nCanvasXPos -= pNMUpDown->iDelta;
	UpdateData(FALSE);
	*pResult = 0;
}

/**
 * Function Name:OnDeltaposSpinYpos
 * Usage:
 * 修改桌布纵坐标消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinYpos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nCanvasYPos += pNMUpDown->iDelta;   // 笛卡尔坐标
	UpdateData(FALSE);
	*pResult = 0;
}

/**
 * Function Name:OnDeltaposSpinYpos
 * Usage:
 * 修改放大镜倍数消息响应函数
*/
void CBilliardDlg::OnDeltaposSpinZoom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nOldZoomValue = m_nZoomValue;
	m_nZoomValue -= pNMUpDown->iDelta;   // 笛卡尔坐标
	if (m_nZoomValue > ZOOM_MAX || m_nZoomValue < ZOOM_MIN) {
		m_nZoomValue = nOldZoomValue;
	}
	ChangeZoom();
	*pResult = 0;
}

/**
 * Function Name:ChangeZoom
 * Usage:
 * 根据zomm改变放大镜大小
*/
void CBilliardDlg::ChangeZoom()
{
	m_nSize = (int)(m_nZoomValue*m_nBallRadius*8+0.5);
	UpdateData(FALSE);
	// Redraw the zoom window
	RECT rect;
	this->GetWindowRect(&rect);
//	m_dlgPreview.MoveWindow(rect.right, rect.top, m_nSize, m_nSize);
	m_dlgPreview.SetWindowPos(this, rect.right,rect.top, m_nSize, m_nSize, SWP_NOOWNERZORDER|SWP_NOACTIVATE|/*SWP_NOREDRAW|*/SWP_NOMOVE|SWP_NOZORDER);
}

/**
 * Function Name:OnBnClickedCfgDefault
 * Usage:
 * 保存当前配置为默认值
*/
void CBilliardDlg::OnBnClickedCfgDefault()
{
	// TODO: 在此添加控件通知处理程序代码
	char szPath[256];
	GetExePath(szPath);
	CString str = szPath;
	WriteConfig(str);
}

/**
 * Function Name:OnBnClickedCfgSave
 * Usage:
 * 保存当前配置
*/
void CBilliardDlg::OnBnClickedCfgSave()
{
	// TODO: 在此添加控件通知处理程序代码
	// szFilters is a text string that includes two file name filters:
	// "*.cfg" for "BA Files"
	char szFilters[]=
	  "BA Files (*.cfg)|*.cfg|";

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg (FALSE, "cfg", "*.cfg",
	  OFN_HIDEREADONLY, szFilters, this);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if( fileDlg.DoModal ()==IDOK )
	{
	  CString pathName = fileDlg.GetPathName();
	  WriteConfig(pathName);
	  
	}
}

/**
 * Function Name:OnBnClickedCfgLoad
 * Usage:
 * 装载指定配置
*/
void CBilliardDlg::OnBnClickedCfgLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	// szFilters is a text string that includes two file name filters:
	// "*.cfg" for "BA Files"
	char szFilters[]=
	  "BA Files (*.cfg)|*.cfg|";

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg (TRUE, "cfg", "*.cfg",
	  OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if( fileDlg.DoModal ()==IDOK )
	{
		CString pathName = fileDlg.GetPathName();
		ReadConfig(pathName);
		UpdateData(FALSE);
		// 预览对话框默认大小
		m_nSize = (int)(m_nZoomValue*m_nBallRadius*8+0.5);
	}
}

/**
 * Function Name:ReadConfig
 * Usage:
 * 读取当前配置
*/
void CBilliardDlg::ReadConfig(const CString& pathName)
{
	// TODO: 在此添加控件通知处理程序代码
	CFile file;
	CFileException fe;
	//以读方式打开文件
	if(!file.Open(pathName, CFile::modeRead, &fe))
	{
		//fe.ReportError();
		return;
	}

	//构建CArchive 对象
	CArchive ar(&file, CArchive::load);
	ar >> m_nCanvasWidth 
		>> m_nCanvasHeight 
		>> m_nBallDiameter 
		>> m_nHoleRadius 
		>> m_nCanvasXPos 
		>> m_nCanvasYPos
		>> m_nZoomValue
		;
	ar.Flush();
	//写完毕，关闭文件流
	ar.Close();
	file.Close();
	m_nBallRadius = (float)m_nBallDiameter/2;
	//更新数据
	UpdateData(FALSE);
}

/**
 * Function Name:WriteConfig
 * Usage:
 * 保存当前配置
*/
void CBilliardDlg::WriteConfig(const CString& pathName)
{
	CFile file;
	CFileException fe;
	//读取最新数据
	if (UpdateData(TRUE) == FALSE) {
		return;
	}
	//以读方式打开文件
	if(!file.Open(pathName, CFile::modeWrite | CFile::modeCreate, &fe))
	{
		fe.ReportError();
		return;
	}
	//构建CArchive 对象
	CArchive ar(&file, CArchive::store);
	ar << m_nCanvasWidth 
		<< m_nCanvasHeight 
		<< m_nBallDiameter 
		<< m_nHoleRadius 
		<< m_nCanvasXPos 
		<< m_nCanvasYPos
		<< m_nZoomValue
		;
	ar.Flush();
	//写完毕，关闭文件流
	ar.Close();
	file.Close();
}

/**
 * Function Name:GetExePath
 * Usage:
 * 获得当前路径
*/
void CBilliardDlg::GetExePath(char* pExePath)
{
    char szPathName[256];
	char szBuf[256];
	char* pfind;

    /* Get current directory */
	GetModuleFileName(NULL, szPathName, sizeof(szPathName));
	strcpy_s(szBuf, sizeof(szBuf), szPathName);
	pfind = strrchr(szBuf, '\\');
	if (pfind != NULL) {
		szPathName[pfind-szBuf+1] = '\0';
	}
	strcat_s(szPathName, sizeof(szPathName), "default.cfg");
	strcpy_s(pExePath, 256, szPathName);
}

/**
 * Function Name:OnCreate
 * Usage:
 * WM_CREATE消息函数
*/
int CBilliardDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	// 拖动窗口过程中不触发WM_ERASEBKGND
	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
	// 创建放大窗口
	m_dlgPreview.Create(IDD_PREVIEW, this);

	return 0;
}

/**
 * Function Name:ShowPreview
 * Usage:
 * 隐藏/显示预览放大对话框
*/
void CBilliardDlg::ShowPreviewDlg(BOOL bShow)
{
	RECT rect;
	this->GetWindowRect(&rect);
	if (bShow) {
		if (m_bFirstZoom) {
			// 第一次显示放大镜，停靠在对话框的右侧
			m_dlgPreview.SetWindowPos(this, rect.right, rect.top, m_nSize, m_nSize, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOREDRAW|SWP_NOZORDER|SWP_SHOWWINDOW);
			m_bFirstZoom = FALSE;
		} else {
			// 以后再显示不改变其位置
			m_dlgPreview.SetWindowPos(this, 0, 0, 0, 0, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOREDRAW|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
		}
	} else {
		m_dlgPreview.SetWindowPos(this, 0, 0, 0, 0, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_HIDEWINDOW);
	}
}

/**
 * Function Name:DrawPreview
 * Usage:
 * 绘制屏幕到指定窗口
*/
void CBilliardDlg::DrawPreview() 
{
	if (m_nShowZoom == BST_CHECKED) {
		// 捕捉屏幕
		m_CaptureEx.CaptureDesktop (1,0,FALSE,m_nBallDiameter*2);
		// 绘制图像
		RECT rect;
		this->GetWindowRect(&rect);
		m_dlgPreview.SetWindowPos(this, rect.right,rect.top, m_nSize, m_nSize, SWP_NOOWNERZORDER|SWP_NOACTIVATE|SWP_NOREDRAW|SWP_NOMOVE|SWP_NOZORDER);
		m_CaptureEx.DisplayLastImage(m_dlgPreview.GetSafeHwnd(), m_nZoomValue);
	}
}

/**
 * Function Name:LoadStr
 * Usage:
 * 从String Table中返回字符串
*/
void CBilliardDlg::LoadStr(UINT uResourceID, char* szBuffer)
{
	char sz[100]; 
	LoadString(AfxGetInstanceHandle(), uResourceID, sz, sizeof(sz)/sizeof(char));
	strcpy_s(szBuffer, 100, sz);
}

/**
 * Function Name:OnEnChangeEdit*
 * Usage:
 * 参数输入改变消息函数
*/
void CBilliardDlg::OnEnChangeEditWidth()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nCanvasWidth;
	if (UpdateData(TRUE) == FALSE) {
		m_nCanvasWidth = nOld;
	}
	UpdateData(FALSE);
}
void CBilliardDlg::OnEnChangeEditHeight()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nCanvasHeight;
	if (UpdateData(TRUE) == FALSE) {
		m_nCanvasHeight = nOld;
	}
	UpdateData(FALSE);
}

void CBilliardDlg::OnEnChangeEditXPos()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nCanvasXPos;
	if (UpdateData(TRUE) == FALSE) {
		m_nCanvasXPos = nOld;
	}
	UpdateData(FALSE);
}

void CBilliardDlg::OnEnChangeEditYPos()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nCanvasYPos;
	if (UpdateData(TRUE) == FALSE) {
		m_nCanvasYPos = nOld;
	}
	UpdateData(FALSE);
}

void CBilliardDlg::OnEnChangeEditBallRadius()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nBallDiameter;
	if (UpdateData(TRUE) == FALSE) {
		m_nBallDiameter = nOld;
	}
	m_nBallRadius = (float)(m_nBallDiameter/2);

	UpdateData(FALSE);
}

void CBilliardDlg::OnEnChangeEditHoleRadius()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nHoleRadius;
	if (UpdateData(TRUE) == FALSE) {
		m_nHoleRadius = nOld;
	}
	UpdateData(FALSE);
}

void CBilliardDlg::OnEnChangeEditZoom()
{
	// TODO:  在此添加控件通知处理程序代码
	int nOld = m_nZoomValue;
	if (UpdateData(TRUE) == FALSE) {
		m_nZoomValue = nOld;
		UpdateData(FALSE);
		return;
	}
	ChangeZoom();
}

/**
 * Function Name:OnLButtonDown
 * Usage:
 * 左键按下消息函数
*/
void CBilliardDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nWidth = 0, nHeight = 0;
	RECT rect;
	m_picDesk.GetWindowRect(&rect);
    this->ClientToScreen(&point);
	nWidth  = abs(rect.right-rect.left);
	nHeight = abs(rect.bottom-rect.top);
	// 判断是否点击选择袋口
	if(PtInRect(&rect, point)) 
	{
		CPoint ptCenter(rect.left+nWidth/2, rect.top+nHeight/2);
		if (point.x <= (rect.left+nWidth/3)) {
			// Left part
			if (point.y <= (rect.top+nHeight/2)) {
				m_nGoal = GOAL_LU;
				SwitchDesk(IDB_BITMAP_LT);
			} else {
				m_nGoal = GOAL_LD;
				SwitchDesk(IDB_BITMAP_LB);
			}
		} else if (point.x > (rect.left+2*nWidth/3)) {
			// Right part
			if (point.y <= (rect.top+nHeight/2)) {
				m_nGoal = GOAL_RU;
				SwitchDesk(IDB_BITMAP_RT);
			} else {
				m_nGoal = GOAL_RD;
				SwitchDesk(IDB_BITMAP_RB);
			}
		} else {
			// Middle part
			if (point.y <= (rect.top+nHeight/2)) {
				m_nGoal = GOAL_MU;
				SwitchDesk(IDB_BITMAP_MT);
			} else {
				m_nGoal = GOAL_MD;
				SwitchDesk(IDB_BITMAP_MB);
			}
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

/**
 * Function Name:SwitchDesk
 * Usage:
 * 切换瞄准袋口对应位图
*/
void CBilliardDlg::SwitchDesk(UINT nResourceID)
{
	HBITMAP hBitmap = m_picDesk.GetBitmap();
	m_picDesk.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(nResourceID)));
	if (GetObjectType(hBitmap) == OBJ_BITMAP) {
		::DeleteObject(hBitmap);
	}
}

/**
 * Function Name:MoveCursor
 * Usage:
 * 微调光标位置
*/
void CBilliardDlg::MoveCursor(int nDirection)
{
	CPoint pt;
	GetCursorPos(&pt);
	if (nDirection == VK_LEFT) {
		SetCursorPos(pt.x-1, pt.y);
	} else if (nDirection == VK_UP) {
		SetCursorPos(pt.x, pt.y-1);
	} else if (nDirection == VK_RIGHT) {
		SetCursorPos(pt.x+1, pt.y);
	} else if (nDirection == VK_DOWN) {
		SetCursorPos(pt.x, pt.y+1);
	}
}

/**
 * Function Name:OnBnClickedAdvance
 * Usage:
 * 关于
*/
void CBilliardDlg::OnBnClickedAdvance()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}

/**
 * Function Name:OnHotKey
 * Usage:
 * Hotkey捕捉
*/
LRESULT CBilliardDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	lParam;
	if(wParam == m_nHOTKEY_A) {//'A'
		m_nGoal = GOAL_LU;
		SwitchDesk(IDB_BITMAP_LT);
	} else if (wParam == m_nHOTKEY_S) {//'S'
		m_nGoal = GOAL_MU;
		SwitchDesk(IDB_BITMAP_MT);
	} else if (wParam == m_nHOTKEY_D) {//'D'
		m_nGoal = GOAL_RU;
		SwitchDesk(IDB_BITMAP_RT);
	} else if (wParam == m_nHOTKEY_Z) {//'Z'
		m_nGoal = GOAL_LD;
		SwitchDesk(IDB_BITMAP_LB);
	} else if (wParam == m_nHOTKEY_X) {//'X'
		m_nGoal = GOAL_MD;
		SwitchDesk(IDB_BITMAP_MB);
	} else if (wParam == m_nHOTKEY_C) {//'C'
		m_nGoal = GOAL_RD;
		SwitchDesk(IDB_BITMAP_RB);
	} else if (wParam == m_nHOTKEY_LEFT) {//LEFT
		MoveCursor(VK_LEFT);
	} else if (wParam == m_nHOTKEY_RIGHT) {//RIGHT
		MoveCursor(VK_RIGHT);
	} else if (wParam == m_nHOTKEY_UP) {//UP
		MoveCursor(VK_UP);
	} else if (wParam == m_nHOTKEY_DOWN) {//DOWN
		MoveCursor(VK_DOWN);
	} else if (wParam == m_nHOTKEY_WHITE) {//White ball
		SetWhiteBallPoint();
	} else if (wParam == m_nHOTKEY_GOAL) {//Goal ball
		SetGoalBallPoint();
	} else if (wParam == m_nHOTKEY_RESET) {// Reset
		ResetReflect();
	}

	return 0;
}

/**
 * Function Name:RefreshAll
 * Usage:
 * 刷新整个屏幕或指定区域
*/
void CBilliardDlg::RefreshAll()
{
	::InvalidateRect(NULL, NULL, FALSE);
}

/**
 * Function Name:SetHotKey
 * Usage:
 * 设定取消热键
*/
void CBilliardDlg::SetHotKey(BOOL bSet)
{
	// Hotkey
	if (bSet == TRUE) {
		if(GlobalFindAtom("BA_HOTKEY_A") == 0)
		{
			m_nHOTKEY_A = GlobalAddAtom("BA_HOTKEY_A");
			RegisterHotKey(m_hWnd,m_nHOTKEY_A,0, 'A');
		}
		if(GlobalFindAtom("BA_HOTKEY_S") == 0)
		{
			m_nHOTKEY_S = GlobalAddAtom("BA_HOTKEY_S");
			RegisterHotKey(m_hWnd,m_nHOTKEY_S,0, 'S');
		}
		if(GlobalFindAtom("BA_HOTKEY_D") == 0)
		{
			m_nHOTKEY_D = GlobalAddAtom("BA_HOTKEY_D");
			RegisterHotKey(m_hWnd,m_nHOTKEY_D,0, 'D');
		}
		if(GlobalFindAtom("BA_HOTKEY_Z") == 0)
		{
			m_nHOTKEY_Z = GlobalAddAtom("BA_HOTKEY_Z");
			RegisterHotKey(m_hWnd,m_nHOTKEY_Z,0, 'Z');
		}
		if(GlobalFindAtom("BA_HOTKEY_X") == 0)
		{
			m_nHOTKEY_X = GlobalAddAtom("BA_HOTKEY_X");
			RegisterHotKey(m_hWnd,m_nHOTKEY_X,0, 'X');
		}
		if(GlobalFindAtom("BA_HOTKEY_C") == 0)
		{
			m_nHOTKEY_C = GlobalAddAtom("BA_HOTKEY_C");
			RegisterHotKey(m_hWnd,m_nHOTKEY_C,0, 'C');
		}
		if(GlobalFindAtom("BA_HOTKEY_LEFT") == 0)
		{
			m_nHOTKEY_LEFT	= GlobalAddAtom("BA_HOTKEY_LEFT");
			RegisterHotKey(m_hWnd,m_nHOTKEY_LEFT,0, 'Q');
		}
		if(GlobalFindAtom("BA_HOTKEY_RIGHT") == 0)
		{
			m_nHOTKEY_RIGHT	= GlobalAddAtom("BA_HOTKEY_RIGHT");
			RegisterHotKey(m_hWnd,m_nHOTKEY_RIGHT,0, 'E');
		}
		if(GlobalFindAtom("BA_HOTKEY_UP") == 0)
		{
			m_nHOTKEY_UP	= GlobalAddAtom("BA_HOTKEY_UP");
			RegisterHotKey(m_hWnd,m_nHOTKEY_UP,0, '2');
		}
		if(GlobalFindAtom("BA_HOTKEY_DOWN") == 0)
		{
			m_nHOTKEY_DOWN	= GlobalAddAtom("BA_HOTKEY_DOWN");
			RegisterHotKey(m_hWnd,m_nHOTKEY_DOWN,0, 'W');
		}
		if(GlobalFindAtom("BA_HOTKEY_WHITE_BALL") == 0)
		{
			m_nHOTKEY_WHITE	= GlobalAddAtom("BA_HOTKEY_WHITE_BALL");
			RegisterHotKey(m_hWnd,m_nHOTKEY_WHITE,0, '1');
		}
		if(GlobalFindAtom("BA_HOTKEY_GOAL") == 0)
		{
			m_nHOTKEY_GOAL	= GlobalAddAtom("BA_HOTKEY_GOAL");
			RegisterHotKey(m_hWnd,m_nHOTKEY_GOAL,0, '3');
		}
		if(GlobalFindAtom("BA_HOTKEY_RESET") == 0)
		{
			m_nHOTKEY_DOWN	= GlobalAddAtom("BA_HOTKEY_RESET");
			RegisterHotKey(m_hWnd,m_nHOTKEY_RESET,0, '4');
		}
	} else {
		if (m_nHOTKEY_A > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_A);
			GlobalDeleteAtom(m_nHOTKEY_A);
			m_nHOTKEY_A = -1;
		}
		if (m_nHOTKEY_S > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_S);
			GlobalDeleteAtom(m_nHOTKEY_S);
			m_nHOTKEY_S = -1;
		}
		if (m_nHOTKEY_D > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_D);
			GlobalDeleteAtom(m_nHOTKEY_D);
			m_nHOTKEY_D = -1;
		}
		if (m_nHOTKEY_Z > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_Z);
			GlobalDeleteAtom(m_nHOTKEY_Z);
			m_nHOTKEY_Z = -1;
		}
		if (m_nHOTKEY_X > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_X);
			GlobalDeleteAtom(m_nHOTKEY_X);
			m_nHOTKEY_X = -1;
		}
		if (m_nHOTKEY_C > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_C);
			GlobalDeleteAtom(m_nHOTKEY_C);
			m_nHOTKEY_C = -1;
		}
		if (m_nHOTKEY_LEFT > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_LEFT);
			GlobalDeleteAtom(m_nHOTKEY_LEFT);
			m_nHOTKEY_LEFT = -1;
		}
		if (m_nHOTKEY_RIGHT > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_RIGHT);
			GlobalDeleteAtom(m_nHOTKEY_RIGHT);
			m_nHOTKEY_RIGHT = -1;
		}
		if (m_nHOTKEY_UP > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_UP);
			GlobalDeleteAtom(m_nHOTKEY_UP);
			m_nHOTKEY_UP = -1;
		}
		if (m_nHOTKEY_DOWN > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_DOWN);
			GlobalDeleteAtom(m_nHOTKEY_DOWN);
			m_nHOTKEY_DOWN = -1;
		}
		if (m_nHOTKEY_WHITE > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_WHITE);
			GlobalDeleteAtom(m_nHOTKEY_WHITE);
			m_nHOTKEY_WHITE = -1;
		}
		if (m_nHOTKEY_GOAL > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_GOAL);
			GlobalDeleteAtom(m_nHOTKEY_GOAL);
			m_nHOTKEY_GOAL = -1;
		}
		if (m_nHOTKEY_RESET > 0) {
			UnregisterHotKey(m_hWnd, m_nHOTKEY_RESET);
			GlobalDeleteAtom(m_nHOTKEY_RESET);
			m_nHOTKEY_RESET = -1;
		}
	}
}

/**
 * Function Name:OnBnClickedCheckHotkey
 * Usage:
 * 设定取消热键响应函数
*/
void CBilliardDlg::OnBnClickedCheckHotkey()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nHotkey = (m_nHotkey==BST_CHECKED)?BST_UNCHECKED:BST_CHECKED;
	UpdateData(FALSE);
	SetHotKey(m_nHotkey == BST_CHECKED ? TRUE : FALSE);
	UpdateMenuItemStatus(IDC_CHECK_HOTKEY);
}

/*	Function Name   : AnimateIcon
	Description		: Function which will act based on the message type that is received as parameter
					  like ADD, MODIFY, DELETE icon in the system tray. Also send a message to display
					  the icon in title bar as well as in the task bar application.
	Function Called	: Shell_NotifyIcon	-	API which will Add, Modify, Delete icon in tray.
					  SendMessage - Send a message to windows
	Variable		: NOTIFYICONDATA - Structure which will have the details of the tray icons
*/
void CBilliardDlg::AddTrayIcon(DWORD dwMsgType,UINT nIndexOfIcon)
{
	nIndexOfIcon;
	HWND hWnd = this->GetSafeHwnd();
	HICON hIconAtIndex = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	NOTIFYICONDATA IconData;

	IconData.cbSize = sizeof(NOTIFYICONDATA);
	IconData.uID = IDR_MAINFRAME;
	IconData.hIcon  = hIconAtIndex;
	IconData.hWnd   = m_hWnd;
	lstrcpyn(IconData.szTip,"BilliardAssist", (int) strlen("BilliardAssist")+1);
	IconData.uCallbackMessage = MYMSG_NOTIFYICON;
	IconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	
	Shell_NotifyIcon(dwMsgType, &IconData);
	this->SendMessage(WM_SETICON, NULL, (long) hIconAtIndex);

	if(hIconAtIndex)
		DestroyIcon(hIconAtIndex);
}

/*	Function Name   : OnTrayNotification
	Description		: CALLBACK routine which will be get executed when a notification is identified on the
					  system tray. 
	Function Called	: LoadMenu	-	Load the menu into the application
*/
afx_msg LRESULT CBilliardDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	wParam;
	switch(lParam)
	{
		case WM_LBUTTONDBLCLK:
		{
			//OnTrayiconShowwindow();
			OnBnClickedCheckHotkey();
			break;
		}
		case WM_RBUTTONDOWN:
		{
			/** Load and verify the menu**/
			if(m_hMenu != NULL)
			{
				POINT pt;
				HWND hWnd = this->GetSafeHwnd();
				::GetCursorPos(&pt);
				::SetForegroundWindow(hWnd);
				::TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
			}
			break ;
		}
	}
	return 0;
}

/**
 * Function Name:OnFileExit
 * Usage:
 * 程序退出消息响应函数
*/
void CBilliardDlg::OnFileExit()
{
	// TODO: 在此添加命令处理程序代码
	PostQuitMessage(0); 
}

/**
 * Function Name:OnTrayiconShowwindow
 * Usage:
 * 显示/隐藏窗口响应函数
*/
void CBilliardDlg::OnTrayiconShowwindow()
{
	// TODO: 在此添加命令处理程序代码
	if (this->IsWindowVisible()) {
		MinimizeWndToTray(this->GetSafeHwnd());
	} else {
		RestoreWndFromTray(this->GetSafeHwnd());
	}
	
	UpdateMenuItemStatus(ID_TRAYICON_SHOWWINDOW);
}

/**
 * Function Name:UpdateMenuItemStatus
 * Usage:
 * 更新各个子菜单项的状态
*/
void CBilliardDlg::UpdateMenuItemStatus(UINT nMenuID)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_hMenu == NULL) {
		return;
	}
	CMenu menu;
	menu.Attach(m_hMenu);
	MENUITEMINFO info;
	info.cbSize = sizeof (MENUITEMINFO); // must fill up this field
	info.fMask = MIIM_STATE;             // get the state of the menu item
	menu.GetMenuItemInfo(nMenuID, &info);

    if (info.fState & MF_CHECKED)
       menu.CheckMenuItem(nMenuID, MF_UNCHECKED | MF_BYCOMMAND);
    else
       menu.CheckMenuItem(nMenuID, MF_CHECKED | MF_BYCOMMAND);
	menu.Detach();
}

/**
 * Function Name:OnClose
 * Usage:
 * 隐藏主窗口
*/
void CBilliardDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MinimizeWndToTray(this->GetSafeHwnd());
	UpdateMenuItemStatus(ID_TRAYICON_SHOWWINDOW);
}

void CBilliardDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 切换袋口光标
	if (GetActiveWindow() == this) {
		int nWidth = 0, nHeight = 0;
		RECT rect;
		m_picDesk.GetWindowRect(&rect);
		this->ClientToScreen(&point);
		// 判断是否点击选择袋口
		if(PtInRect(&rect, point)) 
		{
			//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
			SetCursor(NULL);
		} else {
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CBilliardDlg::SetWhiteBallPoint()
{
	GetCursorPos(&m_ptWhiteBallCenter);
	m_bWhiteBallPointSet = TRUE;
}

void CBilliardDlg::SetGoalBallPoint()
{
	GetCursorPos(&m_ptGoalBallCenter);
	m_bGoalBallPointSet = TRUE;
}

void CBilliardDlg::ResetReflect()
{
	m_bWhiteBallPointSet = FALSE;
	m_bGoalBallPointSet = FALSE;
}

void CBilliardDlg::DrawVirtualCircle(CPoint ptCursor, BOOL bErase)
{
	if (m_bGoalBallPointSet == FALSE || m_bWhiteBallPointSet == FALSE) {
		return;
	}
	int nOffset;
	CPoint point;
	// 获得相交点
	// 获得当前鼠标位置
	CPoint ptCross;
	BOOL bRet = CMath::GetCrossPoint(m_ptGoalBallCenter, m_nBallDiameter, ptCursor, &ptCross);
	// 虚拟白球
	if (bRet) {
		m_ptCross = ptCross;
		// 如果擦除，使用旧的光标位置
		if (bErase == TRUE) {
			ptCross = m_ptCrossOld;
		} else {
			ptCross = m_ptCross;
		}
		// 绘制白球-目标球连线
		m_dcReflect.MoveTo(m_ptWhiteBallCenter);
		if (ptCross.x >= 0 && ptCross.y >= 0) {
			m_dcReflect.LineTo(ptCross);
		}
		// 绘制交叉点圆
		point = ptCross;
		nOffset = (int)(m_nBallRadius+0.5);
		m_dcReflect.Arc(point.x-nOffset, point.y-nOffset,
					 point.x+nOffset, point.y+nOffset,
					 point.x-nOffset, point.y-nOffset,
					 point.x-nOffset, point.y-nOffset
					 );
		double dis = abs((ptCursor.x - ptCross.x) * (ptCursor.x - ptCross.x) + (ptCursor.y - ptCross.y) * (ptCursor.y - ptCross.y));
		double res = sqrt(dis);
		if( res > 1) {
			//SetCursorPos(ptCross.x, ptCross.y);
		}
		CList<CPoint,CPoint&> *ptList = new CList<CPoint,CPoint&>;
		bRet = GetReflectLine(m_ptGoalBallCenter, ptCursor, ptList);
		if (bRet) {
			SetList(ptList, m_pPtList);
			// 如果擦除，使用旧的光标位置
			if (bErase == TRUE) {
				SetList(m_pPtListOld, ptList);
			} else {
				SetList(m_pPtList, ptList);
			}
			if (ptList->GetCount() > 0) {
				CPoint ptCross1 = ptList->GetHead();
				m_dcReflect.MoveTo(m_ptGoalBallCenter);
				m_dcReflect.LineTo(ptCross1);
				CPoint ptOld = ptCross1;
				for (int nIndex = 1; nIndex < ptList->GetCount(); nIndex ++) {
					POSITION pos = ptList->FindIndex(nIndex);
					CPoint ptNew = ptList->GetAt(pos);
					m_dcReflect.MoveTo(ptOld);
					m_dcReflect.LineTo(ptNew);
					ptOld = ptNew;
				}
			}
			// 保存当前位置
			if (bErase == FALSE) {
				SetList(ptList, m_pPtListOld);
			}
		} else {
			//AfxMessageBox("failed to get reflect line");
			TRACE("Failed to reflect\n");
		}
		ptList->RemoveAll();
		delete ptList;
		ptList = NULL;
		// 保存当前位置
		if (bErase == FALSE) {
			m_ptCrossOld = ptCross;
		}
	}
}

void CBilliardDlg::DrawVirtualLine(CPoint ptCursor, BOOL bErase)
{
	if (m_bGoalBallPointSet == FALSE || m_bWhiteBallPointSet == FALSE) {
		return;
	}
	//
	// 绘制白球
	int nOffset = (int)(m_nBallRadius+0.5);
	CPoint point(m_ptWhiteBallCenter);
	m_dcReflect.Arc(point.x-nOffset, point.y-nOffset,
				 point.x+nOffset, point.y+nOffset,
				 point.x-nOffset, point.y-nOffset,
				 point.x-nOffset, point.y-nOffset
				 );

	// 绘制目标球
	point = m_ptGoalBallCenter;
	nOffset = (int)(m_nBallRadius+0.5);
	m_dcReflect.Arc(point.x-nOffset, point.y-nOffset,
				 point.x+nOffset, point.y+nOffset,
				 point.x-nOffset, point.y-nOffset,
				 point.x-nOffset, point.y-nOffset
				 );

	// 绘制白球虚拟轨迹
	point = m_ptGoalBallCenter;
	nOffset = m_nBallDiameter;
	m_dcReflect.Arc(point.x-nOffset, point.y-nOffset,
				 point.x+nOffset, point.y+nOffset,
				 point.x-nOffset, point.y-nOffset,
				 point.x-nOffset, point.y-nOffset
				 );
}

BOOL CBilliardDlg::SetList(CList<CPoint,CPoint&>* ptListFrom, CList<CPoint,CPoint&>* ptListTo)
{
	ptListTo->RemoveAll();
	for (int nIndex = 0; nIndex < ptListFrom->GetCount(); nIndex ++) {
		POSITION pos = ptListFrom->FindIndex(nIndex);
		ptListTo->AddTail(ptListFrom->GetAt(pos));
	}
	return TRUE;
}

BOOL CBilliardDlg::GetReflectLine(CPoint ptCenter, CPoint ptCursor, CList<CPoint,CPoint&>*& ptList)
{
	int nReg = IsInRegion(ptCenter, ptCursor);
	// 求两直线的交点，桌布左侧于连线的焦点
	CPoint ptCross1;
	CPoint ptReflect;
	BOOL bRet = FALSE;
	if (nReg == 1) {
		bRet = Intersection(nReg, ptCursor.x, ptCursor.y, ptCenter.x, ptCenter.y, m_nCanvasXPos, m_nCanvasYPos, m_nCanvasXPos, (m_nCanvasYPos + m_nCanvasHeight), &ptCross1, &ptReflect);
	} else if (nReg == 2) {
		bRet = Intersection(nReg, ptCursor.x, ptCursor.y, ptCenter.x, ptCenter.y, m_nCanvasXPos, m_nCanvasYPos, m_nCanvasXPos + m_nCanvasWidth, m_nCanvasYPos, &ptCross1, &ptReflect);
	} else if (nReg == 3) {
		bRet = Intersection(nReg, ptCursor.x, ptCursor.y, ptCenter.x, ptCenter.y, m_nCanvasXPos + m_nCanvasWidth, m_nCanvasYPos, m_nCanvasXPos + m_nCanvasWidth, m_nCanvasYPos + m_nCanvasHeight, &ptCross1, &ptReflect);
	} else if (nReg == 4) {
		bRet = Intersection(nReg, ptCursor.x, ptCursor.y, ptCenter.x, ptCenter.y, m_nCanvasXPos + m_nCanvasWidth, m_nCanvasYPos + m_nCanvasHeight, m_nCanvasXPos, m_nCanvasYPos + m_nCanvasHeight, &ptCross1, &ptReflect);
	}
	if (bRet) {
		ptList->AddTail(ptCross1);
		if (ptList->GetCount() > 2) {
			return TRUE;
		}
		//if (CanReflect(ptCross1)) {
		//	return GetReflectLine(ptCross1, ptReflect, ptList);
		//}
	}
	return bRet;
}

short CBilliardDlg::IsInRegion(CPoint ptStart, CPoint ptEnd)
{
	short sRegion = 1;
	// ptEnd==>ptStart
	// 模拟桌布布局
	//  --------
	// ①-------②-------③
	//||    *    2    *  ||
	//||    1    *    3  ||
	//||    *    4    *  ||
	// ⑥-------⑤-------④
	//  --------
	// 判断ptStart在区域A?B?C?D?
	// 1
	CRgn rgnA;
	CPoint ptVertex1[3];
	ptVertex1[0].x = ptEnd.x;
	ptVertex1[0].y = ptEnd.y;
	ptVertex1[1].x = m_nCanvasXPos;
	ptVertex1[1].y = m_nCanvasYPos;
	ptVertex1[2].x = m_nCanvasXPos;
	ptVertex1[2].y = m_nCanvasYPos + m_nCanvasHeight;

	rgnA.CreatePolygonRgn(ptVertex1, 3, ALTERNATE);
	BOOL bIn = rgnA.PtInRegion(ptStart);
	rgnA.DeleteObject();
	if (bIn) {
		return 1;
	}
	// 2
	CRgn rgnB;
	CPoint ptVertex2[3];
	ptVertex2[0].x = ptEnd.x;
	ptVertex2[0].y = ptEnd.y;
	ptVertex2[1].x = m_nCanvasXPos;
	ptVertex2[1].y = m_nCanvasYPos;
	ptVertex2[2].x = m_nCanvasXPos + m_nCanvasWidth;
	ptVertex2[2].y = m_nCanvasYPos;

	rgnB.CreatePolygonRgn(ptVertex2, 3, ALTERNATE);
	bIn = rgnB.PtInRegion(ptStart);
	rgnB.DeleteObject();
	if (bIn) {
		return 2;
	}
	// 3
	CRgn rgnC;
	CPoint ptVertex3[3];
	ptVertex3[0].x = ptEnd.x;
	ptVertex3[0].y = ptEnd.y;
	ptVertex3[1].x = m_nCanvasXPos + m_nCanvasWidth;
	ptVertex3[1].y = m_nCanvasYPos;
	ptVertex3[2].x = m_nCanvasXPos + m_nCanvasWidth;
	ptVertex3[2].y = m_nCanvasYPos + m_nCanvasHeight;

	rgnC.CreatePolygonRgn(ptVertex3, 3, ALTERNATE);
	bIn = rgnC.PtInRegion(ptStart);
	rgnC.DeleteObject();
	if (bIn) {
		return 3;
	}
	// 4
	CRgn rgnD;
	CPoint ptVertex4[3];
	ptVertex4[0].x = ptEnd.x;
	ptVertex4[0].y = ptEnd.y;
	ptVertex4[1].x = m_nCanvasXPos + m_nCanvasWidth;
	ptVertex4[1].y = m_nCanvasYPos + m_nCanvasHeight;
	ptVertex4[2].x = m_nCanvasXPos;
	ptVertex4[2].y = m_nCanvasYPos + m_nCanvasHeight;

	rgnD.CreatePolygonRgn(ptVertex4, 3, ALTERNATE);
	bIn = rgnD.PtInRegion(ptStart);
	rgnC.DeleteObject();
	if (bIn) {
		return 4;
	}

	return 0;
}

// 求两直线交点
// 直线 1 上的两点：ptCursor(ax1, ay1), ptCenter(ax2, ay2)
// 直线 2 上的两点：(bx1, by1), (bx2, by2)
// 返回值：true: 有交点，保存在 (ix, iy) 中
//    ：false: 两直线平行
BOOL CBilliardDlg::Intersection(int nReg, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, CPoint* ptCross, CPoint* ptReflect)
{
    int d = (ay2-ay1) * (bx2-bx1) - (by2-by1) * (ax2-ax1);
   
    if (d == 0)
        return FALSE; // 两直线平行就退出，避免除数为 0 的情况
   
	ptCross->x = (
     (ax2-ax1)*(bx2-bx1)*(by1-ay1)+(ay2-ay1)*(bx2-bx1)*ax1-(by2-by1)*(ax2-ax1)*bx1
     ) / d;
	ptCross->y = (
     (ay2-ay1)*(by2-by1)*(bx1-ax1)+(ax2-ax1)*(by2-by1)*ay1-(bx2-bx1)*(ay2-ay1)*by1
     ) / -d;

	if (nReg == 1 || nReg == 3) {
		if (ay1 == ay2) {
			// 垂直不再反射
			return FALSE;
		} else  if (ay1 > ay2) {
			ptReflect->x = ax2;
			ptReflect->y = ay2 - 2*abs(ay2 - ptCross->y);
		} else {
			ptReflect->x = ax2;
			ptReflect->y = ay2 + 2*abs(ay2 - ptCross->y);
		}
	} else if (nReg == 2 || nReg == 4) {
		if (ax1 == ax2) {
			// 垂直不再反射
			return FALSE;
		} else  if (ax1 > ax2) {
			ptReflect->x = ax2 - 2*abs(ax2 - ptCross->x);
			ptReflect->y = ay2;
		} else {
			ptReflect->x = ax2 + 2*abs(ax2 - ptCross->x);
			ptReflect->y = ay2;
		}
	} else {
		return FALSE;
	}
    return TRUE;
}

BOOL CBilliardDlg::CanReflect(CPoint pt)
{
	int x = pt.x;
	int y = pt.y;

	int nHarfWidth = int(m_nCanvasWidth/2+0.5);
	if (x >= (m_nCanvasXPos + m_nHoleRadius) && x <= (m_nCanvasXPos + nHarfWidth - m_nHoleRadius)) {
		return TRUE;
	}
	if (x >= (m_nCanvasXPos + nHarfWidth + m_nHoleRadius) && x <= (m_nCanvasXPos + m_nCanvasWidth - m_nHoleRadius)) {
		return TRUE;
	}
	if (y >= (m_nCanvasYPos + m_nHoleRadius) && y <= (m_nCanvasYPos + m_nCanvasHeight - m_nHoleRadius)) {
		return TRUE;
	}

	return TRUE;
}

