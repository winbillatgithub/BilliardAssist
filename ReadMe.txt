ʹ��˵��:

��һ��,ͨ���������Լ����Ƶȷ�������������Ҫ�İ�ťƤ��.
�ڶ���,����ЩƤ�����뵽��Դ�ļ���
������,��stdafx.h������#include "resource.h" ,���ж�Ӧ��SKIN_BUTTON_INIT_MACRO�궨��,Ȼ����ļ�SkinDialog.cpp��SkinButton.cpp���ӽ���Ŀ��.
���Ĳ�,��������������#include "SkinDialog.h",ͬʱ����һ��CSkinDialog	g_SkinDialog��ȫ�ֱ���.
���岽,�������ڵ�OnInitDialog()���е�CDialog::InitDialog()��������	g_SkinDialog.SubClassDialog(m_hWnd);
������,�������ڵ�DestroyWindow()�е���g_SkinDialog.RemoveSubClass();
���߲�,����,����.


��ϸ��ʹ�÷�����μ����ӳ����Դ�����е�˵������.
