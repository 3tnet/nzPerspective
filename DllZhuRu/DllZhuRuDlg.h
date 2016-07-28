// DllZhuRuDlg.h : header file
//

#if !defined(AFX_DLLZHURUDLG_H__B8A4D2C9_1BC6_4A26_81F8_F5FCFA71B381__INCLUDED_)
#define AFX_DLLZHURUDLG_H__B8A4D2C9_1BC6_4A26_81F8_F5FCFA71B381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDllZhuRuDlg dialog

class CDllZhuRuDlg : public CDialog
{
// Construction
public:
	CDllZhuRuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDllZhuRuDlg)
	enum { IDD = IDD_DLLZHURU_DIALOG };
	CString	m_FilePathName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllZhuRuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDllZhuRuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileDialog();
	afx_msg void OnInto();
	afx_msg void OnClEAR();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLZHURUDLG_H__B8A4D2C9_1BC6_4A26_81F8_F5FCFA71B381__INCLUDED_)
