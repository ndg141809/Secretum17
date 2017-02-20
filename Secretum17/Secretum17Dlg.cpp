
// Secretum17Dlg.cpp : ���� ����
//

#include "stdafx.h"

#include "des.h"
#include "md5.h"

#include "Secretum17.h"
#include "Secretum17Dlg.h"
#include "afxdialogex.h"

#include <locale>

#define DES_MODE 0
#define MD5_MODE 1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DES des;
MD5 md5;

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
		char* temp_path = (char*)malloc(m_filename.GetLength());
		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, temp_path, m_filename.GetLength() + 1, m_filename, _TRUNCATE);
		
		/* ������ �Ѱ��� */
		if (m_Radio == DES_MODE) {
			
			if (des.Get_file(temp_path)) {
				MessageBox(_T("get_file error"));
			}
		}
		else if (m_Radio == MD5_MODE) {

			if (md5.Get_file(temp_path)) {
				MessageBox(_T("get_file error"));
			}
		}

		
		/* ���� ���� üũ */
		check_file_flag = 1;
		// �����Ҵ� �� free ���ٷ��� �ϴµ� ������ ����.
		//free(temp_path);
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
		char* temp_path = (char*)malloc(m_filename.GetLength());
		size_t CharactersConverted = 0;
		wcstombs_s(&CharactersConverted, temp_path, m_filename.GetLength() + 1, m_filename, _TRUNCATE);

		/* key ������ �Ѱ��� */
		if (des.Get_keyfile(temp_path)) {
			MessageBox(_T("get_keyfile error"));
		}
		
		/* ���� ���� üũ */
		check_keyfile_flag = 1;
		//free(temp_path);
	}
}

void CSecretum17Dlg::OnBnClickedButton5()
{
	if (des.Make_keyfile()) {
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

	if (m_Radio == DES_MODE) {

		if (check_keyfile_flag == 0) {
			MessageBox(_T("Please select key file..."));
			return;
		}
		des.DES_encode();
		MessageBox(_T("Success file encryption!"));
	}
	else if (m_Radio == MD5_MODE) {
		CString str = CString::CStringT(CA2CT(md5.MD5_file().c_str()));
		MessageBox(_T("MD5 File : ") + str);
	}


}


void CSecretum17Dlg::OnBnClickedDecodeBtn()
{
	if (check_file_flag == 0 || check_keyfile_flag == 0) {
		MessageBox(_T("Please select file..."));
		return;
	}

	if (m_Radio == DES_MODE) {
		des.DES_decode(); 
		MessageBox(_T("Success file decryption!"));
	}
}

void CSecretum17Dlg::init_mode() {
	file_path_btn.SetWindowTextW(_T(""));
	keyfile_name_edit.SetWindowTextW(_T(""));
	des.input_file = NULL;
	des.key_file = NULL;
	md5.input_file = NULL;
}

void CSecretum17Dlg::set_dialog(bool al_mode) {

	m_Radio = al_mode;
	al_mode = !al_mode;
	keyfile_create_btn.EnableWindow(al_mode);
	keyfile_name_edit.EnableWindow(al_mode);
	keyfile_search_btn.EnableWindow(al_mode);
	keyfile_message.EnableWindow(al_mode);
	decryption_btn.EnableWindow(al_mode);
}

void CSecretum17Dlg::OnBnClickedRadio1()
{
	init_mode();
	set_dialog(DES_MODE);
}


void CSecretum17Dlg::OnBnClickedRadio2()
{
	init_mode();
	set_dialog(MD5_MODE);
}
