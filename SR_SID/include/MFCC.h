/**********************************************************************************************//**
 * @file		MFCC.h
 * @brief		����Ƶ�ʵ���ϵ��.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/12/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 **************************************************************************************************/
#pragma once
#include "feat.h"
#include "signal.h"
#include <string>
using namespace std;

/**********************************************************************************************//**
 * @struct  CfgMFCC
 * @brief   "����Ƶ�ʵ���ϵ��"���ò���.
 **************************************************************************************************/
struct CfgMFCC
{
    /** @brief	��������. */
    string			feattype;
    /** @brief	������, ����. */
    unsigned int	samplerate;
    /** @brief	֡��, ����. */
    float			framesize;
    /** @brief	֡��, ����. */
    float			framerate;
    /** @brief	�Ƿ��Ƴ�ֱ��. */
    bool			removedc;
    /** @brief	��������ϵ��. */
    float			ceplifter;
    /** @brief	�˲�����Ŀ. */
    unsigned int	chlnum;
    /** @brief	������. */
    unsigned int	cepnum;
    /** @brief	�½�ֹƵ��. */
    float			lowpass;
    /** @brief	�Ͻ�ֹƵ��. */
    float			highpass;
    /** @brief	������һ��. */
    bool			normenergy;
    /** @brief	������������. */
    float			energyscale;
    /** @brief	��������. */
    float			silfloor;
    /** @brief	���׾�ֵ����. */
    bool			docmn;
    /** @brief	���׷������. */
    bool			docvn;
    /** @brief	RASTA �˲�. */
    bool			dorasta;
    CfgMFCC() : feattype("MFCC_E_A"), samplerate(8000), framesize(20.f), framerate(10.f), removedc(false), ceplifter(22.f),
        chlnum(24), cepnum(19), lowpass(250.f), highpass(3800.f), normenergy(true), energyscale(19.f), silfloor(50.f),
        docmn(true), docvn(true), dorasta(false) {};
};

/**********************************************************************************************//**
 * @class	MFCC
 * @brief	"����Ƶ�ʵ���ϵ��"������.
 **************************************************************************************************/
class MFCC
{
public:
    /**********************************************************************************************//**
     * @fn		MFCC::MFCC();
     * @brief	�����ĳ�ʼ������.
     **************************************************************************************************/
    MFCC();

    /**********************************************************************************************//**
     * @fn		MFCC::~MFCC();
     * @brief	��β����, �ͷ��ڴ�.
     **************************************************************************************************/
    ~MFCC();

    /**********************************************************************************************//**
     * @fn		bool MFCC::Initialize(const CfgMFCC &cfgmfcc);
     * @brief	��ʼ��.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]	cfgmfcc	��������.
     **************************************************************************************************/
    bool Initialize(const CfgMFCC &cfgmfcc);

    /**********************************************************************************************//**
     * @fn		bool MFCC::DoExtract(const short *wavbuf, unsigned int wavlen, unsigned int smprate, float *&featbuf, FeatInfo &featinfo) const;
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
     * @fn		MFCC::MFCC(const MFCC &mfcc);
     * @brief	���ø��ƹ��캯��.
     * @param [in]	mfcc	"����Ƶ�ʵ���ϵ��"����.
     **************************************************************************************************/
    MFCC(const MFCC &mfcc);

    /**********************************************************************************************//**
     * @fn		MFCC & MFCC::operator=(const MFCC &mfcc);
     * @brief	���ø�ֵ������.
     * @return	�ö����һ��ǳ����.
     * @param [in]	mfcc	"����Ƶ�ʵ���ϵ��"����.
     **************************************************************************************************/
    MFCC & operator=(const MFCC &mfcc);

private:
    /**********************************************************************************************//**
     * @fn		bool MFCC::InitFBank();
     * @brief	��ʼ���˲�����.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     **************************************************************************************************/
    bool InitFBank();

    /**********************************************************************************************//**
     * @fn		float MFCC::Mel(unsigned int k);
     * @brief	�������Ƶ��.
     * @return	�� k �� FFT ��Ӧ������Ƶ��.
     * @param [in]	k	FFT ����.
     **************************************************************************************************/
    float Mel(unsigned int k);

private:
    /** @brief	���ò���. */
    CfgMFCC			m_cfgmfcc;
    /** @brief	��������. */
    unsigned int	m_featkind;
    /** @brief	�˲���Ȩ��. */
    float *			m_chlweight;
    /** @brief	������. */
    float *			m_hamwin;
    /** @brief	����������. */
    float *			m_cepwin;
    /** @brief	DCT �任��. */
    float *			m_costab;
    /** @brief	��¼ÿ���˲�����Ӧ FFT �����Ŀ�ʼλ��. */
    short *			m_bankstart;
    /** @brief	��¼ÿ���˲�����Ӧ FFT ����Ŀ. */
    short *			m_bankleng;
    /** @brief	֡������. */
    unsigned int	m_frmsizelen;
    /** @brief	֡�Ƶ���. */
    unsigned int	m_frmratelen;
    /** @brief	FFT ����. */
    unsigned int	m_fftnum;
    /** @brief	FFT ����. */
    unsigned int	m_fftorder;
    /** @brief	����ά��(���ǰ��ά��) */
    unsigned int	m_basedim;
    /** @brief	���յ�����ά��. */
    unsigned int	m_featdim;
    /** @brief	��С�� FFT ����. */
    unsigned int	m_fftl;
    /** @brief	���� FFT ����. */
    unsigned int	m_ffth;
};