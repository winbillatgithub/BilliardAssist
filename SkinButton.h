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


#if !defined(AFX_SKINBUTTON_H__C670249B_950C_4080_8ED1_E038202BCDF1__INCLUDED_)
#define AFX_SKINBUTTON_H__C670249B_950C_4080_8ED1_E038202BCDF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinButton.h : header file
//

//-----------------------------------------------------------------------
//
// CMemDC, for the fastest paint.
//
//-----------------------------------------------------------------------
class CMemDC : public CDC {
private:    
    CBitmap  m_bitmap;       // Offscreen bitmap
    CBitmap* m_oldBitmap;    // bitmap originally found in CMemDC
    CDC*     m_pDC;          // Saves CDC passed in constructor
    CRect    m_rect;         // Rectangle of drawing area.
    BOOL     m_bMemDC;       // TRUE if CDC really is a Memory DC.
public:
    
    CMemDC(CDC* pDC, const CRect* pRect = NULL) : CDC()
    {
        ASSERT(pDC != NULL); 

        // Some initialization
        m_pDC = pDC;
        m_oldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();

        // Get the rectangle to draw
        if (pRect == NULL) {
            pDC->GetClipBox(&m_rect);
        } else {
            m_rect = *pRect;
        }
        
        if (m_bMemDC) {
            // Create a Memory DC
            CreateCompatibleDC(pDC);
            pDC->LPtoDP(&m_rect);

            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_oldBitmap = SelectObject(&m_bitmap);
            
            SetMapMode(pDC->GetMapMode());
            pDC->DPtoLP(&m_rect);
            SetWindowOrg(m_rect.left, m_rect.top);
        } else {
            // Make a copy of the relevent parts of the current DC for printing
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }

        // Fill background 
        FillSolidRect(m_rect, pDC->GetBkColor());
    }

    
    ~CMemDC()    
    {        
        if (m_bMemDC) {
            // Copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                this, m_rect.left, m_rect.top, SRCCOPY);            
            
            //Swap back the original bitmap.
            SelectObject(m_oldBitmap);        
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.            
            m_hDC = m_hAttribDC = NULL;
        }    
    }
    
    // Allow usage as a pointer    
    CMemDC* operator->() 
    {
        return this;
    }    

    // Allow usage as a pointer    
    operator CMemDC*() 
    {
        return this;
    }
};



/////////////////////////////////////////////////////////////////////////////
// CSkinButton window

typedef struct tagPaintInfo
{
	SIZE      sizeBlock;
	RECT      rectBlockSrc;
	RECT      rectBlockDest;
}PAINTINFO;

class CSkinButton : public CButton
{
// Construction
public:
	CSkinButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinButton();

	// Generated message map functions
public:
	//{{AFX_MSG(CSkinButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	LRESULT afx_msg OnMouseLeave(WPARAM wparam, LPARAM lparam);
	LRESULT afx_msg OnMouseHover(WPARAM wparam, LPARAM lparam);
	void afx_msg OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

	void DrawContent(CMemDC &pDC,UINT state,CRect rect,BOOL Focus,CString &strText);

public:
	BOOL				SubClassWindow(HWND hWnd);

public:
	int					m_nXPos;
	int					m_nYPos;
	
	int					m_nNormalBitmapResID;
	int					m_nFocusBitmapResID;
	int					m_nHoverBitmapResID;
	int					m_nPressedBitmapResID;
	BOOL				m_bEnableStretch;

private:
	BOOL				m_bOverControl;
	BOOL				m_bSelected;
	BOOL				m_bTracking;
	BOOL				m_bFocus;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINBUTTON_H__C670249B_950C_4080_8ED1_E038202BCDF1__INCLUDED_)
