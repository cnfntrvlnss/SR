#define SR_EXPORTS

#include "common\port_zsr.h"
#include "sr/sr.h"
#include "srapi.h"

static SR_ERROR g_SR_SID_Error;
static unsigned g_uHdlCnt = 0;
static SR_FILE g_SaveDir;
static SRConfig g_SRCfg;;
SR_API void SR_SID_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{

}

SR_API SR_HANDLE SR_SID_Init(const SR_FILE& Dir)
{
	if (g_uHdlCnt == 0){
		RetCode retVal = TIT_SR_Intialize(WCsToMBs(Dir.PathName).c_str(), g_SRCfg);
		if (retVal == StsNoErr){
			g_uHdlCnt++;
			return 1;
		}
		switch (retVal){
		case(StsErrCfgItem) :
			swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"CfgError 初始化时候，StsErrCfgItem");
			g_SR_SID_Error.nError = 0;
			return 0;
			break;
		case(StsErrModel) :
			swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"MdlError 初始化时候，StsErrModel");
			g_SR_SID_Error.nError = 0;
			return 0;
			break;
		}
	}
	else{
		if (wcscmp(Dir.PathName, g_SaveDir.PathName) != 0){
			swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"LogicError already be inited by different parameter.");
			g_SR_SID_Error.nError = 0;
			return 0;
		}
		else{
			g_uHdlCnt++;
			return 1;
		}
	}
}

SR_API void SR_SID_Release(SR_HANDLE handle)
{
	if (handle != 1){
		swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"LogicError can't be released by unkown handle.");
		g_SR_SID_Error.nError = 0;
		return;
	}
	else{
		g_uHdlCnt--;
		return;
	}
}

SR_API bool SR_SID_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2)
{
	AdditionalFea1.nLen = 0;
	AdditionalFea2.nLen = 0;
	int spkid1 = 0;
	int spkid2 = 0;
	for (int i = 0; i < Seg.GetCount(); i++){
		const SR_SEG &seg = Seg.GetAt(i);
		if (seg.nType < 0) continue;
		if (seg.nType < spkid1){
			spkid2 = spkid1;
			spkid1 = seg.nType;
		}
		else if(seg.nType > spkid1 && seg.nType < spkid2){
			spkid2 = seg.nType;
		}
	}
	CFastList<SR_SEG, SR_SEG&> Seg1, Seg2;
	for (int i = 0; i < Seg.GetCount(); i++){
		if (Seg.GetAt(i).nType == spkid1){

			Seg1.AddTail(const_cast<SR_SEG&>(Seg.GetAt(i)));
		}
		else if (Seg.GetAt(i).nType == spkid2){
			Seg2.AddTail(const_cast<SR_SEG&>(Seg.GetAt(i)));
		}
	}

	unsigned ffeatSize = sizeof(float)* g_SRCfg.featsize;
	float *ffeat = (float*) malloc(ffeatSize);
	if (ffeat == NULL){
		swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"MemoryError failed to malloc memory float size: %d.", ffeatSize);
		g_SR_SID_Error.nError = 0;
		return false;
	}
	SR_WAVBUF realBuf;
	
	//TODO 未完成  缺失对realBuf内存的管理。
	SR_SS_MergeSegWavBuf(WavBuf, Seg1, realBuf);
	RetCode ret = TIT_SR_ExFeat(realBuf.pWavBuf, realBuf.nWavBufLen, realBuf.wf.nSamplesPerSec, ffeat);
	if (ret == StsNoErr){
		DefaultFea1.nLen = ffeatSize;
		memcpy(DefaultFea1.pData, ffeat, ffeatSize);
	}
	else if (ret == StsErrModel){
		swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"GetFeaError StsErrModel.");
		g_SR_SID_Error.nError = 0;
		return false;
	}
	SR_SS_MergeSegWavBuf(WavBuf, Seg2, realBuf);
	RetCode ret = TIT_SR_ExFeat(realBuf.pWavBuf, realBuf.nWavBufLen, realBuf.wf.nSamplesPerSec, ffeat);
	if (ret == StsNoErr){
		DefaultFea2.nLen = ffeatSize;
		memcpy(DefaultFea2.pData, ffeat, ffeatSize);
	}
	else if (ret == StsErrModel){
		swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"GetFeaError StsErrModel.");
		g_SR_SID_Error.nError = 0;
		return false;
	}
	return true;
}

SR_API bool SR_SID_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2)
{
	SR_WAVBUF wavBuf;
	if (!SR_WF_ReadWavFile(WavFile, wavBuf)) {
		swprintf(g_SR_SID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"EnvironError failed to read wave from file %ls.", WavFile.PathName);
		g_SR_SID_Error.nError = 0;
		return false;
	}
	bool retb = SR_SID_GetFea_Buf(handle, wavBuf, Seg, DefaultFea1, DefaultFea2, AdditionalFea1, AdditionalFea2);
	return retb;
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