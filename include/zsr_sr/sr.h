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


/*语音数据格式*/
//Wave格式WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
//语音格式WAVEFORMATEX
typedef struct _tag_WAVEFORMATEX_ 
{
	unsigned short wFormatTag; //格式类型。默认值：WAVE_FORMAT_PCM 
	unsigned short nChannels; //声道数目。默认值：1（单声道）
	unsigned __int32 nSamplesPerSec; //采样频率。默认值：8000Hz
	unsigned __int32 nAvgBytesPerSec;//平均每秒字节数。默认值：16000字节。 
	unsigned short nBlockAlign; //块尺寸。单声道语音该值为2。
	unsigned short wBitsPerSample; //采样位数。默认值：16位 
	unsigned short cbSize; //cbSize后面扩展信息字节数。
}WAVEFORMATEX, *LPWAVEFORMATEX;
//语音格式WAVEFORMAT
typedef struct waveformat_tag 
{
	unsigned short wFormatTag; //格式类型。
	unsigned short nChannels; //声道数目。
	unsigned __int32 nSamplesPerSec; //采样频率。
	unsigned __int32 nAvgBytesPerSec; //平均每秒字节数。 
	unsigned short nBlockAlign; //块尺寸。单声道语音该值为2
}WAVEFORMAT; 
typedef WAVEFORMAT *PWAVEFORMAT; 
//typedef WAVEFORMAT NEAR *NPWAVEFORMAT; 
//typedef WAVEFORMAT FAR *LPWAVEFORMAT;
typedef struct pcmwaveformat_tag 
{
	WAVEFORMAT wf;
	unsigned short wBitsPerSample; //采样位数。
}PCMWAVEFORMAT; 
typedef PCMWAVEFORMAT *PPCMWAVEFORMAT;
//typedef PCMWAVEFORMAT NEAR *NPPCMWAVEFORMAT;
//typedef PCMWAVEFORMAT FAR *LPPCMWAVEFORMAT;


/*引擎通用定义*/
#define SR_HANDLE unsigned int  //引擎句柄SR_HANDLE
#define SR_UUID_BYTES 32 //UUID字符串长度
#define SR_UUID_CHAR_LEN (SR_UUID_BYTES + 1)
typedef SR_CHAR SR_UUID_STR[SR_UUID_CHAR_LEN]; //UUID字符串SR_UUID_STR

#define SR_MAX_ERROR_CHAR_BYTES 255 //错误信息最大长度
#define SR_MAX_ERROR_CHAR_LEN (SR_MAX_ERROR_CHAR_BYTES + 1)
#ifndef _SR_ERROR_ 
#define _SR_ERROR_ 
typedef struct _tag_SR_Error_ 
{
	int nError; //nError的取值规范ref 71页
	SR_CHAR chError[SR_MAX_ERROR_CHAR_LEN];
}SR_ERROR, *LPSR_ERROR; 
#endif //_SR_ERROR_

/*文件列表数据及列表文件访问接口SR_FileList.DLL*/
//#include "SR_FileList.h"

/*语音数据及语音文件访问接口SR_WaveFile.DLL*/
//#include "SR_WaveFile.h"

/*语音片段数据及语音片段文件访问接口SR_SpeechSeg.DLL*/
//#include "SR_SpeechSeg.h"


#endif //SR_H