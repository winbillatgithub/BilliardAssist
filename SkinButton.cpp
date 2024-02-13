/************************************************************************/
/* CSkinButton and CSkinDialog                                          */
/************************************************************************/
/*
/* 作者: cnmusic(cnmusic@163.net)
/* 版本: 1.0
/* 最后修订日期: 2004-10-2 10:49
/*
/* 说明: 
		 		
		 按钮状态：众所周知一个标准的按钮分为3种状态，无焦点、有焦点、按下
				   对于XP的按钮还有一种获得鼠标指针的状态。

				   这几种状态细分下去还有默认按钮和非默认按钮。对于1.0版的
				   这套代码来说就先不必考虑那么细了。:)
		 
		 按钮皮肤：就像上面的状态一样，这个控件也需要3-4个不同的位图作为每
				   个按钮的皮肤。一个位图对应一个状态。

				   对应的成员变量分别是：
						m_nNormalBitmapResID		标准状态下的位图的资源ID(无焦点、无鼠标光标)
						m_nFocusBitmapResID			获得输入焦点的位图的资源ID(无鼠标光标)
						m_nHoverBitmapResID  		获得鼠标光标的位图的资源ID(可选)		
						m_nPressedBitmapResID		按下状态的位图的资源ID
		
		 宏：SKIN_BUTTON_INIT_MACRO
				 
				 对于每个 CSkinButton 来说，如果把上面的赋值语句都写一遍的话，
				 实在是一个超烦的工作。所以这里可以通过定义这个宏做到一步到位。
				 
				 如在stdafx.h中这样定义：
					#define SKIN_BUTTON_INIT_MACRO		\
						m_nNormalBitmapResID=IDB_BITMAPNOFOCUS;	\
						m_nFocusBitmapResID=IDB_BITMAPFOCUS;	\
						m_nHoverBitmapResID=IDB_BITMAPFOCUS;	\
						m_nPressedBitmapResID=IDB_BITMAPFOCUSSELECTED;	\
				 
				 这样,所有的CSkinButton都会用这4个图片作为按钮的皮肤了.
		 
		 成员变量: 前面的几个资源文件的成员变量这里就不说了。这里说一说
				   m_bEnableStretch。

				   为了适应不同大小的按钮，我们可以用2种方法来将皮肤贴上去。
				   一种就是拉伸，将小的图片直接方法。另一种就是重复，反复
				   贴同一块图上去直道充满。

				   这个成员变量就是用来控制着个的，如果设为TRUE，那么采用
				   拉伸的方法（默认值），否则采用重复贴图的方法来实现。

				   下面是m_nXPos和m_nYPos。经常截取按钮图片的人应该注意到了，
				   大部分的按钮都是对称的。而且都能大概分成几大部分。

					 1 |    2    | 3 
				    -----------------
					 4 |    5    | 6
					-----------------
					 7 |    8    | 9

				   这两个成员变量就是指导 CSkinButton 应该如何将这个皮肤切开
				   成这9个部分的。这里只需要给出第一块的右下的坐标就行了。

				   这样，对于不同大小的按钮，只要相应的重复2、4、5、6、8的内容
				   就可以实现完整的贴图了。

		 CSkinButton 用于给标准的按钮换皮肤。您可以通过两种方法调用它。

		 第一种：通过引用CSkinButton.h文件后将以前的CButton统统修改为
				 CSkinButton 实现基于MFC的换皮肤工作。

				 这种方法的优点是可以在同一个窗体中使用多个不同的按钮皮肤，
				 缺点就是麻烦，必须手动一个按钮一个按钮的替换。而且窗体背景
				 不能和按钮进行融合。相应的消息框的按钮也不能被替换。

		 第二种：使用CSkinDialog的SubClassDialog方法对主窗口进行subclass.
					
				 这种方法的优点是可以实现包括消息框在内的所有的标准按钮的
				 换肤工作。同时提供一个渐变的背景，并能够和图标进行完整的
				 背景融合。
				 缺点就是一个窗体的按钮只能用一套皮肤。要想换另外一套的话
				 需要在打开新窗体之前修改CSkinDialog的m_bSkinButtonsTemplate
				 中的对应参数，有些麻烦。

		 第三种：混合使用，可以使用了CSkinButton的Dialog中再用CSkinDialog进行
				 Hook。不过注意下面的注意事项。

   注意事项：在调用CSkinDialog的时候，如果采用第三种方法混合实现,那么必须在
			 InitDialog中调用SubClassDialog之前调用CDialog::InitDialog(),否则
			 自定义的按钮会出现一些绘图错误。

			 在调用CSkinDialog采用第2种方法SubClass后，如果需要自己绘制窗体
			 的某一部分区域，请在OnPaint或WM_PAINT消息中进行。因为WM_ERASEBKGND
			 消息被CSkinDialog"吃掉"了。
	
	技术点:  这些代码中,用到了下列的技术。
			 
			 + 通过SetWindowLong进行SubClass，为了获得所有的消息

			 + 通过SetWindowHook进行一个线程的Hook，为的是得到MessageBox的创建通知
			   （通过CBT类型的Hook实现）

			 + 通过获取Icon类型的Static当中的Icon，然后画在新的背景上，最后在把
			   这个Static的类型换成Bitmap做到透明的Icon和渐变背景的真正融合。
			   在网上找到N多改变背景色的代码，最多只能把Icon的背景色换成一种单一的颜色。
			   无法实现和渐变背景的融合。于是只好自立更生，发扬DIY精神....
  
	声明：	 这部分代码只是我作为学习OWNERDRAW的一个练手的结果。所以当中
			 一定有不合理的用法或错误的用法（欢迎来信指正）。既然免费提供，
			 当然也不会对使用这部分代码造成的任何损失负责。

			 您可以在任何商业或非商业的软件中使用者部分代码。如果转载，请保留
			 这部分声明的文字。

/************************************************************************

    更新历史：
			  2004-10-2
					+ Version 1.0 发布，一切都是新的....包括BUG....
			  2004-10-3
					+ Version 1.1 发布

					  修正了调用OldWndProc的BUG
					  修正了调用Get/SetWindowLongPtr的不规则的地方.
					  修正了WM_DRAWITEM的用法错误的地方
					  修正了在调用公用打开对话框时造成的堆栈溢出错误
					  在CSkinDialog中增加了m_dwFlags属性,用来设置一些附加的选项
					  增加了新的选项 - SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH 强制返回背景刷子
					  增加了全局的CSkinDialog指针,这样用户可以通过继承CSkinDialog实现自己的背景绘制函数
					  修改了CSkinDialog.SubClassDialog函数,允许重复调用,这样可以处理属性页中的控件
					  修改了WM_ERASEBKGND处理代码,对有最大化按钮的窗体不再进行处理,避免在BCG中进行多余的绘画操作
					  
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

	// 首先获取以前保存的原始的WndProc的地址。
	OldWndProc=(WNDPROC)GetProp(hwnd,"OldWndProc");
	ASSERT(OldWndProc != NULL);

	// 然后是这个控件的SkinButton对象。
	pSkinButton=(CSkinButton*)GetProp(hwnd,"SkinButtonObj");
	ASSERT(pSkinButton != NULL);

	// 然后开始处理消息。
	
	if (uMsg == WM_DRAWITEM)
	{
		pSkinButton->DrawItem((LPDRAWITEMSTRUCT)lParam);
		return TRUE;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		// NOTE: 处理这些消息的时候，必须特别注意hDC的选用，如果参数中传递了HDC，
		// 那么就必须用参数中的。不能再使用GetDC返回的。否则就会出现绘画错误的现象。
		TRACE("SkinButton receive WM_ERASEBKGND message.\n");
		CDC			DC;
		DC.Attach((HDC)wParam);
		pSkinButton->OnEraseBkgnd(&DC);
		DC.Detach();	// 不是我们创建的DC，我们不能销毁它。
		return 1;
	}
	else if (uMsg == WM_PAINT)
	{
		TRACE("SkinButton receive WM_PAINT message.\n");
		pSkinButton->OnPaint();
	}
	else if (uMsg == WM_DESTROY)
	{
		// 窗体注销，我们把我们所增加的Prop去掉。
		RemoveProp(hwnd,"OldWndProc");
		RemoveProp(hwnd,"SkinButtonObj");
		
		// 还原以前的WNDPROC
		SetWindowLong(hwnd,GWL_WNDPROC,(LONG)OldWndProc);

		// 删除CSkinButton对象。
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
	//ON_WM_ERASEBKGND()								// 在通过MFC调用时,我们不用自己处理这两个消息,MFC
	//ON_WM_PAINT()										// 会给我们处理好的.如果多次一举,会造成死循环的.
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


	// 这部分代码把图片进行切割后复制到目标区域。
	CSize    sizeBitMap;
	BITMAP	 BitMapStruct={NULL};
	MyBitMap.GetBitmap(&BitMapStruct);
	sizeBitMap.cx=BitMapStruct.bmWidth;
	sizeBitMap.cy=BitMapStruct.bmHeight;


	// 下面是侧面条。
	PAINTINFO		PaintInfo[5]={NULL};

	// 上边的侧边条
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


	// 下边的条
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

	// 左边的条
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

	// 右边的条
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

	// 中间的部分。
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


	// 首先是左上角。
	pDC->BitBlt(0,0,m_nXPos,m_nYPos,&MyBitmapDC,0,0,SRCCOPY);
	
	// 然后是右上角
	pDC->BitBlt(rect.right-m_nXPos,0,m_nXPos,m_nYPos,&MyBitmapDC,sizeBitMap.cx-m_nXPos,0,SRCCOPY);

	// 左下角
	pDC->BitBlt(0,rect.bottom-m_nYPos,m_nXPos,m_nYPos,&MyBitmapDC,0,sizeBitMap.cy-m_nYPos,SRCCOPY);
	
	// 右下角
	pDC->BitBlt(rect.right-m_nXPos,rect.bottom-m_nYPos,m_nXPos,m_nYPos,&MyBitmapDC,sizeBitMap.cx-m_nXPos,sizeBitMap.cy-m_nYPos,SRCCOPY);

	MyBitmapDC.SelectObject(pOldBitmap);

	// 显示标题
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
	// 首先看看这个hWnd是不是以前已经被SubClass过了。
	if (GetProp(hWnd,"SkinButtonObj") == NULL)
	{
		// 生成一个新的CSkinButton对象。
		CSkinButton		*pNewSkinButton=new CSkinButton;
		pNewSkinButton->m_hWnd=hWnd;						// 绕过Attach的检测。否则对于一个已经采用CButton控制的按钮会出现
															// ASSERT警告的.
		
		// 设置属性。
		pNewSkinButton->m_bEnableStretch=m_bEnableStretch;
		pNewSkinButton->m_nFocusBitmapResID=m_nFocusBitmapResID;
		pNewSkinButton->m_nHoverBitmapResID=m_nHoverBitmapResID;
		pNewSkinButton->m_nNormalBitmapResID=m_nNormalBitmapResID;
		pNewSkinButton->m_nPressedBitmapResID=m_nPressedBitmapResID;
		pNewSkinButton->m_nXPos=m_nXPos;
		pNewSkinButton->m_nYPos=m_nYPos;

		SetProp(hWnd,"SkinButtonObj",(HANDLE)pNewSkinButton);

		// 然后是WNDPROC;
		WNDPROC   OldProc=(WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
		SetProp(hWnd,"OldWndProc",OldProc);

		SetWindowLong(hWnd,GWL_WNDPROC,(LONG)SkinButtonSubclassProc);
		
		return TRUE;
	}

	return FALSE;
}


BOOL CSkinButton::OnEraseBkgnd(CDC* pDC) 
{
	// 我们自己绘制按钮状态。
	// 根据当前按钮的信息。

	// TODO: Add your code to draw the specified item
    CRect		rect;
    GetClientRect(rect);
	
	CMemDC		DC(pDC,&rect);					// 由于传递近来的pDC不一定就是这个按钮的DC，
												// 所以绘画的区域必须手动指定。
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
