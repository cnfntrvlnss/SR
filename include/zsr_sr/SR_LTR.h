#ifndef SR_LTR_H
#define SR_LTR_H

#include "sr.h"

#define SR_MAX_LIDM_NUM 1000 //����ģ�������Ŀ
#define SR_LIDM_NAME_BYTES 40 //����ģ����������ֽ���
#define SR_LIDM_NAME_LEN (SR_LIDM_NAME_BYTES + 1)
typedef SR_CHAR SR_LIDM_NAME_STR[SR_LIDM_NAME_LEN]; //����ģ�������ַ���

//�������ֵ�ѵ������
typedef struct _tag_SR_LTRParam_
{
	SR_UUID_STR chUUID; //����UUID
	SR_LIDM_NAME_STR chName; //��������
	SR_FILE ListFile; //�������������������������б��ļ�����
	CFastList<SR_FILE, SR_FILE&> WavLidfFileList; //���������ļ��б� �� �������������ļ��б�
	SR_FILE chLidFile; //����ģ���ļ�,��ʽΪ"SR_LTRPARAMS.chOutputPath\chUUID_chName.lidm" 
}SR_LTRPARAM, *LPSR_LTRPARAM;

typedef struct _tag_SR_LTRParams_ 
{
	int nInputType; //��������, 1��ʾ����Ϊ�����ļ���2��ʾ����Ϊ�����ļ�(*.ltrf)
	int nThreadNum; //����ѵ�����߳���Ŀ
	SR_FILE OutputPath; //����ʶ��ģ�����Ŀ¼
	int nLtrNum; //������Ŀ, nLtrNum <= SR_MAX_LIDM_NUM
	LPSR_LTRPARAM LTRParams[SR_MAX_LIDM_NUM]; //�������ֵ�ѵ������
}SR_LTRPARAMS, *LPSR_LTRPARAMS;

/**
* ��ʼ������
* \param Dir [in] ���漰�������ڵ�Ŀ¼
* \return �ɹ����������������򷵻�NULL
*/
SR_API SR_HANDLE SR_LTR_Init(const SR_FILE& Dir);

/**
* �ͷ����� 
* \parma handle [in] ������
*/
SR_API void SR_LTR_Release(SR_HANDLE handle);

/**
* ��ȡ��������Ϣ
* \param handle [in] ������
* \param Error [out] ��������Ϣ
*/
SR_API void SR_LTR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* д����ѵ������
* \param LIRParams [in] ����ѵ������
* \param LTRFile [in] ����ѵ�������ļ�����
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_LTR_WriteParams(const SR_LTRPARAMS& LTRParams, const SR_FILE& LTRFile);

/*!
* \brief ������ѵ������
* \param LTRFile [in] ����ѵ�������ļ�
* \param LTRParams [out] ����ѵ������
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_LTR_ReadParams(const SR_FILE& LTRFile, SR_LTRPARAMS& LTRParams);

/*!
* \brief ����ѵ��������ȡ
* \param handle [in] ������ 
* \param WavBuf [in] ��������
* \param WavFile [in] �����ļ�
* \param LtrfFile [in] �����ļ�����
* \return �ɹ�����true, ʧ�ܷ���false
*/
SR_API bool SR_LTR_GetFea_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf,
	const SR_FILE& LtrfFile);
SR_API bool SR_LTR_GetFea_File(SR_HANDLE handle,
	const SR_FILE& WavFile, 
	const SR_FILE& LtrfFile);

/*!
* \brief ����ģ��ѵ��
* \param handle [in] ������
* \param LTRParams [in] ����ѵ������
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_LTR(SR_HANDLE handle, SR_LTRPARAMS& LTRParams);
#endif