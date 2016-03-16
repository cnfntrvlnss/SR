/**********************************************************************************************//**
* @file			audio.h
* @brief		读写音频.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
* @note			支持的格式有: 1) 16 比特量化的线性 PCM; 2) 8 比特 A 律量化的 PCM; 3) 8 比特 U 律量化的 PCM.
**************************************************************************************************/
#pragma once
#include "wav.h"
#include "pcm.h"
#include "alaw.h"
#include "ulaw.h"


/**********************************************************************************************//**
 * @enum	WavFmt
 * @brief	编码格式.
 **************************************************************************************************/
enum class WavFmt : unsigned short
{
    pcm = 0x0001,
    alaw = 0x0006,
    ulaw = 0x0007
};


/**********************************************************************************************//**
 * @fn		Wav *LoadWav( const char *wavfile, WavFmt *wavfmt, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX );
 * @brief	加载音频.
 * @return	成功返回音频对象, 失败返回 nullptr.
 * @param [in]	wavfile		音频路径.
 * @param [in]	wavfmt		音频格式, nullptr 表示自动检测.
 * @param [in]	smprate		采样率, 当 wavfmt != nullptr 时才有效.
 * @param [in]	numchls		通道数, 当 wavfmt != nullptr 时才有效.
 * @param [in]	headcut		掐头, 秒.
 * @param [in]	tailcut		去尾, 秒.
 * @param [in]	minproc		最短处理时长, 秒.
 * @param [in]	maxproc		最长处理时长, 秒.
 * @note	当 wavfmt != nullptr 时, 认为音频文件无头.
 **************************************************************************************************/
Wav *LoadWav(const char *wavfile, WavFmt *wavfmt, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX);


/**********************************************************************************************//**
 * @fn		bool SaveWav( const char *wavfile, const Wav *wav, const WavFmt &wavfmt, bool headless = false );
 * @brief	保存音频.
 * @return	成功返回 true, 失败返回 false.
 * @param [in]	wavfile 	音频路径.
 * @param [in]	wav			音频对象.
 * @param [in]	wavfmt  	音频格式.
 * @param [in]	headless	"true/false" 表示"无头/有头".
 **************************************************************************************************/
bool SaveWav(const char *wavfile, const Wav *wav, const WavFmt &wavfmt, bool headless = false);


/**********************************************************************************************//**
 * @fn		void FreeWav( Wav *&wav );
 * @brief	释放音频对象占用的内存.
 * @param [in,out]	wav		音频对象.
 **************************************************************************************************/
void FreeWav(Wav *&wav);