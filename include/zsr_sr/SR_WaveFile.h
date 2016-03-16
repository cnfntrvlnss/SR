#ifndef SR_WAVEFILE_H
#define SR_WAVEFILE_H
#include "sr.h"

typedef struct _tag_SR_WavBuf_
{
	WAVEFORMATEX wf; //�������ݸ�ʽ ��ǰȡĬ��ֵ 8K, 16BIT, ������, ����PCM����
	int nWavBufLen; //�������ݳ���
	short* pWavBuf; //��������ָ��
}SR_WAVBUF, *LPSR_WAVBUF;

/**
* �������ļ������ݼ������ڴ�, ���Ǳ�׼�ļ���ʽ�������ļ����򡰱�׼��ʽ�������ļ���ת��
* \param File [in] �����ļ�
* \param WavBuf [out] ��������
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_WF_ReadWavFile(const SR_FILE& File, SR_WAVBUF& WavBuf);

/**
* ���ڴ���������ݱ��浽����׼��ʽ�������ļ�����
* \param WavBuf [in] ��������
* \param File [in] �����ļ�
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_WF_WriteWavFile(const SR_WAVBUF& WavBuf, const SR_FILE& File);


#endif //SR_WAVEFILE_H