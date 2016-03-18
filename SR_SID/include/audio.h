/**********************************************************************************************//**
 * @file		audio.h
 * @brief		����Ƶ����з�װ.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/10/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 * @note		֧�ֵĸ�ʽ��: 1) 16 �������������� PCM; 2) 8 ���� A �������� PCM; 3) 8 ���� U �������� PCM.
 **************************************************************************************************/
#pragma once
#include "wav.h"
#include "pcm.h"
#include "alaw.h"
#include "ulaw.h"

/**********************************************************************************************//**
 * @enum	WavFmt
 * @brief	�����ʽ.
 **************************************************************************************************/
enum WavFmt
{
    pcm = 0x0001,
    alaw = 0x0006,
    ulaw = 0x0007
};

/**********************************************************************************************//**
 * @fn		Wav * LoadWav(const char *wavfile, WavFmt *wavfmt, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX);
 * @brief	������Ƶ.
 * @return	�ɹ�������Ƶ����, ʧ�ܷ��� NULL.
 * @param [in]	wavfile		��Ƶ·��.
 * @param [in]	wavfmt		��Ƶ��ʽ, NULL ��ʾ�Զ����.
 * @param [in]	smprate		������, �� wavfmt != NULL ʱ����Ч.
 * @param [in]	numchls		ͨ����, �� wavfmt != NULL ʱ����Ч.
 * @param [in]	headcut		��ͷ, ��.
 * @param [in]	tailcut		ȥβ, ��.
 * @param [in]	minproc		��̴���ʱ��, ��.
 * @param [in]	maxproc		�����ʱ��, ��.
 * @note	�� wavfmt != NULL ʱ, ��Ϊ��Ƶ�ļ���ͷ.
 **************************************************************************************************/
Wav * LoadWav(const char *wavfile, WavFmt *wavfmt, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX);

/**********************************************************************************************//**
 * @fn		bool SaveWav(const char *wavfile, const Wav *wav, const WavFmt &wavfmt, bool headless = false);
 * @brief	������Ƶ.
 * @return	�ɹ����� true, ʧ�ܷ��� false.
 * @param [in]	wavfile 	��Ƶ·��.
 * @param [in]	wav			��Ƶ����.
 * @param [in]	wavfmt  	��Ƶ��ʽ.
 * @param [in]	headless	"true/false" ��ʾ"��ͷ/��ͷ".
 **************************************************************************************************/
bool SaveWav(const char *wavfile, const Wav *wav, const WavFmt &wavfmt, bool headless = false);

/**********************************************************************************************//**
 * @fn		void FreeWav(Wav *&wav);
 * @brief	�ͷ���Ƶ����ռ�õ��ڴ�.
 * @param [in,out]	wav		��Ƶ����.
 **************************************************************************************************/
void FreeWav(Wav *&wav);