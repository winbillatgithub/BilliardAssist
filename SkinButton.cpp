/************************************************************************/
/* CSkinButton and CSkinDialog                                          */
/************************************************************************/
/*
/* ����: cnmusic(cnmusic@163.net)
/* �汾: 1.0
/* ����޶�����: 2004-10-2 10:49
/*
/* ˵��: 
		 		
		 ��ť״̬��������֪һ����׼�İ�ť��Ϊ3��״̬���޽��㡢�н��㡢����
				   ����XP�İ�ť����һ�ֻ�����ָ���״̬��

				   �⼸��״̬ϸ����ȥ����Ĭ�ϰ�ť�ͷ�Ĭ�ϰ�ť������1.0���
				   ���״�����˵���Ȳ��ؿ�����ôϸ�ˡ�:)
		 
		 ��ťƤ�������������״̬һ��������ؼ�Ҳ��Ҫ3-4����ͬ��λͼ��Ϊÿ
				   ����ť��Ƥ����һ��λͼ��Ӧһ��״̬��

				   ��Ӧ�ĳ�Ա�����ֱ��ǣ�
						m_nNormalBitmapResID		��׼״̬�µ�λͼ����ԴID(�޽��㡢�������)
						m_nFocusBitmapResID			������뽹���λͼ����ԴID(�������)
						m_nHoverBitmapResID  		���������λͼ����ԴID(��ѡ)		
						m_nPressedBitmapResID		����״̬��λͼ����ԴID
		
		 �꣺SKIN_BUTTON_INIT_MACRO
				 
				 ����ÿ�� CSkinButton ��˵�����������ĸ�ֵ��䶼дһ��Ļ���
				 ʵ����һ�������Ĺ����������������ͨ���������������һ����λ��
				 
				 ����stdafx.h���������壺
					#define SKIN_BUTTON_INIT_MACRO		\
						m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;	\
						m_nFocusBitmapResID=IDB_BITMAPFOCUS;	\
						m_nHoverBitmapResID=IDB_BITMAPFOCUS;	\
						m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;	\
				 
				 ����,���е�CSkinButton��������4��ͼƬ��Ϊ��ť��Ƥ����.
		 
		 ��Ա����: ǰ��ļ�����Դ�ļ��ĳ�Ա��������Ͳ�˵�ˡ�����˵һ˵
				   m_bEnableStretch��

				   Ϊ����Ӧ��ͬ��С�İ�ť�����ǿ�����2�ַ�������Ƥ������ȥ��
				   һ�־������죬��С��ͼƬֱ�ӷ�������һ�־����ظ�������
				   ��ͬһ��ͼ��ȥֱ��������

				   �����Ա�����������������Ÿ��ģ������ΪTRUE����ô����
				   ����ķ�����Ĭ��ֵ������������ظ���ͼ�ķ�����ʵ�֡�

				   ������m_nXPos��m_nYPos��������ȡ��ťͼƬ����Ӧ��ע�⵽�ˣ�
				   �󲿷ֵİ�ť���ǶԳƵġ����Ҷ��ܴ�ŷֳɼ��󲿷֡�

					 1 |    2    | 3 
				    -----------------
					 4 |    5    | 6
					-----------------
					 7 |    8    | 9

				   ��������Ա��������ָ�� CSkinButton Ӧ����ν����Ƥ���п�
				   ����9�����ֵġ�����ֻ��Ҫ������һ������µ���������ˡ�

				   ���������ڲ�ͬ��С�İ�ť��ֻҪ��Ӧ���ظ�2��4��5��6��8������
				   �Ϳ���ʵ����������ͼ�ˡ�

		 CSkinButton ���ڸ���׼�İ�ť��Ƥ����������ͨ�����ַ�����������

		 ��һ�֣�ͨ������CSkinButton.h�ļ�����ǰ��CButtonͳͳ�޸�Ϊ
				 CSkinButton ʵ�ֻ���MFC�Ļ�Ƥ��������

				 ���ַ������ŵ��ǿ�����ͬһ��������ʹ�ö����ͬ�İ�ťƤ����
				 ȱ������鷳�������ֶ�һ����ťһ����ť���滻�����Ҵ��屳��
				 ���ܺͰ�ť�����ںϡ���Ӧ����Ϣ��İ�ťҲ���ܱ��滻��

		 �ڶ��֣�ʹ��CSkinDialog��SubClassDialog�����������ڽ���subclass.
					
				 ���ַ������ŵ��ǿ���ʵ�ְ�����Ϣ�����ڵ����еı�׼��ť��
				 ����������ͬʱ�ṩһ������ı��������ܹ���ͼ�����������
				 �����ںϡ�
				 ȱ�����һ������İ�ťֻ����һ��Ƥ����Ҫ�뻻����һ�׵Ļ�
				 ��Ҫ�ڴ��´���֮ǰ�޸�CSkinDialog��m_bSkinButtonsTemplate
				 �еĶ�Ӧ��������Щ�鷳��

		 �����֣����ʹ�ã�����ʹ����CSkinButton��Dialog������CSkinDialog����
				 Hook������ע�������ע�����

   ע������ڵ���CSkinDialog��ʱ��������õ����ַ������ʵ��,��ô������
			 InitDialog�е���SubClassDialog֮ǰ����CDialog::InitDialog(),����
			 �Զ���İ�ť�����һЩ��ͼ����

			 �ڵ���CSkinDialog���õ�2�ַ���SubClass�������Ҫ�Լ����ƴ���
			 ��ĳһ������������OnPaint��WM_PAINT��Ϣ�н��С���ΪWM_ERASEBKGND
			 ��Ϣ��CSkinDialog"�Ե�"�ˡ�
	
	������:  ��Щ������,�õ������еļ�����
			 
			 + ͨ��SetWindowLong����SubClass��Ϊ�˻�����е���Ϣ

			 + ͨ��SetWindowHook����һ���̵߳�Hook��Ϊ���ǵõ�MessageBox�Ĵ���֪ͨ
			   ��ͨ��CBT���͵�Hookʵ�֣�

			 + ͨ����ȡIcon���͵�Static���е�Icon��Ȼ�����µı����ϣ�����ڰ�
			   ���Static�����ͻ���Bitmap����͸����Icon�ͽ��䱳���������ںϡ�
			   �������ҵ�N��ı䱳��ɫ�Ĵ��룬���ֻ�ܰ�Icon�ı���ɫ����һ�ֵ�һ����ɫ��
			   �޷�ʵ�ֺͽ��䱳�����ںϡ�����ֻ����������������DIY����....
  
	������	 �ⲿ�ִ���ֻ������ΪѧϰOWNERDRAW��һ�����ֵĽ�������Ե���
			 һ���в�������÷��������÷�����ӭ����ָ��������Ȼ����ṩ��
			 ��ȻҲ�����ʹ���ⲿ�ִ�����ɵ��κ���ʧ����

			 ���������κ���ҵ�����ҵ�������ʹ���߲��ִ��롣���ת�أ��뱣��
			 �ⲿ�����������֡�

/************************************************************************

    ������ʷ��
			  2004-10-2
					+ Version 1.0 ������һ�ж����µ�....����BUG....
			  2004-10-3
					+ Version 1.1 ����

					  �����˵���OldWndProc��BUG
					  �����˵���Get/SetWindowLongPtr�Ĳ�����ĵط�.
					  ������WM_DRAWITEM���÷�����ĵط�
					  �������ڵ��ù��ô򿪶Ի���ʱ��ɵĶ�ջ�������
					  ��CSkinDialog��������m_dwFlags����,��������һЩ���ӵ�ѡ��
					  �������µ�ѡ�� - SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH ǿ�Ʒ��ر���ˢ��
					  ������ȫ�ֵ�CSkinDialogָ��,�����û�����ͨ���̳�CSkinDialogʵ���Լ��ı������ƺ���
					  �޸���CSkinDialog.SubClassDialog����,�����ظ�����,�������Դ�������ҳ�еĿؼ�
					  �޸���WM_ERASEBKGND�������,������󻯰�ť�Ĵ��岻�ٽ��д���,������BCG�н��ж���Ļ滭����
					  
/************************************************************************/
// SkinButton.cpp : implementation file
//

#include "stdafx.h"
#include "SkinButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

LRESULT CALLBACK SkinButtonSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WNDPROC		OldWndProc=NULL;
	CSkinButton	*pSkinButton=NULL;

	// ���Ȼ�ȡ��ǰ�����ԭʼ��WndProc�ĵ�ַ��
	OldWndProc=(WNDPROC)GetProp(hwnd,"OldWndProc");
	ASSERT(OldWndProc != NULL);

	// Ȼ��������ؼ���SkinButton����
	pSkinButton=(CSkinButton*)GetProp(hwnd,"SkinButtonObj");
	ASSERT(pSkinButton != NULL);

	// Ȼ��ʼ������Ϣ��
	
	if (uMsg == WM_DRAWITEM)
	{
		pSkinButton->DrawItem((LPDRAWITEMSTRUCT)lParam);
		return TRUE;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		// NOTE: ������Щ��Ϣ��ʱ�򣬱����ر�ע��hDC��ѡ�ã���������д�����HDC��
		// ��ô�ͱ����ò����еġ�������ʹ��GetDC���صġ�����ͻ���ֻ滭���������
		TRACE("SkinButton receive WM_ERASEBKGND message.\n");
		CDC			DC;
		DC.Attach((HDC)wParam);
		pSkinButton->OnEraseBkgnd(&DC);
		DC.Detach();	// �������Ǵ�����DC�����ǲ�����������
		return 1;
	}
	else if (uMsg == WM_PAINT)
	{
		TRACE("SkinButton receive WM_PAINT message.\n");
		pSkinButton->OnPaint();
	}
	else if (uMsg == WM_DESTROY)
	{
		// ����ע�������ǰ����������ӵ�Propȥ����
		RemoveProp(hwnd,"OldWndProc");
		RemoveProp(hwnd,"SkinButtonObj");
		
		// ��ԭ��ǰ��WNDPROC
		SetWindowLong(hwnd,GWL_WNDPROC,(LONG)OldWndProc);

		// ɾ��CSkinButton����
		pSkinButton->m_hWnd=NULL;
		delete pSkinButton;
		
		return CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		CPoint			Point;
		Point.x=GET_X_LPARAM(lParam);
		Point.y=GET_Y_LPARAM(lParam);

		pSkinButton->OnMouseMove((UINT)wParam,Point);
	}
	else if (uMsg == WM_MOUSEHOVER)
	{
		pSkinButton->OnMouseHover(wParam,lParam);
	}
	else if (uMsg == WM_MOUSELEAVE)
	{
		pSkinButton->OnMouseLeave(wParam,lParam);
	}

	return CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);
}




/////////////////////////////////////////////////////////////////////////////
// CSkinButton

CSkinButton::CSkinButton()
{
	m_nXPos=9;
	m_nYPos=9;

	m_nNormalBitmapResID=0;
	m_nFocusBitmapResID=0;
	m_nHoverBitmapResID=0;
	m_nPressedBitmapResID=0;

	m_bOverControl=FALSE;
	m_bSelected=FALSE;
	m_bTracking=FALSE;

	m_bEnableStretch=TRUE;

#ifndef SKIN_BUTTON_INIT_MACRO
#error SKIN_BUTTON_INIT_MACRO not defined. CSkinButton can not work correctly without a SKIN_BUTTON_INIT_MACRO macro. 
#error see the document at the top of SkinButton.cpp for more information.
#endif
	
	SKIN_BUTTON_INIT_MACRO

}

CSkinButton::~CSkinButton()
{
}


BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	//{{AFX_MSG_MAP(CSkinButton)
	//ON_WM_ERASEBKGND()								// ��ͨ��MFC����ʱ,���ǲ����Լ�������������Ϣ,MFC
	//ON_WM_PAINT()										// ������Ǵ���õ�.������һ��,�������ѭ����.
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinButton message handlers
void CSkinButton::DrawContent(CMemDC &pDC,UINT state,CRect rect,BOOL Focus,CString &strText)
{
	CBitmap			MyBitMap;
	CDC				MyBitmapDC;

	MyBitmapDC.CreateCompatibleDC(NULL);

	if (Focus)
	{
		if (state & ODS_SELECTED)
		{
			MyBitMap.LoadBitmap(m_nPressedBitmapResID);
		}
		else
		{
			MyBitMap.LoadBitmap(m_nFocusBitmapResID);
		}
	}
	else if ((!m_bOverControl) || (m_nHoverBitmapResID == 0))
	{
		MyBitMap.LoadBitmap(m_nNormalBitmapResID);
	}
	else if (m_bOverControl)
	{
		MyBitMap.LoadBitmap(m_nHoverBitmapResID);
	}
	
	CBitmap* pOldBitmap=NULL;
	VERIFY((pOldBitmap=MyBitmapDC.SelectObject(&MyBitMap)) != NULL);


	// �ⲿ�ִ����ͼƬ�����и���Ƶ�Ŀ������
	CSize    sizeBitMap;
	BITMAP	 BitMapStruct={NULL};
	MyBitMap.GetBitmap(&BitMapStruct);
	sizeBitMap.cx=BitMapStruct.bmWidth;
	sizeBitMap.cy=BitMapStruct.bmHeight;


	// �����ǲ�������
	PAINTINFO		PaintInfo[5]={NULL};

	// �ϱߵĲ����
	PaintInfo[0].sizeBlock.cx=sizeBitMap.cx-m_nXPos*2;
	PaintInfo[0].sizeBlock.cy=m_nYPos;
	PaintInfo[0].rectBlockSrc.left=m_nXPos;
	PaintInfo[0].rectBlockSrc.top=0;
	PaintInfo[0].rectBlockSrc.right=sizeBitMap.cx-m_nXPos;
	PaintInfo[0].rectBlockSrc.bottom=m_nYPos;
	PaintInfo[0].rectBlockDest.left=m_nXPos;
	PaintInfo[0].rectBlockDest.top=0;
	PaintInfo[0].rectBlockDest.right=rect.right-m_nXPos;
	PaintInfo[0].rectBlockDest.bottom=m_nYPos;


	// �±ߵ���
	PaintInfo[1].sizeBlock.cx=sizeBitMap.cx-m_nXPos*2;
	PaintInfo[1].sizeBlock.cy=m_nYPos;
	PaintInfo[1].rectBlockSrc.left=m_nXPos;
	PaintInfo[1].rectBlockSrc.top=sizeBitMap.cy-m_nYPos;
	PaintInfo[1].rectBlockSrc.right=sizeBitMap.cx-m_nXPos;
	PaintInfo[1].rectBlockSrc.bottom=sizeBitMap.cy;
	PaintInfo[1].rectBlockDest.left=m_nXPos;
	PaintInfo[1].rectBlockDest.top=rect.bottom-m_nYPos;
	PaintInfo[1].rectBlockDest.right=rect.right-m_nXPos;
	PaintInfo[1].rectBlockDest.bottom=rect.bottom;

	// ��ߵ���
	PaintInfo[2].sizeBlock.cx=m_nXPos;
	PaintInfo[2].sizeBlock.cy=sizeBitMap.cy-m_nYPos*2;
	PaintInfo[2].rectBlockSrc.left=0;
	PaintInfo[2].rectBlockSrc.top=m_nYPos;
	PaintInfo[2].rectBlockSrc.right=m_nXPos;
	PaintInfo[2].rectBlockSrc.bottom=sizeBitMap.cy-m_nYPos;
	PaintInfo[2].rectBlockDest.left=0;
	PaintInfo[2].rectBlockDest.top=m_nYPos;
	PaintInfo[2].rectBlockDest.right=m_nXPos;
	PaintInfo[2].rectBlockDest.bottom=rect.bottom-m_nYPos;

	// �ұߵ���
	PaintInfo[3].sizeBlock.cx=m_nXPos;
	PaintInfo[3].sizeBlock.cy=sizeBitMap.cy-m_nYPos*2;
	PaintInfo[3].rectBlockSrc.left=sizeBitMap.cx-m_nXPos;
	PaintInfo[3].rectBlockSrc.top=m_nYPos;
	PaintInfo[3].rectBlockSrc.right=sizeBitMap.cx;
	PaintInfo[3].rectBlockSrc.bottom=sizeBitMap.cy-m_nYPos;
	PaintInfo[3].rectBlockDest.left=rect.right-m_nXPos;
	PaintInfo[3].rectBlockDest.top=m_nYPos;
	PaintInfo[3].rectBlockDest.right=rect.right;
	PaintInfo[3].rectBlockDest.bottom=rect.bottom-m_nYPos;

	// �м�Ĳ��֡�
	PaintInfo[4].sizeBlock.cx=sizeBitMap.cx-m_nXPos*2;
	PaintInfo[4].sizeBlock.cy=sizeBitMap.cy-m_nYPos*2;
	PaintInfo[4].rectBlockSrc.left=m_nXPos;
	PaintInfo[4].rectBlockSrc.top=m_nYPos;
	PaintInfo[4].rectBlockSrc.right=sizeBitMap.cx-m_nXPos;
	PaintInfo[4].rectBlockSrc.bottom=sizeBitMap.cy-m_nYPos;
	PaintInfo[4].rectBlockDest.left=m_nXPos;
	PaintInfo[4].rectBlockDest.top=m_nYPos;
	PaintInfo[4].rectBlockDest.right=rect.right-m_nXPos;
	PaintInfo[4].rectBlockDest.bottom=rect.bottom-m_nYPos;


	for (int i=0;i<5;i++)
	{
		PAINTINFO		OnePaintInfo=PaintInfo[i];
		
		if (!m_bEnableStretch)
		{
			if ((i == 0) || (i == 1))
			{
				int			xPos=OnePaintInfo.rectBlockDest.left;
				while (xPos <= OnePaintInfo.rectBlockDest.right)
				{
					pDC->BitBlt(xPos,OnePaintInfo.rectBlockDest.top,
								OnePaintInfo.sizeBlock.cx,
								OnePaintInfo.sizeBlock.cy,
								&MyBitmapDC,OnePaintInfo.rectBlockSrc.left,OnePaintInfo.rectBlockSrc.top,
								SRCCOPY);
					xPos+=OnePaintInfo.sizeBlock.cx;
				}
			}
			else if ((i == 2) || (i == 3))
			{
				int			yPos=OnePaintInfo.rectBlockDest.top;
				while (yPos <= OnePaintInfo.rectBlockDest.bottom)
				{
					pDC->BitBlt(OnePaintInfo.rectBlockDest.left,yPos,
								OnePaintInfo.sizeBlock.cx,
								OnePaintInfo.sizeBlock.cy,
								&MyBitmapDC,OnePaintInfo.rectBlockSrc.left,OnePaintInfo.rectBlockSrc.top,
								SRCCOPY);
					yPos+=OnePaintInfo.sizeBlock.cy;
				}
			}
			else
			{
				pDC->StretchBlt(OnePaintInfo.rectBlockDest.left,OnePaintInfo.rectBlockDest.top,
						OnePaintInfo.rectBlockDest.right-OnePaintInfo.rectBlockDest.left,
						OnePaintInfo.rectBlockDest.bottom-OnePaintInfo.rectBlockDest.top,
					    &MyBitmapDC,OnePaintInfo.rectBlockSrc.left,OnePaintInfo.rectBlockSrc.top,
						OnePaintInfo.sizeBlock.cx,OnePaintInfo.sizeBlock.cy,
					    SRCCOPY);
			}
		}
		else 
		{
			pDC->StretchBlt(OnePaintInfo.rectBlockDest.left,OnePaintInfo.rectBlockDest.top,
						OnePaintInfo.rectBlockDest.right-OnePaintInfo.rectBlockDest.left,
						OnePaintInfo.rectBlockDest.bottom-OnePaintInfo.rectBlockDest.top,
					    &MyBitmapDC,OnePaintInfo.rectBlockSrc.left,OnePaintInfo.rectBlockSrc.top,
						OnePaintInfo.sizeBlock.cx,OnePaintInfo.sizeBlock.cy,
					    SRCCOPY);
		}
	}


	// ���������Ͻǡ�
	pDC->BitBlt(0,0,m_nXPos,m_nYPos,&MyBitmapDC,0,0,SRCCOPY);
	
	// Ȼ�������Ͻ�
	pDC->BitBlt(rect.right-m_nXPos,0,m_nXPos,m_nYPos,&MyBitmapDC,sizeBitMap.cx-m_nXPos,0,SRCCOPY);

	// ���½�
	pDC->BitBlt(0,rect.bottom-m_nYPos,m_nXPos,m_nYPos,&MyBitmapDC,0,sizeBitMap.cy-m_nYPos,SRCCOPY);
	
	// ���½�
	pDC->BitBlt(rect.right-m_nXPos,rect.bottom-m_nYPos,m_nXPos,m_nYPos,&MyBitmapDC,sizeBitMap.cx-m_nXPos,sizeBitMap.cy-m_nYPos,SRCCOPY);

	MyBitmapDC.SelectObject(pOldBitmap);

	// ��ʾ����
	CFont		Font;
	Font.Attach((HFONT)::SendMessage(m_hWnd, WM_GETFONT, 0, 0));
	CFont *oldFont=(CFont*)pDC->SelectObject(&Font);
    if (strText != "")
    {
        CSize Extent = pDC->GetTextExtent(strText);
        CPoint pt( rect.CenterPoint().x - Extent.cx/2, 
			rect.CenterPoint().y - Extent.cy/2 );
		
        if (state & ODS_SELECTED) 
        {
			pt.Offset(1,1);
		}
        int nMode = pDC->SetBkMode(TRANSPARENT);
		
        if (state & ODS_DISABLED)
        {
			pDC->DrawState(pt, Extent, strText/*strCaption*/, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		}
        else
		{
			pDC->DrawState(pt, Extent, strText/*strCaption*/, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		}
        pDC->SetBkMode(nMode);
    }
	pDC->SelectObject(oldFont);
	Font.Detach();
}

void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(m_nNormalBitmapResID != 0);
	ASSERT(m_nFocusBitmapResID != 0);
	ASSERT(m_nPressedBitmapResID != 0);

	// TODO: Add your code to draw the specified item
	CDC*		ppDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
    CMemDC		pDC(ppDC);
	CRect		rect = lpDrawItemStruct->rcItem;
    UINT		state = lpDrawItemStruct->itemState;
	CString		strText;
	TCHAR		szBuffer[1024]={NULL};
	
	::GetWindowText(lpDrawItemStruct->hwndItem,szBuffer,1024);
	strText=szBuffer;


	if(state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bSelected = FALSE;
		m_bFocus = FALSE;
	}

	DrawContent(pDC,state,rect,m_bFocus,strText);

	return;
	
}

void CSkinButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW);
	SetProp(m_hWnd,"SkinButtonHandled",(HANDLE)1);
	
	CButton::PreSubclassWindow();
}

void CSkinButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);		
	}	
	CButton::OnMouseMove(nFlags, point);
	
}

LRESULT CSkinButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	wparam;lparam;
	m_bOverControl=TRUE;
	Invalidate();
	return 1;
}

LRESULT CSkinButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	wparam;lparam;
	m_bTracking = FALSE;
	m_bOverControl = FALSE;
	Invalidate(FALSE);
	return 0;
}

BOOL CSkinButton::SubClassWindow(HWND hWnd)
{
	// ���ȿ������hWnd�ǲ�����ǰ�Ѿ���SubClass���ˡ�
	if (GetProp(hWnd,"SkinButtonObj") == NULL)
	{
		// ����һ���µ�CSkinButton����
		CSkinButton		*pNewSkinButton=new CSkinButton;
		pNewSkinButton->m_hWnd=hWnd;						// �ƹ�Attach�ļ�⡣�������һ���Ѿ�����CButton���Ƶİ�ť�����
															// ASSERT�����.
		
		// �������ԡ�
		pNewSkinButton->m_bEnableStretch=m_bEnableStretch;
		pNewSkinButton->m_nFocusBitmapResID=m_nFocusBitmapResID;
		pNewSkinButton->m_nHoverBitmapResID=m_nHoverBitmapResID;
		pNewSkinButton->m_nNormalBitmapResID=m_nNormalBitmapResID;
		pNewSkinButton->m_nPressedBitmapResID=m_nPressedBitmapResID;
		pNewSkinButton->m_nXPos=m_nXPos;
		pNewSkinButton->m_nYPos=m_nYPos;

		SetProp(hWnd,"SkinButtonObj",(HANDLE)pNewSkinButton);

		// Ȼ����WNDPROC;
		WNDPROC   OldProc=(WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
		SetProp(hWnd,"OldWndProc",OldProc);

		SetWindowLong(hWnd,GWL_WNDPROC,(LONG)SkinButtonSubclassProc);
		
		return TRUE;
	}

	return FALSE;
}


BOOL CSkinButton::OnEraseBkgnd(CDC* pDC) 
{
	// �����Լ����ư�ť״̬��
	// ���ݵ�ǰ��ť����Ϣ��

	// TODO: Add your code to draw the specified item
    CRect		rect;
    GetClientRect(rect);
	
	CMemDC		DC(pDC,&rect);					// ���ڴ��ݽ�����pDC��һ�����������ť��DC��
												// ���Ի滭����������ֶ�ָ����
												// pDC->GetClipBox != GetClientRect
	UINT		state = GetState();
	CString		strText;
	TCHAR		szBuffer[1024]={NULL};
	
	::GetWindowText(m_hWnd,szBuffer,1024);
	strText=szBuffer;

	DrawContent(DC,state,rect,m_bFocus,strText);
	
	return TRUE;//CButton::OnEraseBkgnd(pDC);
}

void CSkinButton::OnPaint() 
{
	CDC			*pDc=GetDC(); // device context for painting
	CRect		rect;
	GetClientRect(rect);

    CMemDC		DC(pDc,&rect);
	
    UINT		state = GetState();
	CString		strText;
	TCHAR		szBuffer[1024]={NULL};
	
	::GetWindowText(m_hWnd,szBuffer,1024);
	strText=szBuffer;

	DrawContent(DC,state,rect,m_bFocus,strText);	
}
