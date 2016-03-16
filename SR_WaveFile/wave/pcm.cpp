/**********************************************************************************************//**
* @file			pcm.cpp
* @brief		读写 16 比特量化的线性 PCM.
* @author		许云飞 (kindapple@163.com)
* @version		1.0
* @date			6/10/2015
* @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
**************************************************************************************************/
#include "pcm.h"
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


/**********************************************************************************************//**
 * @struct	PCMHead
 * @brief	16 比特量化的线性 PCM 文件头格式(共 44 字节)
 **************************************************************************************************/

struct PCMHead
{
	struct RIFF_HEADER{
		char chunkid[4];				// 00H 4 "RIFF" 标志
		unsigned int chunksize;			// 04H 4 "RIFF" 大小
		char format[4];					// 08H 4 "WAVE" 标志

	};
	struct WAVE_FORMAT{
		unsigned short audioformat;		// 14H 2 格式类别, 0x0001(PCM), 0x0006(ALAW), 0x0007(MULAW)
		unsigned short numchannels;		// 16H 2 通道数, 单声道为 1, 双声道为 2
		unsigned int samplerate;		// 18H 4 采样率(每秒样点数), 表示每个通道的播放速度
		unsigned int byterate;			// 1CH 4 音频数据传送速率(numchannels * samplerate * bitspersample / 8)
		unsigned short blockalign;		// 20H 2 数据块的调整数(numchannels * bitspersample / 8)
		unsigned short bitspersample;	// 22H 2 单个样本的数据位数, 表示每个声道中各个样本的数据位数. 如果有多个声道, 对每个声道而言, 样本大小都一样.
	};
	struct FMT_BLOCK{
		char subchunk1id[4];			// 0CH 4 "fmt " 标志
		unsigned int subchunk1size;		// 10H 4 过渡字节(不定), 0x00000010(PCM), 0x00000012(ALAW, MULAW)
		WAVE_FORMAT wavFmt;
	};
	struct DATA_BLOCK{
		char datatag[4];				// 24H 4 数据标记符 "data"
		unsigned int datalen;			// 28H 4 语音数据的点数
	};
	RIFF_HEADER riffhd;
	FMT_BLOCK fmtBlk;
	DATA_BLOCK dataBlk;
};

static bool readPCMHead(char *buf, PCMHead &hd, unsigned &skippedSize)
{
	hd.riffhd;
	unsigned st = 0;
	unsigned len = sizeof(PCMHead::RIFF_HEADER);
	memcpy(&hd.riffhd, buf + st, len);
	st += len;
	len = sizeof(PCMHead::FMT_BLOCK);
	memcpy(&hd.fmtBlk, buf + st, len);
	if (hd.fmtBlk.subchunk1size > sizeof(PCMHead::WAVE_FORMAT)){
		st += len + hd.fmtBlk.subchunk1size - sizeof(PCMHead::WAVE_FORMAT);
		hd.fmtBlk.subchunk1size = sizeof(PCMHead::WAVE_FORMAT);
	}
	else if (hd.fmtBlk.subchunk1size == sizeof(PCMHead::WAVE_FORMAT)){
		st += len;

	}
	else{
		return false;
	}
	//继续跳过 可选部分 。
	if ((strncmp(buf + st, "fact", 4) == 0) || (_strnicmp(buf + st, "list", 4) == 0)){
		unsigned tmpDataSize;
		memcpy(&tmpDataSize, buf + st + 4, 4);
		st += 8 + tmpDataSize;
	}
	
	if (strncmp(buf + st, "data", 4) == 0){
		memcpy(&hd.dataBlk, buf + st, sizeof(PCMHead::DATA_BLOCK));
		st += sizeof(PCMHead::DATA_BLOCK);
		if (hd.dataBlk.datalen + st - 8 != hd.riffhd.chunksize){
			return false;
		}
	}
	else{
		return false;
	}
	skippedSize = st;
	return true;
}

bool PCM::Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut, unsigned short tailcut, unsigned short minproc, unsigned short maxproc)
{
    if (smprate > 0)
    {
        if ((numchls != 1) && (numchls != 2))
        {
            return false;
        }
    }

	//TODO 扩展读头逻辑，使之可以跳过可选部分
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

    char *ptr = (char *)MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0);
    if (ptr == nullptr)
    {
        CloseHandle(hmap);
        return false;
    }

    short *buf = nullptr;
    if (smprate == 0)
    {
		PCMHead head;
		unsigned skippedLen;
		if (!readPCMHead(ptr, head, skippedLen)){
			CloseHandle(hmap);
			return false;
		}

		m_wav_len = head.dataBlk.datalen / sizeof(short) / head.fmtBlk.wavFmt.numchannels;
		m_smp_rate = head.fmtBlk.wavFmt.samplerate;
		m_num_chls = head.fmtBlk.wavFmt.numchannels; 
        buf = (short *)(ptr + skippedLen);
    }
    else
    {
        m_wav_len = fs / 2 / numchls;
        m_smp_rate = smprate;
        m_num_chls = numchls;
        buf = (short *)ptr;
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
    if (m_num_chls == 1)
    {
        memcpy(m_wav_buf, buf, sizeof(short) * m_wav_len);
    }
    else
    {
		//then channel num is 2
        for (unsigned int i = 0; i < m_wav_len; i++)
        {
            m_wav_buf[i] = buf[2 * i];
            m_wav_buf[m_wav_len + i] = buf[2 * i + 1];
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

    char *ptr = (char *)mmap(0, fs, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (ptr == MAP_FAILED)
    {
        return false;
    }

    short *buf = nullptr;
    if (smprate == 0)
    {
        PCMHead *head = (PCMHead *)ptr;
        if (strncmp(head->chunkid, "RIFF", 4) || (head->chunksize != fs - 8) || strncmp(head->format, "WAVE", 4) || strncmp(head->subchunk1id, "fmt ", 4) || (head->subchunk1size != 16) || (head->audioformat != 0x0001) || ((head->numchannels != 1) && (head->numchannels != 2)) || (head->byterate != head->numchannels * head->samplerate * head->bitspersample / 8) || (head->blockalign != head->numchannels * head->bitspersample / 8) || (head->bitspersample != 16) || strncmp(head->datatag, "data", 4) || (head->datalen != fs - 44))
        {
            munmap(ptr, fs);
            return false;
        }
        m_wav_len = head->datalen / 2 / head->numchannels;
        m_smp_rate = head->samplerate;
        m_num_chls = head->numchannels;
        buf = (short *)(ptr + 44);
    }
    else
    {
        m_wav_len = fs / 2 / numchls;
        m_smp_rate = smprate;
        m_num_chls = numchls;
        buf = (short *)ptr;
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
    if (m_num_chls == 1)
    {
        memcpy(m_wav_buf, buf, sizeof(short) * m_wav_len);
    }
    else
    {
        for (unsigned int i = 0; i < m_wav_len; i++)
        {
            m_wav_buf[i] = buf[2 * i];
            m_wav_buf[m_wav_len + i] = buf[2 * i + 1];
        }
    }
    munmap(ptr, fs);
    return true;

#endif
}


bool PCM::Save(const char *wavfile, bool headless) const
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

    PCMHead head;
    strncpy(head.riffhd.chunkid, "RIFF", 4);
    head.riffhd.chunksize = m_wav_len * m_num_chls * 2 + 36;
    strncpy(head.riffhd.format, "WAVE", 4);
    strncpy(head.fmtBlk.subchunk1id, "fmt ", 4);
    head.fmtBlk.subchunk1size = 16;
    head.fmtBlk.wavFmt.audioformat = 0x0001;
	head.fmtBlk.wavFmt.numchannels = m_num_chls;
	head.fmtBlk.wavFmt.samplerate = m_smp_rate;
	head.fmtBlk.wavFmt.bitspersample = 16;
	head.fmtBlk.wavFmt.byterate = m_num_chls * m_smp_rate * head.fmtBlk.wavFmt.bitspersample / 8;
	head.fmtBlk.wavFmt.blockalign = m_num_chls * head.fmtBlk.wavFmt.bitspersample / 8;
    strncpy(head.dataBlk.datatag, "data", 4);
    head.dataBlk.datalen = m_wav_len * m_num_chls * 2;

    if (!headless)
    {
        if (1 != fwrite(&head, sizeof(head), 1, fp))
        {
            fclose(fp);
            remove(wavfile);
            return false;
        }
    }

    if (m_num_chls == 1)
    {
        if (head.dataBlk.datalen != fwrite(m_wav_buf, 1, head.dataBlk.datalen, fp))
        {
            fclose(fp);
            remove(wavfile);
            return false;
        }
    }
    else
    {
        short *buf = (short *)malloc(sizeof(short) * m_wav_len * m_num_chls);
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
                buf[i * m_num_chls + j] = m_wav_buf[j * m_wav_len + i];
            }
        }
        if (head.dataBlk.datalen != fwrite(buf, 1, head.dataBlk.datalen, fp))
        {
            fclose(fp);
            remove(wavfile);
            free(buf);
            return false;
        }
        free(buf);
    }
    fclose(fp);
    return true;
}