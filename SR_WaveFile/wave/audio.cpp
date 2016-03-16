/**********************************************************************************************//**
* @file			audio.cpp
* @brief		读写音频.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
* @note			支持的格式有: 1) 16 比特量化的线性 PCM; 2) 8 比特 A 律量化的 PCM; 3) 8 比特 U 律量化的 PCM.
**************************************************************************************************/
#include "audio.h"

Wav *LoadWav(const char *wavfile, WavFmt *wavfmt, unsigned int smprate, unsigned short numchls, unsigned short headcut, unsigned short tailcut, unsigned short minproc, unsigned short maxproc)
{
    Wav *wav = nullptr;
	char *p = new char[5];
	p[1] = '\0';
    if (wavfmt == nullptr)
    {
        wav = new PCM();
        if (wav->Load(wavfile, 0, 0, headcut, tailcut, minproc, maxproc))
        {
            return wav;
        }
        delete wav;

        wav = new ALaw();
        if (wav->Load(wavfile, 0, 0, headcut, tailcut, minproc, maxproc))
        {
            return wav;
        }
        delete wav;

        wav = new ULaw();
        if (wav->Load(wavfile, 0, 0, headcut, tailcut, minproc, maxproc))
        {
            return wav;
        }
        delete wav;

        return nullptr;
    }
    else
    {
        switch (*wavfmt)
        {
        case WavFmt::pcm:
            wav = new PCM();
            if (wav->Load(wavfile, smprate, numchls, headcut, tailcut, minproc, maxproc))
            {
                return wav;
            }
            delete wav;
            return nullptr;
        case WavFmt::alaw:
            wav = new ALaw();
            if (wav->Load(wavfile, smprate, numchls, headcut, tailcut, minproc, maxproc))
            {
                return wav;
            }
            delete wav;
            return nullptr;
        case WavFmt::ulaw:
            wav = new ULaw();
            if (wav->Load(wavfile, smprate, numchls, headcut, tailcut, minproc, maxproc))
            {
                return wav;
            }
            delete wav;
            return nullptr;
        default:
            return nullptr;
        }
    }
}


bool SaveWav(const char *wavfile, const Wav *wav, const WavFmt &wavfmt, bool headless)
{
    switch (wavfmt)
    {
    case WavFmt::pcm:
        if (reinterpret_cast<const PCM *>(wav)->Save(wavfile, headless))
        {
            return true;
        }
        else
        {
            return false;
        }
    case WavFmt::alaw:
        if (reinterpret_cast<const ALaw *>(wav)->Save(wavfile, headless))
        {
            return true;
        }
        else
        {
            return false;
        }
    case WavFmt::ulaw:
        if (reinterpret_cast<const ULaw *>(wav)->Save(wavfile, headless))
        {
            return true;
        }
        else
        {
            return false;
        }
    default:
        return false;
    }
}


void FreeWav(Wav *&wav)
{
    if (wav != nullptr)
    {
        delete wav; wav = nullptr;
    }
}