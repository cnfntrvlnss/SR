/*
2012-10-18 更新标记，增加
*/
#ifndef _LID_TEST_H_
#define _LID_TEST_H_

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////
#define PACMPLID_SUCCESS 				 0			//正确返回
#define PACMPLID_FAILURE 				 0x080000	//错误返回
#define PACMPLID_STATUS_LESSDATA		 0x020001	//有效语音长度不足
//返回结果定义：错误信息
#define PACMPLID_ERROR_EXTRACTFEATURE	 0x010000	//提取特征错误
#define PACMPLID_ERROR_GETFEATURE		 0x010002	//特征后处理打开
#define PACMPLID_ERROR_FILEOPEN			 0x010001	//文件无法打开
#define PACMPLID_ERROR_FEATUREPARM		 0x010005	//特征参数不正确
#define PACMPLID_ERROR_MODELID		     0x010010	//模型ID不正确
#define PACMPLID_ERROR_MODEPARM		     0x010006	//模型参数不正确
///////////////////////////////////////////////////////////////////////////////

/***********************************************************
 数据类型定义
 ***********************************************************/

//输入输出语种参数的数据结构
typedef struct tag_Lid_Lang_Param
{
	int *ipInLangIDs;		//[in] 待识别的语种ID的列表
	int iInLangCnt;			//[in] 待识别的语种的个数

	float *fpOutLangCM;		//[out] 识别出的语种的可信度得分

}LID_LANG_PARAM;


//HANDLE OpenLID(char* szWorkDir, const char **szLangModelPaths,const int *ipLangIDs,int *iIDMap, int iLangCnt);
//void CloseLID(HANDLE hLID);
//HRESULT RunLID(HANDLE hLID, short* pWav, int nLen, float* pScore,int *ipInLangIDs, int iCareLangCnt);
//

//初始化语种识别引擎
//typedef HANDLE (*fun_OpenLID)(char* szWorkDir, const char **szLangModelPaths,const int *ipLangIDs,int *iIDMap, int iLangCnt);
typedef HANDLE (*fun_OpenLID)(char* szWorkDir, const char **szLangModelPaths, int iLangCnt);
//打开一个语种识别会话
typedef HRESULT (*fun_RunLID)(HANDLE hLID, short* pWav, int nLen, float* pScore,int *ipInLangIDs, int iCareLangCnt);
//关闭一个语种识别会话
typedef void (*fun_CloseLID)(HANDLE hLID);




#endif