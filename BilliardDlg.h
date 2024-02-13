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
	BOOL m_bMore;				// �Ƿ���ʾ�����趨
	int m_bStayOnTop;			// �Ƿ�ǰ����ʾ
	BOOL m_bFirstZoom;			// ��һ����ʾ�Ŵ󾵣�ͣ���ڶԻ�����Ҳ�
	int  m_nShowCanvas;			// �Ƿ���ʾģ�⻭��
	int  m_nShowLine;			// �Ƿ���ʾ��׼��
	int  m_nShowZoom;			// �Ƿ���ʾ�Ŵ�
	int m_nHotkey;				// �Ƿ������ȼ�
	int m_nForceRefresh;		// ǿ��ˢ��
	HMENU m_hMenu;				// �Ҽ��˵�
	int		  m_nTimerCanvas;	// ����ģ�����涨ʱ��
	int		  m_nTimerLine;		// ������׼�߶�ʱ��
	int       m_nTimerReflect;	// ���Ʒ����߶�ʱ��
	CDC m_dc;					// Device context��������
	CDC m_dcLine;				// Device context������׼��
	CDC m_dcReflect;			// Device context���Ʒ�����
	int m_nGoal;				// Ŀ����ڣ�1������ 2������ 3������ 4������ 5������ 6������
	CPoint m_PointGoal;			// Ŀ���������
	CPoint m_PointGoalOld;		// Ŀ���������--������
	CPoint m_PointCursor;		// ���λ��
	CPoint m_PointCursorOld;	// ���λ��    --������
	int m_nCanvasWidth;			// �������
	int m_nCanvasHeight;		// �����߶�
	int m_nBallDiameter;			// ̨��ֱ��
	float m_nBallRadius;			// ̨��뾶
	int m_nHoleRadius;			// ���ڰ뾶
	int m_nCanvasXPos;			// �����������Ļ����ĺ�����λ��
	int m_nCanvasYPos;			// �����������Ļ�����������λ��
	int m_nCanvasWidthOld;		// �������--������
	int m_nCanvasHeightOld;		// �����߶�--������
	float m_nBallRadiusOld;		// ̨��뾶--������
	int m_nHoleRadiusOld;		// ���ڰ뾶--������
	int m_nCanvasXPosOld;		// �����������Ļ����ĺ�����λ��--������
	int m_nCanvasYPosOld;		// �����������Ļ�����������λ��--������
	COLORREF m_crLine;			// ��׼����ɫ
	COLORREF m_crCanvasOut;		// ������������ɫ
	COLORREF m_crLineCanvasIn;	// ������������ɫ
	COLORREF m_crReflect;		// ������������ɫ

	CaptureEx	m_CaptureEx;	// ��Ļ��������
	CPreviewDlg m_dlgPreview;	// Ԥ���Ի���
	int m_nSize;				// Ԥ���Ի����С
	int m_nZoomValue;			// Ԥ���Ŵ���
	CStatic m_picDesk;			// ѡ�д�������ͼƬ
	CPoint  m_ptGoalFrom;		// ����
	CPoint  m_ptGoalTo;			// ѡ�д���

	int m_nHOTKEY_A;			// �ȼ�A
	int m_nHOTKEY_S;			// �ȼ�S
	int m_nHOTKEY_D;			// �ȼ�D
	int m_nHOTKEY_Z;			// �ȼ�Z
	int m_nHOTKEY_X;			// �ȼ�X
	int m_nHOTKEY_C;			// �ȼ�C
	int m_nHOTKEY_LEFT;			// �ȼ�LEFT
	int m_nHOTKEY_RIGHT;		// �ȼ�RIGHT
	int m_nHOTKEY_UP;			// �ȼ�UP
	int m_nHOTKEY_DOWN;			// �ȼ�DOWN
	int m_nHOTKEY_WHITE;		// �ȼ���λ����
	int m_nHOTKEY_GOAL;			// �ȼ���λĿ����
	int m_nHOTKEY_RESET;		// �ȼ�ȡ����λ
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
	void ShowTopWindow();		// ǰ����ʾ����
	void KillOwnTimer(int nTimer = -1);			// �رն�ʱ��
	BOOL SetGoalPositon();		// ������׼�Ĵ���ȷ����Ӧ����
	void DrawCanvas(BOOL bErase);				// ����ģ������
	void DrawLine(BOOL bErase);	// ���ƴ��ڵ�����֮�����׼��
	BOOL DrawOddCircle(const CPoint& point, int nOffset); // ����ֱ����������Բ
	void SwitchDesk(UINT nResourceID);			// ����ѡ�д�����
	void DrawPreview();			// ����ͼ��
	BOOL IsCanvasChanged();		// �ж������ߴ��Ƿ����仯
	BOOL IsLineChanged();		// �ж���׼�߳ߴ��Ƿ����仯
	void ReadConfig(const CString& pathName);			// ��ȡ�����ļ�
	void WriteConfig(const CString& pathName);			// д�������ļ�
	void GetExePath(char* pExePath);			// ���ִ��·��
	void ChangeZoom();			// ���ݷŴ����޸Ķ�Ӧ����
	void ShowPreviewDlg(BOOL bShow);			// ��ʾ/����Ԥ���Ի���
	BOOL GetGoalPosition(const CPoint &ptFrom, const CPoint &ptTo, CPoint *point);
	void LoadStr(UINT uResourceID, char* szBuffer);
	void MoveCursor(int nDirection);			// ΢�����λ��
	void RefreshAll();			// ˢ��������Ļ
	void SetHotKey(BOOL bSet);	// �趨/ȡ���ȼ�
	void AddTrayIcon(DWORD dwMsgType,UINT nIndexOfIcon); //��������ͼ��
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
