#ifndef STR_H
#define STR_H

/*UNICODE�����л�*/
#ifdef UNICODE
#undef _T
#define _T(x) L ## x
//UNICODE��ʽ�µ��ַ���
#undef TXT_FORMAT_UTF8
#define TXT_FORMAT_UTF8
//UNICODE��ʽ�£�ǿ��ʹ��UTF-8��ʽ
#endif //UNICODE
#ifndef UNICODE
#undef _T
#define _T(x) x //ANSI��ʽ�µ��ַ���
#endif //UNICODE
#ifdef UNICODE
#undef TXT_FORMAT_UTF8
#define TXT_FORMAT_UTF8 //UNICODE��ʽ�£�ǿ��ʹ��UTF-8��ʽ
#endif
//��Warning C4996�Ĵ���
#define _CRT_SECURE_CPP_OVERLOAD_STAND_NAMES 1
#pragma warning(disable:4996)

//typedef unsigned short wchar_t; 
#ifdef UNICODE 
typedef wchar_t SR_CHAR;
#else 
typedef char SR_CHAR;
#endif //UNICODE 
typedef SR_CHAR* LPSR_CHAR;

/*�ַ����ڴ��������*/
#ifdef UNICODE 
#define STRSET wcsset //�����ַ����е��ַ�Ϊָ���ַ� 
#define _STRSET _wcsset //�����ַ����е��ַ�Ϊָ���ַ�
#define STRCPY wcscpy //�����ַ��� 
#define STRNCPY wcsncpy //�����ַ���
#define STRDUP wcsdup //�����ַ���
#define _STRDUP _wcsdup //�����ַ���
#define STRCAT wcscat //����ַ���
#define STRNCAT wcsncat //����ַ���
#define STRCMP wcscmp //�Ƚ��ַ��� 
#define STRICMP wcsicmp //�Ƚ��ַ���* 
#define STRNCMP wcsncmp //�Ƚ��ַ���*
#define STRNICMP wcsnicmp //�Ƚ��ַ���* 
#define _STRNICMP _wcsnicmp //�Ƚ��ַ���*
#define STRCOLL wcscoll //�Ƚ��ַ���*
#define _STRICOLL _wcsicoll //�Ƚ��ַ���* 
#define _STRNCOLL _wcsncoll //�Ƚ��ַ���*
#define _STRNICOLL _wcsnicoll //�Ƚ��ַ���* 
#define _STRCOLL_L _wcscoll_l //�Ƚ��ַ���* 
#define _STRICOLL_L _wcsicoll_l //�Ƚ��ַ���*
#define _STRNCOLL_L _wcsncoll_l //�Ƚ��ַ���* 
#define _STRNICOLL_L _wcsnicoll_l //�Ƚ��ַ���* 
#define STRLEN wcslen //��ȡ�ַ�������
#define STRCHR wcschr //���ַ����в����ַ�
#define STRSTR wcsstr //���ַ����в������ַ���
#define STRCSPN wcscspn //���ַ����в������ַ���
#define STRPBRK wcspbrk //���ַ����в����ַ����е��ַ�
#define STRSPN wcsspn //���ַ����в��ҵ�һ�����ַ���
#define STRRCHR wcsrchr //���ַ����в��������ֵ��ַ� 
#define STRTOK wcstok //���ַ����в�����һ��token 
#define STRLWR wcslwr //ת��ΪСд
#define _STRLWR _wcslwr //ת��ΪСд
#define _STRICMP _wcsicmp //����Сд�ַ����Ƚ� 
#define _STRICMP_L _wcsicmp_l //����Сд�ַ����Ƚ�
#define STRUPR wcsupr //ת��Ϊ��д 
#define _STRUPR _wcsupr //ת��Ϊ��д
#define STRNSET wcsnset //��ʼ���ַ���Ϊָ����ʽ
#define _STRNSET _wcsnset //��ʼ���ַ���Ϊָ����ʽ 
#define STRREV wcsrev //�ߵ��ַ������ַ�
#define _STRREV _wcsrev //�ߵ��ַ������ַ� 
#define STRXFRM wcsxfrm //����ָ����Ϣת���ַ��� 
#define _STRXFRM_L _wcsxfrm_l //����ָ����Ϣת���ַ���
#define STRERROR _wcserror //��ȡϵͳ������Ϣ 
#define _STRERROR __wcserror //��ȡϵͳ������Ϣ
#else //UNICODE 
#define STRSET strset //�����ַ����е��ַ�Ϊָ���ַ�
#define _STRSET _strset //�����ַ����е��ַ�Ϊָ���ַ�
#define STRCPY strcpy //�����ַ���
#define STRNCPY strncpy //�����ַ��� 
#define STRDUP strdup //�����ַ���
#define _STRDUP _strdup //�����ַ���
#define STRCAT strcat //����ַ���
#define STRNCAT strncat //����ַ���
#define STRCMP strcmp //�Ƚ��ַ���
#define STRICMP stricmp //�Ƚ��ַ���*
#define STRNCMP strncmp //�Ƚ��ַ���*
#define STRNICMP strnicmp //�Ƚ��ַ���* 
#define _STRNICMP _strnicmp //�Ƚ��ַ���*
#define STRCOLL strcoll //�Ƚ��ַ���*
#define _STRICOLL _stricoll //�Ƚ��ַ���*
#define _STRNCOLL _strncoll //�Ƚ��ַ���*
#define _STRNICOLL _strnicoll //�Ƚ��ַ���*
#define _STRCOLL_L _strcoll_l //�Ƚ��ַ���*
#define _STRICOLL_L _stricoll_l //�Ƚ��ַ���* 
#define _STRNCOLL_L _strncoll_l //�Ƚ��ַ���*
#define _STRNICOLL_L _strnicoll_l //�Ƚ��ַ���* 
#define STRLEN strlen //��ȡ�ַ������� 
#define STRCHR strchr //���ַ����в����ַ� 
#define STRSTR strstr //���ַ����в������ַ���
#define STRCSPN strcspn //���ַ����в������ַ���
#define STRPBRK strpbrk //���ַ����в����ַ����е��ַ�
#define STRSPN strspn //���ַ����в��ҵ�һ�����ַ���
#define STRRCHR strrchr //���ַ����в��������ֵ��ַ�
#define STRTOK strtok //���ַ����в�����һ��token
#define STRLWR strlwr //ת��ΪСд
#define _STRLWR _strlwr //ת��ΪСд
#define _STRICMP _stricmp //����Сд�ַ����Ƚ�
#define _STRICMP_L _stricmp_l //����Сд�ַ����Ƚ�
#define STRUPR strupr //ת��Ϊ��д
#define _STRUPR _strupr //ת��Ϊ��д
#define STRNSET strnset //��ʼ���ַ���Ϊָ����ʽ
#define _STRNSET _strnset //��ʼ���ַ���Ϊָ����ʽ 
#define STRREV strrev //�ߵ��ַ������ַ�
#define _STRREV _strrev //�ߵ��ַ������ַ�
#define STRXFRM strxfrm //����ָ����Ϣת���ַ��� 
#define _STRXFRM_L _strxfrm_l //����ָ����Ϣת���ַ���
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
#define FOPEN_MODE_READ L"r" //��ֻ��ģʽ���ļ�
#define FOPEN_MODE_WRITE L"w" //�������ļ����򰴸���дģʽ���ļ� 
#define FOPEN_MODE_APPEND L"a" //�����дģʽ���ļ� 
#define FOPEN_MODE_READ2 L"r+" //����дģʽ���ļ�
#define FOPEN_MODE_WRITE2 L"w+" //�������ļ����򰴶�ģʽ�Ͱ�����дģʽ���ļ�
#define FOPEN_MODE_APPEND2 L"a+" //�������ļ����򰴶�ģʽ�����дģʽ���ļ�
#define FOPEN_MODE_TEXT L"t" //���ı���ʽ���ļ�
#define FOPEN_MODE_BINARY L"b" //�Զ����Ʒ�ʽ���ļ�
#define FOPEN_MODE_COMMIT L"c" //
#define FOPEN_MODE_NOCOMMIT L"n" // 
#define FOPEN_MODE_S L"S" //
#define FOPEN_MODE_R L"R" // 
#define FOPEN_MODE_T L"T" // 
#define FOPEN_MODE_D L"D" //
#else //UNICODE
#define FOPEN_MODE_READ "r" //��ֻ��ģʽ���ļ�
#define FOPEN_MODE_WRITE "w" //�������ļ����򰴸���дģʽ���ļ�
#define FOPEN_MODE_APPEND "a" //�����дģʽ���ļ� 
#define FOPEN_MODE_READ2 "r+" //����дģʽ���ļ�
#define FOPEN_MODE_WRITE2 "w+" //�������ļ����򰴶�ģʽ�Ͱ�����дģʽ���ļ�
#define FOPEN_MODE_APPEND2 "a+" //�������ļ����򰴶�ģʽ�����дģʽ���ļ�
#define FOPEN_MODE_TEXT "t" //���ı���ʽ���ļ� 
#define FOPEN_MODE_BINARY "b" //�Զ����Ʒ�ʽ���ļ�
#define FOPEN_MODE_COMMIT "c" //
#define FOPEN_MODE_NOCOMMIT "n" //
#define FOPEN_MODE_S "S" // 
#define FOPEN_MODE_R "R" // 
#define FOPEN_MODE_T "T" // 
#define FOPEN_MODE_D "D" //
#endif //UNICODE

#endif //STR_H