// NzD3dTsCore.h : NzD3dTsCore DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNzD3dTsCoreApp
// �йش���ʵ�ֵ���Ϣ������� NzD3dTsCore.cpp
//

class CNzD3dTsCoreApp : public CWinApp
{
public:
	CNzD3dTsCoreApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern "C" __declspec(dllexport) void start();