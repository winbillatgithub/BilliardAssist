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
// SkinDialog.h: interface for the CSkinDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINDIALOG_H__EB743BA1_2ACA_42EE_B687_1BDC4203D8AB__INCLUDED_)
#define AFX_SKINDIALOG_H__EB743BA1_2ACA_42EE_B687_1BDC4203D8AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinButton.h"

// ǿ�ƾ�̬��ǩ�������ý���ɫ��Ϊˢ��
// ����������λ����Ϊ�ڴ򿪵Ĺ��öԻ����еļ�����ǩ��"���ҷ�Χ","�ļ���",
// "�ļ�����"���ǲ�����ȷ��ʾ,�������һ����ˢ�ӵĻ�.
#define SKINDIALOG_FLAGS_FORCE_STATIC_BACKGROUND_BRUSH			0x00000010L			

class CSkinDialog  
{
public:
	CSkinDialog();
	virtual ~CSkinDialog();

	// SubClassһ���Ի����������������ӶԻ���,����MessageBox
	BOOL SubClassDialog(HWND hWnd);

	// ȡ��SubClass
	BOOL RemoveSubClass();

	// ������ı���
	virtual void DoGradientFill(CDC *pDC, CRect rect);
	
public:
	CSkinButton			m_bSkinButtonsTemplate;		// Ĭ�ϰ�ť��ģ��
	DWORD				m_dwFlags;
};

#endif // !defined(AFX_SKINDIALOG_H__EB743BA1_2ACA_42EE_B687_1BDC4203D8AB__INCLUDED_)
