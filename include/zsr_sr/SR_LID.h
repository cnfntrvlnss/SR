#ifndef SR_LID_H
#define SR_LID_H

#include "sr.h"
#include "cfastlist.h"

#define SR_MAX_LIDM_NUM 1000 //����ģ�������Ŀ
#define SR_LIDM_NAME_BYTES 40 //����ģ������ֽ���
#define SR_LIDM_NAME_LEN (SR_LIDM_NAME_BYTES + 1)
typedef SR_CHAR SR_LIDM_NAME_STR[SR_LIDM_NAME_LEN];//����ģ�������ַ���

typedef struct _tag_SR_LID_Rst_
{
	SR_UUID_STR chUUID; //����UUID
	SR_LIDM_NAME_STR chName; //��������
	int nLIDScore;  //���Ŷȵ÷� INT(score X1000 + 0.9999)

}SR_LIDRST, *LPSR_LIDRST;

typedef struct _tag_SR_LID_Rsts_
{
	int nRstNum;
	SR_LIDRST LIDRst[SR_MAX_LIDM_NUM];
}SR_LIDRSTS, *LPSR_LIDRSTS;

/**
* ��ʼ������
* \param Dir [in] ���漰�������ڵ�Ŀ¼
* \return �ɹ����������������򷵻�NULL
*/
SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir);

/**
* �ͷ�����
* \param handle [in] ������
*/
SR_API void SR_LID_Release(SR_HANDLE handle);

/**
* ��ȡ���Ĵ���.
* \param [in] ������
* \param [out] ��������Ϣ
*/
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* ����ʶ��
* \param handle [in] ������
* \param WavBuf [in] ��������
* \param WavFile [in] �����ļ�
* \param Seg    [in] ����Ƭ��(Ԥ������)
* \param LidRsts [in] ������ʶ����
* \return �ɹ�����true; ʧ�ܷ���false.
*/
SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);
SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);


#endif
