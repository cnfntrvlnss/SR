/**********************************************************************************************//**
* @file			wav.cpp
* @brief		读写音频.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
**************************************************************************************************/
#include "wav.h"
#include <stdlib.h>


Wav::Wav() : m_wav_buf(nullptr), m_wav_len(0), m_smp_rate(0), m_num_chls(0)
{}


Wav::~Wav()
{
	this->Clear();
}


short * Wav::operator[](unsigned short i)
{
    if (i < m_num_chls)
    {
        return m_wav_buf + m_wav_len * i;
    }
    else
    {
        return nullptr;
    }
}


void Wav::Clear()
{
    if (m_wav_buf != nullptr)
    {
        free(m_wav_buf); m_wav_buf = nullptr;
    }
    m_wav_len  = 0;
    m_smp_rate = 0;
    m_num_chls = 0;
}