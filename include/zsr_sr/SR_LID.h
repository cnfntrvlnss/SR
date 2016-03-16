#ifndef SR_LID_H
#define SR_LID_H

#include "sr.h"
#include "cfastlist.h"

#define SR_MAX_LIDM_NUM 1000 //语种模型最大数目
#define SR_LIDM_NAME_BYTES 40 //语种模型最大字节数
#define SR_LIDM_NAME_LEN (SR_LIDM_NAME_BYTES + 1)
typedef SR_CHAR SR_LIDM_NAME_STR[SR_LIDM_NAME_LEN];//语种模型名称字符串

typedef struct _tag_SR_LID_Rst_
{
	SR_UUID_STR chUUID; //语种UUID
	SR_LIDM_NAME_STR chName; //语种名称
	int nLIDScore;  //置信度得分 INT(score X1000 + 0.9999)

}SR_LIDRST, *LPSR_LIDRST;

typedef struct _tag_SR_LID_Rsts_
{
	int nRstNum;
	SR_LIDRST LIDRst[SR_MAX_LIDM_NUM];
}SR_LIDRSTS, *LPSR_LIDRSTS;

/**
* 初始化引擎
* \param Dir [in] 引擎及参数所在的目录
* \return 成功返回引擎句柄；否则返回NULL
*/
SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir);

/**
* 释放引擎
* \param handle [in] 引擎句柄
*/
SR_API void SR_LID_Release(SR_HANDLE handle);

/**
* 获取最后的错误.
* \param [in] 引擎句柄
* \param [out] 最后错误信息
*/
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* 语种识别
* \param handle [in] 引擎句柄
* \param WavBuf [in] 语音数据
* \param WavFile [in] 语音文件
* \param Seg    [in] 语音片段(预处理结果)
* \param LidRsts [in] 各语种识别结果
* \return 成功返回true; 失败返回false.
*/
SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);
SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);


#endif
