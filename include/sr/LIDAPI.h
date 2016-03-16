/*
2012-10-18 ���±�ǣ�����
*/
#ifndef _LID_TEST_H_
#define _LID_TEST_H_

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////
#define PACMPLID_SUCCESS 				 0			//��ȷ����
#define PACMPLID_FAILURE 				 0x080000	//���󷵻�
#define PACMPLID_STATUS_LESSDATA		 0x020001	//��Ч�������Ȳ���
//���ؽ�����壺������Ϣ
#define PACMPLID_ERROR_EXTRACTFEATURE	 0x010000	//��ȡ��������
#define PACMPLID_ERROR_GETFEATURE		 0x010002	//���������
#define PACMPLID_ERROR_FILEOPEN			 0x010001	//�ļ��޷���
#define PACMPLID_ERROR_FEATUREPARM		 0x010005	//������������ȷ
#define PACMPLID_ERROR_MODELID		     0x010010	//ģ��ID����ȷ
#define PACMPLID_ERROR_MODEPARM		     0x010006	//ģ�Ͳ�������ȷ
///////////////////////////////////////////////////////////////////////////////

/***********************************************************
 �������Ͷ���
 ***********************************************************/

//����������ֲ��������ݽṹ
typedef struct tag_Lid_Lang_Param
{
	int *ipInLangIDs;		//[in] ��ʶ�������ID���б�
	int iInLangCnt;			//[in] ��ʶ������ֵĸ���

	float *fpOutLangCM;		//[out] ʶ��������ֵĿ��Ŷȵ÷�

}LID_LANG_PARAM;


//HANDLE OpenLID(char* szWorkDir, const char **szLangModelPaths,const int *ipLangIDs,int *iIDMap, int iLangCnt);
//void CloseLID(HANDLE hLID);
//HRESULT RunLID(HANDLE hLID, short* pWav, int nLen, float* pScore,int *ipInLangIDs, int iCareLangCnt);
//

//��ʼ������ʶ������
//typedef HANDLE (*fun_OpenLID)(char* szWorkDir, const char **szLangModelPaths,const int *ipLangIDs,int *iIDMap, int iLangCnt);
typedef HANDLE (*fun_OpenLID)(char* szWorkDir, const char **szLangModelPaths, int iLangCnt);
//��һ������ʶ��Ự
typedef HRESULT (*fun_RunLID)(HANDLE hLID, short* pWav, int nLen, float* pScore,int *ipInLangIDs, int iCareLangCnt);
//�ر�һ������ʶ��Ự
typedef void (*fun_CloseLID)(HANDLE hLID);




#endif