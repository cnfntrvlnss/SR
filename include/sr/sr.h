#ifndef _NJ841_SR_H_
#define _NJ841_SR_H_

//SR.h  语音识别接口定义
//设计人：秦榛

////////////////////////////////////////////////////////////////////////////////////////////////////
//接口引用部分
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FastList.h"

//------------------------------------------------------------------------------
//为兼容Linux和Windows平台，引用mmsystem.h和mmreg.h中对语音数据格式的定义如下：
//
#ifndef WAVE_FORMAT_PCM

/* OLD general waveform format structure (information common to all formats) */
typedef struct waveformat_tag {
    WORD    wFormatTag;        /* format type */
    WORD    nChannels;         /* number of channels (i.e. mono, stereo, etc.) */
    DWORD   nSamplesPerSec;    /* sample rate */
    DWORD   nAvgBytesPerSec;   /* for buffer estimation */
    WORD    nBlockAlign;       /* block size of data */
} WAVEFORMAT, *PWAVEFORMAT, NEAR *NPWAVEFORMAT, FAR *LPWAVEFORMAT;

/* flags for wFormatTag field of WAVEFORMAT */
#define WAVE_FORMAT_PCM     1


/* specific waveform format structure for PCM data */
typedef struct pcmwaveformat_tag {
    WAVEFORMAT  wf;
    WORD        wBitsPerSample;
} PCMWAVEFORMAT, *PPCMWAVEFORMAT, NEAR *NPPCMWAVEFORMAT, FAR *LPPCMWAVEFORMAT;
#endif /* WAVE_FORMAT_PCM */

#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_

/*
 *  extended waveform format structure used for all non-PCM formats. this
 *  structure is common to all non-PCM formats.
 */
typedef struct tWAVEFORMATEX
{
    WORD        wFormatTag;         /* format type */
    WORD        nChannels;          /* number of channels (i.e. mono, stereo...) */
    DWORD       nSamplesPerSec;     /* sample rate */
    DWORD       nAvgBytesPerSec;    /* for buffer estimation */
    WORD        nBlockAlign;        /* block size of data */
    WORD        wBitsPerSample;     /* number of bits per sample of mono data */
    WORD        cbSize;             /* the count in bytes of the size of */
                                    /* extra information (after cbSize) */
} WAVEFORMATEX, *PWAVEFORMATEX, NEAR *NPWAVEFORMATEX, FAR *LPWAVEFORMATEX;

#endif /* _WAVEFORMATEX_ */
typedef const WAVEFORMATEX FAR *LPCWAVEFORMATEX;

////////////////////////////////////////////////////////////////////////////////////////////////////
//通用接口
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//UNICODE编码开关
#ifndef UNICODE
#define UNICODE
#endif //UNICODE


//字符串内存操作定义（该部分可根据需要逐步扩充）
#ifdef  UNICODE
    #define STRSET          wcsset          //设置字符串中的字符为指定字符
    #define _STRSET         _wcsset         //设置字符串中的字符为指定字符
    #define STRCPY          wcscpy          //复制字符串
    #define STRNCPY         wcsncpy         //复制字符串
    #define STRDUP          wcsdup          //复制字符串
    #define _STRDUP         _wcsdup         //复制字符串
    #define STRCAT          wcscat          //添加字符串
    #define STRNCAT         wcsncat         //添加字符串
    #define STRCMP          wcscmp          //比较字符串
    #define STRICMP         wcsicmp         //比较字符串*
    #define STRNCMP         wcsncmp         //比较字符串*
    #define STRNICMP        wcsnicmp        //比较字符串*
    #define _STRNICMP       _wcsnicmp       //比较字符串*
    #define STRCOLL         wcscoll         //比较字符串*
    #define _STRICOLL       _wcsicoll       //比较字符串*
    #define _STRNCOLL       _wcsncoll       //比较字符串*
    #define _STRNICOLL      _wcsnicoll      //比较字符串*
    #define _STRCOLL_L      _wcscoll_l      //比较字符串*
    #define _STRICOLL_L     _wcsicoll_l     //比较字符串*
    #define _STRNCOLL_L     _wcsncoll_l     //比较字符串*
    #define _STRNICOLL_L    _wcsnicoll_l    //比较字符串*
    #define STRLEN          wcslen          //获取字符串长度
    #define STRCHR          wcschr          //在字符串中查找字符
    #define STRSTR          wcsstr          //在字符串中查找子字符串
    #define STRCSPN         wcscspn         //在字符串中查找子字符串
    #define STRPBRK         wcspbrk         //在字符串中查找字符集中的字符
    #define STRSPN          wcsspn          //在字符串中查找第一个子字符串
    #define STRRCHR         wcsrchr         //在字符串中查找最后出现的字符
    #define STRTOK          wcstok          //在字符串中查找下一个token
    #define STRLWR          wcslwr          //转换为小写
    #define _STRLWR         _wcslwr         //转换为小写
    #define _STRICMP        _wcsicmp        //进行小写字符串比较
    #define _STRICMP_L      _wcsicmp_l      //进行小写字符串比较
    #define STRUPR          wcsupr          //转换为大写 
    #define _STRUPR         _wcsupr         //转换为大写
    #define STRNSET         wcsnset         //初始化字符串为指定格式
    #define _STRNSET        _wcsnset        //初始化字符串为指定格式
    #define STRREV          wcsrev          //颠倒字符串的字符
    #define _STRREV         _wcsrev         //颠倒字符串的字符
    #define STRXFRM         wcsxfrm         //根据指定信息转换字符串
    #define _STRXFRM_L      _wcsxfrm_l      //根据指定信息转换字符串
    #define STRERROR        _wcserror       //获取系统错误信息
    #define _STRERROR       __wcserror      //获取系统错误信息
#else   //UNICODE
    #define STRSET          strset          //设置字符串中的字符为指定字符
    #define _STRSET         _strset         //设置字符串中的字符为指定字符
    #define STRCPY          strcpy          //复制字符串
    #define STRNCPY         strncpy         //复制字符串
    #define STRDUP          strdup          //复制字符串
    #define _STRDUP         _strdup         //复制字符串
    #define STRCAT          strcat          //添加字符串
    #define STRNCAT         strncat         //添加字符串
    #define STRCMP          strcmp          //比较字符串
    #define STRICMP         stricmp         //比较字符串*
    #define STRNCMP         strncmp         //比较字符串*
    #define STRNICMP        strnicmp        //比较字符串*
    #define _STRNICMP       _strnicmp       //比较字符串*
    #define STRCOLL         strcoll         //比较字符串*
    #define _STRICOLL       _stricoll       //比较字符串*
    #define _STRNCOLL       _strncoll       //比较字符串*
    #define _STRNICOLL      _strnicoll      //比较字符串*
    #define _STRCOLL_L      _strcoll_l      //比较字符串*
    #define _STRICOLL_L     _stricoll_l     //比较字符串*
    #define _STRNCOLL_L     _strncoll_l     //比较字符串*
    #define _STRNICOLL_L    _strnicoll_l    //比较字符串*
    #define STRLEN          strlen          //获取字符串长度
    #define STRCHR          strchr          //在字符串中查找字符
    #define STRSTR          strstr          //在字符串中查找子字符串
    #define STRCSPN         strcspn         //在字符串中查找子字符串
    #define STRPBRK         strpbrk         //在字符串中查找字符集中的字符
    #define STRSPN          strspn          //在字符串中查找第一个子字符串
    #define STRRCHR         strrchr         //在字符串中查找最后出现的字符
    #define STRTOK          strtok          //在字符串中查找下一个token
    #define STRLWR          strlwr          //转换为小写
    #define _STRLWR         _strlwr         //转换为小写
    #define _STRICMP        _stricmp        //进行小写字符串比较
    #define _STRICMP_L      _stricmp_l      //进行小写字符串比较
    #define STRUPR          strupr          //转换为大写
    #define _STRUPR         _strupr         //转换为大写
    #define STRNSET         strnset         //初始化字符串为指定格式
    #define _STRNSET        _strnset        //初始化字符串为指定格式
    #define STRREV          strrev          //颠倒字符串的字符
    #define _STRREV         _strrev         //颠倒字符串的字符
    #define STRXFRM         strxfrm         //根据指定信息转换字符串
    #define _STRXFRM_L      _strxfrm_l      //根据指定信息转换字符串
#endif  //UNICODE

//文件操作定义（该部分可根据需要逐步扩充）
#ifdef  UNICODE
    #define FOPEN           _wfopen         //打开文件
    #define FREOPEN         _wfreopen       //给文件指针重新赋值，并打开文件
    #define _FSOPEN         _wfsopen        //以共享方式打开文件      
    #define _FDOPEN         _wfdopen        //以底层IO操作方式打开文件 
    #define REMOVE          _wremove        //删除文件
    #define FGETC           fgetwc          //从文件中读一个字符
    #define FGETS           fgetws          //从文件中读字符串
    #define FSCANF          fwscanf         //从文件中读格式化数据
    #define FPUTC           fputwc          //向文件中写一个字符
    #define FPUTS           fputws          //向文件中写字符串
    #define FPRINTF         fwprintf        //向文件中写格式化数据
#else   //UNICODE
    #define FOPEN           fopen           //打开文件
    #define FREOPEN         freopen         //给文件指针重新赋值，并打开文件
    #define _FSOPEN         _fsopen         //以共享方式打开文件
    #define _FDOPEN         _fdopen         //以底层IO操作方式打开文件   
    #define REMOVE          remove          //删除文件
    #define FGETC           fgetc           //从文件中读一个字符
    #define FGETS           fgets           //从文件中读字符串
    #define FSCANF          fscanf          //从文件中读格式化数据
    #define FPUTC           fputc           //向文件中写一个字符
    #define FPUTS           fputs           //向文件中写字符串
    #define FPRINTF         fprintf         //向文件中写格式化数据
#endif  //UNICODE

//文件访问标志
#ifdef  UNICODE
    #define FOPEN_MODE_READ     L"r"    //按只读模式打开文件
    #define FOPEN_MODE_WRITE    L"w"    //创建新文件，或按覆盖写模式打开文件
    #define FOPEN_MODE_APPEND   L"a"    //按添加写模式打开文件
    #define FOPEN_MODE_READ2    L"r+"   //按读写模式打开文件
    #define FOPEN_MODE_WRITE2   L"w+"   //创建新文件，或按读模式和按覆盖写模式打开文件
    #define FOPEN_MODE_APPEND2  L"a+"   //创建新文件，或按读模式和添加写模式打开文件
    #define FOPEN_MODE_TEXT     L"t"    //以文本方式打开文件
    #define FOPEN_MODE_BINARY   L"b"    //以二进制方式打开文件
    #define FOPEN_MODE_COMMIT   L"c"    //
    #define FOPEN_MODE_NOCOMMIT L"n"    //
    #define FOPEN_MODE_S        L"S"    //
    #define FOPEN_MODE_R        L"R"    //
    #define FOPEN_MODE_T        L"T"    //
    #define FOPEN_MODE_D        L"D"    //
#else   //UNICODE
    #define FOPEN_MODE_READ     "r"     //按只读模式打开文件
    #define FOPEN_MODE_WRITE    "w"     //创建新文件，或按覆盖写模式打开文件
    #define FOPEN_MODE_APPEND   "a"     //按添加写模式打开文件
    #define FOPEN_MODE_READ2    "r+"    //按读写模式打开文件
    #define FOPEN_MODE_WRITE2   "w+"    //创建新文件，或按读模式和按覆盖写模式打开文件
    #define FOPEN_MODE_APPEND2  "a+"    //创建新文件，或按读模式和添加写模式打开文件
    #define FOPEN_MODE_TEXT     "t"     //以文本方式打开文件
    #define FOPEN_MODE_BINARY   "b"     //以二进制方式打开文件
    #define FOPEN_MODE_COMMIT   "c"     //
    #define FOPEN_MODE_NOCOMMIT "n"     //
    #define FOPEN_MODE_S        "S"     //
    #define FOPEN_MODE_R        "R"     //
    #define FOPEN_MODE_T        "T"     //
    #define FOPEN_MODE_D        "D"     //
#endif  //UNICODE

//------------------------------------------------------------------------------
//引擎句柄：是各引擎实例的唯一标识。
#ifndef SR_HANDLE
#define SR_HANDLE unsigned int
#endif //SR_HANDLE

//动态链接宏定义
#ifdef SR_EXPORTS
#define SR_API extern "C" __declspec(dllexport)
#else
#define SR_API extern "C" __declspec(dllimport)
#endif

//UUID字符串长度
#ifndef SR_UUID_BYTES
#define SR_UUID_BYTES    32
#endif //SR_UUID_BYTES

#ifndef SR_UUID_CHAR_LEN
#define SR_UUID_CHAR_LEN    (SR_UUID_BYTES + 1)
#endif //SR_UUID_CHAR_LEN

//字符串
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#ifndef _SR_STR_
#define _SR_STR_

#ifdef UNICODE
typedef wchar_t SR_CHAR;
#else   
typedef char SR_CHAR;
#endif //UNICODE

typedef SR_CHAR* LPSR_CHAR;
#endif //_SR_STR_

//UUID字符串
#ifndef _SR_UUID_STR_
#define _SR_UUID_STR_
typedef SR_CHAR SR_UUID_STR[SR_UUID_CHAR_LEN];
#endif //_SR_UUID_STR_


//------------------------------------------------------------------------------
//语音数据：是语音在内存中的体现方式。

//语音数据
//说明：
//    1.SR_WAVBUF对各引擎接口的语音内存数据的数据结构进行定义。
//    2.当前：wf各数值均取默认值，即pWavBuf指向的语音数据是采样频率8000Hz、采样
//      位16Bit、单声道、线性PCM编码的语音。
#ifndef _SR_WAVBUF_
#define _SR_WAVBUF_
typedef struct _tag_SR_WavBuf_
{
    WAVEFORMATEX wf;         //语音数据格式
    int          nWavBufLen; //语音数据长度
    short*       pWavBuf;    //语音数据指针
}SR_WAVBUF, *LPSR_WAVBUF;
#endif //_SR_WAVBUF_

//------------------------------------------------------------------------------
//语音片段：是描述特定类型的语音数据范围的数据结构。

//单个语音片段
//说明：
//    1.语音片段的采样点范围是[nStart, nEnd)。
//    2.语音片段类型nType定义如下：小于等于-10：保留；-9：合成语音；-8：话务员
//      提示音；-7：噪音或含较强噪声的语音；-6：彩铃音；-5：转接拨号音；-4：振
//      铃音；-3：传真音或上网音；-2：静默；-1：无效语音（初始值）；0：有效语
//      音；大于等于0：说话人序号。
//    3.语音片段待处理状态nState定义如下：0-删除或忽略处理，1-保留或参与处理。
#ifndef _SR_SEG_
#define _SR_SEG_
typedef struct _tag_SR_Seg_
{
    __int64 nFileID;//语音片段所属文件序号
    int     nStart; //语音片段采样点起点
    int     nEnd;   //语音片段采样点终点
    int     nType;  //语音片段类型
    int     nState; //语音片段待处理状态
}SR_SEG, *LPSR_SEG;
#endif //_SR_SEG_

//------------------------------------------------------------------------------
//单个文件

//文件名最大长度
#ifndef SR_MAX_PATHNAME_BYTES
#define SR_MAX_PATHNAME_BYTES 255
#endif //SR_MAX_PATHNAME_BYTES

#ifndef SR_MAX_PATHNAME_LEN
#define SR_MAX_PATHNAME_LEN (SR_MAX_PATHNAME_BYTES + 1)
#endif //SR_MAX_PATHNAME_LEN

//单个文件
#ifndef _SR_FILE_
#define _SR_FILE_
typedef struct _tag_SR_FILE_
{
    SR_CHAR PathName[SR_MAX_PATHNAME_LEN];
}SR_FILE, *LPSR_FILE;
#endif //_SR_FILE_

//------------------------------------------------------------------------------
//错误信息

//错误信息最大长度
#ifndef SR_MAX_ERROR_CHAR_BYTES
#define SR_MAX_ERROR_CHAR_BYTES 255
#endif //SR_MAX_ERROR_CHAR_BYTES

#ifndef SR_MAX_ERROR_CHAR_LEN
#define SR_MAX_ERROR_CHAR_LEN (SR_MAX_ERROR_CHAR_BYTES + 1)
#endif //SR_MAX_ERROR_CHAR_LEN

//错误信息
#ifndef _SR_ERROR_
#define _SR_ERROR_
typedef struct _tag_SR_Error_
{
    int nError;
    SR_CHAR chError[SR_MAX_ERROR_CHAR_LEN];
}SR_ERROR, *LPSR_ERROR;
#endif //_SR_ERROR_

////////////////////////////////////////////////////////////////////////////////
//语音文件访问接口
////////////////////////////////////////////////////////////////////////////////
//说明：
//    1. “标准文件格式的语音文件”主要包括：
//        采样频率8000Hz、采样位16Bit、单声道、线性PCM编码的Windows标准Wav文件。
//    2. “非标准文件格式的语音文件”主要包括：
//        G.711、G.723、G.729、GSM 610等。

//名称：获取最后错误信息SR_WF_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_WF_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：读语音文件SR_WF_ReadWavFile()
//功能：
//    1.将语音文件的数据加载至内存。
//    2.“非标准文件格式的语音文件”向“标准格式的语音文件”转换。
//参数：
//    File   —— 输入：语音文件
//    WavBuf —— 输出：语音数据
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_WF_ReadWavFile(const SR_FILE& File, SR_WAVBUF& WavBuf);

//名称：写语音文件SR_WF_WriteWavFile()
//功能：
//    1.将内存的语音数据保存到“标准格式的语音文件”中。
//参数：
//    WavBuf —— 输入：语音数据
//    File   —— 输出：语音文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_WF_WriteWavFile(const SR_WAVBUF& WavBuf, const SR_FILE& File);

////////////////////////////////////////////////////////////////////////////////
//语音片段访问接口
////////////////////////////////////////////////////////////////////////////////

//名称：获取最后错误信息SR_SS_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_SS_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：读语音片段文件SR_SS_ReadSegFile()
//功能：
//    1.将语音片段文件的数据加载至内存。
//参数：
//    File —— 输入：语音片段文件
//    Seg  —— 输出：语音片段链表
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_SS_ReadSegFile(const SR_FILE& File,
    CFastList<SR_SEG, SR_SEG&>& Seg);

//名称：写语音片段文件SR_SS_WriteSegFile()
//功能：
//    1.将内存的语音片段数据保存到语音片段文件中。
//参数：
//    Seg  —— 输入：语音片段链表
//    File —— 输出：语音片段文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_SS_WriteSegFile(const CFastList<SR_SEG, SR_SEG&>& Seg,
    const SR_FILE& File);

//名称：根据语音片段合并语音数据SR_SS_MergeSegWavBuf()
//功能：
//    1.根据“语音片段”合并“语音数据”。
//参数：
//    WavBufIn —— 输入：整段语音数据
//    Seg      —— 输入：需要保留的语音片段
//    WavBufOut—— 输出：多个“语音片段”对应的“语音数据”合并后的“语音数据”
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_SS_MergeSegWavBuf(const SR_WAVBUF& WavBufIn, 
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_WAVBUF& WavBufOut);

//名称：计算语音片段偏移SR_SS_CalSegOffset()
//功能：
//    1.以“整段语音的语音片段绝对值（AllAbsSeg）”为参考，计算
//        “分割语音的语音片段相对值（SegOppSeg）”对应的
//        “分割语音的语音片段绝对值（SegAbsSeg）”
//参数：
//    AllAbsSeg —— 输入：整段语音的语音片段绝对值
//    SegOppSeg —— 输入：分割语音的语音片段相对值
//    SegAbsSeg —— 输出：分割语音的语音片段绝对值
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_SS_CalSegOffset(
    const CFastList<SR_SEG, SR_SEG&>& AllAbsSeg,
    const CFastList<SR_SEG, SR_SEG&>& SegOppSeg,
    CFastList<SR_SEG, SR_SEG&>& SegAbsSeg);

////////////////////////////////////////////////////////////////////////////////
//文件列表访问接口
////////////////////////////////////////////////////////////////////////////////

//名称：获取最后错误信息SR_FL_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_FL_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：读列表文件SR_FL_ReadListFile()
//功能：
//    1.将列表文件的数据加载至内存。
//参数：
//    File     —— 输入：列表文件
//    FileList —— 输出：指向文件列表的指针
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_FL_ReadListFile(
    const SR_FILE& File, CFastList<SR_FILE, SR_FILE&>& FileList);

//名称：写列表文件SR_FL_WriteListFile()
//功能：
//    1.将内存的文件列表保存到列表文件中。
//参数：
//    FileList —— 输入：指向文件列表的指针
//    File     —— 输出：列表文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_FL_WriteListFile(
    const CFastList<SR_FILE, SR_FILE&>& FileList, const SR_FILE& File);

////////////////////////////////////////////////////////////////////////////////////////////////////
//识别接口
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//语音预处理接口
////////////////////////////////////////////////////////////////////////////////

//拨号音号码字符串最大长度
#ifndef SR_MAX_PHONE_NUMBER_BYTES
#define SR_MAX_PHONE_NUMBER_BYTES     20
#endif //SR_MAX_PHONE_NUMBER_BYTES

#ifndef SR_MAX_PHONE_NUMBER_LEN
#define SR_MAX_PHONE_NUMBER_LEN     (SR_MAX_PHONE_NUMBER_BYTES + 1)
#endif //SR_MAX_PHONE_NUMBER_LEN

//拨号音号码字符串
#ifndef _SR_PHONE_NUMBER_
#define _SR_PHONE_NUMBER_
typedef SR_CHAR SR_PHONE_NUMBER[SR_MAX_PHONE_NUMBER_LEN];
#endif //_SR_PHONE_NUMBER_

//名称：初始化引擎SR_PTR_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_PTR_Init(const SR_FILE& Dir);

//名称：释放引擎SR_PTR_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_PTR_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_PTR_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_PTR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：预处理SR_PTR_VAD_...()
//功能：
//    1.有效语音检测。
//参数：
//    handle  —— 输入：引擎句柄
//    WavBuf  —— 输入：语音数据
//    WavFile —— 输入：语音文件
//    Seg     —— 输出：语音片段(预处理结果)
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_PTR_VAD_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    CFastList<SR_SEG, SR_SEG&>& Seg);

SR_API bool SR_PTR_VAD_File(SR_HANDLE handle, const SR_FILE& WavFile,
    CFastList<SR_SEG, SR_SEG&>& Seg);

//名称：振铃次数识别SR_PTR_RingTimes_...()
//功能：
//    1.振铃次数识别。
//参数：
//    handle     —— 输入：引擎句柄
//    WavBuf     —— 输入：语音数据
//    WavFile    —— 输入：语音文件
//    Seg        —— 输入：语音片段(预处理结果)
//    nRingTimes —— 输出：振铃次数
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_PTR_RingTimes_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, int& nRingTimes);

SR_API bool SR_PTR_RingTimes_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, int& nRingTimes);

//名称：拨号音号码识别SR_PTR_PhoneNum_...()
//功能：
//    1.拨号音号码识别。
//参数：
//    handle      —— 输入：引擎句柄
//    WavBuf      —— 输入：语音数据
//    WavFile     —— 输入：语音文件
//    Seg         —— 输入：语音片段(预处理结果)
//    PhoneNumber —— 输出：拨号音号码字符串
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_PTR_PhoneNum_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_PHONE_NUMBER& PhoneNumber);

SR_API bool SR_PTR_PhoneNum_File(SR_HANDLE handle, SR_FILE WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_PHONE_NUMBER& PhoneNumber);

////////////////////////////////////////////////////////////////////////////////
//说话人分离聚类接口
////////////////////////////////////////////////////////////////////////////////

//名称：初始化引擎SR_SSC_Init()
//功能：
//    1.初始化引擎。
//参数：
//    pDir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_SSC_Init(const SR_FILE& Dir);

//名称：释放引擎SR_SSC_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_SSC_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_SSC_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_SSC_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：说话人分离SR_SID_Seg_...()
//功能：
//    1.说话人分离。
//参数：
//    handle  —— 输入：引擎句柄
//    WavBuf  —— 输入：语音数据
//    WavFile —— 输入：语音文件
//    nType   —— 输入：分离模式
//    SegIn   —— 输入：语音片段(预处理结果)
//    SegOut  —— 输出：语音片段(说话人分离结果)
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.分离模式nType的取值范围：
//      -1 - 电话语音主被叫分离；
//      -2 - 不确定说话人数目的动态分离；
//      >0 - 指定的说话人数目。
SR_API bool SR_SSC_Seg_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

SR_API bool SR_SSC_Seg_File(SR_HANDLE handle, const SR_FILE& WavFile, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

//名称：说话人聚类SR_SID_Clst_...()
//功能：
//    1.说话人聚类。
//参数：
//    handle    —— 输入：引擎句柄
//    WavBuf    —— 输入：单段语音数据
//    WavFile   —— 输入：单个语音文件
//    nWavNum   —— 输入：语音数据的段数或语音文件的个数
//    pWavBufs  —— 输入：若干段语音数据
//    pWavFiles —— 输入：若干个语音文件
//    nType     —— 输入：聚类模式
//    SegIn     —— 输入：语音片段(说话人分离结果)
//    SegOut    —— 输出：语音片段(说话人聚类结果)
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.分离模式nType的取值范围：
//      -1 - 电话语音主被叫聚类；
//      -2 - 不确定说话人数目的动态聚类；
//      -3 - 对多条语音，单条语音内部按电话语音主被叫聚类，多条语音之间
//           按不确定说话人数目的动态聚类；
//      >0 - 指定的说话人数目。。
SR_API bool SR_SSC_Clst_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

SR_API bool SR_SSC_Clst_File(SR_HANDLE handle, const SR_FILE& WavFile, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

SR_API bool SR_SSC_Clst_Bufs(SR_HANDLE handle,
    int nWavNum, LPSR_WAVBUF pWavBufs, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

SR_API bool SR_SSC_Clst_Files(SR_HANDLE handle,
    int nWavNum, LPSR_FILE pWavFiles, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

////////////////////////////////////////////////////////////////////////////////
//语种训练和语种识别共用定义
////////////////////////////////////////////////////////////////////////////////

//语种模型最大数目
#ifndef SR_MAX_LIDM_NUM
#define SR_MAX_LIDM_NUM     1000
#endif //SR_MAX_LIDM_NUM

//语种模型名称最大字节数
#ifndef SR_LIDM_NAME_BYTES
#define SR_LIDM_NAME_BYTES    40
#endif //SR_LIDM_NAME_BYTES

#ifndef SR_LIDM_NAME_LEN
#define SR_LIDM_NAME_LEN    (SR_LIDM_NAME_BYTES + 1)
#endif //SR_LIDM_NAME_LEN

//语种模型名称字符串
#ifndef _SR_LIDM_NAME_STR_
#define _SR_LIDM_NAME_STR_
typedef SR_CHAR SR_LIDM_NAME_STR[SR_LIDM_NAME_LEN];
#endif //_SR_LIDM_NAME_STR_

////////////////////////////////////////////////////////////////////////////////
//语种训练接口
////////////////////////////////////////////////////////////////////////////////

//单个语种的训练参数
//说明：
//    1.chLidFile格式为"SR_LTRPARAMS.chOutputPath\chUUID_chName.lidm"
#ifndef _SR_LTRPARAM_
#define _SR_LTRPARAM_
typedef struct _tag_SR_LTRParam_
{
    SR_UUID_STR chUUID; //语种UUID
    SR_LIDM_NAME_STR chName;    //语种名称
    SR_FILE ListFile;   //语种样本或语种样本特征的列表文件名称
    CFastList<SR_FILE, SR_FILE&> WavLidfFileList;
                        //语种样本文件列表 或 语种样本特征文件列表
    SR_FILE chLidFile;  //语种模型文件
}SR_LTRPARAM, *LPSR_LTRPARAM;
#endif    //_SR_LTRPARAM_

//多个语种的训练参数
//说明：
//    1.nInputType取值说明：1表示输入为语音文件；2表示输入为特征文件(*.ltrf)
//    2.nLtrNum <= SR_MAX_LIDM_NUM
#ifndef _SR_LTRPARAMS_
#define _SR_LTRPARAMS_
typedef struct _tag_SR_LTRParams_
{
    int     nInputType;     //输入类型
    int     nThreadNum;     //语种训练的线程数目
    SR_FILE OutputPath;     //语种识别模型输出目录
    int     nLtrNum;        //语种数目
    LPSR_LTRPARAM LTRParams[SR_MAX_LIDM_NUM]; //各个语种的训练参数
}SR_LTRPARAMS, *LPSR_LTRPARAMS;
#endif //_SR_LTRPARAMS_

//名称：初始化引擎SR_LTR_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_LTR_Init(const SR_FILE& Dir);

//名称：释放引擎SR_LTR_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_LTR_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_LTR_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_LTR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：写语种训练参数SR_LTR_WriteParams()
//功能：
//    1.写语种训练参数。
//参数：
//    LTRParams —— 输入：语种训练参数
//    LTRFile   —— 输入：语种训练设置文件名称
//              —— 输出：语种训练设置文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_LTR_WriteParams(const SR_LTRPARAMS& LTRParams, 
    const SR_FILE& LTRFile);

//名称：读语种训练参数SR_LTR_ReadParams()
//功能：
//    1.读语种训练参数。
//参数：
//    LTRFile   —— 输入：语种训练设置文件
//    LTRParams —— 输出：语种训练参数
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_LTR_ReadParams(const SR_FILE& LTRFile, SR_LTRPARAMS& LTRParams);

//名称：语种训练特征提取SR_LTR_GetFea_...()
//功能：
//    1.语种训练特征提取。
//参数：
//    handle   —— 输入：引擎句柄
//    WavBuf   —— 输入：语音数据
//    WavFile  —— 输入：语音文件
//    LtrfFile —— 输入：特征文件名称
//             —— 输出：特征文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_LTR_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const SR_FILE& LtrfFile);

SR_API bool SR_LTR_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const SR_FILE& LtrfFile);

//名称：语种模型训练SR_LTR()
//功能：
//    1.语种模型训练。
//参数：
//    handle    —— 输入：引擎句柄
//    LTRParams —— 输入：语种训练参数
//    LTRParams.LTRParams[x].chLidFile —— 输出：语种模型文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_LTR(SR_HANDLE handle, SR_LTRPARAMS& LTRParams);

////////////////////////////////////////////////////////////////////////////////
//语种识别接口
////////////////////////////////////////////////////////////////////////////////

//单个语种识别结果
//说明：
//    1.nLIDScore = INT(实际得分×10000 + 0.9999)
//      这里INT()是取整函数，不是将nLIDScore改为int数据类型
#ifndef _SR_LID_Rst_
#define _SR_LID_Rst_
typedef struct _tag_SR_LID_Rst_
{
    SR_UUID_STR chUUID;     //语种UUID
    SR_LIDM_NAME_STR chName;//语种名称
    int nLIDScore;          //置信度得分
}SR_LIDRST, *LPSR_LIDRST;
#endif //_SR_LID_Rst_

//多个语种识别结果
//说明：
//    1.nRstNum <= SR_MAX_LIDM_NUM
#ifndef _SR_LID_Rsts_
#define _SR_LID_Rsts_
typedef struct _tag_SR_LID_Rsts_
{
    int nRstNum;                      //语种识别结果数目
    SR_LIDRST LIDRst[SR_MAX_LIDM_NUM];   //各语种识别结果
}SR_LIDRSTS, *LPSR_LIDRSTS;
#endif //_SR_LID_Rsts_

//名称：初始化引擎SR_LID_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir);

//名称：释放引擎SR_LID_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_LID_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_LID_GetLastError()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：语种识别SR_LID_...()
//功能：
//    1.语种识别。
//参数：
//    handle  —— 输入：引擎句柄
//    WavBuf  —— 输入：语音数据
//    WavFile —— 输入：语音文件
//    Seg     —— 输入：语音片段(预处理结果)
//    LidRsts —— 输出：各语种识别结果
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);

SR_API bool SR_LID_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);

////////////////////////////////////////////////////////////////////////////////
//口音训练和口音识别共用定义
////////////////////////////////////////////////////////////////////////////////

//口音模型最大数目
#ifndef SR_MAX_AIDM_NUM
#define SR_MAX_AIDM_NUM     1000
#endif //SR_MAX_AIDM_NUM

//口音模型名称最大字节数
#ifndef SR_AIDM_NAME_BYTES
#define SR_AIDM_NAME_BYTES    40
#endif //SR_AIDM_NAME_BYTES

#ifndef SR_AIDM_NAME_LEN
#define SR_AIDM_NAME_LEN    (SR_AIDM_NAME_BYTES + 1)
#endif //SR_AIDM_NAME_LEN

//口音模型名称字符串
#ifndef _SR_AIDM_NAME_STR_
#define _SR_AIDM_NAME_STR_
typedef SR_CHAR SR_AIDM_NAME_STR[SR_LIDM_NAME_LEN];
#endif //_SR_AIDM_NAME_STR_

////////////////////////////////////////////////////////////////////////////////
//口音训练接口
////////////////////////////////////////////////////////////////////////////////

//单个口音的训练参数
//说明：
//    1.chAidFile格式为"SR_ATRPARAMS.chOutputPath\chUUID_chName.aidm"
#ifndef _SR_ATRPARAM_
#define _SR_ATRPARAM_
typedef struct _tagSR_ATRParam_
{
    SR_UUID_STR chUUID;  //口音UUID
    SR_AIDM_NAME_STR chName;  //口音名称
    SR_FILE ListFile;   //口音样本或口音样本特征的列表文件名称
    CFastList<SR_FILE, SR_FILE&> WavAidfFileList;
                        //口音样本文件列表 或 口音样本特征文件列表
    SR_FILE chAidFile;  //口音模型文件
}SR_ATRPARAM, *LPSR_ATRPARAM;
#endif    //_SR_ATRPARAM_

//多个口音的训练参数
//说明：
//    1.nInputType取值说明：1表示输入为语音文件；2表示输入为特征文件(*.atrf)。
//    2.nAtrNum <= SR_MAX_AIDM_NUM。
#ifndef _SR_ATRPARAMS_
#define _SR_ATRPARAMS_
typedef struct _tag_SR_ATRParams_
{
    int     nInputType; //输入类型
    int     nThreadNum; //口音训练的线程数目
    SR_FILE OutputPath; //口音识别模型输出目录
    int     nAtrNum;    //口音数目
    LPSR_ATRPARAM ATRParams[SR_MAX_AIDM_NUM]; //各个口音的训练参数
}SR_ATRPARAMS, *LPSR_ATRPARAMS;
#endif //_SR_ATRPARAMS_

//名称：初始化引擎SR_ATR_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_ATR_Init(const SR_FILE& Dir);

//名称：释放引擎SR_ATR_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_ATR_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_ATR_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_ATR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：写口音训练参数SR_ATR_WriteParams()
//功能：
//    1.写口音训练参数。
//参数：
//    ATRParams —— 输入：口音训练参数
//    ATRFile   —— 输入：口音训练设置文件名称
//              —— 输出：口音训练设置文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_ATR_WriteParams(const SR_ATRPARAMS& ATRParams,
    const SR_FILE& ATRFile);

//名称：读口音训练参数SR_ATR_ReadParams()
//功能：
//    1.读口音训练参数。
//参数：
//    ATRFile   —— 输入：口音训练设置文件
//    ATRParams —— 输出：口音训练参数
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_ATR_ReadParams(const SR_FILE& ATRFile, SR_ATRPARAMS& ATRParams);

//名称：口音训练特征提取SR_ATR_GetFea_...()
//功能：
//    1.口音训练特征提取。
//参数：
//    handle   —— 输入：引擎句柄
//    WavBuf   —— 输入：语音数据
//    WavFile  —— 输入：语音文件
//    AtrfFile —— 输入：特征文件名称
//             —— 输出：特征文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_ATR_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const SR_FILE& AtrfFile);

SR_API bool SR_ATR_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const SR_FILE& AtrfFile);

//名称：口音模型训练SR_ATR()
//功能：
//    1.口音模型训练。
//参数：
//    handle    —— 输入：引擎句柄
//    ATRParams —— 输入：口音训练参数
//    ATRParams.ATRParams[x].chAidFile —— 输出：口音模型文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_ATR(SR_HANDLE handle, SR_ATRPARAMS& ATRParams);

////////////////////////////////////////////////////////////////////////////////
//口音识别接口
////////////////////////////////////////////////////////////////////////////////

//单个口音识别结果
//说明：
//    1.nAIDScore = INT(实际得分×10000 + 0.9999)
//      这里INT()是取整函数，不是将nAIDScore改为int数据类型
#ifndef _SR_AID_Rst_
#define _SR_AID_Rst_
typedef struct _tag_SR_AID_Rst_
{
    SR_UUID_STR chUUID;     //口音UUID
    SR_AIDM_NAME_STR chName;//口音名称
    int nAIDScore;          //置信度得分
}SR_AIDRST, *LPSR_AIDRST;
#endif //_SR_AID_Rst_

//多个口音识别结果
//说明：
//    1.nRstNum <= SR_MAX_AIDM_NUM
#ifndef _SR_AID_Rsts_
#define _SR_AID_Rsts_
typedef struct _tag_SR_AID_Rsts_
{
    int nRstNum;                      //口音识别结果数目
    SR_AIDRST AIDRst[SR_MAX_AIDM_NUM];   //各口音识别结果
}SR_AIDRSTS, *LPSR_AIDRSTS;
#endif //_SR_AID_Rsts_

//名称：初始化引擎SR_AID_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_AID_Init(const SR_FILE& Dir);

//名称：释放引擎SR_AID_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_AID_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_AID_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_AID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：口音识别SR_AID_...()
//功能：
//    1.口音识别。
//参数：
//    handle  —— 输入：引擎句柄
//    WavBuf  —— 输入：语音数据
//    WavFile —— 输入：语音文件
//    Seg     —— 输入：语音片段(预处理结果)
//    AidRsts —— 输出：各口音识别结果
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_AID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_AIDRSTS& AidRsts);

SR_API bool SR_AID_File(SR_HANDLE handle, SR_FILE WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_AIDRSTS& AidRsts);

////////////////////////////////////////////////////////////////////////////////
//说话人识别接口
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//说话人识别标本最大字节数
#ifndef SR_MAX_SPECIMEN_DATA_LEN
#define SR_MAX_SPECIMEN_DATA_LEN    65536  //64KB
#endif //SR_MAX_SPECIMEN_DATA_LEN

//说话人识别标本数据
#ifndef _SR_SPECIMEN_DATA_
#define _SR_SPECIMEN_DATA_
typedef unsigned char SR_SPECIMEN_DATA[SR_MAX_SPECIMEN_DATA_LEN];
#endif //_SR_SPECIMEN_DATA_

//说话人识别标本
#ifndef _SR_SPECIMEN_
#define _SR_SPECIMEN_
typedef __declspec(align(16)) struct _tag_SR_Specimen_
{
	SR_SPECIMEN_DATA pData; //标本数据
	int nLen;               //标本数据长度
}SR_SPECIMEN, *LPSR_SPECIMEN;
#endif //_SR_SPECIMEN_

//------------------------------------------------------------------------------
//说话人识别单人默认特征最大字节数
#ifndef SR_MAX_DEFAULT_FEA_DATA_LEN
#define SR_MAX_DEFAULT_FEA_DATA_LEN		65536  //64KB
#endif //SR_MAX_DEFAULT_FEA_DATA_LEN

//说话人识别单人默认特征数据
#ifndef _SR_DEFAULT_FEA_DATA_
#define _SR_DEFAULT_FEA_DATA_
typedef unsigned char SR_DEFAULT_FEA_DATA[SR_MAX_DEFAULT_FEA_DATA_LEN];
#endif //_SR_DEFAULT_FEA_DATA_

//说话人识别单人默认特征
#ifndef _SR_DEFAULT_FEA_
#define _SR_DEFAULT_FEA_
typedef __declspec(align(16))  struct _tag_SR_DEFAULT_Fea_
{
	SR_DEFAULT_FEA_DATA pData;		//默认特征数据
	int nLen;                       //默认特征数据长度
}SR_DEFAULT_FEA, *LPSR_DEFAULT_FEA;
#endif //_SR_DEFAULT_FEA_

//------------------------------------------------------------------------------
//说话人识别单人附加特征最大字节数
#ifndef SR_MAX_ADDITIONAL_FEA_DATA_LEN
#define SR_MAX_ADDITIONAL_FEA_DATA_LEN      1024//1KB
#endif //SR_MAX_ADDITIONAL_FEA_DATA_LEN

//说话人识别单人附加特征数据
#ifndef _SR_ADDITIONAL_FEA_DATA_
#define _SR_ADDITIONAL_FEA_DATA_
typedef unsigned char SR_ADDITIONAL_FEA_DATA[SR_MAX_ADDITIONAL_FEA_DATA_LEN];
#endif //_SR_ADDITIONAL_FEA_DATA_

//说话人识别单人附加特征
#ifndef _SR_ADDITIONAL_FEA_
#define _SR_ADDITIONAL_FEA_
typedef __declspec(align(16))  struct _tag_SR_ADDITIONAL_Fea_
{
	SR_ADDITIONAL_FEA_DATA pData;		//附加特征数据
	int nLen;               				//附加特征数据长度
}SR_ADDITIONAL_FEA, *LPSR_ADDITIONAL_FEA;
#endif //_SR_ADDITIONAL_FEA_

//说话人训练处理模式
#ifndef _SR_TRAINTYPE_
#define _SR_TRAINTYPE_
typedef enum _tag_SR_TrainType_
{
	SR_AUTOSID_MERGEDSPEECHTRAIN,          //合路并且训练
	SR_AUTOSID_SEPARATEDSPEECHTRAIN,       //分路并且训练
	SR_AUTOSID_SEPARATEDSPEECHANDSEGTRAIN  //分路、产生语音信息并且训练(人工交互与否)
}SR_TRAINTYPE;
#endif 

//------------------------------------------------------------------------------
//名称：初始化引擎SR_SID_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_SID_Init(const SR_FILE& Dir);

//------------------------------------------------------------------------------
//名称：释放引擎SR_SID_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_SID_Release(SR_HANDLE handle);

//------------------------------------------------------------------------------
//名称：获取最后错误信息SR_SID_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_SID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//------------------------------------------------------------------------------
//名称：说话人特征提取SR_SID_GetFea_...()
//功能：
//    1.说话人特征提取。
//参数：
//    handle		     —— 输入：引擎句柄
//    WavBuf		     —— 输入：语音数据
//    WavFile		     —— 输入：语音文件
//    Seg			       —— 输入：语音片段(说话人分离聚类结果)
//    DefaultFea1    —— 输出：说话人1的默认特征GS
//    DefaultFea2    —— 输出：说话人2的默认特征GS
//    AdditionalFea1 —— 输出：说话人1的附加特征T
//    AdditionalFea2 —— 输出：说话人2的附加特征T
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.对于动态聚类得到的多个说话人语音可按Seg.nType不同，逐个调用。
SR_API bool SR_SID_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2);

SR_API bool SR_SID_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2);

//名称：说话人特征比对及性别识别SR_SID_CompFea_...()
//功能：
//    1.说话人特征比对。
//参数：
//    handle            —— 输入：引擎句柄
//    nSpecimenNum      —— 输入：标本数目
//    pSpecimens        —— 输入：多个标本
//    DefaultFea1		    —— 输入：说话人1的默认特征GS
//    DefaultFea2		    —— 输入：说话人2的默认特征GS
//    AdditionalFea1	  —— 输入：说话人1的附加特征T
//    AdditionalFea2	  —— 输入：说话人2的附加特征T
//    FeaFile           —— 输入：特征文件
//    nFeaDataOffset    —— 输入：特征在特征文件中的首字节偏移量
//    nFeaDataNum       —— 输入：特征数目
//    pnResult          —— 输出：与每个模型比对的识别结果得分
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.SR_SID_CompFea_File()将标本与FeaFile特征文件中、开始位置为nFeaDataOffset
//      的、nFeaDataNum个特征进行比对。nFeaDataNum = 1或2。

//说话人附加特征比对
SR_API bool SR_SID_CompFea_AdditionalBuf(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	const SR_ADDITIONAL_FEA& AdditionalFea1, const SR_ADDITIONAL_FEA& AdditionalFea2, 
	int* pnResult);

//说话人默认特征比对
SR_API bool SR_SID_CompFea_DefaultBuf(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2, 
	int* pnResult);

//说话人附加特征文件比对
SR_API bool SR_SID_CompFea_AdditionalFeaFile(SR_HANDLE handle, 
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile, int nFeaDataOffset, int nFeaDataNum, 
	int* pnResult);

//说话人默认特征文件比对
SR_API bool SR_SID_CompFea_DefaultFeaFile(SR_HANDLE handle, 
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile, int nFeaDataOffset, int nFeaDataNum, 
	int* pnResult);

//名称：说话人自动剪辑或标本训练SR_SID_ModelOREdit_...()
//功能：
//    1.说话人标本生成或者语音自动剪辑
//参数：
//    handle            —— 输入：引擎句柄
//    WavBufList        —— 输入：语音列表
//    FileList          —— 输入：语音文件列表
//    summed		        —— 输入：false表示已人工剪辑;true表示自动剪辑
//    dir	              —— 输入：自动剪辑后语音所在目录=>子目录名
//    pSpecimens		    —— 输出：标本
//返回值：
//    成功返回true；失败返回false。
//说明：
//    
SR_API bool SR_SID_ModelOREdit_Bufs(SR_HANDLE handle, const CFastList<SR_WAVBUF, SR_WAVBUF&>& WavBufList, 
	const CFastList<SR_FILE, SR_FILE&>& WavBufName, SR_SPECIMEN& pSpecimens, SR_FILE& dir, SR_TRAINTYPE TrainType); 

SR_API bool SR_SID_ModelOREdit_Files(SR_HANDLE handle, const CFastList<SR_FILE, SR_FILE&>& FileList, 
	SR_SPECIMEN& pSpecimens, SR_FILE& dir, SR_TRAINTYPE TrainType);



////////////////////////////////////////////////////////////////////////////////
//关键词识别和连续语音识别共用定义
////////////////////////////////////////////////////////////////////////////////

//关键词最大字节数
#ifndef SR_MAX_WORD_BYTES
#define SR_MAX_WORD_BYTES 255
#endif //SR_MAX_WORD_BYTES

#ifndef SR_MAX_WORD_LEN
#define SR_MAX_WORD_LEN (SR_MAX_WORD_BYTES + 1)
#endif //SR_MAX_WORD_LEN

//关键词字符串
#ifndef _SR_WORD_STR_
#define _SR_WORD_STR_
typedef SR_CHAR SR_WORD_STR[SR_MAX_WORD_LEN];
#endif //_SR_WORD_STR_

//关键词音素最大字节数
#ifndef SR_MAX_PHONEME_BYTES
#define SR_MAX_PHONEME_BYTES 1023
#endif //SR_MAX_PHONEME_BYTES

#ifndef SR_MAX_PHONEME_LEN
#define SR_MAX_PHONEME_LEN (SR_MAX_PHONEME_BYTES + 1)
#endif //SR_MAX_PHONEME_LEN

//关键词音素字符串
#ifndef _SR_PHONEME_STR_
#define _SR_PHONEME_STR_
typedef SR_CHAR SR_PHONEME_STR[SR_MAX_PHONEME_LEN];
#endif //_SR_PHONEME_STR_

//关键词最大语音样本数
#ifndef SR_MAX_WORD_WAV_BUF_NUM
#define SR_MAX_WORD_WAV_BUF_NUM 10    
#endif //SR_MAX_WORD_WAV_BUF_NUM

//关键词检索逻辑表达式最大字节数
#ifndef SR_MAX_LOGIC_EXP_BYTES
#define SR_MAX_LOGIC_EXP_BYTES 2047
#endif //SR_MAX_LOGIC_EXP_BYTES

#ifndef SR_MAX_LOGIC_EXP_LEN
#define SR_MAX_LOGIC_EXP_LEN (SR_MAX_LOGIC_EXP_BYTES + 1)
#endif //SR_MAX_LOGIC_EXP_LEN

//关键词检索逻辑表达式字符串
#ifndef _SR_LOGIC_EXP_STR_
#define _SR_LOGIC_EXP_STR_
typedef SR_CHAR SR_LOGIC_EXP_STR[SR_MAX_LOGIC_EXP_LEN];
#endif //_SR_LOGIC_EXP_STR_

//关键词
//说明：
//    1.关键词SRWORD描述存储系统中关键词信息。
//    2.关键词UUID是该词在存储系统中关键词的唯一编号。
//    3.nInputType = 1，代表该词是文本输入的关键词；
//      nInputType = 2，代表该词是音素输入的关键词；
//      nInputType = 3，代表该词是语音输入的关键词。
//    4.当nInputType = 1时，chWord既是关键词名称，又是关键词文本。
//      当nInputType = 2或3时，chWord仅代表关键词名称。
//    5.chPhoneme是表征检索词的唯一标识。
//    6.当关键词所属语种的语种为汉语普通话时，关键词音素是空格分隔的带声调的
//      汉语拼音。每个字的拼音后带一个0-4的数字，表示对应的音调。0表示轻声，
//      1-4对应于第1-4声。例如：“zhong1 hua2 ren2 min2 gong4 he2 guo2”。
//      当关键词所属语种的语种为英语时，关键词音素是空格分隔的英语音标。
//      当关键词所属语种的语种为其他语种时，另行定义。
//    7.当nInputType = 3时，nWavBufNum，WavBuf有效。
//    8.nWavBufNum <= SR_MAX_WORD_WAV_BUF_NUM。
//    9.nThreadhold1和nThreadhold2是存储系统中保存的关键词阈值，
//      取值范围是[1,100]。
#ifndef _SR_Word_
#define _SR_Word_
typedef struct _tag_SR_Word_
{
    SR_UUID_STR      chUUID;        //关键词UUID,这里没有存储guid，存储的是关键词本地库ID
    SR_UUID_STR      chLidUUID;     //关键词所属语种的UUID
    SR_LIDM_NAME_STR chLidName;     //关键词所属语种的名称
    int              nInputType;    //关键词输入类型
    SR_WORD_STR      chWord;        //关键词文本（名称）
    SR_PHONEME_STR   chPhoneme;     //关键词音素（空格分隔）
    int              nWavBufNum;    //关键词语音样本数目
    SR_WAVBUF        WavBuf[SR_MAX_WORD_WAV_BUF_NUM]; //关键词语音样本
    int              nThreadhold1;  //实时中标阈值
    int              nThreadhold2;  //后期检索阈值
}SR_WORD, *LPSR_WORD;
#endif //_SR_Word_

//单个检索词
//说明：
//    1.单个检索词SR_SEARCHWORD描述在检索时每个关键词的信息。
//    2.chUUID：用于回写识别结果。
//    3.chWord：用于回写识别结果和界面显示。
//    4.检索词仅与语种一致的关键词索引进行比对，其判别依据是：
//      chLidUUID相同。
//      chLidUUID为空时，检索词仅与非限定语种的关键词索引进行比对。
//    5.chPhoneme：是表征检索词的唯一标识。
//    6.nThreadhold：
//      在实时检索时，应用系统设置nThreadhold = SR_WORD.nThreadhold1，
//      在后期检索时，应用系统设置nThreadhold = SR_WORD.nThreadhold2。
//    7.检索词在语音中的采样点范围为[nStart,nEnd)。
#ifndef _SR_SearchWord_
#define _SR_SearchWord_
typedef struct _tag_SR_SearchWord_
{
    SR_UUID_STR    chUUID;      //检索词UUID
    SR_WORD_STR    chWord;      //检索词名称
    SR_UUID_STR    chLidUUID;   //检索词所属语种的UUID
    SR_PHONEME_STR chPhoneme;   //检索词音素
    int            nThreadhold; //检索词阈值
    int            nStart;      //检索词在语音中的范围
    int            nEnd;        //检索词在语音中的范围
}SR_SEARCHWORD, *LPSR_SEARCHWORD;
#endif //_SR_SearchWord_

//单个检索结果
//说明：
//    1.关键词在语音中的采样点范围为[nStart,nEnd)。
//    2.置信度得分，取值范围为[1,100]。
#ifndef _SR_SearchRst_
#define _SR_SearchRst_
typedef struct _tag_SR_SearchRst_
{
    __int64     nFileID; //文件ID
    SR_UUID_STR chUUID;  //检索词UUID
    SR_WORD_STR chWord;  //检索词名称
    int         nStart;  //关键词在语音中的范围
    int         nEnd;    //关键词在语音中的范围
    int         nScore;  //置信度得分
}SR_SEARCHRST, *LPSR_SEARCHRST;
#endif //_SR_SearchWords_

////////////////////////////////////////////////////////////////////////////////
//关键词识别接口
////////////////////////////////////////////////////////////////////////////////

//名称：初始化引擎SR_KWS_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_KWS_Init(const SR_FILE& Dir);

//名称：释放引擎SR_KWS_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_KWS_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_KWS_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_KWS_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：加载模型SR_KWS_LoadMod()
//功能：
//    1.加载模型。供进程间共享大内存的模型，提高多个引擎实例初始化速度。
//参数：
//    handle  —— 输入：引擎句柄
//    Dir     —— 输入：模型所在目录
//    LidUUID —— 输入：模型所对应的语种，也代表模型的唯一编号
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_KWS_LoadMod(SR_HANDLE handle, const SR_FILE& Dir,
    const SR_UUID_STR& LidUUID);

//名称：选用模型SR_KWS_UseMod()
//功能：
//    1.选用模型。
//参数：
//    handle  —— 输入：当前引擎句柄
//    LidUUID —— 输入：模型所对应的语种，也代表模型的唯一编号
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_KWS_UseMod(SR_HANDLE handle, const SR_UUID_STR& LidUUID);

//名称：释放模型SR_KWS_ReleaseMod()
//功能：
//    1.释放模型。
//参数：
//    handle —— 输入：引擎句柄
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_KWS_ReleaseMod(SR_HANDLE handle);

//名称：获得关键词音素SR_KWS_GetPhoneme()
//功能：
//    1.获得关键词音素。
//参数：
//    handle —— 输入：引擎句柄
//    pWord  —— 输入：关键词
//           —— 输出：pWord->chPhoneme
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.当pWord->nInputType=1时，
//      根据pWord->chWord得到pWord->chPhoneme；
//      当pWord->nInputType=2时，
//      检查pWord->chPhoneme合法性；
//      当pWord->nInputType=3时，
//      根据pWord->nWavBufNum、pWord->WavBuf得到pWord->chPhoneme；
SR_API bool SR_KWS_GetPhoneme(SR_HANDLE handle, SR_WORD& Word);

//名称：关键词特征提取SR_KWS_GetFea_...()
//功能：
//    1.关键词特征提取。
//参数：
//    handle     —— 输入：引擎句柄
//    WavBuf     —— 输入：语音数据
//    WavFile    —— 输入：语音文件
//    Seg        —— 输入：语音片段(预处理结果)
//    nFeaBufLen —— 输出：特征字节数
//    pFeaBuf    —— 输出：特征
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_KWS_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int &nFeaBufLen, void* &pFeaBuf);

SR_API bool SR_KWS_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int &nFeaBufLen, void* &pFeaBuf);

//名称：保存关键词特征SR_KWS_WriteFea()
//功能：
//    1.保存关键词特征。
//参数：
//    handle     —— 输入：引擎句柄
//    nFileID    —— 输入：语音文件在存储系统中的唯一编号
//    nFeaBufLen —— 输入：特征字节数
//    pFeaBuf    —— 输入：特征
//    FeaFile    —— 输入：特征文件名称
//               —— 输出：特征文件
//返回值：
//    成功返回true；失败返回false。
//说明：
SR_API bool SR_KWS_WriteFea(SR_HANDLE handle, __int64 nFileID,
	int nFeaBufLen, void *pFeaBuf, const SR_FILE& FeaFile);

//名称：读关键词特征SR_KWS_ReadFea()
//功能：
//    1.读关键词特征。
//参数：
//    handle     —— 输入：引擎句柄
//    FeaFile    —— 输入：特征文件名称
//    nFileID    —— 输出：语音文件在存储系统中的唯一编号
//    nFeaBufLen —— 输出：特征字节数
//    pFeaBuf    —— 输出：特征
//返回值：
//    成功返回true；失败返回false。
//说明：
SR_API bool SR_KWS_ReadFea(SR_HANDLE handle, const SR_FILE& FeaFile,
    __int64 &nFileID, int &nFeaBufLen, void* &pFeaBuf);

//名称：建立关键词索引SR_KWS_AddFeaToIdx_...()
//功能：
//    1.建立关键词索引。
//参数：
//    handle       —— 输入：引擎句柄
//    nFileID      —— 输入：语音文件在存储系统中的唯一编号
//    nFeaBufLen   —— 输入：特征字节数
//    pFeaBuf      —— 输入：特征
//    FeaFile      —— 输入：特征文件
//    pFeaFileList —— 输入：多个特征文件
//    IdxFile      —— 输入：索引文件名称
//                 —— 输出：索引文件
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_KWS_AddFeaToIdx_Buf(SR_HANDLE handle,
    __int64 nFileID, int nFeaBufLen, void *pFeaBuf, const SR_FILE& IdxFile);

SR_API bool SR_KWS_AddFeaToIdx_File(SR_HANDLE handle,
    const SR_FILE& FeaFile, const SR_FILE& IdxFile);

SR_API bool SR_KWS_AddFeaToIdx_Files(SR_HANDLE handle,
	const CFastList<SR_FILE, SR_FILE&>& FeaFileList, const SR_FILE& IdxFile);

//名称：关键词检索SR_KWS_Search_...()
//功能：
//    1.关键词检索。
//参数：
//    handle         —— 输入：引擎句柄
//    nSearchType    —— 输入：检索模式
//    SearchWordList —— 输入：所有检索词
//    LogicExp       —— 输入：检索逻辑表达式
//    FeaBufLen      —— 输入：特征字节数
//    pFeaBuf        —— 输入：特征
//    FeaFileList    —— 输入：多个特征文件
//    IdxFileList    —— 输入：多个索引文件
//    SearchRstList  —— 输出：检索结果
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.检索模式nSearchType的取值及含义如下：
//      1-低误报、精确比对检索模式；
//      2-低误报、模糊比对检索模式；
//      3-低漏报、精确比对检索模式；
//      4-低漏报、模糊比对检索模式。
SR_API bool SR_KWS_Search_FeaBuf(SR_HANDLE handle, short nSearchType, 
    const CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
    const SR_LOGIC_EXP_STR& LogicExp, int nFeaBufLen, void *pFeaBuf, 
    CFastList<SR_SEARCHRST, SR_SEARCHRST&>& SearchRstList);

SR_API bool SR_KWS_Search_FeaFiles(SR_HANDLE handle, short nSearchType, 
    const CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
    const SR_LOGIC_EXP_STR& LogicExp,
    const CFastList<SR_FILE, SR_FILE&>& FeaFileList,
    CFastList<SR_SEARCHRST, SR_SEARCHRST&>& SearchRstList);

SR_API bool SR_KWS_Search_IdxFiles(SR_HANDLE handle, short nSearchType, 
    const CFastList<SR_SEARCHWORD, SR_SEARCHWORD&>& SearchWordList,
    const SR_LOGIC_EXP_STR& LogicExp,
    const CFastList<SR_FILE, SR_FILE&>& IdxFileList,
    CFastList<SR_SEARCHRST, SR_SEARCHRST&>& SearchRstList);

/*
////////////////////////////////////////////////////////////////////////////////
//连续语音识别接口
////////////////////////////////////////////////////////////////////////////////

/////////////// 训练部分

//训练特定人模型
//说明：
//    1.关键词SRWORD描述存储系统中关键词信息。
#ifndef _SR_Utterance_
#define _SR_Utterance_
typedef struct _tag_SR_Utterance_
{
	SR_WORD_STR      Sentence;        //标注文本
	SR_WAVBUF        WavBuf; //语音句子
}SR_UTTERANCE, *LPSR_UTTERANCE;
#endif //_SR_Utterance_

//名称：特定人模型训练SR_CSR_Train()
//功能：
//    1.加载模型。供进程间共享大内存的模型，提高多个引擎实例初始化速度。
//参数：
//    Dir            —— 输入：模型所在目录
//    Utterances     —— 输入：训练语音和标注列表
//    Model          —— 输出：模型文件
//    Error          —— 输出：错误信息（当函数返回false时）
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_CSR_Train(const SR_FILE& Dir,
	CFastList<SR_UTTERANCE, SR_UTTERANCE&> Utterances,
	const SR_FILE& Model,
	SR_ERROR& Error
	);

////////////////////////////////////////////////////////////////////////////////

//字或单词的最大字节数
#ifndef SR_CSR_MAX_WORD_BYTES
#define SR_CSR_MAX_WORD_BYTES   255
#endif //SR_CSR_MAX_WORD_BYTES

#ifndef SR_CSR_MAX_WORD_LEN
#define SR_CSR_MAX_WORD_LEN   (SR_CSR_MAX_WORD_BYTES + 1)
#endif //SR_CSR_MAX_WORD_LEN

//字或单词字符串
#ifndef _SR_CSR_WORD_STR_
#define _SR_CSR_WORD_STR_
typedef SR_CHAR SR_CSR_WORD_STR[SR_CSR_MAX_WORD_LEN];
#endif //_SR_CSR_WORD_STR_

//字或单词的连续语音识别结果
//说明：
//    1.置信度得分nScore的取值范围是[1,100]。
#ifndef _SR_CSR_WordRst_
#define _SR_CSR_WordRst_
typedef struct _tag_SR_CSR_WordRst_
{
	SR_CSR_WORD_STR chWord; //字或单词
	int nScore;             //置信度得分
}SR_CSR_WORD_RST, *LPSR_CSR_WORD_RST;
#endif //_SR_CSR_WordRst_

//句子的连续语音识别结果
//说明：
//    1.句子在语音中的采样点范围为[nStart,nEnd)。
#ifndef _SR_CSR_SentenceRst_
#define _SR_CSR_SentenceRst_
typedef struct _tag_SR_CSR_SentenceRst_
{
	int nStart;			//句子在语音中的范围
	int nEnd; 			//句子在语音中的范围
	CFastList<SR_CSR_WORD_RST, SR_CSR_WORD_RST&> Sentence; //句子的识别结果
}SR_CSR_SENTENCE_RST, *LPSR_SR_CSR_SENTENCE_RST;
#endif //_SR_CSR_SentenceRst_

//名称：初始化引擎SR_CSR_Init()
//功能：
//    1.初始化引擎。
//参数：
//    Dir —— 输入：引擎及参数所在的目录
//返回值：
//    成功返回引擎句柄；否则返回NULL。
SR_API SR_HANDLE SR_CSR_Init(const SR_FILE& Dir);

//名称：释放引擎SR_CSR_Release()
//功能：
//    1.释放引擎。
//参数：
//    handle —— 输入：引擎句柄
SR_API void SR_CSR_Release(SR_HANDLE handle);

//名称：获取最后错误信息SR_CSR_GetLastError()
//功能：
//    1.获取最后错误信息。
//参数：
//    handle —— 输入：引擎句柄
//    Error  —— 输出：最后错误信息
SR_API void SR_CSR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//名称：加载模型SR_CSR_LoadMod()
//功能：
//    1.加载特定人模型
//参数：
//    handle  —— 输入：引擎句柄
//    Model   —— 输入：模型文件
//    SpkID   —— 输入：模型所对应的特定人，也代表模型的唯一编号
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_CSR_LoadMod(SR_HANDLE handle, const SR_FILE& Model, int SpkID);

//名称：释放模型SR_CSR_ReleaseMod()
//功能：
//    1.释放模型。
//参数：
//    handle     —— 输入：引擎句柄
//    SpkID      —— 输入：释放特定人模型的SpkID
//返回值：
//    成功返回true；失败返回false。
SR_API bool SR_CSR_ReleaseMod(SR_HANDLE handle, int SpkID);

//名称：连续语音识别SR_CSR_...()
//功能：
//    1.连续语音识别。
//参数：
//    handle  —— 输入：引擎句柄
//    WavBuf  —— 输入：语音数据
//    WavFile —— 输入：语音文件
//    Seg     —— 输入：语音片段(预处理结果)
//    nType   —— 输入：识别结果输出模式
//    CsrRst  —— 输出：连续语音识别结果
//返回值：
//    成功返回true；失败返回false。
//说明：
//    1.nType的取值范围是：0-不输出置信度得分；1-输出置信度得分。
//    2.SR_SEG Seg.nType: SpkID,和装载模型的SpkID对应,
//      取值范围：0-未知说话人
SR_API bool SR_CSR_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int nType,
	CFastList<SR_CSR_SENTENCE_RST, SR_CSR_SENTENCE_RST&>& CsrRst);

SR_API bool SR_CSR_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int nType,
	CFastList<SR_CSR_SENTENCE_RST, SR_CSR_SENTENCE_RST&>& CsrRst);
	*/
#endif //_NJ841_SR_H_