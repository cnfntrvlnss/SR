/**********************************************************************************************//**
 * @file		wav.h
 * @brief		读写音频.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/10/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include <limits.h>


/**********************************************************************************************//**
 * @class	Wav
 * @brief	音频基类.
 * @details	1. 转化为 16 比特量化的线性 PCM. 2. 虚基类, 不可直接调用.
 **************************************************************************************************/
class Wav
{
private:
    /**********************************************************************************************//**
     * @fn		Wav::Wav(const Wav &wav) = delete;
     * @brief	禁用复制构造函数.
     * @param [in]	wav	音频对象.
     **************************************************************************************************/
    Wav(const Wav &wav);

    /**********************************************************************************************//**
     * @fn		Wav & Wav::operator=(const Wav &wav) = delete;
     * @brief	禁用赋值操作符.
     * @return	该对象的一份浅拷贝.
     * @param [in]	wav	音频对象.
     **************************************************************************************************/
    Wav & operator=(const Wav &wav);

public:
    /**********************************************************************************************//**
     * @fn		Wav::Wav();
     * @brief	默认构造函数.
     **************************************************************************************************/
    Wav();


    /**********************************************************************************************//**
     * @fn		virtual Wav::~Wav();
     * @brief	析构函数.
     **************************************************************************************************/
    virtual ~Wav();


    /**********************************************************************************************//**
     * @fn		short * Wav::operator[](unsigned short i);
     * @brief	获取对应通道的音频数据.
     * @return	返回第 i 个通道的音频地址; 如果 i 过大, 则返回 nullptr.
     * @param [in]	i	通道索引, i = 0, 1, ..., NChl()-1.
     * @note	当实际存在音频时, 调用才有意义.
     **************************************************************************************************/
    short * operator[](unsigned short i);

    /**********************************************************************************************//**
     * @fn		unsigned int Wav::Len() const
     * @brief	获取语音的长度.
     * @return	单个通道的点数.
     * @note	1. 当实际存在音频时, 调用才有意义. 2. 单位是"点数", 非"时间".
     **************************************************************************************************/
    unsigned int Len() const { return m_wav_len; };

    /**********************************************************************************************//**
     * @fn		unsigned int Wav::Rate() const
     * @brief	获取音频的采样率.
     * @return	音频的采样率, 单位: 点数/秒.
     * @note	当实际存在音频时, 调用才有意义.
     **************************************************************************************************/
    unsigned int Rate() const { return m_smp_rate; };

    /**********************************************************************************************//**
     * @fn		unsigned short Wav::NChl() const
     * @brief	获取音频对象的通道数.
     * @return	通道数.
     * @note	当实际存在音频时, 调用才有意义.
     **************************************************************************************************/
    unsigned short NChl() const { return m_num_chls; };

    /**********************************************************************************************//**
     * @fn		void Wav::Clear();
     * @brief	清空音频缓冲, 释放空间.
     * @note	再次加载音频前, 需要调用该函数释放内存.
     **************************************************************************************************/
    void Clear();

	 /**********************************************************************************************//**
     * @fn		virtual bool Wav::Load( const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX ) = 0;
     * @brief	加载音频.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]	wavfile	音频路径.
     * @param [in]	smprate	采样率, 0 表示"有头", 自动检测.
     * @param [in]	numchls	通道数(1/2), 当 smprate > 0 时才有效.
     * @param [in]	headcut	掐头, 秒.
     * @param [in]	tailcut	去尾, 秒.
     * @param [in]	minproc	最短处理时长, 秒.
     * @param [in]	maxproc	最长处理时长, 秒.
     * @note	1. 如果为标准格式的音频文件, 则置 smprate 为 0; 否则, 按照 smprate 和 numchls 两个参数进行解析. 2. 导致失败的情况有: 1) 参数不对; 2) 音频格式不对; 3) 不支持的音频格式; 4) 内存不足.
     **************************************************************************************************/
    virtual bool Load(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX) = 0;

    /**********************************************************************************************//**
     * @fn		virtual bool Wav::Save( const char *wavfile, bool headless = false ) const = 0;
     * @brief	保存音频.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]	wavfile		音频路径.
     * @param [in]	headless	"true/false" 表示"无头/有头".
     * @note	1. 根据实例对象的具体类型保存. 2. 当实际存在音频时, 调用才有意义. 3. 导致失败的情况有: 1) "空"的音频对象; 2) 无法创建音频文件; 3) 磁盘空间不足; 4) 内存不足.
     **************************************************************************************************/
    virtual bool Save(const char *wavfile, bool headless = false) const = 0;

	bool RepeatLoad(const char *wavfile, unsigned int smprate, unsigned short numchls, unsigned short headcut = 0, unsigned short tailcut = 0, unsigned short minproc = 0, unsigned short maxproc = USHRT_MAX){
		if (m_wav_buf != nullptr){
			this->Clear();
		}
		return Load(wavfile, smprate, numchls, headcut, tailcut, minproc, maxproc);
	}

	void SetData(short *wavBuf, unsigned wavLen, unsigned smpRate){
		if (m_wav_buf != nullptr){
			this->Clear();
		}
		m_wav_buf = wavBuf;
		m_wav_len = wavLen;
		m_smp_rate = smpRate;
		m_num_chls = 1;
	}

protected:


    /** @brief	音频首地址, 按通道存放. */
    short *         m_wav_buf;
    /** @brief	单个通道的点数. */
    unsigned int    m_wav_len;
    /** @brief	采样率. */
    unsigned int    m_smp_rate;
    /** @brief	通道数. */
    unsigned short  m_num_chls;
};