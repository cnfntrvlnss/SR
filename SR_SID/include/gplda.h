/**********************************************************************************************//**
 * @file		gplda.h
 * @brief		��˹�������Լ������ (Gaussian PLDA) ע�ἰ���.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		7/23/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 * @note        ��ַ������� : Garcia-Romero D, Espy-Wilson C Y. Analysis of i-vector length normalization in speaker recognition systems[C], Interspeech. 2011: 249-252.
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
 * @brief	��˹�������Լ������.
 **************************************************************************************************/
class GaussPLDA
{
public:
    friend class GPLDASys;

public:
    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::Load(const char *mpath);
     * @brief   ����ģ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		mpath		ģ��·��.
     **************************************************************************************************/
    bool Load(const char *mpath);

    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::Save(const char *mpath);
     * @brief   ����ģ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		mpath		ģ��·��.
     **************************************************************************************************/
    bool Save(const char *mpath) const;

    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::Enroll(const fvec &ivec, frowvec &tarmdl) const;
     * @brief   ע��˵����ģ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		ivec		�ܱ仯����.
     * @param [in,out]	tarmdl		˵����ģ��.
     * @note    ���ѵ������.
     **************************************************************************************************/
    bool Enroll(const fvec &ivec, frowvec &tarmdl) const;

    /**********************************************************************************************//**
     * @fn      bool GaussPLDA::ExFeat(const fvec &ivec, fvec &tstfeat) const;
     * @brief   ��ȡ������Ƶ������.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		ivec		�ܱ仯����.
     * @param [in,out]	tstfeat		����(����).
     * @note    ������������, �����ƥ���ٶ�, ��������ʷ�����ȳ���.
     **************************************************************************************************/
    bool ExFeat(const fvec &ivec, fvec &tstfeat) const;

    /**********************************************************************************************//**
     * @fn      float GaussPLDA::Match(const frowvec &tarmdl, const fvec &tstfeat) const;
     * @brief   ƥ��, �������ƶ�.
     * @return	���ƶ�, ֵԽ��, Խ����.
     * @param [in]		tarmdl		˵����ģ��.
     * @param [in]	    tstfeat		����(����).
     **************************************************************************************************/
    float Match(const frowvec &tarmdl, const fvec &tstfeat) const;

private:
    /** @brief	ά��. */
    unsigned int    m_dim;
    /** @brief	��, ���� V ���������. */
    unsigned int    m_rank;
    /** @brief	��ֵ. */
    fvec	m_mu;
    /** @brief	�غɾ���. */
    fmat	m_v;
    /** @brief	�в��. */
    fmat	m_sigma;
    /** @brief	P ����, �������׹�ʽ(7). */
    fmat    m_P;
    /** @brief	Q ����, �������׹�ʽ(7). */
    fmat    m_Q;
};