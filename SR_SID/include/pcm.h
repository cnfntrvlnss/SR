/**********************************************************************************************//**
 * @file		pcm.h
 * @brief		��д 16 �������������� PCM.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/10/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 **************************************************************************************************/
#pragma once
#include "wav.h"

/**********************************************************************************************//**
 * @class	PCM
 * @brief	16 �������������� PCM
 * @note    ����, �����ٴμ̳�.
 **************************************************************************************************/
class PCM : public Wav
{
public:
    virtual bool Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX);

    virtual bool Save(const char *wavfile, bool headless = false) const;
};