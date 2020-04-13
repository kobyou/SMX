
// SMxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SMx.h"
#include "SMxDlg.h"
#include "afxdialogex.h"
#include <string>
#include "stringutil.h"
extern "C"
{
#include "Sm2.h"
#include "Sm3.h"
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
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


// CSMxDlg dialog



CSMxDlg::CSMxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SMX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSMxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_PRIVAT_KEY, &CSMxDlg::OnEnChangeEditPrivatKey)
	ON_BN_CLICKED(IDC_BUTTON_KEY_MAKE, &CSMxDlg::OnBnClickedButtonKeyMake)
	ON_BN_CLICKED(IDC_BUTTON_SIGN, &CSMxDlg::OnBnClickedButtonSign)
	ON_BN_CLICKED(IDC_BUTTON_SM3_HASH, &CSMxDlg::OnBnClickedButtonSm3Hash)
	ON_EN_CHANGE(IDC_EDIT_PLAIN_TEXT, &CSMxDlg::OnEnChangeEditPlainText)
END_MESSAGE_MAP()


// CSMxDlg message handlers

BOOL CSMxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if(!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//sm2_MakePubKey();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSMxDlg::OnPaint()
{
	if(IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSMxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSMxDlg::OnEnChangeEditPrivatKey()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CSMxDlg::sm2_MakePubKey()
{
	CEdit* pEdit_PRIVAT_KEY = (CEdit*)GetDlgItem(IDC_EDIT_PRIVAT_KEY);
	CEdit* pEdit_PUBLIC_KEY_X = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY_X);
	CEdit* pEdit_PUBLIC_KEY_Y = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY_Y);
	CEdit* pEdit_PUBLIC_KEY = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY);

	BYTE PriKey[32];
	Ecckey PublicKey;

	//CString strPriKey;
	//pEdit_PRIVAT_KEY->GetWindowText(strPriKey);
	//std::string strPrivatKey;
	//strPrivatKey = strPriKey.GetBuffer(0);

	//HexStr2Bytes(HexStrPrivatKey, (char*)PriKey);

	GenRand(PriKey, sizeof(PriKey));

	//BYTE PubKey[64];
	//EccMakeKey(PriKey, 32, PubKey, 64, 0);
	EccPairKey(PriKey, 32, PublicKey.x, PublicKey.y);

	std::string HexstrPrivatKeyX = Bytes2HexStr((char*)PriKey, sizeof(PriKey));
	ToUpper(HexstrPrivatKeyX);
	pEdit_PRIVAT_KEY->SetWindowText(HexstrPrivatKeyX.c_str());

	std::string HexstrPublicKeyX = Bytes2HexStr((char*)PublicKey.x, sizeof(PublicKey.x));
	ToUpper(HexstrPublicKeyX);
	pEdit_PUBLIC_KEY_X->SetWindowText(HexstrPublicKeyX.c_str());

	std::string HexstrPublicKeyY = Bytes2HexStr((char*)PublicKey.y, sizeof(PublicKey.y));
	ToUpper(HexstrPublicKeyY);
	pEdit_PUBLIC_KEY_Y->SetWindowText(HexstrPublicKeyY.c_str());

	std::string HexstrPublicKey = HexstrPublicKeyX + HexstrPublicKeyY;
	ToUpper(HexstrPublicKey);

	pEdit_PUBLIC_KEY->SetWindowText(HexstrPublicKey.c_str());
}

void CSMxDlg::sm2_Sign()
{
	CEdit* pEdit_PLAIN_TEXT = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_TEXT);
	CEdit* pEdit_SM3_SUMMARY = (CEdit*)GetDlgItem(IDC_EDIT_SM3_SUMMARY);

	// 获取随机数组
	byte random[32];
	GenRand(random, sizeof(random));

	// 提取明文
	CString strPlainTxt;
	pEdit_PLAIN_TEXT->GetWindowTextA(strPlainTxt);

	// 计算摘要->Hash1
	byte *ucPlainTxt = (byte*)malloc(sizeof(byte) * strPlainTxt.GetLength());
	memcpy(ucPlainTxt, strPlainTxt, strPlainTxt.GetLength());

	byte Hash1[32] = { 0 };
	SM3_Hash(ucPlainTxt, strPlainTxt.GetLength(), Hash1, sizeof(Hash1));

	std::string HexstrHash = Bytes2HexStr((char*)Hash1, sizeof(Hash1));
	ToUpper(HexstrHash);
	pEdit_SM3_SUMMARY->SetWindowText(HexstrHash.c_str());

}

void CSMxDlg::sm3_Hash1()
{
	CEdit* pEdit_PLAIN_TEXT = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_TEXT);
	CEdit* pEdit_PLAIN_HEX = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_HEX);
	CEdit* pEdit_SM3_SUMMARY = (CEdit*)GetDlgItem(IDC_EDIT_SM3_SUMMARY);

	// 获取随机数组
	byte random[32];
	GenRand(random, sizeof(random));

	// 提取明文
	CString strPlainTxt;
	pEdit_PLAIN_TEXT->GetWindowTextA(strPlainTxt);

	// 计算摘要->Hash1
	byte *ucPlainTxt = (byte*)malloc(sizeof(byte) * strPlainTxt.GetLength());
	memcpy(ucPlainTxt, strPlainTxt, strPlainTxt.GetLength());

	byte Hash1[32] = { 0 };
	SM3_Hash(ucPlainTxt, strPlainTxt.GetLength(), Hash1, sizeof(Hash1));

	std::string PlainHex = Bytes2HexStr((char*)ucPlainTxt, strPlainTxt.GetLength());
	ToUpper(PlainHex);
	pEdit_PLAIN_HEX->SetWindowText(PlainHex.c_str());

	std::string HexstrHash = Bytes2HexStr((char*)Hash1, sizeof(Hash1));
	ToUpper(HexstrHash);
	pEdit_SM3_SUMMARY->SetWindowText(HexstrHash.c_str());

	free(ucPlainTxt);
}

void CSMxDlg::OnBnClickedButtonKeyMake()
{
	// TODO: 在此添加控件通知处理程序代码
	sm2_MakePubKey();
}


void CSMxDlg::OnBnClickedButtonSign()
{
	// TODO: 在此添加控件通知处理程序代码
	sm2_Sign();
}


void CSMxDlg::OnBnClickedButtonSm3Hash()
{
	// TODO: 在此添加控件通知处理程序代码
	sm3_Hash1();
}


void CSMxDlg::OnEnChangeEditPlainText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEdit_PLAIN_TEXT = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_TEXT);
	CEdit* pEdit_PLAIN_HEX = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_HEX);

	// 提取明文
	CString strPlainTxt;
	pEdit_PLAIN_TEXT->GetWindowTextA(strPlainTxt);

	// 计算摘要->Hash1
	byte *ucPlainTxt = (byte*)malloc(sizeof(byte) * strPlainTxt.GetLength());
	memcpy(ucPlainTxt, strPlainTxt, strPlainTxt.GetLength());

	byte Hash1[32] = { 0 };
	SM3_Hash(ucPlainTxt, strPlainTxt.GetLength(), Hash1, sizeof(Hash1));

	std::string PlainHex = Bytes2HexStr((char*)ucPlainTxt, strPlainTxt.GetLength());
	ToUpper(PlainHex);
	pEdit_PLAIN_HEX->SetWindowText(PlainHex.c_str());

	free(ucPlainTxt);
}
