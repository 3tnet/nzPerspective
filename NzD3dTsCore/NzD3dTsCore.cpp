// NzD3dTsCore.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "NzD3dTsCore.h"
#include "InlineHookFrame.h"
#include <d3d9.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DIP_OFFSET (0x2B6B1 + 0x12)	//DrawIndexedPrimitive������12�ֽ�ƫ��
#define CQ_OFFSET (0x24019 + 0x12) //CreateQuery����ƫ�Ƶ�12�ֽ�ƫ��

void cheakNz();
void hookDip();
void hookCq();
HHOOK HHookKeyboard;
bool isTs = false; //͸�ӿ���
//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//


// CNzD3dTsCoreApp

BEGIN_MESSAGE_MAP(CNzD3dTsCoreApp, CWinApp)
END_MESSAGE_MAP()


// CNzD3dTsCoreApp ����

CNzD3dTsCoreApp::CNzD3dTsCoreApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CNzD3dTsCoreApp ����

CNzD3dTsCoreApp theApp;


// CNzD3dTsCoreApp ��ʼ��

BOOL CNzD3dTsCoreApp::InitInstance()
{
	cheakNz();
	CWinApp::InitInstance();

	return TRUE;
}

LRESULT CALLBACK KeyboardProc(
  int code,       // hook code
  WPARAM wParam,  // virtual-key code
  LPARAM lParam   // keystroke-message information
  ){
	  if(wParam == VK_F2){
		  isTs=true;
	  }
	  if(wParam == VK_F3){
		  isTs=false;
	  }
	  return CallNextHookEx(HHookKeyboard,code,wParam,lParam);
}

extern "C" __declspec(dllexport) void start(){
	HHookKeyboard = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,GetModuleHandle(L"NzD3dTsCore.dll"),0);
	if(!HHookKeyboard)
	{
		AfxMessageBox(L"ʧ��");
	}
	MessageBeep(0xFFFFFFFF);
}
void cheakNz(){
	HWND hwnd = FindWindow(NULL,L"��ս");
	//HWND hwnd = FindWindow(L"TEST",NULL);
	DWORD NZpid;
	GetWindowThreadProcessId(hwnd,&NZpid);
	if(hwnd){
		if(GetCurrentProcessId()==NZpid){
			//��ʼHook
			hookDip();
			//hookCq();
			MessageBeep(0xFFFFFFFF);
		}
	}
}

//���DrawIndexedPrimitive������12�ֽڵĵ�ַ
ULONG GetDipAddress(){
	HANDLE handle =  GetModuleHandle(L"d3d9.dll");
	return (ULONG)handle + DIP_OFFSET;
}
//���CreateQuery������ַ
ULONG GetCQAddress(){
	HANDLE handle =  GetModuleHandle(L"d3d9.dll");
	return (ULONG)handle + CQ_OFFSET;
}
ULONG dipRecoverCodeEnter;
ULONG dipReturnAddr;
__declspec(naked) void _MyDipFun(){
	__asm{
		jmp dipRecoverCodeEnter
	}
}

LPDIRECT3DDEVICE9 M_pDevice;//d3d��������
UINT iOffsetInBytes,iStride;
IDirect3DVertexBuffer9* pStreamData = NULL;
__declspec(naked) void MyDipFun(){
	if(isTs){
		__asm{
			add esp,0x38
			pop M_pDevice
			sub esp,0x3c
		}
		M_pDevice->GetStreamSource(0,&pStreamData,&iOffsetInBytes,&iStride);
		M_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		if(iStride == 32){
			M_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);//�����Ǹ�����Ⱦ״̬������z��
			M_pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_NEVER);
		}
	}
	__asm{
		jmp dipReturnAddr
	}
}

void hookDip(){
	byte oldCode[5];
	InlineHookFeame* hookTool = new InlineHookFeame(GetDipAddress(),(ULONG)MyDipFun,(ULONG)_MyDipFun,oldCode,sizeof(oldCode));
	if(hookTool->StartHook()){
		dipReturnAddr = hookTool->originalAddr+hookTool->codeLen;
		dipRecoverCodeEnter = hookTool->recoverCodeEnter;
	}else{
		::MessageBox(NULL,L"δ֪���ڲ�����",L"error",MB_ICONEXCLAMATION | MB_OK);
	}
}
ULONG cqRecoverCodeEnter;
ULONG cqReturnAddr;
__declspec(naked) void _MyCqFun(){
	__asm{
		add esp,0x14
		mov dword ptr[esp],0x8
		sub esp,0x14
		jmp cqRecoverCodeEnter
	}
}
__declspec(naked) void MyCqFun(){

	__asm{
		jmp cqReturnAddr
	}
}
void hookCq(){
	byte oldCode[5];
	InlineHookFeame* hookTool = new InlineHookFeame(GetCQAddress(),(ULONG)MyCqFun,(ULONG)_MyCqFun,oldCode,sizeof(oldCode));
	if(hookTool->StartHook()){
		cqReturnAddr = hookTool->originalAddr+hookTool->codeLen;
		cqRecoverCodeEnter = hookTool->recoverCodeEnter;
	}else{
		::MessageBox(NULL,L"δ֪���ڲ�����",L"error",MB_ICONEXCLAMATION | MB_OK);
	}
}