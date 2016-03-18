/**********************************************************************************************//**
 * @file		feat.h
 * @brief		���������Ķ���, ����/����������.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/11/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 **************************************************************************************************/
#pragma once
#include <stdlib.h>

/** @brief	������������, ��� 8 λ, ÿһλ����һ������. */
const unsigned int FEAT_BASE_MFCC = 0x00000001;
const unsigned int FEAT_BASE_PLP = 0x00000002;
const unsigned int FEAT_BASE_LPC = 0x00000004;
const unsigned int FEAT_BASE_LPCC = 0x00000008;
const unsigned int FEAT_BASE_PNCC = 0x00000010;
const unsigned int FEAT_BASE_LSP = 0x00000020;
/** @brief	�����ָ��������������. */
const unsigned int FEAT_BASE_MASK = 0x000000FF;

/** @brief	"_E" ��������. */
const unsigned int FEAT_HAS_ENERGY = 0x00000100;
/** @brief	"_0" ��׵���ϵ��, "_E" �� "_0" ����ͬʱ����. */
const unsigned int FEAT_HAS_ZEROC = 0x00000200;
/** @brief	"_D" һ�ײ��ϵ��. */
const unsigned int FEAT_HAS_DELTA = 0x00000400;
/** @brief	"_A" ���ײ��ϵ��. */
const unsigned int FEAT_HAS_ACCS = 0x00000800;
/** @brief	"_T" ���ײ��ϵ��. */
const unsigned int FEAT_HAS_THIRD = 0x00001000;

/** @brief	���׾�ֵ����. */
const unsigned int FEAT_DO_CMN = 0x00002000;
/** @brief	���׷������. */
const unsigned int FEAT_DO_CVN = 0x00004000;
/** @brief	������˲�. */
const unsigned int FEAT_DO_RASTA = 0x00008000;

/**********************************************************************************************//**
 * @struct	FeatInfo
 * @brief	�����ļ���ͷ��Ϣ.
 **************************************************************************************************/
struct FeatInfo
{
    /** @brief	��������. */
    unsigned int featkind;
    /** @brief	����ά��. */
    unsigned int featdim;
    /** @brief	֡��. */
    unsigned int frmnum;
    /** @brief	֡��, ����. */
    float frmrate;
    /** @brief	֡��, ����. */
    float frmsize;
    FeatInfo() : featkind(0), featdim(0), frmnum(0), frmrate(0.f), frmsize(0.f) {};
};

/**********************************************************************************************//**
 * @fn		bool LoadFeat(const char *featfile, float *&featbuf, FeatInfo &featinfo);
 * @brief	��������.
 * @return	�ɹ����� true, ʧ�ܷ��� false.
 * @param [in]		featfile	�����ļ�·��.
 * @param [in,out]	featbuf 	����������.
 * @param [in,out]	featinfo	������Ϣ.
 * @note	1. �����������ɸú�������, �� @ref FreeFeat �����ͷ�. 2. ����ʧ�ܵ�ԭ�������: 1) ���ļ�ʧ��; 2) �ڴ治��; 3) �������ļ�.
 **************************************************************************************************/
bool LoadFeat(const char *featfile, float *&featbuf, FeatInfo &featinfo);

/**********************************************************************************************//**
 * @fn		void FreeFeat(float *&featbuf);
 * @brief	�ͷ�����������.
 * @param [in,out]	featbuf		����������.
 * @note	���� @ref LoadFeat ����������ڴ�, ����øú����ͷ�.
 **************************************************************************************************/
void FreeFeat(float *&featbuf);

/**********************************************************************************************//**
 * @fn		bool SaveFeat(const char *featfile, const float *featbuf, const FeatInfo &featinfo);
 * @brief	��������.
 * @return	�ɹ����� true, ʧ�ܷ��� false.
 * @param [in]	featfile	�����ļ�·��.
 * @param [in]	featbuf 	����������.
 * @param [in]	featinfo	������Ϣ.
 * @note	����ʧ�ܵ�ԭ�����Ϊ: 1) ������Ϣ���Ի򻺳���Ϊ��; 2) ���ļ�ʧ��; 3) ���̿ռ䲻��.
 **************************************************************************************************/
bool SaveFeat(const char *featfile, const float *featbuf, const FeatInfo &featinfo);

/**********************************************************************************************//**
 * @fn		bool IsSameFeat(const FeatInfo &featinfo1, const FeatInfo &featinfo2);
 * @brief	����������Ϣ�ж��Ƿ�Ϊͬһ������.
 * @return	��ͬ�������� true, ��ͬ�������� false.
 * @param [in]	featinfo1	���� 1 �ļ�ͷ.
 * @param [in]	featinfo2	���� 2 �ļ�ͷ.
 **************************************************************************************************/
bool IsSameFeat(const FeatInfo &featinfo1, const FeatInfo &featinfo2);

/**********************************************************************************************//**
 * @fn		bool LoadFeatInfo(const char *featfile, FeatInfo &featinfo);
 * @brief	��ȡ�����ļ���ͷ��Ϣ.
 * @return	�ɹ����� true, ʧ�ܷ��� false.
 * @param [in]		featfile	�����ļ�·��.
 * @param [in,out]	featinfo	������Ϣ.
 * @note	����ʧ�ܵ�ԭ�����Ϊ: 1) ���ļ�ʧ��; 2) �������ļ�.
 **************************************************************************************************/
bool LoadFeatInfo(const char *featfile, FeatInfo &featinfo);