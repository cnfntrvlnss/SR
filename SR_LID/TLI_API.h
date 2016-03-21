#pragma pack( push, enter_tli_api )
#pragma pack ( 8 )

#ifndef __TLIAPI_HEADER_
#define __TLIAPI_HEADER_ 1

#ifndef _MT
#ifdef WIN32
#error("TLI needs multithreading")
#endif
#endif

#if defined( _WIN32 ) || defined ( _WIN64 )
	#ifdef TLI_API_EXPORTS
		#define TLI_DLL_API __declspec(dllexport)
	#else
		#define TLI_DLL_API __declspec(dllimport)
	#endif
#else
    #define TLI_DLL_API
#endif

typedef int TLI_HANDLE;

/******************************** 函数说明 ***********************************
*F
*F 函数名称			: TLI_Init
*F 函数功能			: 引擎初始化
*F 函数类型			: TLI_DLL_API int
*F 函数参数			: char * pszTLISystemDirectory	输入 语种模型（sysdir）路径
*F					: int * pnAllTemplate			输入 语种索引的数组
*F					: char ** ppszAllTemplateLocation 输入 语种名称数组
*F					: int nAllTemplateNumber		输入 语种数
*F					: int nLineNumber				输入 线程数
*F 函数返回值		: 0							初始化成功; 
*F					: -1							初始化失败，模型文件路径错误
*F					: -2							初始化失败，授权失败
*F					: -3							初始化失败，线程数设置错误
*F					: -4							初始化失败，模型文件缺失
*F					: -10						初始化失败，其他错误
*F 其他说明			: 授权文件名为license.txt，需要放在引擎（TLI_API.dll）文件夹下
*F					: 授权号20
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Init(            
							char * pszTLISystemDirectory,
							int * pnAllTemplateIDs,
							char ** ppszAllTemplateLocation,
							int nAllTemplateNumber,
							int nLineNumber
						);

/******************************** 函数说明 ***********************************
*F
*F 函数名称			: TLI_Exit
*F 函数功能			: 引擎退出
*F 函数类型			: TLI_DLL_API int
*F 函数参数			: 无参数
*F 函数返回值		: 0							退出成功
*F					: -1							退出失败
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Exit();

/******************************** 函数说明 ***********************************
*F
*F 函数名称			: TLI_Open
*F 函数功能			: 打开一路线程，获取所开启线程的的句柄
*F 函数类型			: TLI_DLL_API int
*F 函数参数			: TLI_HANDLE & hTGID			输出 所开启线程的的句柄
*F 函数返回值		: 0							打开成功
*F					: -1							打开失败
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Open(
	TLI_HANDLE & hTLI
);

/******************************** 函数说明 ***********************************
*F
*F 函数名称			: TLI_Close
*F 函数功能			: 关闭一路线程
*F 函数类型			: TLI_DLL_API int
*F 函数参数			: TLI_HANDLE hTGID			输入 所关闭线程的句柄
*F 函数返回值		: 0							关闭成功
*F					: -1							关闭失败
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Close(
	TLI_HANDLE hTLI
);

/******************************** 函数说明 ***********************************
*F
*F 函数名称			: TLI_Recognize
*F 函数功能			: 语种识别
*F 函数类型			: TLI_DLL_API int
*F 函数参数			: TLI_HANDLE hTGID			输入 当前线程的句柄
*F					: int * pnCurrentTemplateIDs	输入 语种索引的数组
*F					: int nCurrentTemplateNumber	输入 语种的数目
*F					: void * pvPCMBuffer			输入 PCM数据缓存指针
*F					: int nBytesOfBuffer			输入 PCM数据缓存大小（字节数）
*F					: int nMinLimit				输入 PCM数据时长最小阈值（以秒计），时长
*F												小于该阈值则拒识
*F					: int nMaxLimit				输入 PCM数据时长最大阈值（以秒计），时长
*F												大于该阈值的部分不作处理
*F 函数返回值		: 0							识别成功
*F					: -1						句柄错误
*F					: -2						该线程没有被初始化	
*F					: -3						待判别语言ID或个数错误	
*F					: -4						申请内存错误	
*F					: -5						输入参数非法	
*F					: -6						输入语音太短	
*F					: -7						VAD失败	
*F					: -8						VAD后有效语音太短	
*F					: -9						音乐检测失败
*F					: -10						音乐检测后有效语音太短	
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_Recognize(
	TLI_HANDLE hTLI,
	int * pnCurrentTemplateIDs,
	int nCurrentTemplateNumber,
	void * pvPCMBuffer,
	int nBytesOfBuffer,
	int nMinLimit,
	int nMaxLimit
);

/******************************** 函数说明 ***********************************
*F
*F 函数名称			: TLI_GetResult
*F 函数功能			: 获取识别之后的得分
*F 函数类型			: TLI_DLL_API int
*F 函数参数			: TLI_HANDLE hTGID			输入 当前线程的句柄
*F					: float * pfResults			输出 得分数组指针（需要应用程序申请缓存）
*F					: int nNumber					输入 分数个数（语种个数+拒识得分）
*F 函数返回值		: 0							获取成功
*F					: -1							获取失败
*F
*F*****************************************************************************/
TLI_DLL_API int TLI_GetResult(
	TLI_HANDLE hTLI,
	float * pfResults,
	int nNumber
);

#endif /* __TLIAPI_HEADER_ */

#pragma pack( pop, enter_tli_api )
/* ///////////////////////// End of file "TLI_API.h" //////////////////////// */
