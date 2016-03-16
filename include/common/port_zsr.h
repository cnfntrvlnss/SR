
#pragma once

wchar_t *GB2312sToWCs(const char *strIn);
char *WCsToGB2312s(const wchar_t *strIn);
wchar_t *UTF8sToWCs(const char *strIn);
char *WCsToUTF8s(const wchar_t *strIn);

/**
对本模块的函数错误情况集中由此函数获取。
*/
LPTSTR GenLastErrorStr(LPTSTR lpszFunction);
