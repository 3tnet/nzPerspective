// NzD3dTsCore.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "NzD3dTsCore.h"
#include "InlineHookFrame.h"
#include <d3d9.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DIP_OFFSET (0x2B6B1 + 0x12)	//DrawIndexedPrimitive函数第12字节偏移
#define CQ_OFFSET (0x24019 + 0x12) //CreateQuery函数偏移第12字节偏移

void cheakNz();
void hookDip();
void hookCq();
HHOOK HHookKeyboard;
bool isTs = false; //透视开关
//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//


// CNzD3dTsCoreApp

BEGIN_MESSAGE_MAP(CNzD3dTsCoreApp, CWinApp)
END_MESSAGE_MAP()


// CNzD3dTsCoreApp 构造

CNzD3dTsCoreApp::CNzD3dTsCoreApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CNzD3dTsCoreApp 对象

CNzD3dTsCoreApp theApp;


// CNzD3dTsCoreApp 初始化

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
		AfxMessageBox(L"失败");
	}
	MessageBeep(0xFFFFFFFF);
}
void cheakNz(){
	HWND hwnd = FindWindow(NULL,L"逆战");
	//HWND hwnd = FindWindow(L"TEST",NULL);
	DWORD NZpid;
	GetWindowThreadProcessId(hwnd,&NZpid);
	if(hwnd){
		if(GetCurrentProcessId()==NZpid){
			//开始Hook
			hookDip();
			//hookCq();
			MessageBeep(0xFFFFFFFF);
		}
	}
}

//获得DrawIndexedPrimitive函数第12字节的地址
ULONG GetDipAddress(){
	HANDLE handle =  GetModuleHandle(L"d3d9.dll");
	return (ULONG)handle + DIP_OFFSET;
}
//获得CreateQuery函数地址
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

LPDIRECT3DDEVICE9 M_pDevice;//d3d对象引用
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
			M_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);//这里是更改渲染状态，禁用z轴
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
		::MessageBox(NULL,L"未知的内部错误",L"error",MB_ICONEXCLAMATION | MB_OK);
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
		::MessageBox(NULL,L"未知的内部错误",L"error",MB_ICONEXCLAMATION | MB_OK);
	}
}