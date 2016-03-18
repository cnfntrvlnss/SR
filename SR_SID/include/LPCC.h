/**********************************************************************************************//**
 * @file		LPCC.h
 * @brief		线性预测倒谱系数.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/13/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "feat.h"
#include "signal.h"
#include <string>
using namespace std;

/**********************************************************************************************//**
 * @struct  CfgLPCC
 * @brief   "线性预测倒谱系数"配置参数.
 **************************************************************************************************/
struct CfgLPCC
{
    /** @brief   特征类型. */
    string          feattype;
    /** @brief   采样率, 点数. */
    unsigned int    samplerate;
    /** @brief   帧长, 毫秒. */
    float	        framesize;
    /** @brief   帧移, 毫秒. */
    float	        framerate;
    /** @brief   是否移除直流. */
    bool	        removedc;
    /** @brief   倒谱提升系数. */
    float	        ceplifter;
    /** @brief   倒谱数. */
    unsigned int	cepnum;
    /** @brief   LPC 阶数. */
    unsigned int	lpcoder;
    /** @brief   Compression Factor fo PLP. */
    float	        compressfact;
    /** @brief   倒谱均值规整. */
    bool	        docmn;
    /** @brief   倒谱方差规整. */
    bool	        docvn;
    CfgLPCC() : feattype("LPCC_D"), samplerate(8000), framesize(20.f), framerate(10.f), removedc(true), ceplifter(22.f),
        cepnum(12), lpcoder(18), compressfact(0.33f), docmn(true), docvn(true) {};
};

/**********************************************************************************************//**
 * @class   LPCC
 * @brief   "线性预测倒谱系数"特征类.
 **************************************************************************************************/
class LPCC
{
public:
    /**********************************************************************************************//**
     * @fn      LPCC::LPCC();
     * @brief   基本的初始化工作.
     **************************************************************************************************/
    LPCC();

    /**********************************************************************************************//**
     * @fn      LPCC::~LPCC();
     * @brief   收尾工作, 释放内存.
     **************************************************************************************************/
    ~LPCC();

    /**********************************************************************************************//**
     * @fn      bool LPCC::Initialize(const CfgLPCC &cfglpcc);
     * @brief   初始化.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]  cfglpcc 特征配置.
     **************************************************************************************************/
    bool Initialize(const CfgLPCC &cfglpcc);

    /**********************************************************************************************//**
     * @fn      bool LPCC::DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;
     * @brief   提取特征.
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
     * @fn		LPCC::LPCC(const LPCC &lpcc);
     * @brief	禁用复制构造函数.
     * @param [in]	lpcc	"线性预测倒谱系数"对象.
     **************************************************************************************************/
    LPCC(const LPCC &lpcc);

    /**********************************************************************************************//**
     * @fn		LPCC & LPCC::operator=(const LPCC &lpcc);
     * @brief	禁用赋值操作符.
     * @return	该对象的一份浅拷贝.
     * @param [in]	lpcc	"线性预测倒谱系数"对象.
     **************************************************************************************************/
    LPCC & operator=(const LPCC &lpcc);

private:
    /**********************************************************************************************//**
     * @fn      bool LPCC::Wave2LPC(const float *s, float *a, float &re, float &te) const;
     * @brief   WAVE -> LPC.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]      s   语音信号.
     * @param [in,out]  a   LPC 系数.
     * @param [in,out]  re  The re.
     * @param [in,out]  te  The te.
     **************************************************************************************************/
    bool Wave2LPC(const float *s, float *a, float &re, float &te) const;

    /**********************************************************************************************//**
     * @fn      void LPCC::AutoCorrelate(const float *s, float *r, unsigned int p) const;
     * @brief   将自相关系数 0 至 p 存放到 r, r[0]为能量.
     * @param [in]      s       语音信号.
     * @param [in,out]  r       自相关系数.
     * @param [in]      p       阶数.
     **************************************************************************************************/
    void AutoCorrelate(const float *s, float *r, unsigned int p) const;

    /**********************************************************************************************//**
     * @fn      bool LPCC::Durbin(float *a, const float *r, float &E) const;
     * @brief   Durbins recursion to get LP coeffs for auto values.
     * @return	成功返回 true, 失败返回 false.
     * @param [in,out]  a   If non-null, the float * to process.
     * @param [in]      r   The const float * to process.
     * @param [in,out]  E   The float &amp; to process.
     **************************************************************************************************/
    bool Durbin(float *a, const float *r, float &E) const;

    /**********************************************************************************************//**
     * @fn  void LPCC::LPC2Cepstrum(const float *a, float *c) const;
     * @brief   transfer from lpc to cepstral coef.
     * @param [in]      a   The const float * to process.
     * @param [in,out]  c   If non-null, the float * to process.
     **************************************************************************************************/
    void LPC2Cepstrum(const float *a, float *c) const;

private:
    /** @brief   配置参数. */
    CfgLPCC		    m_cfglpcc;
    /** @brief   特征类型. */
    unsigned int    m_featkind;
    /** @brief   海明窗. */
    float *		    m_hamwin;
    /** @brief   倒谱提升窗. */
    float *		    m_cepwin;
    /** @brief   帧长点数. */
    unsigned int    m_frmsizelen;
    /** @brief   帧移点数. */
    unsigned int    m_frmratelen;
    /** @brief   基本维数(差分前的维数) */
    unsigned int    m_basedim;
    /** @brief   最终的特征维数. */
    unsigned int    m_featdim;
};