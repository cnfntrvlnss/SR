#define SR_EXPORTS
#include "common/port_zsr.h"
#include "sr/FastList_Ex.h"
#include "sr/sr.h"

#define LANGNAMELEN 30
typedef wchar_t(*PWCHARARR)[LANGNAMELEN];
unsigned *g_uTemplateNum;

static SR_ERROR g_SR_LID_Error;

static bool LoadLangList(const wchar_t *strLangList, unsigned *ptrTemplateNum, PWCHARARR &ptrLangNameArr)//给全局变量赋初值
{
	struct LangPair
	{
		char ID[3];
		char LangName[28];
	};
	FILE *fpList;
	string tmpPath = WCsToGB2312s(strLangList);
	if (!(fpList = fopen(tmpPath.c_str(), "rb")))
	{
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES,  L"failed to open file %ls", strLangList);
		return false;
	}
	char Line[256];
	int nLangNum = 0;
	while (!feof(fpList))
	{
		if (!fgets(Line, 256, fpList))
		{
			continue;
		}
		int len = strlen(Line) - 1;
		while (Line[len] == '\r' || Line[len] == '\n')
		{
			Line[len--] = '\0';
		}
		if (strlen(Line) == 0) continue;
		nLangNum++;
	}
	fseek(fpList, 0L, SEEK_SET);
	LangPair *pLangPair;
	pLangPair = new LangPair[nLangNum];
	char seps[] = " \t";
	char *token;
	int i = 0;
	while (!feof(fpList))
	{
		if (!fgets(Line, 256, fpList))
		{
			continue;
		}
		int len = strlen(Line) - 1;
		while (Line[len] == '\r' || Line[len] == '\n')
		{
			Line[len--] = '\0';
		}
		token = NULL;
		if (strlen(Line) == 0)
			continue;
		token = strtok(Line, seps);
		strcpy(pLangPair[i].ID, token);
		token = strtok(NULL, seps);
		strcpy(pLangPair[i].LangName, token);
		i++;
	}
	fclose(fpList);

	*ptrTemplateNum = nLangNum;
	ptrLangNameArr = static_cast<PCHARARR>(malloc((nLangNum + 1) * sizeof(char[LANGNAMELEN])));
	for (i = 0; i<nLangNum; i++)
	{
		 strcpy(ptrLangNameArr[i], pLangPair[i].LangName);
	}
	strcpy(ptrLangNameArr[nLangNum], "others");
	delete pLangPair;
	return true;
}
//=====================================SR functions====================================
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{
	return;
}

SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir)
{
	wstring langListFile = Path_JoinPath(Dir.PathName, L"lang.list");

	return (SR_HANDLE)0;
}

SR_API void SR_LID_Release(SR_HANDLE handle)
{
	return;
}

SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts)
{
	return false;
}

SR_API bool SR_LID_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts)
{
	return false;
}