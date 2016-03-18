/**********************************************************************************************//**
 * @file		MFCC.h
 * @brief		美尔频率倒谱系数.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/12/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "feat.h"
#include "signal.h"
#include <string>
using namespace std;

/**********************************************************************************************//**
 * @struct  CfgMFCC
 * @brief   "美尔频率倒谱系数"配置参数.
 **************************************************************************************************/
struct CfgMFCC
{
    /** @brief	特征类型. */
    string			feattype;
    /** @brief	采样率, 点数. */
    unsigned int	samplerate;
    /** @brief	帧长, 毫秒. */
    float			framesize;
    /** @brief	帧移, 毫秒. */
    float			framerate;
    /** @brief	是否移除直流. */
    bool			removedc;
    /** @brief	倒谱提升系数. */
    float			ceplifter;
    /** @brief	滤波器数目. */
    unsigned int	chlnum;
    /** @brief	倒谱数. */
    unsigned int	cepnum;
    /** @brief	下截止频率. */
    float			lowpass;
    /** @brief	上截止频率. */
    float			highpass;
    /** @brief	能量归一化. */
    bool			normenergy;
    /** @brief	能量缩放因子. */
    float			energyscale;
    /** @brief	静音门限. */
    float			silfloor;
    /** @brief	倒谱均值规整. */
    bool			docmn;
    /** @brief	倒谱方差规整. */
    bool			docvn;
    /** @brief	RASTA 滤波. */
    bool			dorasta;
    CfgMFCC() : feattype("MFCC_E_A"), samplerate(8000), framesize(20.f), framerate(10.f), removedc(false), ceplifter(22.f),
        chlnum(24), cepnum(19), lowpass(250.f), highpass(3800.f), normenergy(true), energyscale(19.f), silfloor(50.f),
        docmn(true), docvn(true), dorasta(false) {};
};

/**********************************************************************************************//**
 * @class	MFCC
 * @brief	"美尔频率倒谱系数"特征类.
 **************************************************************************************************/
class MFCC
{
public:
    /**********************************************************************************************//**
     * @fn		MFCC::MFCC();
     * @brief	基本的初始化工作.
     **************************************************************************************************/
    MFCC();

    /**********************************************************************************************//**
     * @fn		MFCC::~MFCC();
     * @brief	收尾工作, 释放内存.
     **************************************************************************************************/
    ~MFCC();

    /**********************************************************************************************//**
     * @fn		bool MFCC::Initialize(const CfgMFCC &cfgmfcc);
     * @brief	初始化.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]	cfgmfcc	特征配置.
     **************************************************************************************************/
    bool Initialize(const CfgMFCC &cfgmfcc);

    /**********************************************************************************************//**
     * @fn		bool MFCC::DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;
     * @brief	提取特征.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		wavbuf		语音内存.
     * @param [in]		wavlen		语音长度.
     * @param [in]		smprate		采样率.
     * @param [in,out]	featbuf 	特征内存.
     * @param [in,out]	featinfo	特征信息.
     * @note	特征内存由该函数开辟, 由 @ref FreeFeat 释放.
     **************************************************************************************************/
    bool DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;

private:
    /**********************************************************************************************//**
     * @fn		MFCC::MFCC(const MFCC &mfcc);
     * @brief	禁用复制构造函数.
     * @param [in]	mfcc	"美尔频率倒谱系数"对象.
     **************************************************************************************************/
    MFCC(const MFCC &mfcc);

    /**********************************************************************************************//**
     * @fn		MFCC & MFCC::operator=(const MFCC &mfcc);
     * @brief	禁用赋值操作符.
     * @return	该对象的一份浅拷贝.
     * @param [in]	mfcc	"美尔频率倒谱系数"对象.
     **************************************************************************************************/
    MFCC & operator=(const MFCC &mfcc);

private:
    /**********************************************************************************************//**
     * @fn		bool MFCC::InitFBank();
     * @brief	初始化滤波器组.
     * @return	成功返回 true, 失败返回 false.
     **************************************************************************************************/
    bool InitFBank();

    /**********************************************************************************************//**
     * @fn		float MFCC::Mel(unsigned int k);
     * @brief	求解美尔频率.
     * @return	第 k 个 FFT 对应的美尔频率.
     * @param [in]	k	FFT 索引.
     **************************************************************************************************/
    float Mel(unsigned int k);

private:
    /** @brief	配置参数. */
    CfgMFCC			m_cfgmfcc;
    /** @brief	特征类型. */
    unsigned int	m_featkind;
    /** @brief	滤波器权重. */
    float *			m_chlweight;
    /** @brief	海明窗. */
    float *			m_hamwin;
    /** @brief	倒谱提升窗. */
    float *			m_cepwin;
    /** @brief	DCT 变换表. */
    float *			m_costab;
    /** @brief	记录每个滤波器对应 FFT 索引的开始位置. */
    short *			m_bankstart;
    /** @brief	记录每个滤波器对应 FFT 的数目. */
    short *			m_bankleng;
    /** @brief	帧长点数. */
    unsigned int	m_frmsizelen;
    /** @brief	帧移点数. */
    unsigned int	m_frmratelen;
    /** @brief	FFT 点数. */
    unsigned int	m_fftnum;
    /** @brief	FFT 阶数. */
    unsigned int	m_fftorder;
    /** @brief	基本维数(差分前的维数) */
    unsigned int	m_basedim;
    /** @brief	最终的特征维数. */
    unsigned int	m_featdim;
    /** @brief	最小的 FFT 索引. */
    unsigned int	m_fftl;
    /** @brief	最大的 FFT 索引. */
    unsigned int	m_ffth;
};