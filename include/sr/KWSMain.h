/*
2012-10-18 ���±�ǣ�����
*/
#pragma once

#include "SoundFile/SoundFile.h"
#include "LIKWSIntf.h"
#include "publicdef.h"
#include "SRDefine/SR.h"

///////////////////////////////////////////////////////////////////////////////
//�ӿ�
//���ƣ���ʼ������
typedef SR_HANDLE (*fun_SR_KWS_Init)(const SR_FILE& Dir);

//���ƣ��ͷ�����
typedef int (*fun_SR_KWS_Release)(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_KWS_GetLastError()
typedef int (*fun_SR_KWS_GetLastError)(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�����ģ��SR_KWS_LoadMod()
typedef int (*fun_SR_KWS_LoadMod)(SR_HANDLE handle, const SR_FILE& Dir,
    const SR_UUID_STR& LidUUID);

//���ƣ�ѡ��ģ��SR_KWS_UseMod()
typedef int (*fun_SR_KWS_UseMod)(SR_HANDLE handle, const SR_UUID_STR& LidUUID);

//���ƣ��ͷ�ģ��SR_KWS_ReleaseMod()
typedef int (*fun_SR_KWS_ReleaseMod)(SR_HANDLE handle);

//���ƣ���ùؼ�������SR_KWS_GetPhoneme()
typedef int (*fun_SR_KWS_GetPhoneme)(SR_HANDLE handle, SR_WORD& Word);

//���ƣ��ؼ���������ȡSR_KWS_GetFea_...()
typedef int (*fun_SR_KWS_GetFea_Buf)(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int &nFeaBufLen, void* &pFeaBuf);

typedef int (*fun_SR_KWS_GetFea_File)(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int &nFeaBufLen, void* &pFeaBuf);

//���ƣ�����ؼ�������SR_KWS_WriteFea()
typedef int (*fun_SR_KWS_WriteFea)(SR_HANDLE handle, __int64 nFileID,
	int nFeaBufLen, void *pFeaBuf, const SR_FILE& FeaFile);

//���ƣ����ؼ�������SR_KWS_ReadFea()
typedef int (*fun_SR_KWS_ReadFea)(SR_HANDLE handle, const SR_FILE& FeaFile,
    __int64 &nFileID, int &nFeaBufLen, void* &pFeaBuf);

//���ƣ������ؼ�������SR_KWS_AddFeaToIdx_...()
typedef int (*fun_SR_KWS_AddFeaToIdx_Buf)(SR_HANDLE handle,
    __int64 nFileID, int nFeaBufLen, void *pFeaBuf, const SR_FILE& IdxFile);

typedef int (*fun_SR_KWS_AddFeaToIdx_File)(SR_HANDLE handle,
    const SR_FILE& FeaFile, const SR_FILE& IdxFile);

typedef int (*fun_SR_KWS_AddFeaToIdx_Files)(SR_HANDLE handle,
	const CFastList<SR_FILE, SR_FILE&>& FeaFileList, const SR_FILE& IdxFile);

//���ƣ��ؼ��ʼ���SR_KWS_Search_...()
typedef int (*fun_SR_KWS_Search_FeaBuf)(SR_HANDLE handle, short nSearchType, 
    const CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
    const SR_LOGIC_EXP_STR& LogicExp, int nFeaBufLen, void *pFeaBuf, 
    CFastList<SR_SEARCHRST, SR_SEARCHRST&>& SearchRstList);

typedef int (*fun_SR_KWS_Search_FeaFiles)(SR_HANDLE handle, short nSearchType, 
    const CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
    const SR_LOGIC_EXP_STR& LogicExp,
    const CFastList<SR_FILE, SR_FILE&>& FeaFileList,
    CFastList<SR_SEARCHRST, SR_SEARCHRST&>& SearchRstList);

typedef int (*fun_SR_KWS_Search_IdxFiles)(SR_HANDLE handle, short nSearchType, 
    const CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
    const SR_LOGIC_EXP_STR& LogicExp,
    const CFastList<SR_FILE, SR_FILE&>& IdxFileList,
    CFastList<SR_SEARCHRST, SR_SEARCHRST&>& SearchRstList);

//////////////////////////////////////////////////////////////////////////
inline bool CharToUnicode(const char* stdchar, SR_CHAR* srchar, int srsize)
{
	return MultiByteToWideChar(CP_ACP, 0, stdchar, -1, srchar, srsize);
}

inline bool ReadBinaryFile(const char* filename, char*& buffer, int& buffersize)
{
	if (!filename)
		return FALSE;

	FILE* fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		return FALSE;
	}
	fseek(fp, 0, SEEK_END);
	buffersize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = new char[buffersize];
	memset(buffer, 0, buffersize);

	if (!buffer) {
		fclose(fp);
		return FALSE;
	}
	fread(buffer, sizeof(char), buffersize, fp);
	fclose(fp);
	return TRUE;
}

inline bool UnicodeToString(const SR_CHAR* srchar, CString& stdchar)
{
	int size = WideCharToMultiByte(CP_ACP, 0, srchar, -1, NULL, 0, NULL, NULL);
	char *ch = new char[size+1];
	int ret = WideCharToMultiByte(CP_ACP, 0, srchar, -1, ch, size, NULL, NULL);
	if (ret) 
	{
		stdchar = CString(ch);
		delete [] ch;
		return true;
	}
	else 
	{
		stdchar = "";
		delete [] ch;
		return false;
	}
}

class CKWSMain
{
public:
	CKWSMain(void);
	~CKWSMain(void);
public:
	//����dll
	BOOL LoadDLL(CString szDLLType);
	//��ʼ������
	BOOL	Initialize(CString szExePath, CString szSuffix);    
	//�ؼ�������
	int	Index(INT64 nPhoneRecordID, CString strFilePath, CString strExAB, CString& strIdxPath);				
	void	Finalize();
	BOOL	MergeIndex(char** szIdxFileList, int nIdxNum, char* target);
	void	AddIdxFileToList(char** pIdxFilePathList, int nFileCount, CFastList<SR_FILE, SR_FILE&>& IdxFileList);
	BOOL	Search(CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
					SR_LOGIC_EXP_STR& LogicExp,CFastList<SR_FILE, SR_FILE&>& IdxFileList, 
					CFastList<SR_SEARCHRST, SR_SEARCHRST&>& srSearchRst);
	BOOL	SetSearchWordList(
		CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
		LIKWS_WORDSEQ * pWordSeq, int nLogicExpSeqNum, 
		CKWSNode**m_ppKWSNode, int* pnKWSNum,
		CMapStringToOb *m_pMapGUID2Kwords,
		CString& strSortNumber);

	BOOL GetPhoneme(SR_WORD &srKword);


private:
	int					m_nCount;							//�Ѿ������������ļ�����
	CString			m_szDestIndexFile;			//Ŀ�������ļ�						
	int					m_nResNum;	
	CSoundFile	m_SoundFile;
	
	HINSTANCE hDLL_KWS;
	fun_SR_KWS_Init SR_KWS_Init_;
	fun_SR_KWS_Release SR_KWS_Release_;
	fun_SR_KWS_GetLastError SR_KWS_GetLastError_;
	fun_SR_KWS_LoadMod SR_KWS_LoadMod_;
	fun_SR_KWS_UseMod SR_KWS_UseMod_;
	fun_SR_KWS_ReleaseMod SR_KWS_ReleaseMod_;
	fun_SR_KWS_GetPhoneme SR_KWS_GetPhoneme_;
	fun_SR_KWS_GetFea_Buf SR_KWS_GetFea_Buf_;
	fun_SR_KWS_GetFea_File SR_KWS_GetFea_File_;
	fun_SR_KWS_WriteFea SR_KWS_WriteFea_;
	fun_SR_KWS_ReadFea SR_KWS_ReadFea_;
	fun_SR_KWS_AddFeaToIdx_Buf SR_KWS_AddFeaToIdx_Buf_;
	fun_SR_KWS_AddFeaToIdx_File SR_KWS_AddFeaToIdx_File_;
	fun_SR_KWS_AddFeaToIdx_Files SR_KWS_AddFeaToIdx_Files_;
	fun_SR_KWS_Search_FeaBuf SR_KWS_Search_FeaBuf_;
	fun_SR_KWS_Search_FeaFiles SR_KWS_Search_FeaFiles_;
	fun_SR_KWS_Search_IdxFiles SR_KWS_Search_IdxFiles_;

public:
	CString 				m_szSuffix;							//�������ͺ�׺,cn,en,ot(����ڲ�ʹ��)
	SR_HANDLE	m_hKWS;		
	CString				m_szResult;
	int						m_nLangISO;
};

#ifndef _KwsFilter
#define _KwsFilter
//Ŀ���˹�������
class CKwsFilter : public CFilter
{
public:
	CKwsFilter();
	~CKwsFilter();
	virtual BOOL IsMatchCondition(CPhoneRecord * pRecord, int nLangISO=0); 
};
#endif//_KwsFilter