#ifndef PORT_ZSR__H
#define PORT_ZSR__H
#include <string>
using std::string;
using std::wstring;
/*
typedef struct{} *POSITION;
typedef unsigned short WORD;
typedef unsigned long DWORD;
#define NEAR
#define FAR
*/
#if defined(_WIN32) || defined(_WIN64)
#include <afx.h>

#endif
//========================character encodings========================================
wstring GB2312sToWCs(const char *strIn);
string WCsToGB2312s(const wchar_t *strIn);
wstring UTF8sToWCs(const char *strIn);
string WCsToUTF8s(const wchar_t *strIn);


//======================file and directory======================================
#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEP L'\\'

#else
#define PATH_SEPCH L'/'

#endif

wstring Path_GetDir(const wstring &path)
{
	return path.substr(0, path.rfind(PATH_SEP));
}

inline wstring Path_GetFName(const wstring &path)
{
	return path.substr(path.rfind(PATH_SEP) + 1);
}

inline wstring Path_JoinPath(const wstring &path1, const wstring &path2)
{
	char lastc = path1[path1.length() - 1];
	if (lastc == PATH_SEP){
		return path1 + PATH_SEP + path2;
	}
	else{
		return path1 + path2;
	}
}

/**
对本模块的函数错误情况集中由此函数获取。
*/
const char* getLastErrorStr();


#endif