
// AVMVideoDecomposingTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAVMVideoDecomposingToolApp: 
// �йش����ʵ�֣������ AVMVideoDecomposingTool.cpp
//

class CAVMVideoDecomposingToolApp : public CWinApp
{
public:
	CAVMVideoDecomposingToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAVMVideoDecomposingToolApp theApp;