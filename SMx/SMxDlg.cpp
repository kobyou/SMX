
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
	DDX_Control(pDX, IDC_LIST_LOG, ctlListBoxLog);
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
	ON_EN_CHANGE(IDC_EDIT_IDIV, &CSMxDlg::OnEnChangeEditIdiv)
	//ON_EN_CHANGE(IDC_EDIT_PLAIN_HEX, &CSMxDlg::OnEnChangeEditPlainHex)
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

void CSMxDlg:: MsgOut(const char* _Format, ...)
{
	char str_tmp[1024] = { 0 };
	va_list vArgList;
	va_start(vArgList, _Format);
	_vsnprintf_s(str_tmp, 512, _Format, vArgList);
	va_end(vArgList);

	int nCurSel = ctlListBoxLog.GetCurSel();
	ctlListBoxLog.AddString(str_tmp);
	ctlListBoxLog.SetCurSel(nCurSel + 1);
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
	//CEdit* pEdit_PUBLIC_KEY = (CEdit*)GetDlgItem(IDC_LIST_LOG);

	MsgOut("SM2_Gen Keypair:");

	BYTE PriKey[32] = { 0 };
	Ecckey PublicKey;

	CString strPriKey;
	pEdit_PRIVAT_KEY->GetWindowText(strPriKey);
	if(strPriKey.GetLength() == 0) {
		GenRand(PriKey, sizeof(PriKey));
	}
	else {
		if(strPriKey.GetLength() <= 64) {
			std::string strPrivatKey;
			strPrivatKey = strPriKey.GetBuffer(0);
			HexStr2Bytes(strPrivatKey, (char*)PriKey);
		}
		else {
			std::string strPrivatKey;
			strPrivatKey = strPriKey.GetBuffer(0);
			HexStr2Bytes(strPrivatKey.substr(0, 64), (char*)PriKey);
		}
	}


	//BYTE PubKey[64];
	//EccMakeKey(PriKey, 32, PubKey, 64, 0);
	EccPairKey(PriKey, 32, PublicKey.x, PublicKey.y);

	std::string HexstrPrivatKey = Bytes2HexStr((char*)PriKey, sizeof(PriKey));
	ToUpper(HexstrPrivatKey);
	pEdit_PRIVAT_KEY->SetWindowText(HexstrPrivatKey.c_str());

	std::string HexstrPublicKeyX = Bytes2HexStr((char*)PublicKey.x, sizeof(PublicKey.x));
	ToUpper(HexstrPublicKeyX);
	pEdit_PUBLIC_KEY_X->SetWindowText(HexstrPublicKeyX.c_str());

	std::string HexstrPublicKeyY = Bytes2HexStr((char*)PublicKey.y, sizeof(PublicKey.y));
	ToUpper(HexstrPublicKeyY);
	pEdit_PUBLIC_KEY_Y->SetWindowText(HexstrPublicKeyY.c_str());

	std::string HexstrPublicKey = HexstrPublicKeyX + HexstrPublicKeyY;
	ToUpper(HexstrPublicKey);

	pEdit_PUBLIC_KEY->SetWindowText(HexstrPublicKey.c_str());


	MsgOut("Private Key:%s", HexstrPrivatKey.c_str());
	MsgOut("Public Key X:%s", HexstrPublicKeyX.c_str());
	MsgOut("Public Key Y:%s", HexstrPublicKeyY.c_str());

}

void CSMxDlg::sm2_Sign()
{
	CEdit* pEdit_PRIVAT_KEY = (CEdit*)GetDlgItem(IDC_EDIT_PRIVAT_KEY);
	CEdit* pEdit_PLAIN_TEXT = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_TEXT);
	CEdit* pEdit_PLAIN_HEX = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_HEX);
	CEdit* pEdit_SM3_SUMMARY = (CEdit*)GetDlgItem(IDC_EDIT_SM3_SUMMARY);
	CEdit* pEdit_E = (CEdit*)GetDlgItem(IDC_EDIT_E);
	CEdit* pEdit_SIGN = (CEdit*)GetDlgItem(IDC_EDIT_SIGN);


	// 获取随机数组
	byte random[32] = { 0 };
	GenRand(random, sizeof(random));

	//std::string HexRnd = "59276E27D506861A16680F3AD9C02DCCEF3CC1FA3CDBE4CE6D54B80DEAC1BC21";
	//HexStr2Bytes(HexRnd, (char*)random);


	// 提取明文
	CString strHexTxt;
	pEdit_PLAIN_HEX->GetWindowTextA(strHexTxt);
	std::string HexTxt = strHexTxt.GetBuffer(0);


	// 计算摘要->Hash1
	byte *ucPlainTxt = (byte*)malloc(sizeof(byte) * (strHexTxt.GetLength() / 2 + 1));
	HexStr2Bytes(HexTxt, (char*)ucPlainTxt);
	//memcpy(ucPlainTxt, strPlainTxt, strPlainTxt.GetLength());

	byte Hash1[32] = { 0 };
	SM3_Hash(ucPlainTxt, strHexTxt.GetLength() / 2, Hash1, sizeof(Hash1));

	std::string HexstrHash = Bytes2HexStr((char*)Hash1, sizeof(Hash1));
	ToUpper(HexstrHash);
	pEdit_SM3_SUMMARY->SetWindowText(HexstrHash.c_str());

	//Za计算
	byte Hash2[32] = { 0 };
	SM2_Get_Z((CHAR*)Hash2);

	//byte Hash2[32] = { 0 };
	//CString E("");
	//pEdit_E->GetWindowTextA(E);
	//if(E.GetLength() > 0) {
	//	std::string HexZA = E.GetBuffer(0);
	//	HexStr2Bytes(HexZA, (char*)Hash2);
	//}
	//else {
	//	MessageBox("Error:ZA value is NULL!");
	//	return;
	//}

	byte Hash3[32] = { 0 };
	char cMSG[64] = { 0 };
	memcpy(cMSG, (char*)Hash1, sizeof(Hash1));
	memcpy(cMSG + sizeof(Hash1), (char*)Hash2, sizeof(Hash2));
	SM3_Hash((byte*)cMSG, sizeof(cMSG), Hash3, sizeof(Hash3));


	// 私钥
	CString strPriKey("");
	pEdit_PRIVAT_KEY->GetWindowTextA(strPriKey);
	BYTE PriKey[32] = {0};
	std::string HexPriKey = strPriKey.GetBuffer(0);
	HexStr2Bytes(HexPriKey, (char*)PriKey);

	//byte E[32] = { 0 };
	SM2_Get_E((char*)Hash3);

	// 计算签名
	BYTE sign[64];
	EccSign(Hash3, 32, random, 32, PriKey, 32, sign, 64);

	std::string HexSign = Bytes2HexStr((char*)sign, sizeof(sign));
	ToUpper(HexSign);
	pEdit_SIGN->SetWindowTextA(HexSign.c_str());

	return;
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
	if(strPlainTxt.GetLength() == 0) {
		MessageBox("Plain Text is NULL!!");
		return;
	}

	// 计算摘要->Hash1
	byte *ucPlainTxt = (byte*)malloc(sizeof(byte) * (strPlainTxt.GetLength() + 1));
	memcpy(ucPlainTxt, strPlainTxt, strPlainTxt.GetLength());

	byte Hash1[32] = { 0 };
	SM3_Hash(ucPlainTxt, strPlainTxt.GetLength(), Hash1, sizeof(Hash1));

	std::string PlainHex = Bytes2HexStr((char*)ucPlainTxt, strPlainTxt.GetLength());
	ToUpper(PlainHex);
	pEdit_PLAIN_HEX->SetWindowText(PlainHex.c_str());

	std::string HexstrHash = Bytes2HexStr((char*)Hash1, sizeof(Hash1));
	ToUpper(HexstrHash);
	pEdit_SM3_SUMMARY->SetWindowText(HexstrHash.c_str());

	char E[32] = { 0 };
	SM2_Get_E(E);

	free(ucPlainTxt);

	MsgOut("SM3 Hash:");
	MsgOut("SM3 Hash Result:%s", HexstrHash.c_str());
}

int CSMxDlg::SM2_Get_Z(char Za[])
{

	CEdit* pEdit_PUBLIC_KEY = (CEdit*)GetDlgItem(IDC_EDIT_PUBLIC_KEY);
	CEdit* pEdit_IDIV = (CEdit*)GetDlgItem(IDC_EDIT_IDIV);
	CEdit* pEdit_E = (CEdit*)GetDlgItem(IDC_EDIT_E);

	unsigned char ENTLA[2];// = { 0x00, 0x80 };
	unsigned char IDA[256] = {0};// = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };
	unsigned char Msg[1024] = {0};	//210 = IDA_len + 2 + SM2_NUMWORD * 6

	CString strPublicKey; //public key
	pEdit_PUBLIC_KEY->GetWindowTextA(strPublicKey);
	if(strPublicKey.GetLength() != 128) {
		return 1;
	}
	std::string S_pubkey = strPublicKey.GetBuffer(0);
	byte Pub[64] = { 0 };
	HexStr2Bytes(S_pubkey, (char*)Pub);

	CString strIDA(""); //ID
	int IDlen = 0;
	std::string HexStrIDA;
	pEdit_IDIV->GetWindowTextA(strIDA);

	if(strIDA.GetLength() == 0) {
		memcpy(IDA, "1234567812345678", 16);
		IDlen = 16;
	}
	else {
		if(strIDA.GetLength() <= 256) {
			memcpy(IDA, strIDA.GetBuffer(), strIDA.GetLength());
			IDlen = strIDA.GetLength();
		}
		else {
			MessageBox("Error:IDA Lenth > 256...");
			return 1;
		}
	}


	//int userid_bitlen = ((strlen((CHAR*)IDA)) << 3);
	ENTLA[0] = (CHAR)((IDlen * 8) / 256);
	ENTLA[1] = (CHAR)((IDlen * 8) & 0xFF);

	//ZA = Hash(ENTLA || IDA || a || b || Gx || Gy || xA|| yA)
	memcpy(Msg, ENTLA, 2);
	memcpy(Msg + 2, IDA, IDlen);
	memcpy(Msg + 2 + IDlen, sm2_par_dig, sizeof(sm2_par_dig));
	memcpy(Msg + 2 + IDlen + sizeof(sm2_par_dig), Pub, 64);

	byte Hash2[32] = { 0 };
	SM3_Hash(Msg, 2 + IDlen + sizeof(sm2_par_dig) + 64, Hash2, sizeof(Hash2));

	//std::string HexHash2 = Bytes2HexStr((char*)Hash2, sizeof(Hash2));
	//ToUpper(HexHash2);
	//pEdit_E->SetWindowText(HexHash2.c_str());

	memcpy(Za, Hash2, sizeof(Hash2));

	return 0;

}

int CSMxDlg::SM2_Get_E(char e[])
{
	CEdit* pEdit_PLAIN_HEX = (CEdit*)GetDlgItem(IDC_EDIT_PLAIN_HEX);
	CEdit* pEdit_E = (CEdit*)GetDlgItem(IDC_EDIT_E);

	MsgOut("SM2_Get_E:");

	char Za[32] = { 0 };
	SM2_Get_Z(Za);

	std::string HexZa = Bytes2HexStr((char*)Za, sizeof(Za));

	CString strPlainHex; //plain text
	pEdit_PLAIN_HEX->GetWindowTextA(strPlainHex);
	if(strPlainHex.GetLength() == 0) {
		return 1;
	}

	std::string ZA_MSG = HexZa + strPlainHex.GetBuffer(0);
	ToUpper(ZA_MSG);

	char* ZaMsg = new char[ZA_MSG.length() / 2];
	HexStr2Bytes(ZA_MSG, ZaMsg);

	byte E[32] = { 0 };
	SM3_Hash((byte*)ZaMsg, ZA_MSG.length() / 2, E, sizeof(E));


	std::string HexHash2 = Bytes2HexStr((char*)E, sizeof(E));
	ToUpper(HexHash2);
	pEdit_E->SetWindowText(HexHash2.c_str());

	MsgOut("Za_hash:%s", ZA_MSG.c_str());
	MsgOut("e_hash:%s", HexHash2.c_str());

	return 0;
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
	byte *ucPlainTxt = (byte*)malloc(sizeof(byte) * (strPlainTxt.GetLength() + 1));
	memcpy(ucPlainTxt, strPlainTxt, strPlainTxt.GetLength());

	std::string PlainHex = Bytes2HexStr((char*)ucPlainTxt, strPlainTxt.GetLength());
	ToUpper(PlainHex);
	pEdit_PLAIN_HEX->SetWindowText(PlainHex.c_str());

	char e[32] = { 0 };
	SM2_Get_E(e);

	free(ucPlainTxt);

}


void CSMxDlg::OnEnChangeEditIdiv()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	char e[32] = { 0 };
	SM2_Get_E(e);
}


//void CSMxDlg::OnEnChangeEditPlainHex()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
