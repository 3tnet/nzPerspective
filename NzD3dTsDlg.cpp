// NzD3dTsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NzD3dTs.h"
#include "NzD3dTsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNzD3dTsDlg �Ի���




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


// CNzD3dTsDlg ��Ϣ�������

BOOL CNzD3dTsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNzD3dTsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CNzD3dTsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HMODULE NzD3dTsCore = NULL;
void CNzD3dTsDlg::OnBnClickedOk()
{
	m_start_btn.SetWindowText(L"������");
	m_start_btn.EnableWindow(false);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NzD3dTsCore = LoadLibrary(L"NzD3dTsCore.dll");
	if(NzD3dTsCore){
		FARPROC proc = GetProcAddress(NzD3dTsCore,"start");
		if(proc){
			proc();
		}else{
			::MessageBox(this->m_hWnd,L"δ֪����",L"error",MB_ICONEXCLAMATION | MB_OK);
		}
	}else{
		::MessageBox(this->m_hWnd,L"��ʧ NzD3dTsCore.dll",L"error",MB_ICONEXCLAMATION | MB_OK);
	}
}

void CNzD3dTsDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(NzD3dTsCore){
		FreeLibrary(NzD3dTsCore);
	}
	OnCancel();
}
