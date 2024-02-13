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
// SkinDialog.h: interface for the CSkinDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINDIALOG_H__EB743BA1_2ACA_42EE_B687_1BDC4203D8AB__INCLUDED_)
#define AFX_SKINDIALOG_H__EB743BA1_2ACA_42EE_B687_1BDC4203D8AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinButton.h"

// 强制静态标签背景采用渐进色作为刷子
// 引入这个标记位是因为在打开的公用对话框中的几个标签如"查找范围","文件名",
// "文件类型"总是不能正确显示,如果返回一个空刷子的话.
#define SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH			0x00000010L			

class CSkinDialog  
{
public:
	CSkinDialog();
	virtual ~CSkinDialog();

	// SubClass一个对话框和它下面的所有子对话框,包括MessageBox
	BOOL SubClassDialog(HWND hWnd);

	// 取消SubClass
	BOOL RemoveSubClass();

	// 画渐变的背景
	virtual void DoGradientFill(CDC *pDC, CRect rect);
	
public:
	CSkinButton			m_bSkinButtonsTemplate;		// 默认按钮的模版
	DWORD				m_dwFlags;
};

#endif // !defined(AFX_SKINDIALOG_H__EB743BA1_2ACA_42EE_B687_1BDC4203D8AB__INCLUDED_)
