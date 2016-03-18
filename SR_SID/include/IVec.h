/**********************************************************************************************//**
 * @file		IVec.h
 * @brief		��ȡ�ܱ仯����.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		7/20/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 * @note        ѵ���㷨: Kenny P, Boulianne G, Dumouchel P. Eigenvoice modeling with sparse training data[J]. IEEE Transactions on Speech and Audio Processing, 2005, 13(3): 345-354.
 * @note        ���㷨: Matejka P, Glembek O, Castaldo F, et al. Full-covariance UBM and heavy-tailed PLDA in i-vector speaker verification[C]. 2011 IEEE International Conference on Acoustics, Speech and Signal Processing (ICASSP), 2011: 4828-4831.
 **************************************************************************************************/
#pragma once
#include "DiagGMM.h"

/**********************************************************************************************//**
 * @class	IVector
 * @brief	�ܱ仯������ȡ��.
 **************************************************************************************************/
class IVector
{
public:
    /**********************************************************************************************//**
     * @fn      IVector::IVector();
     * @brief	Ĭ�Ϲ���.
     **************************************************************************************************/
    IVector() : m_ubm(NULL), m_dim(0), m_mix(0), m_rank(0) {};

    /**********************************************************************************************//**
     * @fn      IVector::IVector(const DiagGMM *ubm);
     * @brief	����, ��ʼ��.
     * @param [in]		ubm		��ϸ�˹-ͨ�ñ���ģ��.
     **************************************************************************************************/
    IVector(const DiagGMM *ubm);

    /**********************************************************************************************//**
     * @fn      bool IVector::Load(const char *tmodel);
     * @brief	����ģ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		tmodel		ģ��·��.
     * @note    ʧ�ܵ�ԭ��: 1. ģ��·������ȷ; 2. �ͻ�ϸ�˹-ͨ�ñ���ģ�Ͳ�ƥ��; 3. �ڴ治��.
     **************************************************************************************************/
    bool Load(const char *tmodel);

    /**********************************************************************************************//**
     * @fn      bool IVector::Save(const char *tmodel) const;
     * @brief	����ģ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		tmodel		ģ��·��.
     **************************************************************************************************/
    bool Save(const char *tmodel) const;

    /**********************************************************************************************//**
     * @fn      void IVector::Extract(const DiagStat2 &dstat, fvec &ivec) const;
     * @brief	��ȡ�ܱ仯����.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		dstat		���ͳ����.
     * @param [in,out]	ivec		�ܱ仯����.
     * @note    ����ĳ��ͳ�����Ѿ������Ĺ�һ��.
     **************************************************************************************************/
    void Extract(const DiagStat2 &dstat, fvec &ivec) const;

protected:
    /** @brief	��ϸ�˹-ͨ�ñ���ģ��. */
    const DiagGMM *     m_ubm;
    /** @brief	ά��. */
    unsigned int        m_dim;
    /** @brief	�����. */
    unsigned int        m_mix;
    /** @brief	��, �ܱ仯����ά��. */
    unsigned int        m_rank;
    /** @brief	T. */
    fmat                m_T;
    /** @brief	������, T^t * ��^(-1). */
    fmat                m_Tt;
    /** @brief	������, T^t * ��^(-1) * T. */
    fcube               m_TtT;
};