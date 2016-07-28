// DllZhuRuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DllZhuRu.h"
#include "DllZhuRuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDllZhuRuDlg dialog

CDllZhuRuDlg::CDllZhuRuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDllZhuRuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDllZhuRuDlg)
	m_FilePathName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDllZhuRuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDllZhuRuDlg)
	DDX_Text(pDX, IDC_FILE_PATH, m_FilePathName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDllZhuRuDlg, CDialog)
	//{{AFX_MSG_MAP(CDllZhuRuDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE_DIALOG, OnFileDialog)
	ON_BN_CLICKED(IDC_INTO, OnInto)
	ON_BN_CLICKED(IDC_ClEAR, OnClEAR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDllZhuRuDlg message handlers

BOOL CDllZhuRuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDllZhuRuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDllZhuRuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDllZhuRuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDllZhuRuDlg::OnFileDialog() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dllFile(true,NULL,NULL,0,"��̬���ӿ�dll|*.dll|�����ļ�|*.*|");
	if(IDOK ==dllFile.DoModal())
	{
	 	m_FilePathName=dllFile.GetPathName();
		UpdateData(false);
	}
}
HMODULE	hmodule;
void CDllZhuRuDlg::OnInto() 
{
	// TODO: Add your control notification handler code here
    hmodule = ::LoadLibrary(m_FilePathName);
	if(hmodule){
		FARPROC proc = ::GetProcAddress(hmodule,"setUpHook");
		if(proc){
			proc();
		}else{
			MessageBox("����");
		}
	}else{
		MessageBox("Dll��ȡ����");
	}
}

void CDllZhuRuDlg::OnClEAR() 
{
	// TODO: Add your control notification handler code here
	::FreeLibrary(hmodule);
}
