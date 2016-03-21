#pragma pack( push, enter_tli_api )
#pragma pack ( 8 )

#ifndef __TLIAPI_HEADER_
#define __TLIAPI_HEADER_ 1

#ifndef _MT
#ifdef WIN32
#error("TLI needs multithreading")
#endif
#endif

#if defined( _WIN32 ) || defined ( _WIN64 )
	#ifdef TLI_API_EXPORTS
		#define TLI_DLL_API __declspec(dllexport)
	#else
		#define TLI_DLL_API __declspec(dllimport)
	#endif
#else
    #define TLI_DLL_API
#endif

typedef int TLI_HANDLE;

/******************************** ����˵�� ***********************************
*F
*F ��������			: TLI_Init
*F ��������			: �����ʼ��
*F ��������			: TLI_DLL_API int
*F ��������			: char * pszTLISystemDirectory	���� ����ģ�ͣ�sysdir��·��
*F					: int * pnAllTemplate			���� ��������������
*F					: char ** ppszAllTemplateLocation ���� ������������
*F					: int nAllTemplateNumber		���� ������
*F					: int nLineNumber				���� �߳���
*F ��������ֵ		: 0							��ʼ���ɹ�; 
*F					: -1							��ʼ��ʧ�ܣ�ģ���ļ�·������
*F					: -2							��ʼ��ʧ�ܣ���Ȩʧ��
*F					: -3							��ʼ��ʧ�ܣ��߳������ô���
*F					: -4							��ʼ��ʧ�ܣ�ģ���ļ�ȱʧ
*F					: -10						��ʼ��ʧ�ܣ���������
*F ����˵��			: ��Ȩ�ļ���Ϊlicense.txt����Ҫ�������棨TLI_API.dll���ļ�����
*F					: ��Ȩ��20
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Init(            
							char * pszTLISystemDirectory,
							int * pnAllTemplateIDs,
							char ** ppszAllTemplateLocation,
							int nAllTemplateNumber,
							int nLineNumber
						);

/******************************** ����˵�� ***********************************
*F
*F ��������			: TLI_Exit
*F ��������			: �����˳�
*F ��������			: TLI_DLL_API int
*F ��������			: �޲���
*F ��������ֵ		: 0							�˳��ɹ�
*F					: -1							�˳�ʧ��
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Exit();

/******************************** ����˵�� ***********************************
*F
*F ��������			: TLI_Open
*F ��������			: ��һ·�̣߳���ȡ�������̵߳ĵľ��
*F ��������			: TLI_DLL_API int
*F ��������			: TLI_HANDLE & hTGID			��� �������̵߳ĵľ��
*F ��������ֵ		: 0							�򿪳ɹ�
*F					: -1							��ʧ��
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Open(
	TLI_HANDLE & hTLI
);

/******************************** ����˵�� ***********************************
*F
*F ��������			: TLI_Close
*F ��������			: �ر�һ·�߳�
*F ��������			: TLI_DLL_API int
*F ��������			: TLI_HANDLE hTGID			���� ���ر��̵߳ľ��
*F ��������ֵ		: 0							�رճɹ�
*F					: -1							�ر�ʧ��
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Close(
	TLI_HANDLE hTLI
);

/******************************** ����˵�� ***********************************
*F
*F ��������			: TLI_Recognize
*F ��������			: ����ʶ��
*F ��������			: TLI_DLL_API int
*F ��������			: TLI_HANDLE hTGID			���� ��ǰ�̵߳ľ��
*F					: int * pnCurrentTemplateIDs	���� ��������������
*F					: int nCurrentTemplateNumber	���� ���ֵ���Ŀ
*F					: void * pvPCMBuffer			���� PCM���ݻ���ָ��
*F					: int nBytesOfBuffer			���� PCM���ݻ����С���ֽ�����
*F					: int nMinLimit				���� PCM����ʱ����С��ֵ������ƣ���ʱ��
*F												С�ڸ���ֵ���ʶ
*F					: int nMaxLimit				���� PCM����ʱ�������ֵ������ƣ���ʱ��
*F												���ڸ���ֵ�Ĳ��ֲ�������
*F ��������ֵ		: 0							ʶ��ɹ�
*F					: -1						�������
*F					: -2						���߳�û�б���ʼ��	
*F					: -3						���б�����ID���������	
*F					: -4						�����ڴ����	
*F					: -5						��������Ƿ�	
*F					: -6						��������̫��	
*F					: -7						VADʧ��	
*F					: -8						VAD����Ч����̫��	
*F					: -9						���ּ��ʧ��
*F					: -10						���ּ�����Ч����̫��	
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Recognize(
	TLI_HANDLE hTLI,
	int * pnCurrentTemplateIDs,
	int nCurrentTemplateNumber,
	void * pvPCMBuffer,
	int nBytesOfBuffer,
	int nMinLimit,
	int nMaxLimit
);

/******************************** ����˵�� ***********************************
*F
*F ��������			: TLI_GetResult
*F ��������			: ��ȡʶ��֮��ĵ÷�
*F ��������			: TLI_DLL_API int
*F ��������			: TLI_HANDLE hTGID			���� ��ǰ�̵߳ľ��
*F					: float * pfResults			��� �÷�����ָ�루��ҪӦ�ó������뻺�棩
*F					: int nNumber					���� �������������ָ���+��ʶ�÷֣�
*F ��������ֵ		: 0							��ȡ�ɹ�
*F					: -1							��ȡʧ��
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_GetResult(
	TLI_HANDLE hTLI,
	float * pfResults,
	int nNumber
);

#endif /* __TLIAPI_HEADER_ */

#pragma pack( pop, enter_tli_api )
/* ///////////////////////// End of file "TLI_API.h" //////////////////////// */
