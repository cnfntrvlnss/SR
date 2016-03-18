/**********************************************************************************************//**
 * @file		PLP.h
 * @brief		感知线性预测.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/14/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "feat.h"
#include "signal.h"
#pragma warning(push)
#pragma warning(disable:4100)
#include "feat/feature-plp.h"
#pragma warning(pop)
#include <string>
using namespace std;
using namespace kaldi;

/**********************************************************************************************//**
 * @struct  CfgPLP
 * @brief   "感知线性预测"配置参数.
 **************************************************************************************************/
struct CfgPLP
{
    /** @brief   特征类型. */
    string          feattype;
    /** @brief   采样率, 点数. */
    unsigned int    samplerate;
    /** @brief   帧长, 毫秒. */
    float           framesize;
    /** @brief   帧移, 毫秒. */
    float	        framerate;
    /** @brief   是否移除直流. */
    bool	        removedc;
    /** @brief   倒谱提升系数. */
    float	        ceplifter;
    /** @brief   滤波器数目. */
    unsigned int    chlnum;
    /** @brief   倒谱数. */
    unsigned int    cepnum;
    /** @brief   下截止频率. */
    float	        lowpass;
    /** @brief   上截止频率. */
    float	        highpass;
    /** @brief   LPC 阶数. */
    unsigned int    lpcoder;
    /** @brief   Compression Factor fo PLP. */
    float	        compressfact;
    /** @brief   倒谱均值规整. */
    bool	        docmn;
    /** @brief   倒谱方差规整. */
    bool	        docvn;
    /** @brief   RASTA 滤波. */
    bool	        dorasta;
    CfgPLP() : feattype("PLP_E_A"), samplerate(8000), framesize(20.f), framerate(10.f), removedc(false), ceplifter(22.f),
        chlnum(24), cepnum(19), lowpass(250.f), highpass(3800.f), lpcoder(18), compressfact(0.33f), docmn(true),
        docvn(true), dorasta(false) {};
};

/**********************************************************************************************//**
 * @class   PLP
 * @brief   "感知线性预测"特征类.
 **************************************************************************************************/
class PLP
{
public:
    /**********************************************************************************************//**
     * @fn      PLP::PLP();
     * @brief   基本的初始化工作.
     **************************************************************************************************/
    PLP();

    /**********************************************************************************************//**
     * @fn      PLP::~PLP();
     * @brief   收尾工作, 释放内存.
     **************************************************************************************************/
    ~PLP();

    /**********************************************************************************************//**
     * @fn      bool PLP::Initialize(const CfgPLP &cfgplp);
     * @brief	初始化.
     * @return	成功返回 true, 失败返回 false.
     * @param   cfgplp  特征配置.
     **************************************************************************************************/
    bool Initialize(const CfgPLP &cfgplp);

    /**********************************************************************************************//**
     * @fn      bool PLP::DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;
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
     * @fn		PLP::PLP(const PLP &plp);
     * @brief	禁用复制构造函数.
     * @param [in]	plp	"感知线性预测"对象.
     **************************************************************************************************/
    PLP(const PLP &plp);

    /**********************************************************************************************//**
     * @fn		PLP & PLP::operator=(const PLP &plp);
     * @brief	禁用赋值操作符.
     * @return	该对象的一份浅拷贝.
     * @param [in]	plp	"感知线性预测"对象.
     **************************************************************************************************/
    PLP & operator=(const PLP &plp);

private:
    /** @brief   配置参数. */
    PlpOptions      m_plp_opts;
    /** @brief   特征类型. */
    unsigned int    m_featkind;
    /** @brief   帧长点数. */
    unsigned int    m_frmsizelen;
    /** @brief   帧移点数. */
    unsigned int    m_frmratelen;
    /** @brief   基本维数(差分前的维数) */
    unsigned int    m_basedim;
    /** @brief   最终的特征维数. */
    unsigned int    m_featdim;
};