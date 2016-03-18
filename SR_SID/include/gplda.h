/**********************************************************************************************//**
 * @file		gplda.h
 * @brief		高斯概率线性鉴别分析 (Gaussian PLDA) 注册及打分.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/23/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 * @note        打分方法参照 : Garcia-Romero D, Espy-Wilson C Y. Analysis of i-vector length normalization in speaker recognition systems[C], Interspeech. 2011: 249-252.
 **************************************************************************************************/
#pragma once
#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4702)
#include <armadillo>
#pragma warning(pop)
using namespace arma;

/**********************************************************************************************//**
 * @class	GaussPLDA
 * @brief	高斯概率线性鉴别分析.
 **************************************************************************************************/
class GaussPLDA
{
public:
    friend class GPLDASys;

public:
    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::Load(const char *mpath);
     * @brief   加载模型.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		mpath		模型路径.
     **************************************************************************************************/
    bool Load(const char *mpath);

    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::Save(const char *mpath);
     * @brief   保存模型.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		mpath		模型路径.
     **************************************************************************************************/
    bool Save(const char *mpath) const;

    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::Enroll(const fvec &ivec, frowvec &tarmdl) const;
     * @brief   注册说话人模型.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		ivec		总变化因子.
     * @param [in,out]	tarmdl		说话人模型.
     * @note    针对训练语音.
     **************************************************************************************************/
    bool Enroll(const fvec &ivec, frowvec &tarmdl) const;

    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::ExFeat(const fvec &ivec, fvec &tstfeat) const;
     * @brief   提取测试音频的特征.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]		ivec		总变化因子.
     * @param [in,out]	tstfeat		特征(广义).
     * @note    将该特征存下, 可提高匹对速度, 适用于历史检索等场合.
     **************************************************************************************************/
    bool ExFeat(const fvec &ivec, fvec &tstfeat) const;

    /**********************************************************************************************//**
     * @fn      float GaussPLDA::Match(const frowvec &tarmdl, const fvec &tstfeat) const;
     * @brief   匹对, 计算相似度.
     * @return	相似度, 值越大, 越相似.
     * @param [in]		tarmdl		说话人模型.
     * @param [in]	    tstfeat		特征(广义).
     **************************************************************************************************/
    float Match(const frowvec &tarmdl, const fvec &tstfeat) const;

private:
    /** @brief	维数. */
    unsigned int    m_dim;
    /** @brief	秩, 等于 V 矩阵的列数. */
    unsigned int    m_rank;
    /** @brief	均值. */
    fvec	m_mu;
    /** @brief	载荷矩阵. */
    fmat	m_v;
    /** @brief	残差方差. */
    fmat	m_sigma;
    /** @brief	P 矩阵, 参照文献公式(7). */
    fmat    m_P;
    /** @brief	Q 矩阵, 参照文献公式(7). */
    fmat    m_Q;
};