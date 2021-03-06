#define SR_EXPORTS
#include "common\port_zsr.h"
#include "sr\FastList_Ex.h"
#include "sr\sr.h"

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#define MAX_LINE_LENGTH 2048

#define MYFATAL(FORMAT, ...) FPRINTF(stderr, _T("FATAL: ") FORMAT _T("\n"), ##__VA_ARGS__); system("pause"); exit(1);
#define MYERROR(FORMAT, ...) fwprintf(stderr, _T("ERROR: ") FORMAT _T("\n"), ##__VA_ARGS__);

//errno: 文件列表访问接口 -401 至 - 500
SR_ERROR g_fileList_err = { 0, {'\0'} };

void SR_FL_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{
	Error.nError = g_fileList_err.nError;
	Error.chError;
	STRCPY(Error.chError, g_fileList_err.chError);
}

bool SR_FL_WriteListFile(const CFastList<SR_FILE, SR_FILE&>& FileList, const SR_FILE& File)
{
	char bsPath[MAX_PATH];
	//wcstombs(bsPath, File.PathName, SR_MAX_PATHNAME_LEN);
	string strFile = WCsToGB2312s(File.PathName);
	strncpy(bsPath, strFile.c_str(), MAX_PATH);
	FILE *fp = fopen(bsPath, "wt");
	if (fp == NULL){
		MYERROR(_T("fail to open file %ls"), File.PathName);
		return false;
	}
	POSITION pos = FileList.GetHeadPosition();
	for (unsigned i = 0; i < FileList.GetCount(); i++)
	{
		string tmpStr = WCsToUTF8s(FileList.GetNext(pos).PathName);
		fprintf(fp, "%s\n", tmpStr.c_str());
	}
	fclose(fp);
	return true;
}
bool SR_FL_ReadListFile(const SR_FILE& File, CFastList<SR_FILE, SR_FILE&>& FileList)
{
	char bsFile[MAX_PATH];
	//wcstombs(bsFile, File.PathName, SR_MAX_PATHNAME_LEN);
	string strFile = WCsToGB2312s(File.PathName);
	strncpy(bsFile, strFile.c_str(), MAX_PATH);
	FILE *fd = fopen(bsFile, "rt");
	if (fd == NULL){
		MYERROR(_T("fail to open file %ls"), File.PathName);
		return false;
	}
	SR_FILE curFile;
	char tmpStr[SR_MAX_PATHNAME_LEN +1];
	tmpStr[SR_MAX_PATHNAME_LEN] = '\0';
	while (fgets(tmpStr, SR_MAX_PATHNAME_LEN, fd) != NULL){
		int lastIdx = strlen(tmpStr) - 1;
		while (lastIdx >=0 && strchr(" \t\r\n", tmpStr[lastIdx]) != NULL){
			tmpStr[lastIdx] = '\0';
			lastIdx--;
		}
		if (lastIdx < 0) continue;
		wstring tmpWStr = UTF8sToWCs(tmpStr);
		wcsncpy(curFile.PathName, tmpWStr.c_str(), SR_MAX_PATHNAME_LEN);
		FileList.AddTail(curFile);
	}
	return true;
}
