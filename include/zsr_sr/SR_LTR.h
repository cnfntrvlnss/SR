#ifndef SR_LTR_H
#define SR_LTR_H

#include "sr.h"

#define SR_MAX_LIDM_NUM 1000 //语种模型最大数目
#define SR_LIDM_NAME_BYTES 40 //语种模型名称最大字节数
#define SR_LIDM_NAME_LEN (SR_LIDM_NAME_BYTES + 1)
typedef SR_CHAR SR_LIDM_NAME_STR[SR_LIDM_NAME_LEN]; //语种模型名称字符串

//单个语种的训练参数
typedef struct _tag_SR_LTRParam_
{
	SR_UUID_STR chUUID; //语种UUID
	SR_LIDM_NAME_STR chName; //语种名称
	SR_FILE ListFile; //语种样本或语种样本特征的列表文件名称
	CFastList<SR_FILE, SR_FILE&> WavLidfFileList; //语种样本文件列表 或 语种样本特征文件列表
	SR_FILE chLidFile; //语种模型文件,格式为"SR_LTRPARAMS.chOutputPath\chUUID_chName.lidm" 
}SR_LTRPARAM, *LPSR_LTRPARAM;

typedef struct _tag_SR_LTRParams_ 
{
	int nInputType; //输入类型, 1表示输入为语音文件；2表示输入为特征文件(*.ltrf)
	int nThreadNum; //语种训练的线程数目
	SR_FILE OutputPath; //语种识别模型输出目录
	int nLtrNum; //语种数目, nLtrNum <= SR_MAX_LIDM_NUM
	LPSR_LTRPARAM LTRParams[SR_MAX_LIDM_NUM]; //各个语种的训练参数
}SR_LTRPARAMS, *LPSR_LTRPARAMS;

/**
* 初始化引擎
* \param Dir [in] 引擎及参数所在的目录
* \return 成功返回引擎句柄；否则返回NULL
*/
SR_API SR_HANDLE SR_LTR_Init(const SR_FILE& Dir);

/**
* 释放引擎 
* \parma handle [in] 引擎句柄
*/
SR_API void SR_LTR_Release(SR_HANDLE handle);

/**
* 获取最后错误信息
* \param handle [in] 引擎句柄
* \param Error [out] 最后错误信息
*/
SR_API void SR_LTR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* 写语种训练参数
* \param LIRParams [in] 语种训练参数
* \param LTRFile [in] 语种训练设置文件名称
* \return 成功返回true；失败返回false
*/
SR_API bool SR_LTR_WriteParams(const SR_LTRPARAMS& LTRParams, const SR_FILE& LTRFile);

/*!
* \brief 读语种训练参数
* \param LTRFile [in] 语种训练设置文件
* \param LTRParams [out] 语种训练参数
* \return 成功返回true；失败返回false
*/
SR_API bool SR_LTR_ReadParams(const SR_FILE& LTRFile, SR_LTRPARAMS& LTRParams);

/*!
* \brief 语种训练特征提取
* \param handle [in] 引擎句柄 
* \param WavBuf [in] 语音数据
* \param WavFile [in] 语音文件
* \param LtrfFile [in] 特征文件名称
* \return 成功返回true, 失败返回false
*/
SR_API bool SR_LTR_GetFea_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf,
	const SR_FILE& LtrfFile);
SR_API bool SR_LTR_GetFea_File(SR_HANDLE handle,
	const SR_FILE& WavFile, 
	const SR_FILE& LtrfFile);

/*!
* \brief 语种模型训练
* \param handle [in] 引擎句柄
* \param LTRParams [in] 语种训练参数
* \return 成功返回true；失败返回false
*/
SR_API bool SR_LTR(SR_HANDLE handle, SR_LTRPARAMS& LTRParams);
#endif