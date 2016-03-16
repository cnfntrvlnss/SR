#ifndef SR_FILELIST_H
#define SR_FILELIST_H

#include "sr.h"
#include "cfastlist.h"

#define SR_MAX_PATHNAME_BYTES 255
#define SR_MAX_PATHNAME_LEN (SR_MAX_PATHNAME_BYTES + 1) //文件名最大长度

typedef struct _tag_SR_FILE_ 
{ 
	SR_CHAR PathName[SR_MAX_PATHNAME_LEN];
}SR_FILE, *LPSR_FILE;

/**
* 获取最后错误信息
* \param handle [in] 引擎句柄
* \param Error  [out] 最后错误信息
*/
SR_API void SR_FL_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

/**
* 将列表文件的数据加载至内存
* \param File [in] 列表文件
* \FileList [out] 指向文件列表的指针
* \return 成功返回true；失败返回false
*/
SR_API bool SR_FL_ReadListFile(const SR_FILE& File, CFastList<SR_FILE, SR_FILE&>& FileList);

/**
* 将内存的文件列表保存到列表文件中
* \param FileList [in] 指向文件列表的指针
* \param File [out] 列表文件
* \return 成功返回true, 失败返回false
*/
SR_API bool SR_FL_WriteListFile(const CFastList<SR_FILE, SR_FILE&>& FileList,
	const SR_FILE& File);
#endif


