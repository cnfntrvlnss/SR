/**********************************************************************************************//**
 * @file		alaw.h
 * @brief		��д 8 ���� A �������� PCM.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/10/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 **************************************************************************************************/
#pragma once
#include "wav.h"

/**********************************************************************************************//**
 * @class	ALaw
 * @brief	8 ���� A �������� PCM.
 * @note	����, �����ٴμ̳�.
 **************************************************************************************************/
class ALaw : public Wav
{
public:
    virtual bool Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX);

    virtual bool Save(const char *wavfile, bool headless = false) const;
};