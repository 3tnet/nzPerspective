#include "stdafx.h"
#include "InlineHookFrame.h"
InlineHookFeame::InlineHookFeame(ULONG originalAddr,ULONG MyFunAddr,ULONG _MyFunAddr,PBYTE recoverCode,SIZE_T codeLen){
	this->originalAddr = originalAddr;
	this->MyFunAddr = MyFunAddr;
	this->_MyFunAddr = _MyFunAddr;
	this->recoverCode = recoverCode;
	this->codeLen = codeLen;
}
bool InlineHookFeame::StartHook(){
	DWORD oldProtect = 0;
	if(VirtualProtect((LPVOID)this->originalAddr,this->codeLen,PAGE_EXECUTE_READWRITE,&oldProtect)){
		memcpy(this->recoverCode,(LPVOID)this->originalAddr,this->codeLen);
		
		DWORD jmpAddr = (DWORD)this->_MyFunAddr - this->originalAddr - 5;
		DWORD originalFunAddr = (DWORD)this->originalAddr;
		_asm{
			mov eax,originalFunAddr
			mov byte ptr[eax],0xe9
			add eax,1
			mov ebx,jmpAddr
			mov dword ptr[eax],ebx
		}
		VirtualProtect((LPVOID)this->originalAddr,this->codeLen,oldProtect,&oldProtect);
		LPVOID lpParameter = VirtualAlloc(NULL,(DWORD)this->recoverCode + 5,MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);
		if(lpParameter){
			this->recoverCodeEnter = (ULONG)lpParameter;
			originalFunAddr = this->recoverCodeEnter + this->codeLen;
			jmpAddr = (DWORD)this->MyFunAddr - originalFunAddr - 5;
			memcpy(lpParameter,(LPVOID)this->recoverCode,this->codeLen);
			__asm{
				mov eax,originalFunAddr
				mov byte ptr[eax],0xe9
				add eax,1
				mov ebx,jmpAddr
				mov dword ptr[eax],ebx
			}
			return true;
		}
	}
	return false;
}