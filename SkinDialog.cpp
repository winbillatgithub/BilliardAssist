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
			 
			 + ͨ��SetWindowLongPtr����SubClass��Ϊ�˻�����е���Ϣ

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
// ö���Ӵ������õĻص�����,������CSkinButtonSubClass���е�����Button
// ˳�㿴����û��Icon���͵�Static,�����,��ô�����ͱ����ں�һ��.
BOOL CALLBACK EnumSkinWindowProc(HWND hwnd,LPARAM lParam)
{
	TCHAR		szBuffer[512]={NULL};
	CSkinButton	*pSkinButton=(CSkinButton*)lParam;

	GetClassName(hwnd,szBuffer,512);

	ASSERT(g_pGlobalSkinDialogObj != NULL);					// ����ȷ��ȫ�ֵ�CSkinDialog����ֵ.

	if (lstrcmpi(szBuffer,"Button") == 0)
	{
		DWORD dwOldStyle=GetWindowLong(hwnd,GWL_STYLE);
		if (((dwOldStyle & BS_RADIOBUTTON) != BS_RADIOBUTTON) && ((dwOldStyle & BS_AUTORADIOBUTTON) != BS_AUTORADIOBUTTON)
			&& ((dwOldStyle & BS_CHECKBOX) != BS_CHECKBOX))
		{
			if (GetProp(hwnd,"SkinButtonHandled") == NULL)		
			{
				dwOldStyle |= BS_OWNERDRAW;						// ����BS_OWNERDRAW�����Ա���WM_DRAWITEM��Ϣ.
				SetWindowLong(hwnd,GWL_STYLE,dwOldStyle);
			
				pSkinButton->SubClassWindow(hwnd);				// CSkinButton ��ֻ�������İ�ť����Ȥ.
			}
		}
	}
	else if (lstrcmpi(szBuffer,"Static") == 0)
	{
		ICONINFO	IconInfo={NULL};
		HICON		hIcon=(HICON)SendMessage(hwnd,STM_GETICON,0,0);
		if (hIcon != NULL)
		{	
			// ����SS_BITMAP��ǣ�ͬʱȥ��SS_ICON��ǡ�
			DWORD dwOldStyle=GetWindowLong(hwnd,GWL_STYLE);
			dwOldStyle &= ~SS_ICON;
			dwOldStyle |= SS_BITMAP;
			SetWindowLong(hwnd,GWL_STYLE,dwOldStyle);
		
			// ����ͼ�����ɫλ������ɫ��Ĺ�ϵ������ɫ�ı����޷���ȷ�ĺ�Icon�����ںϡ�
			// (ͨ������ˢ��ʵ�ֵĽ���Ǳ���ɫ��ǿ��ת������ӽ�����ɫ)
			// 
			// ������õķ����ǰ�Iconת���������˱������BitmapȻ����ʾ��
			// 
			// ���鷳�Ķ�����:)

			CRect		rect;
			CBitmap		Bitmap;
			CDC			BitmapDC;
			CDC			ClientDC;
			CBitmap     ClientBitmap;
			CDC			PrevDC;
			CRect		rect2;
			CBrush		Brush;
			HWND		hwndParent=GetParent(hwnd);				// ��Ϊ������EuumChildWindows�е��õģ�����hwndһ����һ���Ӵ��ڵ�hWnd
			CBitmap     *pOldClientBitmap=NULL;
			CBitmap		*pOldBitmap=NULL;

			PrevDC.Attach(GetDC(hwnd));
			GetClientRect(GetParent(hwnd),&rect);
			GetWindowRect(hwnd,&rect2);
			
			::ScreenToClient(GetParent(hwnd), (LPPOINT)&rect2);
			::ScreenToClient(GetParent(hwnd), ((LPPOINT)&rect2)+1);
	
			ClientDC.CreateCompatibleDC(&PrevDC);
			BitmapDC.CreateCompatibleDC(&PrevDC);

			ClientBitmap.CreateCompatibleBitmap(&PrevDC,rect.Width(),rect.Height());	// �������屳�����Ǹ�Bitmap
			Bitmap.CreateCompatibleBitmap(&PrevDC,rect2.Width(),rect2.Height());		// ������ͼ����Ǹ�С��Bitmap
		
			pOldClientBitmap=ClientDC.SelectObject(&ClientBitmap);						// ѡ�ж���
			pOldBitmap=BitmapDC.SelectObject(&Bitmap);
			
			g_pGlobalSkinDialogObj->DoGradientFill(&ClientDC,rect);									// ��佥��ɫ����

			// Ȼ��ӱ����а�����ռ����ڵ�λ�ö�Ӧ��ͼ�󡰿١�����
			BitmapDC.BitBlt(0,0,rect2.Width(),rect2.Height(),&ClientDC,rect2.left,rect2.top,SRCCOPY);
			
			// ��ԭ����ͼ��
			VERIFY(DrawIcon(BitmapDC,0,0,hIcon));
			
			// ���¿ؼ���ͼ��Ϊλͼ
			SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)Bitmap);
			
			ClientDC.SelectObject(pOldClientBitmap);
			BitmapDC.SelectObject(pOldBitmap);

			PrevDC.DeleteDC();
			
			Bitmap.Detach();		// ��������������������λͼ�Ļ������Ǿ�ʲôҲ�ò����ˡ�
			
		}
	}

	// ����ö�ٵ�ǰ���ڵ��Ӵ��ڣ��Ѱ�ť���͵�Style������OwnerDraw��ǡ�
	// ͨ������ûʲô�õ�,��Ϊ�ܶ��Ӵ��ڻ�û��ʼ���������. ^_^
	EnumChildWindows(hwnd,EnumSkinWindowProc,lParam);

	return TRUE;
}

//----------------------------------------------------------------------------------
// CSkinDialog Subclass���WndProc����
LRESULT CALLBACK SkinWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WNDPROC		OldWndProc=NULL;
	OldWndProc=(WNDPROC)GetProp(hwnd,"SkinWindowOldWndProc");
	ASSERT(OldWndProc != NULL);

	if (uMsg == WM_DRAWITEM)
	{	
		// ���յ���WM_DRAWITEM���͵���Ӧ�Ŀؼ��С����������ġ���������->���Ի���
		LPDRAWITEMSTRUCT	pDrawInfo=(LPDRAWITEMSTRUCT)lParam;
		
		if ((pDrawInfo->CtlType == ODT_BUTTON))
		{
			// ��������ť��CSkinButton Subclass�������ť����CSkinButton���ƵĻ������ǲŻ����Ϣת����
			// �����ڴ򿪹��öԻ����лᱻ�ظ����õģ�
			// Ĭ������£�WM_DRAWITEMֻ�ᱻ���͸����壬�����Ƕ�Ӧ�Ŀؼ���
			if ((GetProp(pDrawInfo->hwndItem,"SkinButtonObj") != NULL)				// ����ͨ��CSkinButton subclass��İ�ť.
				|| (GetProp(pDrawInfo->hwndItem,"SkinButtonHandled") != NULL))		// ����ʹ��MFC�������õ�CSkinButton
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
		if ((((nWindowStyle & WS_DLGFRAME) == WS_DLGFRAME)		// ֻ��ԶԻ������͵Ĵ�����߱��Ϊʹ��CSKinDialog��
			 || (GetProp(hwnd,"SkinWindowHandled") != NULL))
			 && ((nWindowStyle & WS_MINIMIZEBOX) == 0))
		{																		// ������ʹ��BCG��ʱ���ѵ����Ĳ˵�Ҳ�����ϵģ�
			TCHAR			szBuffer[128];
			GetWindowText(hwnd,szBuffer,128);
			TRACE("SkinDialog receive WM_ERASEBKGND message for window %s.\n",szBuffer);
			
			CDC			dc;
			CRect		rect;
			dc.Attach((HDC)wParam);
	
			::GetClientRect(hwnd,&rect);
			
			// �����Լ���һ��
			g_pGlobalSkinDialogObj->DoGradientFill(&dc,rect);
			dc.Detach();
			
			// ��������ǰ�Ĵ��뻭��Ĭ�ϵ�MFC�Ĵ��������ǵĽ��䱳�������ġ�
			// CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);
			
			// �����Ѿ��Լ�������,����ϵͳ������ :)��
			return TRUE;
		}
	}
	else if (uMsg == WM_CTLCOLORSTATIC)
	{
		TCHAR		szBuffer[512];
		GetWindowText((HWND)lParam,szBuffer,512);
		if (lstrcmpi(szBuffer,"") != 0)					// ���ڱ��ⲻΪ�յ�Static,���ǰѱ���ȥ��.
		{												// TODO: ����Frame,������Ѻ��������©����,��һ����취���.
			
			if ((g_pGlobalSkinDialogObj == NULL)
				|| ((g_pGlobalSkinDialogObj->m_dwFlags & SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH) != SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH))
			{
				SetBkMode((HDC)wParam,TRANSPARENT);
				return (long)(HBRUSH)GetStockObject(NULL_BRUSH);
			}
			else
			{
				// ԭ������ͼ�걳���ķ���������һ�������ˢ�������Ʊ�����������ֲ��У���ɫ�������⡣
				// û�뵽����,��Ȼ���������ַ����Ը���Щ"���"�ľ�̬��ǩ,Ч����Ȼ���ǲ�һ����.
				// ����һ��Ҫ��ҪҲ����λͼ.
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
				
				

				// NOTE: ������Щͼ����16ɫ�ģ���������32λ���ɫ�ģ������е�ͼ�걳������ֲ���ȫ���ϵ������
				// TODO: ͨ��ת��ͼ�굽32λ���ɫ������������.		-- FAILED û���ҵ���Ӧ��ת������. :(

				Brush.CreatePatternBrush(&Bitmap);

				ClientDC.SelectObject(pOldClientBitmap);
				BitmapDC.SelectObject(pOldBitmap);

				PrevDC.DeleteDC();			// ���������ͨ��GetDC���ɵ�һ���µģ����Ǳ��븺�����١�
				DC.Detach();				// ���DC�������ǹ���ģ��������ǲ�����������
				
				hbr=Brush;

				Brush.Detach();
				return (long)(HBRUSH)hbr;
			}
		}
		

	}

	return CallWindowProc(OldWndProc,hwnd,uMsg,wParam,lParam);

}

//----------------------------------------------------------------------------
// Hook ���õĻص�����
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
			SkinDialog.SubClassDialog(hwnd);			// ��SubClassDialogȥ�ж��ǲ����ظ�Hook��.
        return 0;

    }

    // ������һ��Hook
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
		// û�а�װ��Hook�����ǰ�װ����
	    hSkinDialogHook = SetWindowsHookEx(
					WH_CBT, 
					CBTProc, 
					NULL, 
					GetCurrentThreadId()            // ֻHook��ǰ�߳�!!!
					);
	}
	
	// ���ȣ�ö�����е��Ӵ��ڣ��Ѱ�ť���͵�Style������OwnerDraw��ǡ�
	EnumChildWindows(hWnd,EnumSkinWindowProc,(LPARAM)&m_bSkinButtonsTemplate);

	if (GetProp(hWnd,"SkinWindowOldWndProc") == NULL)
	{
		// ��ȡ��ǰ��WndProc
		WNDPROC OldWndProc=(WNDPROC)GetWindowLong(hWnd,GWL_WNDPROC);
		
		// ����������
		SetProp(hWnd,"SkinWindowOldWndProc",(HANDLE)OldWndProc);
		
		// �����µ�WndProc
		SetWindowLong(hWnd,GWL_WNDPROC,(LONG)SkinWindowProc);

		SetProp(hWnd,"SkinWindowHandled",(HANDLE)1L);
	}
	else
	{
		// ֻ����SubClassһ�Ρ�
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
