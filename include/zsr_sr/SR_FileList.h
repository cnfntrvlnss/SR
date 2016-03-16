#ifndef SR_FILELIST_H
#define SR_FILELIST_H

#include "sr.h"
#include "cfastlist.h"

#define SR_MAX_PATHNAME_BYTES 255
#define SR_MAX_PATHNAME_LEN (SR_MAX_PATHNAME_BYTES + 1) //�ļ�����󳤶�

typedef struct _tag_SR_FILE_ 
{ 
	SR_CHAR PathName[SR_MAX_PATHNAME_LEN];
}SR_FILE, *LPSR_FILE;

/**
* ��ȡ��������Ϣ
* \param handle [in] ������
* \param Error  [out] ��������Ϣ
*/
SR_API void SR_FL_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* ���б��ļ������ݼ������ڴ�
* \param File [in] �б��ļ�
* \FileList [out] ָ���ļ��б��ָ��
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_FL_ReadListFile(const SR_FILE& File, CFastList<SR_FILE, SR_FILE&>& FileList);

/**
* ���ڴ���ļ��б��浽�б��ļ���
* \param FileList [in] ָ���ļ��б��ָ��
* \param File [out] �б��ļ�
* \return �ɹ�����true, ʧ�ܷ���false
*/
SR_API bool SR_FL_WriteListFile(const CFastList<SR_FILE, SR_FILE&>& FileList,
	const SR_FILE& File);
#endif


