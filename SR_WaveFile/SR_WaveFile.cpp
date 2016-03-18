// SR_WaveFile.cpp : 定义 DLL 应用程序的导出函数。
//

#define SR_EXPORTS
#include "common\port_zsr.h"
#include "sr\FastList_Ex.h"
#include "sr/sr.h"
#include "wave\audio.h"

//语音文件访问接口 - 201至 - 300
SR_ERROR g_SR_WF_err = { 0, {'\0'} };
void SR_WF_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{

}

bool SR_WF_ReadWavFile(const SR_FILE& File, SR_WAVBUF& WavBuf)
{
	char *tmpStr = WCsToGB2312s(File.PathName);
	std::string curFile = tmpStr;
	free(tmpStr);
	Wav *retwav = LoadWav(curFile.c_str(), nullptr, 0, 0);
	if (retwav == nullptr){
		return false;
	}
	WavBuf.nWavBufLen = retwav->Len();
	WavBuf.pWavBuf = (short *)malloc(sizeof(short)* retwav->Len());
	memcpy(WavBuf.pWavBuf, (*retwav)[0], sizeof(short)* retwav->Len());
	WavBuf.wf.wFormatTag = WAVE_FORMAT_PCM;
	WavBuf.wf.nSamplesPerSec = retwav->Rate();
	WavBuf.wf.nChannels = 1;

	return true;
}

bool SR_WF_WriteWavFile(const SR_WAVBUF& WavBuf, const SR_FILE& File)
{
	char *tmpStr = WCsToGB2312s(File.PathName);
	std::string curFile = tmpStr;
	free(tmpStr);
	Wav * wav = new PCM();
	wav->SetData(WavBuf.pWavBuf, WavBuf.nWavBufLen, WavBuf.wf.nSamplesPerSec);
	bool retb = wav->Save(curFile.c_str());
	return retb;
}