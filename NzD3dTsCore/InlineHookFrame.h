#include "stdafx.h"
class InlineHookFeame{
	public:
		ULONG originalAddr;//Hook�ĵ�ַ
		ULONG MyFunAddr;//�滻������ַ
		ULONG _MyFunAddr;//ִ�лָ����뺯����ַ
		PBYTE recoverCode;//�ָ�����
		SIZE_T codeLen;//�ָ����볤��
		ULONG recoverCodeEnter;//ִ�лָ�������ڵ�ַ
		InlineHookFeame(ULONG originalAddr,ULONG MyFunAddr,ULONG _MyFunAddr,PBYTE recoverCode,SIZE_T codeLen);
		bool StartHook();
};
