// NzD3dTs.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNzD3dTsApp:
// �йش����ʵ�֣������ NzD3dTs.cpp
//

class CNzD3dTsApp : public CWinApp
{
public:
	CNzD3dTsApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNzD3dTsApp theApp;