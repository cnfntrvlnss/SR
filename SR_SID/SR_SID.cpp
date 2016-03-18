#define SR_EXPORTS

#include "common\port_zsr.h"
#include "sr/sr.h"

SR_API void SR_SID_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{

}

SR_API SR_HANDLE SR_SID_Init(const SR_FILE& Dir)
{
	return (SR_HANDLE)0;
}

SR_API void SR_SID_Release(SR_HANDLE handle)
{
	return;
}

SR_API bool SR_SID_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2)
{
	return false;
}

SR_API bool SR_SID_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2)
{
	return false;
}

//说话人附加特征比对
SR_API bool SR_SID_CompFea_AdditionalBuf(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	const SR_ADDITIONAL_FEA& AdditionalFea1, const SR_ADDITIONAL_FEA& AdditionalFea2,
	int* pnResult)
{
	return false;
}

//说话人默认特征比对
SR_API bool SR_SID_CompFea_DefaultBuf(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	int* pnResult)
{
	return false;
}

//说话人附加特征文件比对
SR_API bool SR_SID_CompFea_AdditionalFeaFile(SR_HANDLE handle,
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile, int nFeaDataOffset, int nFeaDataNum,
	int* pnResult)
{
	return false;
}

//说话人默认特征文件比对
SR_API bool SR_SID_CompFea_DefaultFeaFile(SR_HANDLE handle,
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile, int nFeaDataOffset, int nFeaDataNum,
	int* pnResult)
{
	return false;
}

SR_API bool SR_SID_ModelOREdit_Bufs(SR_HANDLE handle, const CFastList<SR_WAVBUF, SR_WAVBUF&>& WavBufList,
	const CFastList<SR_FILE, SR_FILE&>& WavBufName, SR_SPECIMEN& pSpecimens, SR_FILE& dir, SR_TRAINTYPE TrainType)
{
	return false;
}

SR_API bool SR_SID_ModelOREdit_Files(SR_HANDLE handle, const CFastList<SR_FILE, SR_FILE&>& FileList,
	SR_SPECIMEN& pSpecimens, SR_FILE& dir, SR_TRAINTYPE TrainType)
{
	return false;
}