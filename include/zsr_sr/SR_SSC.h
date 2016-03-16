#ifndef SR_SSC_H
#define SR_SSC_H

#include "sr.h"

/**
* 初始化引擎
* \param pDir [in] 引擎及参数所在的目录
* \return 成功返回引擎句柄；否则返回NULL
*/
SR_API SR_HANDLE SR_SSC_Init(const SR_FILE& Dir);

/**
* 释放引擎
* \param handle [in] 引擎句柄
*/
SR_API void SR_SSC_Release(SR_HANDLE handle);

/**
* 获取最后错误信息
* \param handle [in] 引擎句柄
* \param Error [out] 最后错误信息
*/
SR_API void SR_SSC_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* 说话人分离
* \param handle [in] 引擎句柄
* \param WavBuf [in] 语音数据
* \param WavFile [in] 语音文件
* \param nType [in] 分离模式
* \param SegIn [in] 语音片段(预处理结果)
* \param SegOut [out] 语音片段(说话人分离结果)
* \return 成功返回true；失败返回false
* \note:  1.分离模式nType的取值范围:
-1 - 电话语音主被叫分离（说话人数目可为0、1、2）;
-2 - 不确定说话人数目的动态分离;
>0 - 指定的说话人数目
*/
SR_API bool SR_SSC_Seg_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);
SR_API bool SR_SSC_Seg_File(SR_HANDLE handle,
	const SR_FILE& WavFile,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);

/**
* 说话人聚类
* \param handle [in] 引擎句柄
* \param WavBuf [in]  单段语音数据
* \param WavFile [in] 单个语音文件
* \param nWavNum [in] 语音数据的段数或语音文件的个数
* \param pWavBufs [in] 若干段语音数据
* \param pWavFiles [in] 若干个语音文件
* \param nType [in] 聚类模式
* \param SegIn [in] 语音片段(说话人分离结果)
* \param SegOut [out] 语音片段(说话人聚类结果)
* \return 成功返回true；失败返回false
* \note: 1.分离模式nType的取值范围：
-1 - 电话语音主被叫聚类（说话人数目可为0、1、2）
-2 - 不确定说话人数目的动态聚类
-3 - 对多条语音，单条语音内部按电话语音主被叫聚类，多条语音之间按不确定说话人数目的动态聚类
>0 - 指定的说话人数目
*/
SR_API bool SR_SSC_Clst_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf, 
	int nType, const CFastList<SR_SEG, SR_SEG&>& SegIn, 
	CFastList<SR_SEG, SR_SEG&>& SegOut);
SR_API bool SR_SSC_Clst_File(SR_HANDLE handle,
	const SR_FILE& WavFile,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut); 
SR_API bool SR_SSC_Clst_Bufs(SR_HANDLE handle,
	int nWavNum,
	LPSR_WAVBUF pWavBufs,
	int nType, 
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);
SR_API bool SR_SSC_Clst_Files(SR_HANDLE handle, 
	int nWavNum,
	LPSR_FILE pWavFiles,
	int nType,
	const CFastList<SR_SEG, SR_SEG&>& SegIn,
	CFastList<SR_SEG, SR_SEG&>& SegOut);
#endif