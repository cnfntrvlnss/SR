#ifndef SR_SID_H
#define SR_SID_H

#include "sr.h"

#define SR_MAX_SPECIMEN_DATA_LEN 131072 //128KB; ˵����ʶ��걾����ֽ���
typedef unsigned char SR_SPECIMEN_DATA[SR_MAX_SPECIMEN_DATA_LEN]; //˵����ʶ��걾����
//˵����ʶ��걾
typedef struct _tag_SR_Specimen_
{
	int nLen; //�걾���ݳ��� 
	SR_SPECIMEN_DATA pData; //�걾����
}SR_SPECIMEN, *LPSR_SPECIMEN;

#define SR_MAX_FEA_DATA_LEN 131072 //128KB; ˵����ʶ������������ֽ���
typedef unsigned char SR_FEA_DATA[SR_MAX_FEA_DATA_LEN]; //˵����ʶ����������
//˵����ʶ����������
typedef struct _tag_SR_Fea_ {
	int nLen; //�������ݳ���
	SR_FEA_DATA pData; //��������
}SR_FEA, *LPSR_FEA;

/*!
* \brief ��ʼ������
* \param Dir [in] ���漰�������ڵ�Ŀ¼
* \return �ɹ����������������򷵻�NULL
*/
SR_API SR_HANDLE SR_SID_Init(const SR_FILE& Dir);

/*!
* �ͷ�����
* \param handle [in] ������
*/
SR_API void SR_SID_Release(SR_HANDLE handle);

/*!
* \brief ��ȡ��������Ϣ
* \param handle [in] ������
* \param Error [out] ��������Ϣ
*/
SR_API void SR_SID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/*!
* \brief �걾ѵ��
* \param handle [in] ������
* \param nWavNum [in] ��������
* \param pWavBufs [in] ��������������
* \param pWavFiles [in] ���ɸ������ļ�
* \param Seg [in] ����Ƭ��(Ԥ�����˵���˷��������˹��������)
* \param Specimen [out]  �걾
* \return �ɹ�����true��ʧ�ܷ���false
*/
SR_API bool SR_SID_Train_Bufs(SR_HANDLE handle, 
	int nWavNum, 
	LPSR_WAVBUF pWavBufs,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_SPECIMEN& Specimen);
SR_API bool SR_SID_Train_Files(SR_HANDLE handle,
	int nWavNum,
	LPSR_FILE pWavFiles,
	const CFastList<SR_SEG, SR_SEG&>& Seg, 
	SR_SPECIMEN& Specimen);

/*!
* \brief ˵����������ȡ
* \param handle [in] ������
* \param WavBuf [in] ��������
* \parma Seg [in] ����Ƭ��(˵���˷��������)
* \param Fea1 [out] ˵����1������
* \param Fea2 [out] ˵����2������
* \return �ɹ�����true��ʧ�ܷ���false
* \note 1.���ڶ�̬����õ��Ķ��˵���������ɰ�Seg.nType��ͬ���������
*/
SR_API bool SR_SID_GetFea_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, 
	SR_FEA& Fea1, 
	SR_FEA& Fea2);
SR_API bool SR_SID_GetFea_File(SR_HANDLE handle, 
	const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_FEA& Fea1,
	SR_FEA& Fea2);

/*!
* \brief ˵����������ȡ
* \param handle [in] ������
* \param nSpecimenNum [in]
* \param pSpecimens [in]
* \param Fea1 [in]
* \param Fea2 [in]
* \param FeaFile [in]
* \param nFeaDataOffset [in]
* \param nFeaDataNum [in]
* \param nSexScore1 [out]
* \param nSexScore2 [out]
* \param pnResult [out]
* \return �ɹ�����true��ʧ�ܷ���false
* \note 1.nSexScore1 = INT(�Ա�ʶ������ʵ�ʵ÷֡�10000 + 0.9999)����INT()��ȡ��������
���ǽ�nSexScore1��Ϊint�������͡�
2.nSexScore2 = INT(�Ա�ʶ������ʵ�ʵ÷֡�10000 + 0.9999)
3.���Ա�ʶ������ʵ�ʵ÷֡�Ӧ��һ����0-100���ӽ�0��ʾ���������ӽ�100��ʾ��Ů����
4.nSexScore1��nSexScore2����ȡֵ���壺-1��δʶ��-2��ʶ��ʧ�ܣ� -3��ͯ��
5.SR_SID_CompFea_File()���걾��FeaFile�����ļ��С���ʼλ��ΪnFeaDataOffset��
nFeaDataNum���������бȶԡ�nFeaDataNum = 1��2
*/
SR_API bool SR_SID_CompFea_Buf(SR_HANDLE handle, 
	int nSpecimenNum,
	SR_SPECIMEN* pSpecimens, 
	const SR_FEA& Fea1,
	const SR_FEA& Fea2,
	int& nSexScore1,
	int& nSexScore2,
	int* pnResult); 
SR_API bool SR_SID_CompFea_File(SR_HANDLE handle,
	int nSpecimenDataNum,
	SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile,
	int nFeaDataOffset, 
	int nFeaDataNum,
	int& nSexScore1,
	int& nSexScore2,
	int* pnResult);
#endif