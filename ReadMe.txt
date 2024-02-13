使用说明:

第一步,通过截屏或自己绘制等方法创建出所需要的按钮皮肤.
第二步,把这些皮肤加入到资源文件中
第三步,在stdafx.h中增加#include "resource.h" ,还有对应的SKIN_BUTTON_INIT_MACRO宏定义,然后把文件SkinDialog.cpp和SkinButton.cpp增加进项目里.
第四步,在主窗口中增加#include "SkinDialog.h",同时增加一个CSkinDialog	g_SkinDialog的全局变量.
第五步,在主窗口的OnInitDialog()当中的CDialog::InitDialog()后面增加	g_SkinDialog.SubClassDialog(m_hWnd);
第六步,在主窗口的DestroyWindow()中调用g_SkinDialog.RemoveSubClass();
第七步,编译,运行.


详细的使用方法请参见例子程序和源代码中的说明文字.
