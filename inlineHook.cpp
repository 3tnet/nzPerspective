// inlineHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "inlineHook.h"
#include "InlineHookFrame.h"
HHOOK HkeybordHook;
HWND NzHwnd;
ULONG shopAddr=0;
WNDPROC oldWindowProc;

void cheak();
void alert(char * str,HWND hwnd = NULL){
	MessageBox(hwnd,str,"3t永远站在前方为你导航！",MB_OK);
}
void hookFun();
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			cheak();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
LRESULT CALLBACK keybordProc(
    int nCode,
	WPARAM wParam,
	LPARAM lParam
){
	return CallNextHookEx(HkeybordHook,nCode,wParam,lParam);
}
//======================
LRESULT CALLBACK WindowProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
  ){
	  if(uMsg == WM_KEYDOWN){
		  if(wParam == VK_UP){
			  char str[256];
			  sprintf(str,"%x",shopAddr);
			  OutputDebugString(str);
		  }
	  }
	  return CallWindowProc(oldWindowProc,hwnd,uMsg,wParam,lParam);
}
void cheak(){
	NzHwnd = FindWindow(NULL,"逆战");
	if(NzHwnd){
		DWORD NZpid = NULL;
		GetWindowThreadProcessId(NzHwnd,&NZpid);
		if(NZpid){
			if(GetCurrentProcessId() == NZpid){
				//注入逆战
				if(HkeybordHook){
					UnhookWindowsHookEx(HkeybordHook);
				}
				OSVERSIONINFO sysVerInfo;
				sysVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
				GetVersionEx(&sysVerInfo);
				if(sysVerInfo.dwMajorVersion == 6 && sysVerInfo.dwMinorVersion == 3){//win8.1
					alert("对不起，暂只支持windows7版本!");
				}else if(sysVerInfo.dwMajorVersion == 6 && sysVerInfo.dwMinorVersion == 2){//win8
					alert("对不起，暂只支持windows7版本!");
				}else if(sysVerInfo.dwMajorVersion == 6 && sysVerInfo.dwMinorVersion == 1){//win7
					hookFun();
				}else{
					alert("对不起，暂只支持windows7版本!");
				}
				alert("ok");
				MessageBeep(0xFFFFFFFF);
				oldWindowProc = (WNDPROC)SetWindowLong(NzHwnd,GWL_WNDPROC,(LONG)WindowProc);
			}
		}
	}
}


void setUpHook(){
	HkeybordHook = SetWindowsHookEx(WH_KEYBOARD,keybordProc,GetModuleHandle("inlineHook.dll"),0);
	if(HkeybordHook){
		MessageBox(NULL,"设置钩子成功","提示",0);
	}else{
		MessageBox(NULL,"设置钩子失败","提示",0);
	}
}

ULONG GetAddress(){
	HANDLE handle =  GetModuleHandle("tgame.exe");
	return (ULONG)handle + 0x62e14;
}

BYTE oldCode[5];
ULONG oldCodeEnter;
ULONG returnAddr;

__declspec(naked) void _MyFun(){
	__asm{
		jmp oldCodeEnter
	}
}
__declspec(naked) void MyFun(){
	__asm{
		mov esi,dword ptr[eax]
		mov shopAddr,esi;
		jmp returnAddr
	}
}
void hookFun(){
	char str[256];
	sprintf(str,"GetAddress:%x",GetAddress());
	alert(str);
	InlineHookFeame* hookTool = new InlineHookFeame(GetAddress(),(ULONG)MyFun,(ULONG)_MyFun,oldCode,sizeof(oldCode));
	returnAddr = hookTool->originalAddr+hookTool->codeLen;
	if(hookTool->StartHook()){
		oldCodeEnter = hookTool->recoverCodeEnter;
	}else{
		alert("失败");
	}
}