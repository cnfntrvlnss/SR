/**********************************************************************************************//**
 * @file		feat.h
 * @brief		基本特征的定义, 加载/保存特征等.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/11/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include <stdlib.h>

/** @brief	基本特征类型, 最后 8 位, 每一位代表一种特征. */
const unsigned int FEAT_BASE_MFCC = 0x00000001;
const unsigned int FEAT_BASE_PLP = 0x00000002;
const unsigned int FEAT_BASE_LPC = 0x00000004;
const unsigned int FEAT_BASE_LPCC = 0x00000008;
const unsigned int FEAT_BASE_PNCC = 0x00000010;
const unsigned int FEAT_BASE_LSP = 0x00000020;
/** @brief	用来恢复出最基本的类型. */
const unsigned int FEAT_BASE_MASK = 0x000000FF;

/** @brief	"_E" 对数能量. */
const unsigned int FEAT_HAS_ENERGY = 0x00000100;
/** @brief	"_0" 零阶倒谱系数, "_E" 和 "_0" 不能同时设置. */
const unsigned int FEAT_HAS_ZEROC = 0x00000200;
/** @brief	"_D" 一阶差分系数. */
const unsigned int FEAT_HAS_DELTA = 0x00000400;
/** @brief	"_A" 二阶差分系数. */
const unsigned int FEAT_HAS_ACCS = 0x00000800;
/** @brief	"_T" 三阶差分系数. */
const unsigned int FEAT_HAS_THIRD = 0x00001000;

/** @brief	倒谱均值规整. */
const unsigned int FEAT_DO_CMN = 0x00002000;
/** @brief	倒谱方差规整. */
const unsigned int FEAT_DO_CVN = 0x00004000;
/** @brief	相对谱滤波. */
const unsigned int FEAT_DO_RASTA = 0x00008000;

/**********************************************************************************************//**
 * @struct	FeatInfo
 * @brief	特征文件的头信息.
 **************************************************************************************************/
struct FeatInfo
{
    /** @brief	特征类型. */
    unsigned int featkind;
    /** @brief	特征维数. */
    unsigned int featdim;
    /** @brief	帧数. */
    unsigned int frmnum;
    /** @brief	帧移, 毫秒. */
    float frmrate;
    /** @brief	帧长, 毫秒. */
    float frmsize;
    FeatInfo() : featkind(0), featdim(0), frmnum(0), frmrate(0.f), frmsize(0.f) {};
};

/**********************************************************************************************//**
 * @fn		bool LoadFeat(const char *featfile, float *&featbuf, FeatInfo &featinfo);
 * @brief	加载特征.
 * @return	成功返回 true, 失败返回 false.
 * @param [in]		featfile	特征文件路径.
 * @param [in,out]	featbuf 	特征缓冲区.
 * @param [in,out]	featinfo	特征信息.
 * @note	1. 特征缓冲区由该函数分配, 由 @ref FreeFeat 函数释放. 2. 导致失败的原因可能是: 1) 打开文件失败; 2) 内存不足; 3) 非特征文件.
 **************************************************************************************************/
bool LoadFeat(const char *featfile, float *&featbuf, FeatInfo &featinfo);

/**********************************************************************************************//**
 * @fn		void FreeFeat(float *&featbuf);
 * @brief	释放特征缓冲区.
 * @param [in,out]	featbuf		特征缓冲区.
 * @note	调用 @ref LoadFeat 函数会分配内存, 需调用该函数释放.
 **************************************************************************************************/
void FreeFeat(float *&featbuf);

/**********************************************************************************************//**
 * @fn		bool SaveFeat(const char *featfile, const float *featbuf, const FeatInfo &featinfo);
 * @brief	保存特征.
 * @return	成功返回 true, 失败返回 false.
 * @param [in]	featfile	特征文件路径.
 * @param [in]	featbuf 	特征缓冲区.
 * @param [in]	featinfo	特征信息.
 * @note	导致失败的原因可能为: 1) 特征信息不对或缓冲区为空; 2) 打开文件失败; 3) 磁盘空间不足.
 **************************************************************************************************/
bool SaveFeat(const char *featfile, const float *featbuf, const FeatInfo &featinfo);

/**********************************************************************************************//**
 * @fn		bool IsSameFeat(const FeatInfo &featinfo1, const FeatInfo &featinfo2);
 * @brief	根据特征信息判断是否为同一种特征.
 * @return	相同特征返回 true, 不同特征返回 false.
 * @param [in]	featinfo1	特征 1 文件头.
 * @param [in]	featinfo2	特征 2 文件头.
 **************************************************************************************************/
bool IsSameFeat(const FeatInfo &featinfo1, const FeatInfo &featinfo2);

/**********************************************************************************************//**
 * @fn		bool LoadFeatInfo(const char *featfile, FeatInfo &featinfo);
 * @brief	读取特征文件的头信息.
 * @return	成功返回 true, 失败返回 false.
 * @param [in]		featfile	特征文件路径.
 * @param [in,out]	featinfo	特征信息.
 * @note	导致失败的原因可能为: 1) 打开文件失败; 2) 非特征文件.
 **************************************************************************************************/
bool LoadFeatInfo(const char *featfile, FeatInfo &featinfo);