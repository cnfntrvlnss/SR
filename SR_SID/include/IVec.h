/**********************************************************************************************//**
 * @file		IVec.h
 * @brief		提取总变化因子.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/20/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 * @note        训练算法: Kenny P, Boulianne G, Dumouchel P. Eigenvoice modeling with sparse training data[J]. IEEE Transactions on Speech and Audio Processing, 2005, 13(3): 345-354.
 * @note        简化算法: Matejka P, Glembek O, Castaldo F, et al. Full-covariance UBM and heavy-tailed PLDA in i-vector speaker verification[C]. 2011 IEEE International Conference on Acoustics, Speech and Signal Processing (ICASSP), 2011: 4828-4831.
 **************************************************************************************************/
#pragma once
#include "DiagGMM.h"

/**********************************************************************************************//**
 * @class	IVector
 * @brief	总变化因子提取器.
 **************************************************************************************************/
class IVector
{
public:
    /**********************************************************************************************//**
     * @fn      IVector::IVector();
     * @brief	默认构造.
     **************************************************************************************************/
    IVector() : m_ubm(NULL), m_dim(0), m_mix(0), m_rank(0) {};

    /**********************************************************************************************//**
     * @fn      IVector::IVector(const DiagGMM *ubm);
     * @brief	构造, 初始化.
     * @param [in]		ubm		混合高斯-通用背景模型.
     **************************************************************************************************/
    IVector(const DiagGMM *ubm);

    /**********************************************************************************************//**
     * @fn      bool IVector::Load(const char *tmodel);
     * @brief	加载模型.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		tmodel		模型路径.
     * @note    失败的原因: 1. 模型路径不正确; 2. 和混合高斯-通用背景模型不匹配; 3. 内存不足.
     **************************************************************************************************/
    bool Load(const char *tmodel);

    /**********************************************************************************************//**
     * @fn      bool IVector::Save(const char *tmodel) const;
     * @brief	保存模型.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		tmodel		模型路径.
     **************************************************************************************************/
    bool Save(const char *tmodel) const;

    /**********************************************************************************************//**
     * @fn      void IVector::Extract(const DiagStat2 &dstat, fvec &ivec) const;
     * @brief	提取总变化因子.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		dstat		充分统计量.
     * @param [in,out]	ivec		总变化因子.
     * @note    这里的充分统计量已经过中心归一化.
     **************************************************************************************************/
    void Extract(const DiagStat2 &dstat, fvec &ivec) const;

protected:
    /** @brief	混合高斯-通用背景模型. */
    const DiagGMM *     m_ubm;
    /** @brief	维数. */
    unsigned int        m_dim;
    /** @brief	混合数. */
    unsigned int        m_mix;
    /** @brief	秩, 总变化因子维数. */
    unsigned int        m_rank;
    /** @brief	T. */
    fmat                m_T;
    /** @brief	加速用, T^t * Σ^(-1). */
    fmat                m_Tt;
    /** @brief	加速用, T^t * Σ^(-1) * T. */
    fcube               m_TtT;
};