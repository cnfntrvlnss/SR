
#pragma once

wchar_t *GB2312sToWCs(const char *strIn);
char *WCsToGB2312s(const wchar_t *strIn);
wchar_t *UTF8sToWCs(const char *strIn);
char *WCsToUTF8s(const wchar_t *strIn);

/**
�Ա�ģ��ĺ���������������ɴ˺�����ȡ��
*/
LPTSTR GenLastErrorStr(LPTSTR lpszFunction);
