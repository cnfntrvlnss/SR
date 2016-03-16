#ifndef SR_SSC_H
#define SR_SSC_H

#include "sr.h"

/**
* ��ʼ������
* \param pDir [in] ���漰�������ڵ�Ŀ¼
* \return �ɹ����������������򷵻�NULL
*/
SR_API SR_HANDLE SR_SSC_Init(const SR_FILE& Dir);

/**
* �ͷ�����
* \param handle [in] ������
*/
SR_API void SR_SSC_Release(SR_HANDLE handle);

/**
* ��ȡ��������Ϣ
* \param handle [in] ������
* \param Error [out] ��������Ϣ
*/
SR_API void SR_SSC_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* ˵���˷���
* \param handle [in] ������
* \param WavBuf [in] ��������
* \param WavFile [in] �����ļ�
* \param nType [in] ����ģʽ
* \param SegIn [in] ����Ƭ��(Ԥ������)
* \param SegOut [out] ����Ƭ��(˵���˷�����)
* \return �ɹ�����true��ʧ�ܷ���false
* \note:  1.����ģʽnType��ȡֵ��Χ:
-1 - �绰���������з��루˵������Ŀ��Ϊ0��1��2��;
-2 - ��ȷ��˵������Ŀ�Ķ�̬����;
>0 - ָ����˵������Ŀ
*/
SR_API bool SR_SSC_Seg_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);
SR_API bool SR_SSC_Seg_File(SR_HANDLE handle,
	const SR_FILE& WavFile,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);

/**
* ˵���˾���
* \param handle [in] ������
* \param WavBuf [in]  ������������
* \param WavFile [in] ���������ļ�
* \param nWavNum [in] �������ݵĶ����������ļ��ĸ���
* \param pWavBufs [in] ���ɶ���������
* \param pWavFiles [in] ���ɸ������ļ�
* \param nType [in] ����ģʽ
* \param SegIn [in] ����Ƭ��(˵���˷�����)
* \param SegOut [out] ����Ƭ��(˵���˾�����)
* \return �ɹ�����true��ʧ�ܷ���false
* \note: 1.����ģʽnType��ȡֵ��Χ��
-1 - �绰���������о��ࣨ˵������Ŀ��Ϊ0��1��2��
-2 - ��ȷ��˵������Ŀ�Ķ�̬����
-3 - �Զ������������������ڲ����绰���������о��࣬��������֮�䰴��ȷ��˵������Ŀ�Ķ�̬����
>0 - ָ����˵������Ŀ
*/
SR_API bool SR_SSC_Clst_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf, 
	int nType, const CFastList<SR_SEG, SR_SEG&>& SegIn, 
	CFastList<SR_SEG, SR_SEG&>& SegOut);
SR_API bool SR_SSC_Clst_File(SR_HANDLE handle,
	const SR_FILE& WavFile,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut); 
SR_API bool SR_SSC_Clst_Bufs(SR_HANDLE handle,
	int nWavNum,
	LPSR_WAVBUF pWavBufs,
	int nType, 
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);
SR_API bool SR_SSC_Clst_Files(SR_HANDLE handle, 
	int nWavNum,
	LPSR_FILE pWavFiles,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);
#endif