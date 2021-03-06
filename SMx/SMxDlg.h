
// SMxDlg.h : header file
//

#pragma once


// CSMxDlg dialog
class CSMxDlg : public CDialogEx {
	// Construction
public:
	CSMxDlg(CWnd* pParent = nullptr);	// standard constructor

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMX_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditPrivatKey();

	void sm2_MakePubKey();
	void sm2_Sign();
	int sm2_Verify();
	int sm2_Encrypt();
	int sm2_Decrypt();
	void sm3_Hash1();
	int SM2_Get_Z(char Za[]);
	int SM2_Get_E(char E[]);
	afx_msg void OnBnClickedButtonKeyMake();
	afx_msg void OnBnClickedButtonSign();
	afx_msg void OnBnClickedButtonSm3Hash();
	afx_msg void OnEnChangeEditPlainText();
	afx_msg void OnEnChangeEditIdiv();
	CListBox ctlListBoxLog;

	void MsgOut(const char* _Format, ...);
	afx_msg void OnBnClickedButtonSm2Verify();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSm2Ency();
	afx_msg void OnBnClickedButtonSm2Dnci();
};
