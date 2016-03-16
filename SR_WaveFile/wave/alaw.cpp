/**********************************************************************************************//**
* @file			alaw.cpp
* @brief		读写 8 比特 A 律量化的 PCM.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
**************************************************************************************************/
#include "alaw.h"
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


static const unsigned char ALawCompressTable[] =
{
    1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};


static const short ALawDecompressTable[] =
{
    0xEA80, 0xEB80, 0xE880, 0xE980, 0xEE80, 0xEF80, 0xEC80, 0xED80,
    0xE280, 0xE380, 0xE080, 0xE180, 0xE680, 0xE780, 0xE480, 0xE580,
    0xF540, 0xF5C0, 0xF440, 0xF4C0, 0xF740, 0xF7C0, 0xF640, 0xF6C0,
    0xF140, 0xF1C0, 0xF040, 0xF0C0, 0xF340, 0xF3C0, 0xF240, 0xF2C0,
    0xAA00, 0xAE00, 0xA200, 0xA600, 0xBA00, 0xBE00, 0xB200, 0xB600,
    0x8A00, 0x8E00, 0x8200, 0x8600, 0x9A00, 0x9E00, 0x9200, 0x9600,
    0xD500, 0xD700, 0xD100, 0xD300, 0xDD00, 0xDF00, 0xD900, 0xDB00,
    0xC500, 0xC700, 0xC100, 0xC300, 0xCD00, 0xCF00, 0xC900, 0xCB00,
    0xFEA8, 0xFEB8, 0xFE88, 0xFE98, 0xFEE8, 0xFEF8, 0xFEC8, 0xFED8,
    0xFE28, 0xFE38, 0xFE08, 0xFE18, 0xFE68, 0xFE78, 0xFE48, 0xFE58,
    0xFFA8, 0xFFB8, 0xFF88, 0xFF98, 0xFFE8, 0xFFF8, 0xFFC8, 0xFFD8,
    0xFF28, 0xFF38, 0xFF08, 0xFF18, 0xFF68, 0xFF78, 0xFF48, 0xFF58,
    0xFAA0, 0xFAE0, 0xFA20, 0xFA60, 0xFBA0, 0xFBE0, 0xFB20, 0xFB60,
    0xF8A0, 0xF8E0, 0xF820, 0xF860, 0xF9A0, 0xF9E0, 0xF920, 0xF960,
    0xFD50, 0xFD70, 0xFD10, 0xFD30, 0xFDD0, 0xFDF0, 0xFD90, 0xFDB0,
    0xFC50, 0xFC70, 0xFC10, 0xFC30, 0xFCD0, 0xFCF0, 0xFC90, 0xFCB0,
    0x1580, 0x1480, 0x1780, 0x1680, 0x1180, 0x1080, 0x1380, 0x1280,
    0x1D80, 0x1C80, 0x1F80, 0x1E80, 0x1980, 0x1880, 0x1B80, 0x1A80,
    0x0AC0, 0x0A40, 0x0BC0, 0x0B40, 0x08C0, 0x0840, 0x09C0, 0x0940,
    0x0EC0, 0x0E40, 0x0FC0, 0x0F40, 0x0CC0, 0x0C40, 0x0DC0, 0x0D40,
    0x5600, 0x5200, 0x5E00, 0x5A00, 0x4600, 0x4200, 0x4E00, 0x4A00,
    0x7600, 0x7200, 0x7E00, 0x7A00, 0x6600, 0x6200, 0x6E00, 0x6A00,
    0x2B00, 0x2900, 0x2F00, 0x2D00, 0x2300, 0x2100, 0x2700, 0x2500,
    0x3B00, 0x3900, 0x3F00, 0x3D00, 0x3300, 0x3100, 0x3700, 0x3500,
    0x0158, 0x0148, 0x0178, 0x0168, 0x0118, 0x0108, 0x0138, 0x0128,
    0x01D8, 0x01C8, 0x01F8, 0x01E8, 0x0198, 0x0188, 0x01B8, 0x01A8,
    0x0058, 0x0048, 0x0078, 0x0068, 0x0018, 0x0008, 0x0038, 0x0028,
    0x00D8, 0x00C8, 0x00F8, 0x00E8, 0x0098, 0x0088, 0x00B8, 0x00A8,
    0x0560, 0x0520, 0x05E0, 0x05A0, 0x0460, 0x0420, 0x04E0, 0x04A0,
    0x0760, 0x0720, 0x07E0, 0x07A0, 0x0660, 0x0620, 0x06E0, 0x06A0,
    0x02B0, 0x0290, 0x02F0, 0x02D0, 0x0230, 0x0210, 0x0270, 0x0250,
    0x03B0, 0x0390, 0x03F0, 0x03D0, 0x0330, 0x0310, 0x0370, 0x0350
};


/**********************************************************************************************//**
 * @fn		static unsigned char LinearToALawSample(short sample)
 * @brief	ALaw - Biased Linear Input Code Compressed Code.
 * @return	A 律量化的 PCM 值.
 * @param [in]	sample	线性 PCM 值.
 * @note	0000000wxyza 000wxyz
 * 			0000001wxyza 001wxyz
 * 			000001wxyzab 010wxyz
 * 			00001wxyzabc 011wxyz
 * 			0001wxyzabcd 100wxyz
 * 			001wxyzabcde 101wxyz
 * 			01wxyzabcdef 110wxyz
 * 			1wxyzabcdefg 111wxyz
 **************************************************************************************************/
static unsigned char LinearToALawSample(short sample)
{
    unsigned char compressedbyte = 0;
    unsigned char sign = ((~sample) >> 8) & 0x80;
    if (sign == 0)
    {
        sample = -sample;
    }
    if (sample > 0x7F7B)
    {
        sample = 0x7F7B;
    }
    if (sample >= 0x100)
    {
        unsigned char exponent = ALawCompressTable[(sample >> 8) & 0x7F];
        unsigned char mantissa = (sample >> (exponent + 3)) & 0x0F;
        compressedbyte = (exponent << 4) | mantissa;
    }
    else
    {
        compressedbyte = (unsigned char)(sample >> 4);
    }
    compressedbyte ^= (sign ^ 0x55);
    return compressedbyte;
}


/**********************************************************************************************//**
 * @struct	ALawHead
 * @brief	8 比特 A 律量化的 PCM 文件头格式(共 58 字节)
 **************************************************************************************************/
struct ALawHead
{
    char chunkid[4];				// 00H 4 "RIFF" 标志
    unsigned int chunksize;			// 04H 4 "RIFF" 大小(文件长度-8)
    char format[4];					// 08H 4 "WAVE" 标志
    char subchunk1id[4];			// 0CH 4 "fmt " 标志
    unsigned int subchunk1size;		// 10H 4 过渡字节(不定), 0x00000010(PCM), 0x00000012(ALAW, ULAW)
    unsigned short audioformat;		// 14H 2 格式类别 ,0x0001(PCM), 0x0006(ALAW), 0x0007(ULAW)
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


bool ALaw::Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut, unsigned short tailcut, unsigned short minproc, unsigned short maxproc)
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
        ALawHead head;
        memcpy(&head, ptr, 34);
        memcpy(&head.bitspersample, ptr + 34, 24);
        if (strncmp(head.chunkid, "RIFF", 4) || (head.chunksize != fs - 8) || strncmp(head.format, "WAVE", 4) || strncmp(head.subchunk1id, "fmt ", 4) || (head.subchunk1size != 18) || (head.audioformat != 0x0006) || ((head.numchannels != 1) && (head.numchannels != 2)) || (head.byterate != head.numchannels * head.samplerate * head.bitspersample / 8) || (head.blockalign != head.numchannels * head.bitspersample / 8) || (head.bitspersample != 8) || strncmp(head.datatag, "data", 4) || (head.datalen != fs - 58))
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
    else if (m_wav_len > (headcut + maxproc + tailcut) * m_smp_rate)
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
            m_wav_buf[j * m_wav_len + i] = ALawDecompressTable[buf[i * m_num_chls + j]];
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
        ALawHead head;
        memcpy(&head, ptr, 34);
        memcpy(&head.bitspersample, ptr + 34, 24);
        if (strncmp(head.chunkid, "RIFF", 4) || (head.chunksize != fs - 8) || strncmp(head.format, "WAVE", 4) || strncmp(head.subchunk1id, "fmt ", 4) || (head.subchunk1size != 18) || (head.audioformat != 0x0006) || ((head.numchannels != 1) && (head.numchannels != 2)) || (head.byterate != head.numchannels * head.samplerate * head.bitspersample / 8) || (head.blockalign != head.numchannels * head.bitspersample / 8) || (head.bitspersample != 8) || strncmp(head.datatag, "data", 4) || (head.datalen != fs - 58))
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
    else if (m_wav_len > (headcut + maxproc + tailcut) * m_smp_rate)
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
            m_wav_buf[j * m_wav_len + i] = ALawDecompressTable[buf[i * m_num_chls + j]];
        }
    }
    munmap(ptr, fs);
    return true;

#endif
}


bool ALaw::Save(const char *wavfile, bool headless) const
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

    ALawHead head;
    strncpy(head.chunkid, "RIFF", 4);
    head.chunksize = m_wav_len * m_num_chls + 50;
    strncpy(head.format, "WAVE", 4);
    strncpy(head.subchunk1id, "fmt ", 4);
    head.subchunk1size = 18;
    head.audioformat = 0x0006;
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
            buf[i * m_num_chls + j] = LinearToALawSample(m_wav_buf[j * m_wav_len + i]);
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