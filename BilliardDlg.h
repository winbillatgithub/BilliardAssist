// BilliardDlg.h : header file
//

#if !defined(AFX_BILLIARDDLG_H__C053C1AA_0252_472E_B520_8269C4293CFD__INCLUDED_)
#define AFX_BILLIARDDLG_H__C053C1AA_0252_472E_B520_8269C4293CFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxwin.h"
#include "SkinButton.h"
#include "CaptureEx.h"
#include "PreviewDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CBilliardDlg dialog

class CBilliardDlg : public CDialog
{
private:
// Private variables
	BOOL m_bMore;				// 是否显示参数设定
	int m_bStayOnTop;			// 是否前端显示
	BOOL m_bFirstZoom;			// 第一次显示放大镜，停靠在对话框的右侧
	int  m_nShowCanvas;			// 是否显示模拟画布
	int  m_nShowLine;			// 是否显示瞄准线
	int  m_nShowZoom;			// 是否显示放大镜
	int m_nHotkey;				// 是否启动热键
	int m_nForceRefresh;		// 强制刷新
	HMENU m_hMenu;				// 右键菜单
	int		  m_nTimerCanvas;	// 绘制模拟桌面定时器
	int		  m_nTimerLine;		// 绘制瞄准线定时器
	int       m_nTimerReflect;	// 绘制反射线定时器
	CDC m_dc;					// Device context绘制桌布
	CDC m_dcLine;				// Device context绘制瞄准线
	CDC m_dcReflect;			// Device context绘制反射线
	int m_nGoal;				// 目标袋口，1：左上 2：中上 3：右上 4：左下 5：中下 6：右下
	CPoint m_PointGoal;			// 目标袋口坐标
	CPoint m_PointGoalOld;		// 目标袋口坐标--擦除用
	CPoint m_PointCursor;		// 光标位置
	CPoint m_PointCursorOld;	// 光标位置    --擦除用
	int m_nCanvasWidth;			// 桌布宽度
	int m_nCanvasHeight;		// 桌布高度
	int m_nBallDiameter;			// 台球直径
	float m_nBallRadius;			// 台球半径
	int m_nHoleRadius;			// 袋口半径
	int m_nCanvasXPos;			// 桌布相对于屏幕坐标的横坐标位置
	int m_nCanvasYPos;			// 桌布相对于屏幕坐标的纵坐标位置
	int m_nCanvasWidthOld;		// 桌布宽度--擦除用
	int m_nCanvasHeightOld;		// 桌布高度--擦除用
	float m_nBallRadiusOld;		// 台球半径--擦除用
	int m_nHoleRadiusOld;		// 袋口半径--擦除用
	int m_nCanvasXPosOld;		// 桌布相对于屏幕坐标的横坐标位置--擦除用
	int m_nCanvasYPosOld;		// 桌布相对于屏幕坐标的纵坐标位置--擦除用
	COLORREF m_crLine;			// 瞄准线颜色
	COLORREF m_crCanvasOut;		// 桌布外轮廓颜色
	COLORREF m_crLineCanvasIn;	// 桌布内轮廓颜色
	COLORREF m_crReflect;		// 桌布内轮廓颜色

	CaptureEx	m_CaptureEx;	// 屏幕拷贝对象
	CPreviewDlg m_dlgPreview;	// 预览对话框
	int m_nSize;				// 预览对话框大小
	int m_nZoomValue;			// 预览放大倍数
	CStatic m_picDesk;			// 选中袋口桌面图片
	CPoint  m_ptGoalFrom;		// 中心
	CPoint  m_ptGoalTo;			// 选中袋口

	int m_nHOTKEY_A;			// 热键A
	int m_nHOTKEY_S;			// 热键S
	int m_nHOTKEY_D;			// 热键D
	int m_nHOTKEY_Z;			// 热键Z
	int m_nHOTKEY_X;			// 热键X
	int m_nHOTKEY_C;			// 热键C
	int m_nHOTKEY_LEFT;			// 热键LEFT
	int m_nHOTKEY_RIGHT;		// 热键RIGHT
	int m_nHOTKEY_UP;			// 热键UP
	int m_nHOTKEY_DOWN;			// 热键DOWN
	int m_nHOTKEY_WHITE;		// 热键定位白球
	int m_nHOTKEY_GOAL;			// 热键定位目标球
	int m_nHOTKEY_RESET;		// 热键取消定位
//////////////////////////////////////////////////////////////////////////////////////////
	BOOL m_bGoalBallPointSet;
	BOOL m_bWhiteBallPointSet;
	CPoint m_ptGoalBallCenter;
	CPoint m_ptWhiteBallCenter;
	CPoint m_ptCross;
	CPoint m_ptCrossOld;
	CList<CPoint,CPoint&>* m_pPtList;
	CList<CPoint,CPoint&>* m_pPtListOld;
// Private functions
	void ShowTopWindow();		// 前端显示函数
	void KillOwnTimer(int nTimer = -1);			// 关闭定时器
	BOOL SetGoalPositon();		// 根据瞄准的袋口确定对应坐标
	void DrawCanvas(BOOL bErase);				// 绘制模拟桌布
	void DrawLine(BOOL bErase);	// 绘制袋口到白球之间的瞄准线
	BOOL DrawOddCircle(const CPoint& point, int nOffset); // 绘制直径是奇数的圆
	void SwitchDesk(UINT nResourceID);			// 绘制选中袋口线
	void DrawPreview();			// 绘制图像
	BOOL IsCanvasChanged();		// 判断桌布尺寸是否发生变化
	BOOL IsLineChanged();		// 判断瞄准线尺寸是否发生变化
	void ReadConfig(const CString& pathName);			// 读取配置文件
	void WriteConfig(const CString& pathName);			// 写入配置文件
	void GetExePath(char* pExePath);			// 获得执行路径
	void ChangeZoom();			// 根据放大率修改对应设置
	void ShowPreviewDlg(BOOL bShow);			// 显示/隐藏预览对话框
	BOOL GetGoalPosition(const CPoint &ptFrom, const CPoint &ptTo, CPoint *point);
	void LoadStr(UINT uResourceID, char* szBuffer);
	void MoveCursor(int nDirection);			// 微调光标位置
	void RefreshAll();			// 刷新整个屏幕
	void SetHotKey(BOOL bSet);	// 设定/取消热键
	void AddTrayIcon(DWORD dwMsgType,UINT nIndexOfIcon); //增加托盘图标
	void UpdateMenuItemStatus(UINT nMenuID);
	///////////////////////////////////////////////////////////////////
	void SetWhiteBallPoint();
	void SetGoalBallPoint();
	void ResetReflect();
	BOOL IsReflectChanged(CPoint ptCursor);
	void DrawVirtualCircle(CPoint ptCursor, BOOL bErase);
	void DrawVirtualLine(CPoint ptCursor, BOOL bErase);
	BOOL SetList(CList<CPoint,CPoint&>* ptListFrom, CList<CPoint,CPoint&>* ptListTo);
	BOOL GetReflectLine(CPoint ptCenter, CPoint ptCursor, CList<CPoint,CPoint&>*& ptList);
	short IsInRegion(CPoint ptStart, CPoint ptEnd);
	BOOL Intersection(int nReg, int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2, CPoint* ptCross, CPoint* ptReflect);
	BOOL CanReflect(CPoint pt);
// Construction
public:
	CBilliardDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CBilliardDlg)
	enum { IDD = IDD_BILLIARD_DIALOG };
	CButton m_btnTop;
	CSkinButton		m_btnParam;
	CSkinButton		m_btnCfgDefault;
	CSkinButton		m_btnCfgSave;
	CSkinButton		m_btnCfgLoad;
	CSkinButton		m_btnAdv;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBilliardDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBilliardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedParam();
	afx_msg void OnBnClickedCheckTop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckShowcanvas();
	afx_msg void OnBnClickedCheckShowline();
	afx_msg void OnBnClickedCheckZoom();
	afx_msg void OnDeltaposSpinWidth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHeight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBallRadius(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHoleRadius(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinXpos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinYpos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinZoom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCfgDefault();
	afx_msg void OnBnClickedCfgSave();
	afx_msg void OnBnClickedCfgLoad();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnChangeEditWidth();
	afx_msg void OnEnChangeEditHeight();
	afx_msg void OnEnChangeEditXPos();
	afx_msg void OnEnChangeEditYPos();
	afx_msg void OnEnChangeEditBallRadius();
	afx_msg void OnEnChangeEditHoleRadius();
	afx_msg void OnEnChangeEditZoom();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedAdvance();
	afx_msg void OnBnClickedCheckHotkey();
	afx_msg void OnFileExit();
	afx_msg void OnTrayiconShowwindow();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCheckForceRefresh();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILLIARDDLG_H__C053C1AA_0252_472E_B520_8269C4293CFD__INCLUDED_)
