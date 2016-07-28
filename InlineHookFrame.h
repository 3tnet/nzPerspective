#include "stdafx.h"
class InlineHookFeame{
	public:
		ULONG originalAddr;//Hook的地址
		ULONG MyFunAddr;//替换函数地址
		ULONG _MyFunAddr;//执行恢复代码函数地址
		PBYTE recoverCode;//恢复代码
		SIZE_T codeLen;//恢复代码长度
		ULONG recoverCodeEnter;//执行恢复代码入口地址
		InlineHookFeame(ULONG originalAddr,ULONG MyFunAddr,ULONG _MyFunAddr,PBYTE recoverCode,SIZE_T codeLen);
		bool StartHook();
};
