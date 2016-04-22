/**********************************************************************************************//**
* @file			pcm.h
* @brief		读写 16 比特量化的线性 PCM.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
**************************************************************************************************/
#pragma once
#include "wav.h"


/**********************************************************************************************//**
* @class	PCM
* @brief	16 比特量化的线性 PCM
* @details	子类, 不可再次继承.
**************************************************************************************************/
class PCM : public Wav
{
public:
    virtual bool Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX) override;

    virtual bool Save(const char *wavfile, bool headless = false) const override;
};