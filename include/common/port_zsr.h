#ifndef PORT_ZSR__H
#define PORT_ZSR__H

/*
typedef struct{} *POSITION;
typedef unsigned short WORD;
typedef unsigned long DWORD;
#define NEAR
#define FAR
*/
#if defined(WIN32) || defined(_WINDLL)
#include <afx.h>

#endif

wchar_t *GB2312sToWCs(const char *strIn);
char *WCsToGB2312s(const wchar_t *strIn);
wchar_t *UTF8sToWCs(const char *strIn);
char *WCsToUTF8s(const wchar_t *strIn);

/**
�Ա�ģ��ĺ���������������ɴ˺�����ȡ��
*/
const char* getLastErrorStr();


#endif