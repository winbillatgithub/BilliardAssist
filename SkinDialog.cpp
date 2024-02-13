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
			 
			 + 通过SetWindowLongPtr进行SubClass，为了获得所有的消息

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

// SkinDialog.cpp: implementation of the CSkinDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static HHOOK	hSkinDialogHook=NULL;
CSkinDialog		*g_pGlobalSkinDialogObj=NULL;
//------------------------------------------------------------------------
// 枚举子窗口所用的回调函数,用来让CSkinButtonSubClass当中的所有Button
// 顺便看看有没有Icon类型的Static,如果有,那么把它和背景融合一下.
BOOL CALLBACK EnumSkinWindowProc(HWND hwnd,LPARAM lParam)
{
	TCHAR		szBuffer[512]={NULL};
	CSkinButton	*pSkinButton=(CSkinButton*)lParam;

	GetClassName(hwnd,szBuffer,512);

	ASSERT(g_pGlobalSkinDialogObj != NULL);					// 必须确保全局的CSkinDialog被赋值.

	if (lstrcmpi(szBuffer,"Button") == 0)
	{
		DWORD dwOldStyle=GetWindowLong(hwnd,GWL_STYLE);
		if (((dwOldStyle & BS_RADIOBUTTON) != BS_RADIOBUTTON) && ((dwOldStyle & BS_AUTORADIOBUTTON) != BS_AUTORADIOBUTTON)
			&& ((dwOldStyle & BS_CHECKBOX) != BS_CHECKBOX))
		{
			if (GetProp(hwnd,"SkinButtonHandled") == NULL)		
			{
				dwOldStyle |= BS_OWNERDRAW;						// 增加BS_OWNERDRAW属性以便获得WM_DRAWITEM消息.
				SetWindowLong(hwnd,GWL_STYLE,dwOldStyle);
			
				pSkinButton->SubClassWindow(hwnd);				// CSkinButton 类只对真正的按钮感兴趣.
			}
		}
	}
	else if (lstrcmpi(szBuffer,"Static") == 0)
	{
		ICONINFO	IconInfo={NULL};
		HICON		hIcon=(HICON)SendMessage(hwnd,STM_GETICON,0,0);
		if (hIcon != NULL)
		{	
			// 增加SS_BITMAP标记，同时去掉SS_ICON标记。
			DWORD dwOldStyle=GetWindowLong(hwnd,GWL_STYLE);
			dwOldStyle &= ~SS_ICON;
			dwOldStyle |= SS_BITMAP;
			SetWindowLong(hwnd,GWL_STYLE,dwOldStyle);
		
			// 由于图标的颜色位数和颜色表的关系，渐进色的背景无法正确的和Icon进行融合。
			// (通过构造刷子实现的结果是背景色被强制转换成最接近的颜色)
			// 
			// 这里采用的方法是把Icon转换成增加了背景后的Bitmap然后显示。
			// 
			// 好麻烦的东西。:)

			CRect		rect;
			CBitmap		Bitmap;
			CDC			BitmapDC;
			CDC			ClientDC;
			CBitmap     ClientBitmap;
			CDC			PrevDC;
			CRect		rect2;
			CBrush		Brush;
			HWND		hwndParent=GetParent(hwnd);				// 因为这是在EuumChildWindows中调用的，所以hwnd一定是一个子窗口的hWnd
			CBitmap     *pOldClientBitmap=NULL;
			CBitmap		*pOldBitmap=NULL;

			PrevDC.Attach(GetDC(hwnd));
			GetClientRect(GetParent(hwnd),&rect);
			GetWindowRect(hwnd,&rect2);
			
			::ScreenToClient(GetParent(hwnd), (LPPOINT)&rect2);
			::ScreenToClient(GetParent(hwnd), ((LPPOINT)&rect2)+1);
	
			ClientDC.CreateCompatibleDC(&PrevDC);
			BitmapDC.CreateCompatibleDC(&PrevDC);

			ClientBitmap.CreateCompatibleBitmap(&PrevDC,rect.Width(),rect.Height());	// 整个窗体背景的那个Bitmap
			Bitmap.CreateCompatibleBitmap(&PrevDC,rect2.Width(),rect2.Height());		// 用来画图标的那个小的Bitmap
		
			pOldClientBitmap=ClientDC.SelectObject(&ClientBitmap);						// 选中对象
			pOldBitmap=BitmapDC.SelectObject(&Bitmap);
			
			g_pGlobalSkinDialogObj->DoGradientFill(&ClientDC,rect);									// 填充渐进色背景

			// 然后从背景中把这个空间所在的位置对应的图象“抠”出来
			BitmapDC.BitBlt(0,0,rect2.Width(),rect2.Height(),&ClientDC,rect2.left,rect2.top,SRCCOPY);
			
			// 画原来的图标
			VERIFY(DrawIcon(BitmapDC,0,0,hIcon));
			
			// 更新控件的图象为位图
			SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)Bitmap);
			
			ClientDC.SelectObject(pOldClientBitmap);
			BitmapDC.SelectObject(pOldBitmap);

			PrevDC.DeleteDC();
			
			Bitmap.Detach();		// 如果让析构函数销毁这个位图的话，我们就什么也得不到了。
			
		}
	}

	// 继续枚举当前窗口的子窗口，把按钮类型的Style增加上OwnerDraw标记。
	// 通常都是没什么用的,因为很多子窗口还没开始构造出来呢. ^_^
	EnumChildWindows(hwnd,EnumSkinWindowProc,lParam);

	return TRUE;
}

//----------------------------------------------------------------------------------
// CSkinDialog Subclass后的WndProc过程
LRESULT CALLBACK SkinWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WNDPROC		OldWndProc=NULL;
	OldWndProc=(WNDPROC)GetProp(hwnd,"SkinWindowOldWndProc");
	ASSERT(OldWndProc != NULL);

	if (uMsg == WM_DRAWITEM)
	{	
		// 将收到的WM_DRAWITEM发送到对应的控件中。做到真正的“属主画”->“自画”
		LPDRAWITEMSTRUCT	pDrawInfo=(LPDRAWITEMSTRUCT)lParam;
		
		if ((pDrawInfo->CtlType == ODT_BUTTON))
		{
			// 如果这个按钮被CSkinButton Subclass或这个按钮是由CSkinButton控制的话，我们才会把消息转发．
			// 否则在打开公用对话框中会被重复调用的．
			// 默认情况下，WM_DRAWITEM只会被发送给窗体，而不是对应的控件．
			if ((GetProp(pDrawInfo->hwndItem,"SkinButtonObj") != NULL)				// 这是通过CSkinButton subclass后的按钮.
				|| (GetProp(pDrawInfo->hwndItem,"SkinButtonHandled") != NULL))		// 这是使用MFC方法调用的CSkinButton
			{
				return SendMessage(pDrawInfo->hwndItem,uMsg,wParam,lParam);
			}
		}
		else
		{
			return CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);
		}
	}
	else if (uMsg == WM_DESTROY)
	{
		SetWindowLong(hwnd,GWL_WNDPROC,(LONG)OldWndProc);
		RemoveProp(hwnd,"SkinWindowOldWndProc");

		return CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		LONG nWindowStyle=GetWindowLong(hwnd,GWL_STYLE);
		if ((((nWindowStyle & WS_DLGFRAME) == WS_DLGFRAME)		// 只针对对话框类型的窗体或者标记为使用CSKinDialog的
			 || (GetProp(hwnd,"SkinWindowHandled") != NULL))
			 && ((nWindowStyle & WS_MINIMIZEBOX) == 0))
		{																		// 否则，在使用BCG的时候会把弹出的菜单也绘制上的．
			TCHAR			szBuffer[128];
			GetWindowText(hwnd,szBuffer,128);
			TRACE("SkinDialog receive WM_ERASEBKGND message for window %s.\n",szBuffer);
			
			CDC			dc;
			CRect		rect;
			dc.Attach((HDC)wParam);
	
			::GetClientRect(hwnd,&rect);
			
			// 我们自己画一遍
			g_pGlobalSkinDialogObj->DoGradientFill(&dc,rect);
			dc.Detach();
			
			// 不交给以前的代码画，默认的MFC的代码会把我们的渐变背景擦掉的。
			// CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);
			
			// 我们已经自己绘制了,不劳系统费心了 :)。
			return TRUE;
		}
	}
	else if (uMsg == WM_CTLCOLORSTATIC)
	{
		TCHAR		szBuffer[512];
		GetWindowText((HWND)lParam,szBuffer,512);
		if (lstrcmpi(szBuffer,"") != 0)					// 对于标题不为空的Static,我们把背景去掉.
		{												// TODO: 对于Frame,这样会把后面的线条漏出来,下一版想办法解决.
			
			if ((g_pGlobalSkinDialogObj == NULL)
				|| ((g_pGlobalSkinDialogObj->m_dwFlags & SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH) != SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH))
			{
				SetBkMode((HDC)wParam,TRANSPARENT);
				return (long)(HBRUSH)GetStockObject(NULL_BRUSH);
			}
			else
			{
				// 原来处理图标背景的方法，创建一个特殊的刷子来绘制背景，但最后发现不行，颜色数的问题。
				// 没想到的是,居然可以用这种方法对付那些"顽固"的静态标签,效果当然还是差一点了.
				// 考虑一下要不要也换成位图.
				CDC			DC;
				CRect		rect;
				CBitmap		Bitmap;
				CDC			BitmapDC;
				CDC			ClientDC;
				CBitmap     ClientBitmap;
				CDC			PrevDC;
				CRect		rect2;
				CBrush		Brush;
				HBRUSH		hbr;
				CBitmap     *pOldClientBitmap=NULL;
				CBitmap		*pOldBitmap=NULL;

				PrevDC.Attach(GetDC(hwnd));
				DC.Attach((HDC)wParam);

				DC.SetBkMode(TRANSPARENT);
				GetClientRect(hwnd,&rect);
				GetWindowRect((HWND)lParam,&rect2);
				
				::ScreenToClient(hwnd, (LPPOINT)&rect2);
				::ScreenToClient(hwnd, ((LPPOINT)&rect2)+1);
		
				ClientDC.CreateCompatibleDC(&PrevDC);
				BitmapDC.CreateCompatibleDC(&PrevDC);

				ClientBitmap.CreateCompatibleBitmap(&PrevDC,rect.Width(),rect.Height());
				Bitmap.CreateCompatibleBitmap(&PrevDC,rect2.Width(),rect2.Height());	
			
				pOldClientBitmap=ClientDC.SelectObject(&ClientBitmap);				
				pOldBitmap=BitmapDC.SelectObject(&Bitmap);
				
				g_pGlobalSkinDialogObj->DoGradientFill(&ClientDC,rect);		

				BitmapDC.BitBlt(0,0,rect2.Width(),rect2.Height(),&ClientDC,rect2.left,rect2.top,SRCCOPY);	// Copy the content to the Icon DC.
				
				

				// NOTE: 由于有些图标是16色的，而背景是32位真彩色的，所以有的图标背景会出现不完全符合的情况。
				// TODO: 通过转换图标到32位真彩色来解决这个问题.		-- FAILED 没有找到对应的转换函数. :(

				Brush.CreatePatternBrush(&Bitmap);

				ClientDC.SelectObject(pOldClientBitmap);
				BitmapDC.SelectObject(pOldBitmap);

				PrevDC.DeleteDC();			// 这个是我们通过GetDC生成的一个新的，我们必须负责销毁。
				DC.Detach();				// 这个DC不是我们构造的，所以我们不能销毁它。
				
				hbr=Brush;

				Brush.Detach();
				return (long)(HBRUSH)hbr;
			}
		}
		

	}

	return CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);

}

//----------------------------------------------------------------------------
// Hook 所用的回调函数
LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode < 0)
    {
		return CallNextHookEx(hSkinDialogHook, nCode, wParam, lParam);
	}
	
    switch(nCode)
    {
	    case HCBT_ACTIVATE:
			HWND		hwnd = (HWND)wParam;
			CSkinDialog SkinDialog;
			SkinDialog.SubClassDialog(hwnd);			// 让SubClassDialog去判断是不是重复Hook了.
        return 0;

    }

    // 调用下一个Hook
    return CallNextHookEx(hSkinDialogHook, nCode, wParam, lParam);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinDialog::CSkinDialog()
{

}

CSkinDialog::~CSkinDialog()
{

}

BOOL CSkinDialog::SubClassDialog(HWND hWnd)
{
	if (g_pGlobalSkinDialogObj == NULL)
	{
		g_pGlobalSkinDialogObj=this;
	}

	if (hSkinDialogHook == NULL)
	{
		// 没有安装过Hook？我们安装它。
	    hSkinDialogHook = SetWindowsHookEx(
					WH_CBT, 
					CBTProc, 
					NULL, 
					GetCurrentThreadId()            // 只Hook当前线程!!!
					);
	}
	
	// 首先，枚举所有的子窗口，把按钮类型的Style增加上OwnerDraw标记。
	EnumChildWindows(hWnd,EnumSkinWindowProc,(LPARAM)&m_bSkinButtonsTemplate);

	if (GetProp(hWnd,"SkinWindowOldWndProc") == NULL)
	{
		// 获取以前的WndProc
		WNDPROC OldWndProc=(WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
		
		// 保存下来。
		SetProp(hWnd,"SkinWindowOldWndProc",(HANDLE)OldWndProc);
		
		// 设置新的WndProc
		SetWindowLong(hWnd,GWL_WNDPROC,(LONG)SkinWindowProc);

		SetProp(hWnd,"SkinWindowHandled",(HANDLE)1L);
	}
	else
	{
		// 只允许SubClass一次。
		return FALSE;
	}

	return FALSE;
}

BOOL CSkinDialog::RemoveSubClass()
{
	BOOL bResult=FALSE;
	if (hSkinDialogHook != NULL)
	{
		bResult=UnhookWindowsHookEx(hSkinDialogHook);
		hSkinDialogHook=NULL;
	}
	
	return bResult;
}

void CSkinDialog::DoGradientFill(CDC *pDC, CRect rect)
{
	CBrush pBrush[64];
	int nWidth = (rect.right) - (rect.left);
    int nHeight = (rect.bottom) - (rect.top);
    CRect rct;
	BOOL m_bOverControl=FALSE;
	BOOL Focus=FALSE;
	int i = 0;

    for (i=0; i<64; i++)
	{
		pBrush[i].CreateSolidBrush(RGB(255-(i/1.6), 255-(i/1.4), 255-(i/1.3)));
	}
	
	
    for (i=rect.top; i<nHeight+2; i++) 
	{
        rct.SetRect (rect.left, i, nWidth+2, i + 1);
        pDC->FillRect (&rct, &pBrush[((i * 63) / nHeight)]);
    }
	
    for (i=0; i<64; i++)
	{
		pBrush[i].DeleteObject();
	}
}
