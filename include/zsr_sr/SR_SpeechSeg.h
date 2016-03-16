#ifndef SR_SPEECHSEG_H
#define SR_SPEECHSEG_H

#include "cfastlist.h"
#include "sr.h"

/**
*
* \note 
1) ����Ƭ�εĲ����㷶Χ��[nStart, nEnd)��
2) ����Ƭ������nType�������£�С�ڵ���-10��������-9���ϳ�������-8������Ա��ʾ����
-7�������򺬽�ǿ������������-6����������-5��ת�Ӳ�������-4����������
-3������������������-2����Ĭ��-1����Ч��������ʼֵ����0����Ч������
���ڵ���0��˵������š�
3) ����Ƭ�δ�����״̬nState�������£�0-ɾ������Դ���1-��������봦��
*/
typedef struct _tag_SR_Seg_
{
	__int64 nFileID;//����Ƭ�������ļ����
	int nStart; //����Ƭ�β��������
	int nEnd; //����Ƭ�β������յ� 
	int nType; //����Ƭ������ 
	int nState; //����Ƭ�δ�����״̬
}SR_SEG, *LPSR_SEG;

/**
* ��ȡ��������Ϣ
* \handle [in] ������
* \Error [out] ��������Ϣ
*/
SR_API void SR_SS_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* ������Ƭ���ļ������ݼ������ڴ�
* \param File [in] ����Ƭ���ļ�
* \param Seg [out] ����Ƭ������
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_SS_ReadSegFile(const SR_FILE& File, CFastList<SR_SEG, SR_SEG&>& Seg);

/**
* ���ڴ������Ƭ�����ݱ��浽����Ƭ���ļ���
* \param Seg [in] ����Ƭ������
* \param File [in] ����Ƭ���ļ�
* \return �ɹ�����true, ʧ�ܷ���false
*/
SR_API bool SR_SS_WriteSegFile(const CFastList<SR_SEG, SR_SEG&>& Seg, const SR_FILE& File);

/**
* ���ݡ�����Ƭ�Ρ��ϲ����������ݡ�
* \param WavBufIn [in] ������������
* \param Seg [in] ��Ҫ����������Ƭ��
* \param WavBufOut [out] ���������Ƭ�Ρ���Ӧ�ġ��������ݡ��ϲ���ġ��������ݡ�
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_SS_MergeSegWavBuf(const SR_WAVBUF& WavBufIn,
	const CFastList<SR_SEG, SR_SEG&>& Seg, 
	SR_WAVBUF& WavBufOut);

/**
* �ԡ���������������Ƭ�ξ���ֵ��AllAbsSeg����Ϊ�ο���
���㡰�ָ�����������Ƭ�����ֵ��SegOppSeg����
��Ӧ�ġ��ָ�����������Ƭ�ξ���ֵ��SegAbsSeg����
* \param AllAbsSeg [in] ��������������Ƭ�ξ���ֵ
* \param SegOppSeg [in] �ָ�����������Ƭ�����ֵ
* \param SegAbsSeg [out] �ָ�����������Ƭ�ξ���ֵ
*/
SR_API bool SR_SS_CalSegOffset(const CFastList<SR_SEG,
	SR_SEG&>& AllAbsSeg,
	const CFastList<SR_SEG, SR_SEG&>& SegOppSeg,
	CFastList<SR_SEG, SR_SEG&>& SegAbsSeg);


#endif
