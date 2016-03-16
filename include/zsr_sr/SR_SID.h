#ifndef SR_SID_H
#define SR_SID_H

#include "sr.h"

#define SR_MAX_SPECIMEN_DATA_LEN 131072 //128KB; 说话人识别标本最大字节数
typedef unsigned char SR_SPECIMEN_DATA[SR_MAX_SPECIMEN_DATA_LEN]; //说话人识别标本数据
//说话人识别标本
typedef struct _tag_SR_Specimen_
{
	int nLen; //标本数据长度 
	SR_SPECIMEN_DATA pData; //标本数据
}SR_SPECIMEN, *LPSR_SPECIMEN;

#define SR_MAX_FEA_DATA_LEN 131072 //128KB; 说话人识别单人特征最大字节数
typedef unsigned char SR_FEA_DATA[SR_MAX_FEA_DATA_LEN]; //说话人识别特征数据
//说话人识别特征数据
typedef struct _tag_SR_Fea_ {
	int nLen; //特征数据长度
	SR_FEA_DATA pData; //特征数据
}SR_FEA, *LPSR_FEA;

/*!
* \brief 初始化引擎
* \param Dir [in] 引擎及参数所在的目录
* \return 成功返回引擎句柄；否则返回NULL
*/
SR_API SR_HANDLE SR_SID_Init(const SR_FILE& Dir);

/*!
* 释放引擎
* \param handle [in] 引擎句柄
*/
SR_API void SR_SID_Release(SR_HANDLE handle);

/*!
* \brief 获取最后错误信息
* \param handle [in] 引擎句柄
* \param Error [out] 最后错误信息
*/
SR_API void SR_SID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/*!
* \brief 标本训练
* \param handle [in] 引擎句柄
* \param nWavNum [in] 语音条数
* \param pWavBufs [in] 若干条语音数据
* \param pWavFiles [in] 若干个语音文件
* \param Seg [in] 语音片段(预处理或说话人分离聚类或人工剪辑结果)
* \param Specimen [out]  标本
* \return 成功返回true；失败返回false
*/
SR_API bool SR_SID_Train_Bufs(SR_HANDLE handle, 
	int nWavNum, 
	LPSR_WAVBUF pWavBufs,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_SPECIMEN& Specimen);
SR_API bool SR_SID_Train_Files(SR_HANDLE handle,
	int nWavNum,
	LPSR_FILE pWavFiles,
	const CFastList<SR_SEG, SR_SEG&>& Seg, 
	SR_SPECIMEN& Specimen);

/*!
* \brief 说话人特征提取
* \param handle [in] 引擎句柄
* \param WavBuf [in] 语音数据
* \parma Seg [in] 语音片段(说话人分离聚类结果)
* \param Fea1 [out] 说话人1的特征
* \param Fea2 [out] 说话人2的特征
* \return 成功返回true；失败返回false
* \note 1.对于动态聚类得到的多个说话人语音可按Seg.nType不同，逐个调用
*/
SR_API bool SR_SID_GetFea_Buf(SR_HANDLE handle,
	const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, 
	SR_FEA& Fea1, 
	SR_FEA& Fea2);
SR_API bool SR_SID_GetFea_File(SR_HANDLE handle, 
	const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_FEA& Fea1,
	SR_FEA& Fea2);

/*!
* \brief 说话人特征提取
* \param handle [in] 引擎句柄
* \param nSpecimenNum [in]
* \param pSpecimens [in]
* \param Fea1 [in]
* \param Fea2 [in]
* \param FeaFile [in]
* \param nFeaDataOffset [in]
* \param nFeaDataNum [in]
* \param nSexScore1 [out]
* \param nSexScore2 [out]
* \param pnResult [out]
* \return 成功返回true；失败返回false
* \note 1.nSexScore1 = INT(性别识别引擎实际得分×10000 + 0.9999)这里INT()是取整函数，
不是将nSexScore1改为int数据类型。
2.nSexScore2 = INT(性别识别引擎实际得分×10000 + 0.9999)
3.“性别识别引擎实际得分”应归一化到0-100，接近0表示像男声，接近100表示像女声。
4.nSexScore1、nSexScore2其他取值含义：-1，未识别；-2，识别失败； -3，童声
5.SR_SID_CompFea_File()将标本与FeaFile特征文件中、开始位置为nFeaDataOffset的
nFeaDataNum个特征进行比对。nFeaDataNum = 1或2
*/
SR_API bool SR_SID_CompFea_Buf(SR_HANDLE handle, 
	int nSpecimenNum,
	SR_SPECIMEN* pSpecimens, 
	const SR_FEA& Fea1,
	const SR_FEA& Fea2,
	int& nSexScore1,
	int& nSexScore2,
	int* pnResult); 
SR_API bool SR_SID_CompFea_File(SR_HANDLE handle,
	int nSpecimenDataNum,
	SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile,
	int nFeaDataOffset, 
	int nFeaDataNum,
	int& nSexScore1,
	int& nSexScore2,
	int* pnResult);
#endif