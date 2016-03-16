/**********************************************************************************************//**
* @file			ulaw.cpp
* @brief		读写 8 比特 U 律量化的 PCM.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
**************************************************************************************************/
#include "ulaw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#endif


static const unsigned char ULawCompressTable[] =
{
    0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};


static const short ULawDecompressTable[] =
{
    0x8284, 0x8684, 0x8A84, 0x8E84, 0x9284, 0x9684, 0x9A84, 0x9E84,
    0xA284, 0xA684, 0xAA84, 0xAE84, 0xB284, 0xB684, 0xBA84, 0xBE84,
    0xC184, 0xC384, 0xC584, 0xC784, 0xC984, 0xCB84, 0xCD84, 0xCF84,
    0xD184, 0xD384, 0xD584, 0xD784, 0xD984, 0xDB84, 0xDD84, 0xDF84,
    0xE104, 0xE204, 0xE304, 0xE404, 0xE504, 0xE604, 0xE704, 0xE804,
    0xE904, 0xEA04, 0xEB04, 0xEC04, 0xED04, 0xEE04, 0xEF04, 0xF004,
    0xF0C4, 0xF144, 0xF1C4, 0xF244, 0xF2C4, 0xF344, 0xF3C4, 0xF444,
    0xF4C4, 0xF544, 0xF5C4, 0xF644, 0xF6C4, 0xF744, 0xF7C4, 0xF844,
    0xF8A4, 0xF8E4, 0xF924, 0xF964, 0xF9A4, 0xF9E4, 0xFA24, 0xFA64,
    0xFAA4, 0xFAE4, 0xFB24, 0xFB64, 0xFBA4, 0xFBE4, 0xFC24, 0xFC64,
    0xFC94, 0xFCB4, 0xFCD4, 0xFCF4, 0xFD14, 0xFD34, 0xFD54, 0xFD74,
    0xFD94, 0xFDB4, 0xFDD4, 0xFDF4, 0xFE14, 0xFE34, 0xFE54, 0xFE74,
    0xFE8C, 0xFE9C, 0xFEAC, 0xFEBC, 0xFECC, 0xFEDC, 0xFEEC, 0xFEFC,
    0xFF0C, 0xFF1C, 0xFF2C, 0xFF3C, 0xFF4C, 0xFF5C, 0xFF6C, 0xFF7C,
    0xFF88, 0xFF90, 0xFF98, 0xFFA0, 0xFFA8, 0xFFB0, 0xFFB8, 0xFFC0,
    0xFFC8, 0xFFD0, 0xFFD8, 0xFFE0, 0xFFE8, 0xFFF0, 0xFFF8, 0x0000,
    0x7D7C, 0x797C, 0x757C, 0x717C, 0x6D7C, 0x697C, 0x657C, 0x617C,
    0x5D7C, 0x597C, 0x557C, 0x517C, 0x4D7C, 0x497C, 0x457C, 0x417C,
    0x3E7C, 0x3C7C, 0x3A7C, 0x387C, 0x367C, 0x347C, 0x327C, 0x307C,
    0x2E7C, 0x2C7C, 0x2A7C, 0x287C, 0x267C, 0x247C, 0x227C, 0x207C,
    0x1EFC, 0x1DFC, 0x1CFC, 0x1BFC, 0x1AFC, 0x19FC, 0x18FC, 0x17FC,
    0x16FC, 0x15FC, 0x14FC, 0x13FC, 0x12FC, 0x11FC, 0x10FC, 0x0FFC,
    0x0F3C, 0x0EBC, 0x0E3C, 0x0DBC, 0x0D3C, 0x0CBC, 0x0C3C, 0x0BBC,
    0x0B3C, 0x0ABC, 0x0A3C, 0x09BC, 0x093C, 0x08BC, 0x083C, 0x07BC,
    0x075C, 0x071C, 0x06DC, 0x069C, 0x065C, 0x061C, 0x05DC, 0x059C,
    0x055C, 0x051C, 0x04DC, 0x049C, 0x045C, 0x041C, 0x03DC, 0x039C,
    0x036C, 0x034C, 0x032C, 0x030C, 0x02EC, 0x02CC, 0x02AC, 0x028C,
    0x026C, 0x024C, 0x022C, 0x020C, 0x01EC, 0x01CC, 0x01AC, 0x018C,
    0x0174, 0x0164, 0x0154, 0x0144, 0x0134, 0x0124, 0x0114, 0x0104,
    0x00F4, 0x00E4, 0x00D4, 0x00C4, 0x00B4, 0x00A4, 0x0094, 0x0084,
    0x0078, 0x0070, 0x0068, 0x0060, 0x0058, 0x0050, 0x0048, 0x0040,
    0x0038, 0x0030, 0x0028, 0x0020, 0x0018, 0x0010, 0x0008, 0x0000
};


/**********************************************************************************************//**
 * @fn		static unsigned char LinearToULawSample(short sample)
 * @brief	ULaw - Biased Linear Input Code Compressed Code.
 * @return	U 律量化的 PCM 值.
 * @param [in]	sample	线性 PCM 值.
 * @note	00000001wxyza   000wxyz
 * 			0000001wxyzab   001wxyz
 * 			000001wxyzabc   010wxyz
 * 			00001wxyzabcd   011wxyz
 * 			001wxyzabcdef   101wxyz
 * 			01wxyzabcdefg   110wxyz
 * 			1wxyzabcdefgh   111wxyz
 **************************************************************************************************/
static unsigned char LinearToULawSample(short sample)
{
    unsigned char sign = (sample >> 8) & 0x80;
    if (sign != 0)
    {
        sample = -sample;
    }
    if (sample > 0x7F7B)
    {
        sample = 0x7F7B;
    }
    sample += 0x84;
    unsigned char exponent =ULawCompressTable[(sample >> 7) & 0xFF];
    unsigned char mantissa = (sample >> (exponent + 3)) & 0x0F;
    return ~(sign | (exponent << 4) | mantissa);
}


/**********************************************************************************************//**
 * @struct	ULawHead
 * @brief	8 比特 U 律量化的 PCM 文件头格式(共 58 字节).
 **************************************************************************************************/
struct ULawHead
{
    char chunkid[4];				// 00H 4 "RIFF" 标志
    unsigned int chunksize;			// 04H 4 "RIFF" 大小(文件长度-8)
    char format[4];					// 08H 4 "WAVE" 标志
    char subchunk1id[4];			// 0CH 4 "fmt " 标志
    unsigned int subchunk1size;		// 10H 4 过渡字节(不定), 0x00000010(PCM), 0x00000012(ALAW, ULaw)
    unsigned short audioformat;		// 14H 2 格式类别 ,0x0001(PCM), 0x0006(ALAW), 0x0007(ULaw)
    unsigned short numchannels;		// 16H 2 通道数, 单声道为 1, 双声道为 2
    unsigned int samplerate;		// 18H 4 采样率(每秒样点数), 表示每个通道的播放速度
    unsigned int byterate;			// 1CH 4 音频数据传送速率(numchannels * samplerate * bitspersample / 8)
    unsigned short blockalign;		// 20H 2 数据块的调整数(numchannels * bitspersample / 8)
    unsigned int bitspersample;		// 22H 2 单个样本的数据位数, 表示每个声道中各个样本的数据位数. 如果有多个声道, 对每个声道而言, 样本大小都一样.
    char subchunk2id[4];			// 26H 4 "fact" 标志
    unsigned int temp1;				// 2AH 4 0x00000004
    unsigned int temp2;				// 2EH 4 0x00075300
    char datatag[4];				// **H 4 数据标记符 "data"
    unsigned int datalen;			// **H 4 语音数据的点数(文件长度-58)
};


bool ULaw::Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut, unsigned short tailcut, unsigned short minproc, unsigned short maxproc)
{
    if (smprate > 0)
    {
        if ((numchls != 1) && (numchls != 2))
        {
            return false;
        }
    }

#if defined(_WIN32) || defined(_WIN64)

    int slen = MultiByteToWideChar(CP_ACP, 0, wavfile, -1, NULL, 0);
    wchar_t *wf = (wchar_t *)malloc(sizeof(wchar_t) * slen);
    if (wf == nullptr)
    {
        return false;
    }
    MultiByteToWideChar(CP_ACP, 0, wavfile, -1, wf, slen);

    HANDLE hfile = CreateFile(wf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
    free(wf);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    DWORD fs = GetFileSize(hfile, NULL);

    HANDLE hmap = CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle(hfile);
    if (hmap == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    unsigned char *ptr = (unsigned char *)MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0);
    if (ptr == nullptr)
    {
        CloseHandle(hmap);
        return false;
    }

    unsigned char *buf = nullptr;
    if (smprate == 0)
    {
        ULawHead head;
        memcpy(&head, ptr, 34);
        memcpy(&head.bitspersample, ptr + 34, 24);
        if (strncmp(head.chunkid, "RIFF", 4) || (head.chunksize != fs - 8) || strncmp(head.format, "WAVE", 4) || strncmp(head.subchunk1id, "fmt ", 4) || (head.subchunk1size != 18) || (head.audioformat != 0x0007) || ((head.numchannels != 1) && (head.numchannels != 2)) || (head.byterate != head.numchannels * head.samplerate * head.bitspersample / 8) || (head.blockalign != head.numchannels * head.bitspersample / 8) || (head.bitspersample != 8) || strncmp(head.datatag, "data", 4) || (head.datalen != fs - 58))
        {
            CloseHandle(hmap);
            return false;
        }
        m_wav_len = head.datalen / head.numchannels;
        m_smp_rate = head.samplerate;
        m_num_chls = head.numchannels;
        buf = ptr + 58;
    }
    else
    {
        m_wav_len = fs / numchls;
        m_smp_rate = smprate;
        m_num_chls = numchls;
        buf = ptr;
    }

    if (m_wav_len < (headcut + minproc + tailcut) * m_smp_rate)
    {
        m_wav_len = 0;
        m_smp_rate = 0;
        m_num_chls = 0;
        CloseHandle(hmap);
        return false;
    }
    else if (m_wav_len >(headcut + maxproc + tailcut) * m_smp_rate)
    {
        m_wav_len = maxproc * m_smp_rate;
    }
    else
    {
        m_wav_len -= (headcut + tailcut) * m_smp_rate;
    }

    m_wav_buf = (short *)malloc(sizeof(short) * m_wav_len * m_num_chls);
    if (m_wav_buf == nullptr)
    {
        m_wav_len = 0;
        m_smp_rate = 0;
        m_num_chls = 0;
        CloseHandle(hmap);
        return false;
    }
    buf += headcut * m_smp_rate * m_num_chls;
    for (unsigned short j = 0; j < m_num_chls; j++)
    {
        for (unsigned int i = 0; i < m_wav_len; i++)
        {
            m_wav_buf[j * m_wav_len + i] = ULawDecompressTable[buf[i * m_num_chls + j]];
        }
    }
    CloseHandle(hmap);
    return true;

#else

    int fd = open(wavfile, O_RDONLY);
    if (fd == -1)
    {
        return false;
    }

    struct stat st;
    if (fstat(fd, &st) == -1)
    {
        close(fd);
        return false;
    }
    long fs = st.st_size;

    unsigned char *ptr = (unsigned char *)mmap(0, fs, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (ptr == MAP_FAILED)
    {
        return false;
    }

    unsigned char *buf = nullptr;
    if (smprate == 0)
    {
        ULawHead head;
        memcpy(&head, ptr, 34);
        memcpy(&head.bitspersample, ptr + 34, 24);
        if (strncmp(head.chunkid, "RIFF", 4) || (head.chunksize != fs - 8) || strncmp(head.format, "WAVE", 4) || strncmp(head.subchunk1id, "fmt ", 4) || (head.subchunk1size != 18) || (head.audioformat != 0x0007) || ((head.numchannels != 1) && (head.numchannels != 2)) || (head.byterate != head.numchannels * head.samplerate * head.bitspersample / 8) || (head.blockalign != head.numchannels * head.bitspersample / 8) || (head.bitspersample != 8) || strncmp(head.datatag, "data", 4) || (head.datalen != fs - 58))
        {
            munmap(ptr, fs);
            return false;
        }
        m_wav_len = head.datalen / head.numchannels;
        m_smp_rate = head.samplerate;
        m_num_chls = head.numchannels;
        buf = ptr + 58;
    }
    else
    {
        m_wav_len = fs / numchls;
        m_smp_rate = smprate;
        m_num_chls = numchls;
        buf = ptr;
    }

    if (m_wav_len < (headcut + minproc + tailcut) * m_smp_rate)
    {
        m_wav_len = 0;
        m_smp_rate = 0;
        m_num_chls = 0;
        munmap(ptr, fs);
        return false;
    }
    else if (m_wav_len >(headcut + maxproc + tailcut) * m_smp_rate)
    {
        m_wav_len = maxproc * m_smp_rate;
    }
    else
    {
        m_wav_len -= (headcut + tailcut) * m_smp_rate;
    }

    m_wav_buf = (short *)malloc(sizeof(short) * m_wav_len * m_num_chls);
    if (m_wav_buf == nullptr)
    {
        m_wav_len = 0;
        m_smp_rate = 0;
        m_num_chls = 0;
        munmap(ptr, fs);
        return false;
    }
    buf += headcut * m_smp_rate * m_num_chls;
    for (unsigned short j = 0; j < m_num_chls; j++)
    {
        for (unsigned int i = 0; i < m_wav_len; i++)
        {
            m_wav_buf[j * m_wav_len + i] = ULawDecompressTable[buf[i * m_num_chls + j]];
        }
    }
    munmap(ptr, fs);
    return true;

#endif
}


bool ULaw::Save(const char *wavfile, bool headless) const
{
    if ((m_wav_buf == nullptr) || (m_wav_len == 0) || (m_smp_rate == 0) || (m_num_chls == 0))
    {
        return false;
    }

    FILE *fp = fopen(wavfile, "wb");
    if (fp == nullptr)
    {
        return false;
    }

    ULawHead head;
    strncpy(head.chunkid, "RIFF", 4);
    head.chunksize = m_wav_len * m_num_chls + 50;
    strncpy(head.format, "WAVE", 4);
    strncpy(head.subchunk1id, "fmt ", 4);
    head.subchunk1size = 18;
    head.audioformat = 0x0007;
    head.numchannels = m_num_chls;
    head.samplerate = m_smp_rate;
    head.byterate = m_num_chls * m_smp_rate;
    head.blockalign = m_num_chls;
    head.bitspersample = 8;
    strncpy(head.subchunk2id, "fact", 4);
    head.temp1 = 0x00000004;
    head.temp2 = 0x00075300;
    strncpy(head.datatag, "data", 4);
    head.datalen = m_wav_len * m_num_chls;

    if (!headless)
    {
        if ((1 != fwrite(&head, 34, 1, fp)) || (1 != fwrite(&head.bitspersample, 24, 1, fp)))
        {
            fclose(fp);
            remove(wavfile);
            return false;
        }
    }

    unsigned char *buf = (unsigned char *)malloc(head.datalen);
    if (buf == nullptr)
    {
        fclose(fp);
        remove(wavfile);
        return false;
    }
    for (unsigned short j = 0; j < m_num_chls; j++)
    {
        for (unsigned int i = 0; i < m_wav_len; i++)
        {
            buf[i * m_num_chls + j] = LinearToULawSample(m_wav_buf[j * m_wav_len + i]);
        }
    }
    if (head.datalen != fwrite(buf, 1, head.datalen, fp))
    {
        fclose(fp);
        remove(wavfile);
        free(buf);
        return false;
    }
    fclose(fp);
    free(buf);
    return true;
}