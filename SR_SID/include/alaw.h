/**********************************************************************************************//**
 * @file		alaw.h
 * @brief		读写 8 比特 A 律量化的 PCM.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/10/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "wav.h"

/**********************************************************************************************//**
 * @class	ALaw
 * @brief	8 比特 A 律量化的 PCM.
 * @note	子类, 不可再次继承.
 **************************************************************************************************/
class ALaw : public Wav
{
public:
    virtual bool Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX);

    virtual bool Save(const char *wavfile, bool headless = false) const;
};