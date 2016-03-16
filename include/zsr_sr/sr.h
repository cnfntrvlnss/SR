#ifndef SR_H
#define SR_H

#include "unicodec.h"

#ifdef SR_EXPORTS 
#define SR_API 
extern "C" __declspec(dllexport)
#else 
#define SR_API 
extern "C" __declspec(dllimport)
#endif


/*�������ݸ�ʽ*/
//Wave��ʽWAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
//������ʽWAVEFORMATEX
typedef struct _tag_WAVEFORMATEX_ 
{
	unsigned short wFormatTag; //��ʽ���͡�Ĭ��ֵ��WAVE_FORMAT_PCM 
	unsigned short nChannels; //������Ŀ��Ĭ��ֵ��1����������
	unsigned __int32 nSamplesPerSec; //����Ƶ�ʡ�Ĭ��ֵ��8000Hz
	unsigned __int32 nAvgBytesPerSec;//ƽ��ÿ���ֽ�����Ĭ��ֵ��16000�ֽڡ� 
	unsigned short nBlockAlign; //��ߴ硣������������ֵΪ2��
	unsigned short wBitsPerSample; //����λ����Ĭ��ֵ��16λ 
	unsigned short cbSize; //cbSize������չ��Ϣ�ֽ�����
}WAVEFORMATEX, *LPWAVEFORMATEX;
//������ʽWAVEFORMAT
typedef struct waveformat_tag 
{
	unsigned short wFormatTag; //��ʽ���͡�
	unsigned short nChannels; //������Ŀ��
	unsigned __int32 nSamplesPerSec; //����Ƶ�ʡ�
	unsigned __int32 nAvgBytesPerSec; //ƽ��ÿ���ֽ����� 
	unsigned short nBlockAlign; //��ߴ硣������������ֵΪ2
}WAVEFORMAT; 
typedef WAVEFORMAT *PWAVEFORMAT; 
//typedef WAVEFORMAT NEAR *NPWAVEFORMAT; 
//typedef WAVEFORMAT FAR *LPWAVEFORMAT;
typedef struct pcmwaveformat_tag 
{
	WAVEFORMAT wf;
	unsigned short wBitsPerSample; //����λ����
}PCMWAVEFORMAT; 
typedef PCMWAVEFORMAT *PPCMWAVEFORMAT;
//typedef PCMWAVEFORMAT NEAR *NPPCMWAVEFORMAT;
//typedef PCMWAVEFORMAT FAR *LPPCMWAVEFORMAT;


/*����ͨ�ö���*/
#define SR_HANDLE unsigned int  //������SR_HANDLE
#define SR_UUID_BYTES 32 //UUID�ַ�������
#define SR_UUID_CHAR_LEN (SR_UUID_BYTES + 1)
typedef SR_CHAR SR_UUID_STR[SR_UUID_CHAR_LEN]; //UUID�ַ���SR_UUID_STR

#define SR_MAX_ERROR_CHAR_BYTES 255 //������Ϣ��󳤶�
#define SR_MAX_ERROR_CHAR_LEN (SR_MAX_ERROR_CHAR_BYTES + 1)
#ifndef _SR_ERROR_ 
#define _SR_ERROR_ 
typedef struct _tag_SR_Error_ 
{
	int nError; //nError��ȡֵ�淶ref 71ҳ
	SR_CHAR chError[SR_MAX_ERROR_CHAR_LEN];
}SR_ERROR, *LPSR_ERROR; 
#endif //_SR_ERROR_

/*�ļ��б����ݼ��б��ļ����ʽӿ�SR_FileList.DLL*/
//#include "SR_FileList.h"

/*�������ݼ������ļ����ʽӿ�SR_WaveFile.DLL*/
//#include "SR_WaveFile.h"

/*����Ƭ�����ݼ�����Ƭ���ļ����ʽӿ�SR_SpeechSeg.DLL*/
//#include "SR_SpeechSeg.h"


#endif //SR_H