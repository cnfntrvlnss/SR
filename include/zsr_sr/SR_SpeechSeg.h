#ifndef SR_SPEECHSEG_H
#define SR_SPEECHSEG_H

#include "cfastlist.h"
#include "sr.h"

/**
*
* \note 
1) 语音片段的采样点范围是[nStart, nEnd)。
2) 语音片段类型nType定义如下：小于等于-10：保留；-9：合成语音；-8：话务员提示音；
-7：噪音或含较强噪声的语音；-6：彩铃音；-5：转接拨号音；-4：振铃音；
-3：传真音或上网音；-2：静默；-1：无效语音（初始值）；0：有效语音；
大于等于0：说话人序号。
3) 语音片段待处理状态nState定义如下：0-删除或忽略处理，1-保留或参与处理。
*/
typedef struct _tag_SR_Seg_
{
	__int64 nFileID;//语音片段所属文件序号
	int nStart; //语音片段采样点起点
	int nEnd; //语音片段采样点终点 
	int nType; //语音片段类型 
	int nState; //语音片段待处理状态
}SR_SEG, *LPSR_SEG;

/**
* 获取最后错误信息
* \handle [in] 引擎句柄
* \Error [out] 最后错误信息
*/
SR_API void SR_SS_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* 将语音片段文件的数据加载至内存
* \param File [in] 语音片段文件
* \param Seg [out] 语音片段链表
* \return 成功返回true；失败返回false
*/
SR_API bool SR_SS_ReadSegFile(const SR_FILE& File, CFastList<SR_SEG, SR_SEG&>& Seg);

/**
* 将内存的语音片段数据保存到语音片段文件中
* \param Seg [in] 语音片段链表
* \param File [in] 语音片段文件
* \return 成功返回true, 失败返回false
*/
SR_API bool SR_SS_WriteSegFile(const CFastList<SR_SEG, SR_SEG&>& Seg, const SR_FILE& File);

/**
* 根据“语音片段”合并“语音数据”
* \param WavBufIn [in] 整段语音数据
* \param Seg [in] 需要保留的语音片段
* \param WavBufOut [out] 多个“语音片段”对应的“语音数据”合并后的“语音数据”
* \return 成功返回true；失败返回false
*/
SR_API bool SR_SS_MergeSegWavBuf(const SR_WAVBUF& WavBufIn,
	const CFastList<SR_SEG, SR_SEG&>& Seg, 
	SR_WAVBUF& WavBufOut);

/**
* 以“整段语音的语音片段绝对值（AllAbsSeg）”为参考，
计算“分割语音的语音片段相对值（SegOppSeg）”
对应的“分割语音的语音片段绝对值（SegAbsSeg）”
* \param AllAbsSeg [in] 整段语音的语音片段绝对值
* \param SegOppSeg [in] 分割语音的语音片段相对值
* \param SegAbsSeg [out] 分割语音的语音片段绝对值
*/
SR_API bool SR_SS_CalSegOffset(const CFastList<SR_SEG,
	SR_SEG&>& AllAbsSeg,
	const CFastList<SR_SEG, SR_SEG&>& SegOppSeg,
	CFastList<SR_SEG, SR_SEG&>& SegAbsSeg);


#endif
