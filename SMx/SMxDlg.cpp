
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
	sm2_MakePubKey();

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



	BYTE PriKey[32];
	Ecckey PublicKey;
	HexStr2Bytes(HexStrPrivatKey, (char*)PriKey);

	//BYTE PubKey[64];
	//EccMakeKey(PriKey, 32, PubKey, 64, 0);
	EccPairKey(PriKey, 32, PublicKey.x, PublicKey.y);

	CEdit* pEdit0 = (CEdit*)GetDlgItem(IDC_EDIT_PRIVAT_KEY);
	pEdit0->SetWindowText(HexStrPrivatKey.c_str());

	std::string HexstrPublicKeyX = Bytes2HexStr((char*)PublicKey.x, sizeof(PublicKey.x));
	ToUpper(HexstrPublicKeyX);
	CEdit* pEdit_Key_X = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY_X);
	pEdit_Key_X->SetWindowText(HexstrPublicKeyX.c_str());

	std::string HexstrPublicKeyY = Bytes2HexStr((char*)PublicKey.y, sizeof(PublicKey.y));
	ToUpper(HexstrPublicKeyY);
	CEdit* pEdit_Key_Y = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY_Y);
	pEdit_Key_Y->SetWindowText(HexstrPublicKeyY.c_str());

	std::string HexstrPublicKey = HexstrPublicKeyX + HexstrPublicKeyY;
	ToUpper(HexstrPublicKey);
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY);
	pEdit1->SetWindowText(HexstrPublicKey.c_str());
}