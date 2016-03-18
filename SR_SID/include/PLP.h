/**********************************************************************************************//**
 * @file		PLP.h
 * @brief		��֪����Ԥ��.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/14/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
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
 * @brief   "��֪����Ԥ��"���ò���.
 **************************************************************************************************/
struct CfgPLP
{
    /** @brief   ��������. */
    string          feattype;
    /** @brief   ������, ����. */
    unsigned int    samplerate;
    /** @brief   ֡��, ����. */
    float           framesize;
    /** @brief   ֡��, ����. */
    float	        framerate;
    /** @brief   �Ƿ��Ƴ�ֱ��. */
    bool	        removedc;
    /** @brief   ��������ϵ��. */
    float	        ceplifter;
    /** @brief   �˲�����Ŀ. */
    unsigned int    chlnum;
    /** @brief   ������. */
    unsigned int    cepnum;
    /** @brief   �½�ֹƵ��. */
    float	        lowpass;
    /** @brief   �Ͻ�ֹƵ��. */
    float	        highpass;
    /** @brief   LPC ����. */
    unsigned int    lpcoder;
    /** @brief   Compression Factor fo PLP. */
    float	        compressfact;
    /** @brief   ���׾�ֵ����. */
    bool	        docmn;
    /** @brief   ���׷������. */
    bool	        docvn;
    /** @brief   RASTA �˲�. */
    bool	        dorasta;
    CfgPLP() : feattype("PLP_E_A"), samplerate(8000), framesize(20.f), framerate(10.f), removedc(false), ceplifter(22.f),
        chlnum(24), cepnum(19), lowpass(250.f), highpass(3800.f), lpcoder(18), compressfact(0.33f), docmn(true),
        docvn(true), dorasta(false) {};
};

/**********************************************************************************************//**
 * @class   PLP
 * @brief   "��֪����Ԥ��"������.
 **************************************************************************************************/
class PLP
{
public:
    /**********************************************************************************************//**
     * @fn      PLP::PLP();
     * @brief   �����ĳ�ʼ������.
     **************************************************************************************************/
    PLP();

    /**********************************************************************************************//**
     * @fn      PLP::~PLP();
     * @brief   ��β����, �ͷ��ڴ�.
     **************************************************************************************************/
    ~PLP();

    /**********************************************************************************************//**
     * @fn      bool PLP::Initialize(const CfgPLP &cfgplp);
     * @brief	��ʼ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param   cfgplp  ��������.
     **************************************************************************************************/
    bool Initialize(const CfgPLP &cfgplp);

    /**********************************************************************************************//**
     * @fn      bool PLP::DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;
     * @brief	��ȡ����.
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
     * @fn		PLP::PLP(const PLP &plp);
     * @brief	���ø��ƹ��캯��.
     * @param [in]	plp	"��֪����Ԥ��"����.
     **************************************************************************************************/
    PLP(const PLP &plp);

    /**********************************************************************************************//**
     * @fn		PLP & PLP::operator=(const PLP &plp);
     * @brief	���ø�ֵ������.
     * @return	�ö����һ��ǳ����.
     * @param [in]	plp	"��֪����Ԥ��"����.
     **************************************************************************************************/
    PLP & operator=(const PLP &plp);

private:
    /** @brief   ���ò���. */
    PlpOptions      m_plp_opts;
    /** @brief   ��������. */
    unsigned int    m_featkind;
    /** @brief   ֡������. */
    unsigned int    m_frmsizelen;
    /** @brief   ֡�Ƶ���. */
    unsigned int    m_frmratelen;
    /** @brief   ����ά��(���ǰ��ά��) */
    unsigned int    m_basedim;
    /** @brief   ���յ�����ά��. */
    unsigned int    m_featdim;
};