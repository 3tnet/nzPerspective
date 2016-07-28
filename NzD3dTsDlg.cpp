// NzD3dTsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NzD3dTs.h"
#include "NzD3dTsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNzD3dTsDlg 对话框




CNzD3dTsDlg::CNzD3dTsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNzD3dTsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNzD3dTsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_start_btn);
}

BEGIN_MESSAGE_MAP(CNzD3dTsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CNzD3dTsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNzD3dTsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNzD3dTsDlg 消息处理程序

BOOL CNzD3dTsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNzD3dTsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CNzD3dTsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HMODULE NzD3dTsCore = NULL;
void CNzD3dTsDlg::OnBnClickedOk()
{
	m_start_btn.SetWindowText(L"已启动");
	m_start_btn.EnableWindow(false);
	// TODO: 在此添加控件通知处理程序代码
	NzD3dTsCore = LoadLibrary(L"NzD3dTsCore.dll");
	if(NzD3dTsCore){
		FARPROC proc = GetProcAddress(NzD3dTsCore,"start");
		if(proc){
			proc();
		}else{
			::MessageBox(this->m_hWnd,L"未知错误",L"error",MB_ICONEXCLAMATION | MB_OK);
		}
	}else{
		::MessageBox(this->m_hWnd,L"丢失 NzD3dTsCore.dll",L"error",MB_ICONEXCLAMATION | MB_OK);
	}
}

void CNzD3dTsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(NzD3dTsCore){
		FreeLibrary(NzD3dTsCore);
	}
	OnCancel();
}
