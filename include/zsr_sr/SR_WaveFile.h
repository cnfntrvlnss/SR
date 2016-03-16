#ifndef SR_WAVEFILE_H
#define SR_WAVEFILE_H
#include "sr.h"

typedef struct _tag_SR_WavBuf_
{
	WAVEFORMATEX wf; //语音数据格式 当前取默认值 8K, 16BIT, 单声道, 线性PCM编码
	int nWavBufLen; //语音数据长度
	short* pWavBuf; //语音数据指针
}SR_WAVBUF, *LPSR_WAVBUF;

/**
* 将语音文件的数据加载至内存, “非标准文件格式的语音文件”向“标准格式的语音文件”转换
* \param File [in] 语音文件
* \param WavBuf [out] 语音数据
* \return 成功返回true；失败返回false
*/
SR_API bool SR_WF_ReadWavFile(const SR_FILE& File, SR_WAVBUF& WavBuf);

/**
* 将内存的语音数据保存到“标准格式的语音文件”中
* \param WavBuf [in] 语音数据
* \param File [in] 语音文件
* \return 成功返回true；失败返回false
*/
SR_API bool SR_WF_WriteWavFile(const SR_WAVBUF& WavBuf, const SR_FILE& File);


#endif //SR_WAVEFILE_H