/*
2012-10-18 更新标记，增加
*/
#include <windows.h>
//////////////////////////////////////////////////////////////////////////////
#define PACMPSID_SUCCESS 				 0			//正确返回
#define PACMPSID_FAILURE 				 0x080000	//错误返回
#define PACMPSID_STATUS_LESSDATA		 0x020001	//有效语音长度不足
//返回结果定义：错误信息
#define PACMPSID_ERROR_EXTRACTFEATURE	 0x010000	//提取特征错误
#define PACMPSID_ERROR_GETFEATURE		 0x010002	//特征后处理打开
#define PACMPSID_ERROR_FILEOPEN			 0x010001	//文件无法打开
#define PACMPSID_ERROR_FEATUREPARM		 0x010005	//特征参数不正确
#define PACMPSID_ERROR_MODESID		     0x010010	//模型ID不正确
#define PACMPSID_ERROR_MODEPARM		     0x010006	//模型参数不正确
///////////////////////////////////////////////////////////////////////////////
//部分新接口
//名称：初始化引擎
typedef SR_HANDLE (*fun_SR_SID_Init)(const SR_FILE& Dir);

//名称：释放引擎
typedef int (*fun_SR_SID_Release)(SR_HANDLE handle);

//名称：说话人特征提取
typedef int (*fun_SR_SID_GetFea_File)(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2);

//说话人附加特征比对
typedef int  (*fun_SR_SID_CompFea_AdditionalBuf)(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	const SR_ADDITIONAL_FEA& AdditionalFea1, const SR_ADDITIONAL_FEA& AdditionalFea2, 
	int* pnResult);

//说话人默认特征比对
typedef int  (*fun_SR_SID_CompFea_DefaultBuf)(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2, 
	int* pnResult);

//标本训练
typedef int (*fun_SR_SID_Train_Files)(SR_HANDLE handle, int nCount, SR_FILE* pWavFiles, 
	const CFastList<SR_SEG, SR_SEG&>& Seg,SR_SPECIMEN& pSpecimens);

 
typedef int(*fun_SR_SID_Train_SummedFiles)(SR_HANDLE handle, int nWavNum,
	LPSR_FILE pWavFiles, CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_SPECIMEN& Specimen, SR_FILE& dir);
//一步获取合路语音标本比对得分
typedef int (*fun_SR_SID_GetScr_File)(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	int* pnResult);
