
// Secretum17Dlg.cpp : ���� ����
//

#include "stdafx.h"

#include "des.h"
#include "md5.h"

#include "Secretum17.h"
#include "Secretum17Dlg.h"
#include "afxdialogex.h"

#include <locale>

#define BLOCK 1
#define HASH 0
#define DES_MODE 0
#define MD5_MODE 1
#define AES_MODE 2

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* �θ� Ŭ���� ������ ���� */
Block_AL* block_al;
Hash_AL* hash_al;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSecretum17Dlg ��ȭ ����



CSecretum17Dlg::CSecretum17Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SECRETUM17_DIALOG, pParent)
	, m_Radio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSecretum17Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Control(pDX, IDC_KEY_FILEOPEN, keyfile_search_btn);
	DDX_Control(pDX, IDC_BUTTON5, keyfile_create_btn);
	DDX_Control(pDX, IDC_EDIT2, keyfile_name_edit);
	DDX_Control(pDX, IDC_KEYFILE_MESSAGE, keyfile_message);
	DDX_Control(pDX, IDC_KEYFILE_GROUP, keyfile_group);
	DDX_Control(pDX, IDC_FILEOPEN, file_select_btn);
	DDX_Control(pDX, IDC_EDIT1, file_path_btn);
	DDX_Control(pDX, IDC_ENCODE_BTN, encryption_btn);
	DDX_Control(pDX, IDC_DECODE_BTN, decryption_btn);
}

BEGIN_MESSAGE_MAP(CSecretum17Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILEOPEN, &CSecretum17Dlg::OnBnClickedFileopen)
	ON_BN_CLICKED(IDC_KEY_FILEOPEN, &CSecretum17Dlg::OnBnClickedKeyFileopen)
	
	ON_BN_CLICKED(IDC_BUTTON5, &CSecretum17Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_ENCODE_BTN, &CSecretum17Dlg::OnBnClickedEncodeBtn)
	ON_BN_CLICKED(IDC_DECODE_BTN, &CSecretum17Dlg::OnBnClickedDecodeBtn)
	ON_BN_CLICKED(IDC_RADIO1, &CSecretum17Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSecretum17Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSecretum17Dlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CSecretum17Dlg �޽��� ó����

BOOL CSecretum17Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	/* �ѱ� ��� ���� üũ */
	setlocale(LC_ALL, "Korean");

	/* radio btn 1 func click */
	OnBnClickedRadio1();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSecretum17Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSecretum17Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSecretum17Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSecretum17Dlg::OnBnClickedFileopen()
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("�������(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("*.txt"), _T("txt"), OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		/* ���� ���� ��� ��� */
		CString pathName = dlg.GetPathName();
		CEdit *p = (CEdit*)GetDlgItem(IDC_EDIT1);
		p->SetWindowTextW(pathName);

		/* ���� �̸� �� ���� */
		CString m_filename = dlg.GetFileName();
		
		/* CString -> char* ����ȯ */
		file_name = (char*)malloc(m_filename.GetLength());
		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, file_name, m_filename.GetLength() + 1, m_filename, _TRUNCATE);

		/* ���� üũ */
		check_file_flag = 1;
	}
}

void CSecretum17Dlg::OnBnClickedKeyFileopen()
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("KEY FILE(*.key)|*.key||");
	CFileDialog dlg(TRUE, _T("*.key"), _T("tmpkey"), OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		/* ���� ���� ��� ��� */
		CString pathName = dlg.GetPathName();
		CEdit *p = (CEdit*)GetDlgItem(IDC_EDIT2);
		p->SetWindowTextW(pathName);

		/* ���� �̸� �� ���� */
		CString m_filename = dlg.GetFileName();

		/* CString -> char* ����ȯ */
		char* keyfile_name = (char*)malloc(m_filename.GetLength());
		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, keyfile_name, m_filename.GetLength() + 1, m_filename, _TRUNCATE);
		
		/* ���� üũ */
		check_keyfile_flag = 1;
	}
}

void CSecretum17Dlg::OnBnClickedButton5()
{
	if (block_al->Make_keyfile()) {
		MessageBox(_T("Fail!! Not make keyfile"));
	}
	else {
		MessageBox(_T("Make keyfile"));
	}
	
}


void CSecretum17Dlg::OnBnClickedEncodeBtn()
{
	if (check_file_flag == 0) {
		MessageBox(_T("Please select file..."));
		return;
	}

	if (algorithm == BLOCK) {

		if (check_keyfile_flag == 0) {
			MessageBox(_T("Please select key file..."));
			return;
		}

		/* ������ �ѱ� */
		if (block_al->Get_file(file_name)) {
			MessageBox(_T("get_file error"));
		}

		/* key ������ �Ѱ��� */
		if (block_al->Get_keyfile(keyfile_name)) {
			MessageBox(_T("get_keyfile error"));
		}

		/* ��ȣȭ */
		block_al->Encryption();
		MessageBox(_T("Success file encryption!"));
	}
	else if (algorithm == HASH) {

		if (hash_al->Get_file(file_name)) {
			MessageBox(_T("get_file error"));
		}

		/* ��ȣȭ */
		hash_al->Encryption();
		CString str = CString::CStringT(CA2CT(hash_al->MD5_result.c_str()));
		MessageBox(_T("MD5 File : ") + str);
	}

}


void CSecretum17Dlg::OnBnClickedDecodeBtn()
{
	if (check_file_flag == 0 || check_keyfile_flag == 0) {
		MessageBox(_T("Please select file..."));
		return;
	}

	/* ��ȣȭ */
	if (algorithm == BLOCK) {
		block_al->Decryption();
		MessageBox(_T("Success file decryption!"));
	}
}


void CSecretum17Dlg::set_dialog(bool al) {

	/* �ؽ�Ʈ area �ʱ�ȭ */
	file_path_btn.SetWindowTextW(_T(""));
	keyfile_name_edit.SetWindowTextW(_T(""));

	/* mode�� ���� dialog ��ȯ */
	keyfile_create_btn.EnableWindow(al);
	keyfile_name_edit.EnableWindow(al);
	keyfile_search_btn.EnableWindow(al);
	keyfile_message.EnableWindow(al);
	decryption_btn.EnableWindow(al);
}


void CSecretum17Dlg::OnBnClickedRadio1()
{
	set_dialog(BLOCK);
	algorithm = BLOCK;
	m_Radio = DES_MODE;	
}


void CSecretum17Dlg::OnBnClickedRadio2()
{
	set_dialog(HASH);
	algorithm = HASH;
	m_Radio = MD5_MODE;
}


void CSecretum17Dlg::OnBnClickedRadio3()
{
	set_dialog(BLOCK);
	algorithm = BLOCK;
	m_Radio = AES_MODE;
}
