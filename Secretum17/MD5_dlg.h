#pragma once


// MD5_dlg ��ȭ �����Դϴ�.

class MD5_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(MD5_dlg)

public:
	MD5_dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MD5_dlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MD5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
