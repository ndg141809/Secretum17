
// Secretum17.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSecretum17App:
// �� Ŭ������ ������ ���ؼ��� Secretum17.cpp�� �����Ͻʽÿ�.
//

class CSecretum17App : public CWinApp
{
public:
	CSecretum17App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSecretum17App theApp;