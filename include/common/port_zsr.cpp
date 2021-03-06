#include "port_zsr.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <strsafe.h>
#else

#endif


#if defined(_WIN32) || defined(_WIN64)
wstring(*MBsToWCs) (const char *strIn) = GB2312sToWCs;
string(*WCsToMBs)(const wchar_t *strIn) = WCsToGB2312s;
inline static wchar_t *msMBsToWCs(const char *strIn, unsigned int codePage)
{
	int rett = MultiByteToWideChar(codePage, 0, strIn, -1, nullptr, 0);
	if (rett == 0){
		return nullptr;
	}
	wchar_t *deswcs = (wchar_t*)malloc(sizeof(wchar_t)* rett + 1);
	if (deswcs == nullptr){
		return nullptr;
	}
	if (0 == MultiByteToWideChar(codePage, 0, strIn, -1, deswcs, rett)){
		DWORD err = GetLastError();
		free(deswcs);
		SetLastError(err);
		return nullptr;
	}
	return deswcs;
}

inline static char *msWCsToMBs(const wchar_t *strIn, unsigned int codePage)
{
	int rett = WideCharToMultiByte(codePage, 0, strIn, -1, nullptr, 0, nullptr, nullptr);
	if (rett == 0){
		return nullptr;
	}
	char *descs = (char*)malloc(sizeof(char)* rett + 1);
	if (descs == nullptr){
		return nullptr;
	}
	if (0 == WideCharToMultiByte(codePage, 0, strIn, -1, descs, rett, nullptr, nullptr)){
		DWORD err = GetLastError();
		free(descs);
		SetLastError(err);
		return nullptr;
	}
	return descs;
}

wstring GB2312sToWCs(const char *param)
{
	wchar_t *wcs = msMBsToWCs(param, CP_ACP);
	wstring wret = wcs;
	free(wcs);
	return wret;
}

string WCsToGB2312s(const wchar_t *strIn)
{
	char *tmpcs = msWCsToMBs(strIn, CP_ACP);
	string ret = tmpcs;
	free(tmpcs);
	return ret;
}

wstring UTF8sToWCs(const char *strIn)
{
	wchar_t *tmpwcs = msMBsToWCs(strIn, CP_UTF8);
	wstring ret = tmpwcs;
	free(tmpwcs);
	return ret;
}

string WCsToUTF8s(const wchar_t *strIn)
{
	char *tmpcs = msWCsToMBs(strIn, CP_UTF8);
	string ret = tmpcs;
	free(tmpcs);
	return ret;
}

LPTSTR GenLastErrorStr(LPTSTR lpszFunction, DWORD dw)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)malloc((lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);

	LocalFree(lpMsgBuf);
	//LocalFree(lpDisplayBuf);

	return (LPTSTR)lpDisplayBuf;
}
#else

#endif
