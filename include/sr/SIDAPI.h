/*
2012-10-18 ���±�ǣ�����
*/
#include <windows.h>
//////////////////////////////////////////////////////////////////////////////
#define PACMPSID_SUCCESS 				 0			//��ȷ����
#define PACMPSID_FAILURE 				 0x080000	//���󷵻�
#define PACMPSID_STATUS_LESSDATA		 0x020001	//��Ч�������Ȳ���
//���ؽ�����壺������Ϣ
#define PACMPSID_ERROR_EXTRACTFEATURE	 0x010000	//��ȡ��������
#define PACMPSID_ERROR_GETFEATURE		 0x010002	//���������
#define PACMPSID_ERROR_FILEOPEN			 0x010001	//�ļ��޷���
#define PACMPSID_ERROR_FEATUREPARM		 0x010005	//������������ȷ
#define PACMPSID_ERROR_MODESID		     0x010010	//ģ��ID����ȷ
#define PACMPSID_ERROR_MODEPARM		     0x010006	//ģ�Ͳ�������ȷ
///////////////////////////////////////////////////////////////////////////////
//�����½ӿ�
//���ƣ���ʼ������
typedef SR_HANDLE (*fun_SR_SID_Init)(const SR_FILE& Dir);

//���ƣ��ͷ�����
typedef int (*fun_SR_SID_Release)(SR_HANDLE handle);

//���ƣ�˵����������ȡ
typedef int (*fun_SR_SID_GetFea_File)(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2);

//˵���˸��������ȶ�
typedef int  (*fun_SR_SID_CompFea_AdditionalBuf)(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	const SR_ADDITIONAL_FEA& AdditionalFea1, const SR_ADDITIONAL_FEA& AdditionalFea2, 
	int* pnResult);

//˵����Ĭ�������ȶ�
typedef int  (*fun_SR_SID_CompFea_DefaultBuf)(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2, 
	int* pnResult);

//�걾ѵ��
typedef int (*fun_SR_SID_Train_Files)(SR_HANDLE handle, int nCount, SR_FILE* pWavFiles, 
	const CFastList<SR_SEG, SR_SEG&>& Seg,SR_SPECIMEN& pSpecimens);

 
typedef int(*fun_SR_SID_Train_SummedFiles)(SR_HANDLE handle, int nWavNum,
	LPSR_FILE pWavFiles, CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_SPECIMEN& Specimen, SR_FILE& dir);
//һ����ȡ��·�����걾�ȶԵ÷�
typedef int (*fun_SR_SID_GetScr_File)(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	int* pnResult);
