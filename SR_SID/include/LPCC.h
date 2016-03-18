/**********************************************************************************************//**
 * @file		LPCC.h
 * @brief		����Ԥ�⵹��ϵ��.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/13/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 **************************************************************************************************/
#pragma once
#include "feat.h"
#include "signal.h"
#include <string>
using namespace std;

/**********************************************************************************************//**
 * @struct  CfgLPCC
 * @brief   "����Ԥ�⵹��ϵ��"���ò���.
 **************************************************************************************************/
struct CfgLPCC
{
    /** @brief   ��������. */
    string          feattype;
    /** @brief   ������, ����. */
    unsigned int    samplerate;
    /** @brief   ֡��, ����. */
    float	        framesize;
    /** @brief   ֡��, ����. */
    float	        framerate;
    /** @brief   �Ƿ��Ƴ�ֱ��. */
    bool	        removedc;
    /** @brief   ��������ϵ��. */
    float	        ceplifter;
    /** @brief   ������. */
    unsigned int	cepnum;
    /** @brief   LPC ����. */
    unsigned int	lpcoder;
    /** @brief   Compression Factor fo PLP. */
    float	        compressfact;
    /** @brief   ���׾�ֵ����. */
    bool	        docmn;
    /** @brief   ���׷������. */
    bool	        docvn;
    CfgLPCC() : feattype("LPCC_D"), samplerate(8000), framesize(20.f), framerate(10.f), removedc(true), ceplifter(22.f),
        cepnum(12), lpcoder(18), compressfact(0.33f), docmn(true), docvn(true) {};
};

/**********************************************************************************************//**
 * @class   LPCC
 * @brief   "����Ԥ�⵹��ϵ��"������.
 **************************************************************************************************/
class LPCC
{
public:
    /**********************************************************************************************//**
     * @fn      LPCC::LPCC();
     * @brief   �����ĳ�ʼ������.
     **************************************************************************************************/
    LPCC();

    /**********************************************************************************************//**
     * @fn      LPCC::~LPCC();
     * @brief   ��β����, �ͷ��ڴ�.
     **************************************************************************************************/
    ~LPCC();

    /**********************************************************************************************//**
     * @fn      bool LPCC::Initialize(const CfgLPCC &cfglpcc);
     * @brief   ��ʼ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]  cfglpcc ��������.
     **************************************************************************************************/
    bool Initialize(const CfgLPCC &cfglpcc);

    /**********************************************************************************************//**
     * @fn      bool LPCC::DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;
     * @brief   ��ȡ����.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]		wavbuf		�����ڴ�.
     * @param [in]		wavlen		��������.
     * @param [in]		smprate		������.
     * @param [in,out]	featbuf 	�����ڴ�.
     * @param [in,out]	featinfo	������Ϣ.
     * @note	�����ڴ��ɸú�������, �� @ref FreeFeat �ͷ�.
     **************************************************************************************************/
    bool DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;

private:
    /**********************************************************************************************//**
     * @fn		LPCC::LPCC(const LPCC &lpcc);
     * @brief	���ø��ƹ��캯��.
     * @param [in]	lpcc	"����Ԥ�⵹��ϵ��"����.
     **************************************************************************************************/
    LPCC(const LPCC &lpcc);

    /**********************************************************************************************//**
     * @fn		LPCC & LPCC::operator=(const LPCC &lpcc);
     * @brief	���ø�ֵ������.
     * @return	�ö����һ��ǳ����.
     * @param [in]	lpcc	"����Ԥ�⵹��ϵ��"����.
     **************************************************************************************************/
    LPCC & operator=(const LPCC &lpcc);

private:
    /**********************************************************************************************//**
     * @fn      bool LPCC::Wave2LPC(const float *s, float *a, float &re, float &te) const;
     * @brief   WAVE -> LPC.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]      s   �����ź�.
     * @param [in,out]  a   LPC ϵ��.
     * @param [in,out]  re  The re.
     * @param [in,out]  te  The te.
     **************************************************************************************************/
    bool Wave2LPC(const float *s, float *a, float &re, float &te) const;

    /**********************************************************************************************//**
     * @fn      void LPCC::AutoCorrelate(const float *s, float *r, unsigned int p) const;
     * @brief   �������ϵ�� 0 �� p ��ŵ� r, r[0]Ϊ����.
     * @param [in]      s       �����ź�.
     * @param [in,out]  r       �����ϵ��.
     * @param [in]      p       ����.
     **************************************************************************************************/
    void AutoCorrelate(const float *s, float *r, unsigned int p) const;

    /**********************************************************************************************//**
     * @fn      bool LPCC::Durbin(float *a, const float *r, float &E) const;
     * @brief   Durbins recursion to get LP coeffs for auto values.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
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
    /** @brief   ���ò���. */
    CfgLPCC		    m_cfglpcc;
    /** @brief   ��������. */
    unsigned int    m_featkind;
    /** @brief   ������. */
    float *		    m_hamwin;
    /** @brief   ����������. */
    float *		    m_cepwin;
    /** @brief   ֡������. */
    unsigned int    m_frmsizelen;
    /** @brief   ֡�Ƶ���. */
    unsigned int    m_frmratelen;
    /** @brief   ����ά��(���ǰ��ά��) */
    unsigned int    m_basedim;
    /** @brief   ���յ�����ά��. */
    unsigned int    m_featdim;
};