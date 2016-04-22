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
#include <afxmt.h>

#else
#endif
//========================character encodings========================================
wstring GB2312sToWCs(const char *strIn);
string WCsToGB2312s(const wchar_t *strIn);
wstring UTF8sToWCs(const char *strIn);
string WCsToUTF8s(const wchar_t *strIn);

extern wstring (*MBsToWCs) (const char *strIn);
extern string (*WCsToMBs)(const wchar_t *strIn);

//======================file and directory======================================
#if defined(_WIN32) || defined(_WIN64)
#include<io.h>
#include <direct.h>
#define ACCESS(f) _access(f, 0)
#define MKDIR(d) _mkdir(d)
#define PATH_SEP L'\\'

#else
#define PATH_SEPCH L'/'
#include<stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#define ACCESS(f) access(f, 0)
#define MKDIR(d) mkdir(d, S_IRWXU)
#endif

inline wstring Path_GetDir(const wstring &path)
{
	return path.substr(0, path.rfind(PATH_SEP, path.length() - 2));
}

inline wstring Path_GetFName(const wstring &path)
{
	return path.substr(path.rfind(PATH_SEP) + 1);
}

inline wstring Path_JoinPath(const wstring &path1, const wstring &path2)
{
	wchar_t lastc = path1[path1.length() - 1];
	if (lastc != PATH_SEP){
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