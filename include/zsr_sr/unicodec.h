#ifndef STR_H
#define STR_H

/*UNICODE编码切换*/
#ifdef UNICODE
#undef _T
#define _T(x) L ## x
//UNICODE方式下的字符串
#undef TXT_FORMAT_UTF8
#define TXT_FORMAT_UTF8
//UNICODE方式下，强制使用UTF-8格式
#endif //UNICODE
#ifndef UNICODE
#undef _T
#define _T(x) x //ANSI方式下的字符串
#endif //UNICODE
#ifdef UNICODE
#undef TXT_FORMAT_UTF8
#define TXT_FORMAT_UTF8 //UNICODE方式下，强制使用UTF-8格式
#endif
//对Warning C4996的处理
#define _CRT_SECURE_CPP_OVERLOAD_STAND_NAMES 1
#pragma warning(disable:4996)

//typedef unsigned short wchar_t; 
#ifdef UNICODE 
typedef wchar_t SR_CHAR;
#else 
typedef char SR_CHAR;
#endif //UNICODE 
typedef SR_CHAR* LPSR_CHAR;

/*字符串内存操作定义*/
#ifdef UNICODE 
#define STRSET wcsset //设置字符串中的字符为指定字符 
#define _STRSET _wcsset //设置字符串中的字符为指定字符
#define STRCPY wcscpy //复制字符串 
#define STRNCPY wcsncpy //复制字符串
#define STRDUP wcsdup //复制字符串
#define _STRDUP _wcsdup //复制字符串
#define STRCAT wcscat //添加字符串
#define STRNCAT wcsncat //添加字符串
#define STRCMP wcscmp //比较字符串 
#define STRICMP wcsicmp //比较字符串* 
#define STRNCMP wcsncmp //比较字符串*
#define STRNICMP wcsnicmp //比较字符串* 
#define _STRNICMP _wcsnicmp //比较字符串*
#define STRCOLL wcscoll //比较字符串*
#define _STRICOLL _wcsicoll //比较字符串* 
#define _STRNCOLL _wcsncoll //比较字符串*
#define _STRNICOLL _wcsnicoll //比较字符串* 
#define _STRCOLL_L _wcscoll_l //比较字符串* 
#define _STRICOLL_L _wcsicoll_l //比较字符串*
#define _STRNCOLL_L _wcsncoll_l //比较字符串* 
#define _STRNICOLL_L _wcsnicoll_l //比较字符串* 
#define STRLEN wcslen //获取字符串长度
#define STRCHR wcschr //在字符串中查找字符
#define STRSTR wcsstr //在字符串中查找子字符串
#define STRCSPN wcscspn //在字符串中查找子字符串
#define STRPBRK wcspbrk //在字符串中查找字符集中的字符
#define STRSPN wcsspn //在字符串中查找第一个子字符串
#define STRRCHR wcsrchr //在字符串中查找最后出现的字符 
#define STRTOK wcstok //在字符串中查找下一个token 
#define STRLWR wcslwr //转换为小写
#define _STRLWR _wcslwr //转换为小写
#define _STRICMP _wcsicmp //进行小写字符串比较 
#define _STRICMP_L _wcsicmp_l //进行小写字符串比较
#define STRUPR wcsupr //转换为大写 
#define _STRUPR _wcsupr //转换为大写
#define STRNSET wcsnset //初始化字符串为指定格式
#define _STRNSET _wcsnset //初始化字符串为指定格式 
#define STRREV wcsrev //颠倒字符串的字符
#define _STRREV _wcsrev //颠倒字符串的字符 
#define STRXFRM wcsxfrm //根据指定信息转换字符串 
#define _STRXFRM_L _wcsxfrm_l //根据指定信息转换字符串
#define STRERROR _wcserror //获取系统错误信息 
#define _STRERROR __wcserror //获取系统错误信息
#else //UNICODE 
#define STRSET strset //设置字符串中的字符为指定字符
#define _STRSET _strset //设置字符串中的字符为指定字符
#define STRCPY strcpy //复制字符串
#define STRNCPY strncpy //复制字符串 
#define STRDUP strdup //复制字符串
#define _STRDUP _strdup //复制字符串
#define STRCAT strcat //添加字符串
#define STRNCAT strncat //添加字符串
#define STRCMP strcmp //比较字符串
#define STRICMP stricmp //比较字符串*
#define STRNCMP strncmp //比较字符串*
#define STRNICMP strnicmp //比较字符串* 
#define _STRNICMP _strnicmp //比较字符串*
#define STRCOLL strcoll //比较字符串*
#define _STRICOLL _stricoll //比较字符串*
#define _STRNCOLL _strncoll //比较字符串*
#define _STRNICOLL _strnicoll //比较字符串*
#define _STRCOLL_L _strcoll_l //比较字符串*
#define _STRICOLL_L _stricoll_l //比较字符串* 
#define _STRNCOLL_L _strncoll_l //比较字符串*
#define _STRNICOLL_L _strnicoll_l //比较字符串* 
#define STRLEN strlen //获取字符串长度 
#define STRCHR strchr //在字符串中查找字符 
#define STRSTR strstr //在字符串中查找子字符串
#define STRCSPN strcspn //在字符串中查找子字符串
#define STRPBRK strpbrk //在字符串中查找字符集中的字符
#define STRSPN strspn //在字符串中查找第一个子字符串
#define STRRCHR strrchr //在字符串中查找最后出现的字符
#define STRTOK strtok //在字符串中查找下一个token
#define STRLWR strlwr //转换为小写
#define _STRLWR _strlwr //转换为小写
#define _STRICMP _stricmp //进行小写字符串比较
#define _STRICMP_L _stricmp_l //进行小写字符串比较
#define STRUPR strupr //转换为大写
#define _STRUPR _strupr //转换为大写
#define STRNSET strnset //初始化字符串为指定格式
#define _STRNSET _strnset //初始化字符串为指定格式 
#define STRREV strrev //颠倒字符串的字符
#define _STRREV _strrev //颠倒字符串的字符
#define STRXFRM strxfrm //根据指定信息转换字符串 
#define _STRXFRM_L _strxfrm_l //根据指定信息转换字符串
#endif//UNICODE

#ifdef UNICODE
#define STRTOD wcstod
#define MEMCPY wmemcpy
#define PRINTF wprintf
#define FGETS fgetws
#define FPRINTF fwprintf
#else //UNICODE
#define STRTOD strtod
#define MEMCPY memcpy
#define PRINTF printf
#define FGETS fgets
#define FPRINTF fprintf
#endif //UNICODE

#ifdef UNICODE
#define FOPEN_MODE_READ L"r" //按只读模式打开文件
#define FOPEN_MODE_WRITE L"w" //创建新文件，或按覆盖写模式打开文件 
#define FOPEN_MODE_APPEND L"a" //按添加写模式打开文件 
#define FOPEN_MODE_READ2 L"r+" //按读写模式打开文件
#define FOPEN_MODE_WRITE2 L"w+" //创建新文件，或按读模式和按覆盖写模式打开文件
#define FOPEN_MODE_APPEND2 L"a+" //创建新文件，或按读模式和添加写模式打开文件
#define FOPEN_MODE_TEXT L"t" //以文本方式打开文件
#define FOPEN_MODE_BINARY L"b" //以二进制方式打开文件
#define FOPEN_MODE_COMMIT L"c" //
#define FOPEN_MODE_NOCOMMIT L"n" // 
#define FOPEN_MODE_S L"S" //
#define FOPEN_MODE_R L"R" // 
#define FOPEN_MODE_T L"T" // 
#define FOPEN_MODE_D L"D" //
#else //UNICODE
#define FOPEN_MODE_READ "r" //按只读模式打开文件
#define FOPEN_MODE_WRITE "w" //创建新文件，或按覆盖写模式打开文件
#define FOPEN_MODE_APPEND "a" //按添加写模式打开文件 
#define FOPEN_MODE_READ2 "r+" //按读写模式打开文件
#define FOPEN_MODE_WRITE2 "w+" //创建新文件，或按读模式和按覆盖写模式打开文件
#define FOPEN_MODE_APPEND2 "a+" //创建新文件，或按读模式和添加写模式打开文件
#define FOPEN_MODE_TEXT "t" //以文本方式打开文件 
#define FOPEN_MODE_BINARY "b" //以二进制方式打开文件
#define FOPEN_MODE_COMMIT "c" //
#define FOPEN_MODE_NOCOMMIT "n" //
#define FOPEN_MODE_S "S" // 
#define FOPEN_MODE_R "R" // 
#define FOPEN_MODE_T "T" // 
#define FOPEN_MODE_D "D" //
#endif //UNICODE

#endif //STR_H