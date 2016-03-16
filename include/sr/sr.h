#ifndef _NJ841_SR_H_
#define _NJ841_SR_H_

//SR.h  ����ʶ��ӿڶ���
//����ˣ����

////////////////////////////////////////////////////////////////////////////////////////////////////
//�ӿ����ò���
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FastList.h"

//------------------------------------------------------------------------------
//Ϊ����Linux��Windowsƽ̨������mmsystem.h��mmreg.h�ж��������ݸ�ʽ�Ķ������£�
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
//ͨ�ýӿ�
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//UNICODE���뿪��
#ifndef UNICODE
#define UNICODE
#endif //UNICODE


//�ַ����ڴ�������壨�ò��ֿɸ�����Ҫ�����䣩
#ifdef  UNICODE
    #define STRSET          wcsset          //�����ַ����е��ַ�Ϊָ���ַ�
    #define _STRSET         _wcsset         //�����ַ����е��ַ�Ϊָ���ַ�
    #define STRCPY          wcscpy          //�����ַ���
    #define STRNCPY         wcsncpy         //�����ַ���
    #define STRDUP          wcsdup          //�����ַ���
    #define _STRDUP         _wcsdup         //�����ַ���
    #define STRCAT          wcscat          //����ַ���
    #define STRNCAT         wcsncat         //����ַ���
    #define STRCMP          wcscmp          //�Ƚ��ַ���
    #define STRICMP         wcsicmp         //�Ƚ��ַ���*
    #define STRNCMP         wcsncmp         //�Ƚ��ַ���*
    #define STRNICMP        wcsnicmp        //�Ƚ��ַ���*
    #define _STRNICMP       _wcsnicmp       //�Ƚ��ַ���*
    #define STRCOLL         wcscoll         //�Ƚ��ַ���*
    #define _STRICOLL       _wcsicoll       //�Ƚ��ַ���*
    #define _STRNCOLL       _wcsncoll       //�Ƚ��ַ���*
    #define _STRNICOLL      _wcsnicoll      //�Ƚ��ַ���*
    #define _STRCOLL_L      _wcscoll_l      //�Ƚ��ַ���*
    #define _STRICOLL_L     _wcsicoll_l     //�Ƚ��ַ���*
    #define _STRNCOLL_L     _wcsncoll_l     //�Ƚ��ַ���*
    #define _STRNICOLL_L    _wcsnicoll_l    //�Ƚ��ַ���*
    #define STRLEN          wcslen          //��ȡ�ַ�������
    #define STRCHR          wcschr          //���ַ����в����ַ�
    #define STRSTR          wcsstr          //���ַ����в������ַ���
    #define STRCSPN         wcscspn         //���ַ����в������ַ���
    #define STRPBRK         wcspbrk         //���ַ����в����ַ����е��ַ�
    #define STRSPN          wcsspn          //���ַ����в��ҵ�һ�����ַ���
    #define STRRCHR         wcsrchr         //���ַ����в��������ֵ��ַ�
    #define STRTOK          wcstok          //���ַ����в�����һ��token
    #define STRLWR          wcslwr          //ת��ΪСд
    #define _STRLWR         _wcslwr         //ת��ΪСд
    #define _STRICMP        _wcsicmp        //����Сд�ַ����Ƚ�
    #define _STRICMP_L      _wcsicmp_l      //����Сд�ַ����Ƚ�
    #define STRUPR          wcsupr          //ת��Ϊ��д 
    #define _STRUPR         _wcsupr         //ת��Ϊ��д
    #define STRNSET         wcsnset         //��ʼ���ַ���Ϊָ����ʽ
    #define _STRNSET        _wcsnset        //��ʼ���ַ���Ϊָ����ʽ
    #define STRREV          wcsrev          //�ߵ��ַ������ַ�
    #define _STRREV         _wcsrev         //�ߵ��ַ������ַ�
    #define STRXFRM         wcsxfrm         //����ָ����Ϣת���ַ���
    #define _STRXFRM_L      _wcsxfrm_l      //����ָ����Ϣת���ַ���
    #define STRERROR        _wcserror       //��ȡϵͳ������Ϣ
    #define _STRERROR       __wcserror      //��ȡϵͳ������Ϣ
#else   //UNICODE
    #define STRSET          strset          //�����ַ����е��ַ�Ϊָ���ַ�
    #define _STRSET         _strset         //�����ַ����е��ַ�Ϊָ���ַ�
    #define STRCPY          strcpy          //�����ַ���
    #define STRNCPY         strncpy         //�����ַ���
    #define STRDUP          strdup          //�����ַ���
    #define _STRDUP         _strdup         //�����ַ���
    #define STRCAT          strcat          //����ַ���
    #define STRNCAT         strncat         //����ַ���
    #define STRCMP          strcmp          //�Ƚ��ַ���
    #define STRICMP         stricmp         //�Ƚ��ַ���*
    #define STRNCMP         strncmp         //�Ƚ��ַ���*
    #define STRNICMP        strnicmp        //�Ƚ��ַ���*
    #define _STRNICMP       _strnicmp       //�Ƚ��ַ���*
    #define STRCOLL         strcoll         //�Ƚ��ַ���*
    #define _STRICOLL       _stricoll       //�Ƚ��ַ���*
    #define _STRNCOLL       _strncoll       //�Ƚ��ַ���*
    #define _STRNICOLL      _strnicoll      //�Ƚ��ַ���*
    #define _STRCOLL_L      _strcoll_l      //�Ƚ��ַ���*
    #define _STRICOLL_L     _stricoll_l     //�Ƚ��ַ���*
    #define _STRNCOLL_L     _strncoll_l     //�Ƚ��ַ���*
    #define _STRNICOLL_L    _strnicoll_l    //�Ƚ��ַ���*
    #define STRLEN          strlen          //��ȡ�ַ�������
    #define STRCHR          strchr          //���ַ����в����ַ�
    #define STRSTR          strstr          //���ַ����в������ַ���
    #define STRCSPN         strcspn         //���ַ����в������ַ���
    #define STRPBRK         strpbrk         //���ַ����в����ַ����е��ַ�
    #define STRSPN          strspn          //���ַ����в��ҵ�һ�����ַ���
    #define STRRCHR         strrchr         //���ַ����в��������ֵ��ַ�
    #define STRTOK          strtok          //���ַ����в�����һ��token
    #define STRLWR          strlwr          //ת��ΪСд
    #define _STRLWR         _strlwr         //ת��ΪСд
    #define _STRICMP        _stricmp        //����Сд�ַ����Ƚ�
    #define _STRICMP_L      _stricmp_l      //����Сд�ַ����Ƚ�
    #define STRUPR          strupr          //ת��Ϊ��д
    #define _STRUPR         _strupr         //ת��Ϊ��д
    #define STRNSET         strnset         //��ʼ���ַ���Ϊָ����ʽ
    #define _STRNSET        _strnset        //��ʼ���ַ���Ϊָ����ʽ
    #define STRREV          strrev          //�ߵ��ַ������ַ�
    #define _STRREV         _strrev         //�ߵ��ַ������ַ�
    #define STRXFRM         strxfrm         //����ָ����Ϣת���ַ���
    #define _STRXFRM_L      _strxfrm_l      //����ָ����Ϣת���ַ���
#endif  //UNICODE

//�ļ��������壨�ò��ֿɸ�����Ҫ�����䣩
#ifdef  UNICODE
    #define FOPEN           _wfopen         //���ļ�
    #define FREOPEN         _wfreopen       //���ļ�ָ�����¸�ֵ�������ļ�
    #define _FSOPEN         _wfsopen        //�Թ���ʽ���ļ�      
    #define _FDOPEN         _wfdopen        //�Եײ�IO������ʽ���ļ� 
    #define REMOVE          _wremove        //ɾ���ļ�
    #define FGETC           fgetwc          //���ļ��ж�һ���ַ�
    #define FGETS           fgetws          //���ļ��ж��ַ���
    #define FSCANF          fwscanf         //���ļ��ж���ʽ������
    #define FPUTC           fputwc          //���ļ���дһ���ַ�
    #define FPUTS           fputws          //���ļ���д�ַ���
    #define FPRINTF         fwprintf        //���ļ���д��ʽ������
#else   //UNICODE
    #define FOPEN           fopen           //���ļ�
    #define FREOPEN         freopen         //���ļ�ָ�����¸�ֵ�������ļ�
    #define _FSOPEN         _fsopen         //�Թ���ʽ���ļ�
    #define _FDOPEN         _fdopen         //�Եײ�IO������ʽ���ļ�   
    #define REMOVE          remove          //ɾ���ļ�
    #define FGETC           fgetc           //���ļ��ж�һ���ַ�
    #define FGETS           fgets           //���ļ��ж��ַ���
    #define FSCANF          fscanf          //���ļ��ж���ʽ������
    #define FPUTC           fputc           //���ļ���дһ���ַ�
    #define FPUTS           fputs           //���ļ���д�ַ���
    #define FPRINTF         fprintf         //���ļ���д��ʽ������
#endif  //UNICODE

//�ļ����ʱ�־
#ifdef  UNICODE
    #define FOPEN_MODE_READ     L"r"    //��ֻ��ģʽ���ļ�
    #define FOPEN_MODE_WRITE    L"w"    //�������ļ����򰴸���дģʽ���ļ�
    #define FOPEN_MODE_APPEND   L"a"    //�����дģʽ���ļ�
    #define FOPEN_MODE_READ2    L"r+"   //����дģʽ���ļ�
    #define FOPEN_MODE_WRITE2   L"w+"   //�������ļ����򰴶�ģʽ�Ͱ�����дģʽ���ļ�
    #define FOPEN_MODE_APPEND2  L"a+"   //�������ļ����򰴶�ģʽ�����дģʽ���ļ�
    #define FOPEN_MODE_TEXT     L"t"    //���ı���ʽ���ļ�
    #define FOPEN_MODE_BINARY   L"b"    //�Զ����Ʒ�ʽ���ļ�
    #define FOPEN_MODE_COMMIT   L"c"    //
    #define FOPEN_MODE_NOCOMMIT L"n"    //
    #define FOPEN_MODE_S        L"S"    //
    #define FOPEN_MODE_R        L"R"    //
    #define FOPEN_MODE_T        L"T"    //
    #define FOPEN_MODE_D        L"D"    //
#else   //UNICODE
    #define FOPEN_MODE_READ     "r"     //��ֻ��ģʽ���ļ�
    #define FOPEN_MODE_WRITE    "w"     //�������ļ����򰴸���дģʽ���ļ�
    #define FOPEN_MODE_APPEND   "a"     //�����дģʽ���ļ�
    #define FOPEN_MODE_READ2    "r+"    //����дģʽ���ļ�
    #define FOPEN_MODE_WRITE2   "w+"    //�������ļ����򰴶�ģʽ�Ͱ�����дģʽ���ļ�
    #define FOPEN_MODE_APPEND2  "a+"    //�������ļ����򰴶�ģʽ�����дģʽ���ļ�
    #define FOPEN_MODE_TEXT     "t"     //���ı���ʽ���ļ�
    #define FOPEN_MODE_BINARY   "b"     //�Զ����Ʒ�ʽ���ļ�
    #define FOPEN_MODE_COMMIT   "c"     //
    #define FOPEN_MODE_NOCOMMIT "n"     //
    #define FOPEN_MODE_S        "S"     //
    #define FOPEN_MODE_R        "R"     //
    #define FOPEN_MODE_T        "T"     //
    #define FOPEN_MODE_D        "D"     //
#endif  //UNICODE

//------------------------------------------------------------------------------
//���������Ǹ�����ʵ����Ψһ��ʶ��
#ifndef SR_HANDLE
#define SR_HANDLE unsigned int
#endif //SR_HANDLE

//��̬���Ӻ궨��
#ifdef SR_EXPORTS
#define SR_API extern "C" __declspec(dllexport)
#else
#define SR_API extern "C" __declspec(dllimport)
#endif

//UUID�ַ�������
#ifndef SR_UUID_BYTES
#define SR_UUID_BYTES    32
#endif //SR_UUID_BYTES

#ifndef SR_UUID_CHAR_LEN
#define SR_UUID_CHAR_LEN    (SR_UUID_BYTES + 1)
#endif //SR_UUID_CHAR_LEN

//�ַ���
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

//UUID�ַ���
#ifndef _SR_UUID_STR_
#define _SR_UUID_STR_
typedef SR_CHAR SR_UUID_STR[SR_UUID_CHAR_LEN];
#endif //_SR_UUID_STR_


//------------------------------------------------------------------------------
//�������ݣ����������ڴ��е����ַ�ʽ��

//��������
//˵����
//    1.SR_WAVBUF�Ը�����ӿڵ������ڴ����ݵ����ݽṹ���ж��塣
//    2.��ǰ��wf����ֵ��ȡĬ��ֵ����pWavBufָ������������ǲ���Ƶ��8000Hz������
//      λ16Bit��������������PCM�����������
#ifndef _SR_WAVBUF_
#define _SR_WAVBUF_
typedef struct _tag_SR_WavBuf_
{
    WAVEFORMATEX wf;         //�������ݸ�ʽ
    int          nWavBufLen; //�������ݳ���
    short*       pWavBuf;    //��������ָ��
}SR_WAVBUF, *LPSR_WAVBUF;
#endif //_SR_WAVBUF_

//------------------------------------------------------------------------------
//����Ƭ�Σ��������ض����͵��������ݷ�Χ�����ݽṹ��

//��������Ƭ��
//˵����
//    1.����Ƭ�εĲ����㷶Χ��[nStart, nEnd)��
//    2.����Ƭ������nType�������£�С�ڵ���-10��������-9���ϳ�������-8������Ա
//      ��ʾ����-7�������򺬽�ǿ������������-6����������-5��ת�Ӳ�������-4����
//      ������-3������������������-2����Ĭ��-1����Ч��������ʼֵ����0����Ч��
//      �������ڵ���0��˵������š�
//    3.����Ƭ�δ�����״̬nState�������£�0-ɾ������Դ���1-��������봦��
#ifndef _SR_SEG_
#define _SR_SEG_
typedef struct _tag_SR_Seg_
{
    __int64 nFileID;//����Ƭ�������ļ����
    int     nStart; //����Ƭ�β��������
    int     nEnd;   //����Ƭ�β������յ�
    int     nType;  //����Ƭ������
    int     nState; //����Ƭ�δ�����״̬
}SR_SEG, *LPSR_SEG;
#endif //_SR_SEG_

//------------------------------------------------------------------------------
//�����ļ�

//�ļ�����󳤶�
#ifndef SR_MAX_PATHNAME_BYTES
#define SR_MAX_PATHNAME_BYTES 255
#endif //SR_MAX_PATHNAME_BYTES

#ifndef SR_MAX_PATHNAME_LEN
#define SR_MAX_PATHNAME_LEN (SR_MAX_PATHNAME_BYTES + 1)
#endif //SR_MAX_PATHNAME_LEN

//�����ļ�
#ifndef _SR_FILE_
#define _SR_FILE_
typedef struct _tag_SR_FILE_
{
    SR_CHAR PathName[SR_MAX_PATHNAME_LEN];
}SR_FILE, *LPSR_FILE;
#endif //_SR_FILE_

//------------------------------------------------------------------------------
//������Ϣ

//������Ϣ��󳤶�
#ifndef SR_MAX_ERROR_CHAR_BYTES
#define SR_MAX_ERROR_CHAR_BYTES 255
#endif //SR_MAX_ERROR_CHAR_BYTES

#ifndef SR_MAX_ERROR_CHAR_LEN
#define SR_MAX_ERROR_CHAR_LEN (SR_MAX_ERROR_CHAR_BYTES + 1)
#endif //SR_MAX_ERROR_CHAR_LEN

//������Ϣ
#ifndef _SR_ERROR_
#define _SR_ERROR_
typedef struct _tag_SR_Error_
{
    int nError;
    SR_CHAR chError[SR_MAX_ERROR_CHAR_LEN];
}SR_ERROR, *LPSR_ERROR;
#endif //_SR_ERROR_

////////////////////////////////////////////////////////////////////////////////
//�����ļ����ʽӿ�
////////////////////////////////////////////////////////////////////////////////
//˵����
//    1. ����׼�ļ���ʽ�������ļ�����Ҫ������
//        ����Ƶ��8000Hz������λ16Bit��������������PCM�����Windows��׼Wav�ļ���
//    2. ���Ǳ�׼�ļ���ʽ�������ļ�����Ҫ������
//        G.711��G.723��G.729��GSM 610�ȡ�

//���ƣ���ȡ��������ϢSR_WF_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_WF_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ��������ļ�SR_WF_ReadWavFile()
//���ܣ�
//    1.�������ļ������ݼ������ڴ档
//    2.���Ǳ�׼�ļ���ʽ�������ļ����򡰱�׼��ʽ�������ļ���ת����
//������
//    File   ���� ���룺�����ļ�
//    WavBuf ���� �������������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_WF_ReadWavFile(const SR_FILE& File, SR_WAVBUF& WavBuf);

//���ƣ�д�����ļ�SR_WF_WriteWavFile()
//���ܣ�
//    1.���ڴ���������ݱ��浽����׼��ʽ�������ļ����С�
//������
//    WavBuf ���� ���룺��������
//    File   ���� ����������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_WF_WriteWavFile(const SR_WAVBUF& WavBuf, const SR_FILE& File);

////////////////////////////////////////////////////////////////////////////////
//����Ƭ�η��ʽӿ�
////////////////////////////////////////////////////////////////////////////////

//���ƣ���ȡ��������ϢSR_SS_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_SS_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�������Ƭ���ļ�SR_SS_ReadSegFile()
//���ܣ�
//    1.������Ƭ���ļ������ݼ������ڴ档
//������
//    File ���� ���룺����Ƭ���ļ�
//    Seg  ���� ���������Ƭ������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_SS_ReadSegFile(const SR_FILE& File,
    CFastList<SR_SEG, SR_SEG&>& Seg);

//���ƣ�д����Ƭ���ļ�SR_SS_WriteSegFile()
//���ܣ�
//    1.���ڴ������Ƭ�����ݱ��浽����Ƭ���ļ��С�
//������
//    Seg  ���� ���룺����Ƭ������
//    File ���� ���������Ƭ���ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_SS_WriteSegFile(const CFastList<SR_SEG, SR_SEG&>& Seg,
    const SR_FILE& File);

//���ƣ���������Ƭ�κϲ���������SR_SS_MergeSegWavBuf()
//���ܣ�
//    1.���ݡ�����Ƭ�Ρ��ϲ����������ݡ���
//������
//    WavBufIn ���� ���룺������������
//    Seg      ���� ���룺��Ҫ����������Ƭ��
//    WavBufOut���� ��������������Ƭ�Ρ���Ӧ�ġ��������ݡ��ϲ���ġ��������ݡ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_SS_MergeSegWavBuf(const SR_WAVBUF& WavBufIn, 
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_WAVBUF& WavBufOut);

//���ƣ���������Ƭ��ƫ��SR_SS_CalSegOffset()
//���ܣ�
//    1.�ԡ���������������Ƭ�ξ���ֵ��AllAbsSeg����Ϊ�ο�������
//        ���ָ�����������Ƭ�����ֵ��SegOppSeg������Ӧ��
//        ���ָ�����������Ƭ�ξ���ֵ��SegAbsSeg����
//������
//    AllAbsSeg ���� ���룺��������������Ƭ�ξ���ֵ
//    SegOppSeg ���� ���룺�ָ�����������Ƭ�����ֵ
//    SegAbsSeg ���� ������ָ�����������Ƭ�ξ���ֵ
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_SS_CalSegOffset(
    const CFastList<SR_SEG, SR_SEG&>& AllAbsSeg,
    const CFastList<SR_SEG, SR_SEG&>& SegOppSeg,
    CFastList<SR_SEG, SR_SEG&>& SegAbsSeg);

////////////////////////////////////////////////////////////////////////////////
//�ļ��б���ʽӿ�
////////////////////////////////////////////////////////////////////////////////

//���ƣ���ȡ��������ϢSR_FL_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_FL_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ����б��ļ�SR_FL_ReadListFile()
//���ܣ�
//    1.���б��ļ������ݼ������ڴ档
//������
//    File     ���� ���룺�б��ļ�
//    FileList ���� �����ָ���ļ��б��ָ��
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_FL_ReadListFile(
    const SR_FILE& File, CFastList<SR_FILE, SR_FILE&>& FileList);

//���ƣ�д�б��ļ�SR_FL_WriteListFile()
//���ܣ�
//    1.���ڴ���ļ��б��浽�б��ļ��С�
//������
//    FileList ���� ���룺ָ���ļ��б��ָ��
//    File     ���� ������б��ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_FL_WriteListFile(
    const CFastList<SR_FILE, SR_FILE&>& FileList, const SR_FILE& File);

////////////////////////////////////////////////////////////////////////////////////////////////////
//ʶ��ӿ�
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//����Ԥ����ӿ�
////////////////////////////////////////////////////////////////////////////////

//�����������ַ�����󳤶�
#ifndef SR_MAX_PHONE_NUMBER_BYTES
#define SR_MAX_PHONE_NUMBER_BYTES     20
#endif //SR_MAX_PHONE_NUMBER_BYTES

#ifndef SR_MAX_PHONE_NUMBER_LEN
#define SR_MAX_PHONE_NUMBER_LEN     (SR_MAX_PHONE_NUMBER_BYTES + 1)
#endif //SR_MAX_PHONE_NUMBER_LEN

//�����������ַ���
#ifndef _SR_PHONE_NUMBER_
#define _SR_PHONE_NUMBER_
typedef SR_CHAR SR_PHONE_NUMBER[SR_MAX_PHONE_NUMBER_LEN];
#endif //_SR_PHONE_NUMBER_

//���ƣ���ʼ������SR_PTR_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_PTR_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_PTR_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_PTR_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_PTR_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_PTR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�Ԥ����SR_PTR_VAD_...()
//���ܣ�
//    1.��Ч������⡣
//������
//    handle  ���� ���룺������
//    WavBuf  ���� ���룺��������
//    WavFile ���� ���룺�����ļ�
//    Seg     ���� ���������Ƭ��(Ԥ������)
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_PTR_VAD_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    CFastList<SR_SEG, SR_SEG&>& Seg);

SR_API bool SR_PTR_VAD_File(SR_HANDLE handle, const SR_FILE& WavFile,
    CFastList<SR_SEG, SR_SEG&>& Seg);

//���ƣ��������ʶ��SR_PTR_RingTimes_...()
//���ܣ�
//    1.�������ʶ��
//������
//    handle     ���� ���룺������
//    WavBuf     ���� ���룺��������
//    WavFile    ���� ���룺�����ļ�
//    Seg        ���� ���룺����Ƭ��(Ԥ������)
//    nRingTimes ���� ������������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_PTR_RingTimes_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, int& nRingTimes);

SR_API bool SR_PTR_RingTimes_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, int& nRingTimes);

//���ƣ�����������ʶ��SR_PTR_PhoneNum_...()
//���ܣ�
//    1.����������ʶ��
//������
//    handle      ���� ���룺������
//    WavBuf      ���� ���룺��������
//    WavFile     ���� ���룺�����ļ�
//    Seg         ���� ���룺����Ƭ��(Ԥ������)
//    PhoneNumber ���� ����������������ַ���
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_PTR_PhoneNum_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_PHONE_NUMBER& PhoneNumber);

SR_API bool SR_PTR_PhoneNum_File(SR_HANDLE handle, SR_FILE WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_PHONE_NUMBER& PhoneNumber);

////////////////////////////////////////////////////////////////////////////////
//˵���˷������ӿ�
////////////////////////////////////////////////////////////////////////////////

//���ƣ���ʼ������SR_SSC_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    pDir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_SSC_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_SSC_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_SSC_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_SSC_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_SSC_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�˵���˷���SR_SID_Seg_...()
//���ܣ�
//    1.˵���˷��롣
//������
//    handle  ���� ���룺������
//    WavBuf  ���� ���룺��������
//    WavFile ���� ���룺�����ļ�
//    nType   ���� ���룺����ģʽ
//    SegIn   ���� ���룺����Ƭ��(Ԥ������)
//    SegOut  ���� ���������Ƭ��(˵���˷�����)
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.����ģʽnType��ȡֵ��Χ��
//      -1 - �绰���������з��룻
//      -2 - ��ȷ��˵������Ŀ�Ķ�̬���룻
//      >0 - ָ����˵������Ŀ��
SR_API bool SR_SSC_Seg_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

SR_API bool SR_SSC_Seg_File(SR_HANDLE handle, const SR_FILE& WavFile, int nType,
    const CFastList<SR_SEG, SR_SEG&>& SegIn, CFastList<SR_SEG, SR_SEG&>& SegOut);

//���ƣ�˵���˾���SR_SID_Clst_...()
//���ܣ�
//    1.˵���˾��ࡣ
//������
//    handle    ���� ���룺������
//    WavBuf    ���� ���룺������������
//    WavFile   ���� ���룺���������ļ�
//    nWavNum   ���� ���룺�������ݵĶ����������ļ��ĸ���
//    pWavBufs  ���� ���룺���ɶ���������
//    pWavFiles ���� ���룺���ɸ������ļ�
//    nType     ���� ���룺����ģʽ
//    SegIn     ���� ���룺����Ƭ��(˵���˷�����)
//    SegOut    ���� ���������Ƭ��(˵���˾�����)
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.����ģʽnType��ȡֵ��Χ��
//      -1 - �绰���������о��ࣻ
//      -2 - ��ȷ��˵������Ŀ�Ķ�̬���ࣻ
//      -3 - �Զ������������������ڲ����绰���������о��࣬��������֮��
//           ����ȷ��˵������Ŀ�Ķ�̬���ࣻ
//      >0 - ָ����˵������Ŀ����
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
//����ѵ��������ʶ���ö���
////////////////////////////////////////////////////////////////////////////////

//����ģ�������Ŀ
#ifndef SR_MAX_LIDM_NUM
#define SR_MAX_LIDM_NUM     1000
#endif //SR_MAX_LIDM_NUM

//����ģ����������ֽ���
#ifndef SR_LIDM_NAME_BYTES
#define SR_LIDM_NAME_BYTES    40
#endif //SR_LIDM_NAME_BYTES

#ifndef SR_LIDM_NAME_LEN
#define SR_LIDM_NAME_LEN    (SR_LIDM_NAME_BYTES + 1)
#endif //SR_LIDM_NAME_LEN

//����ģ�������ַ���
#ifndef _SR_LIDM_NAME_STR_
#define _SR_LIDM_NAME_STR_
typedef SR_CHAR SR_LIDM_NAME_STR[SR_LIDM_NAME_LEN];
#endif //_SR_LIDM_NAME_STR_

////////////////////////////////////////////////////////////////////////////////
//����ѵ���ӿ�
////////////////////////////////////////////////////////////////////////////////

//�������ֵ�ѵ������
//˵����
//    1.chLidFile��ʽΪ"SR_LTRPARAMS.chOutputPath\chUUID_chName.lidm"
#ifndef _SR_LTRPARAM_
#define _SR_LTRPARAM_
typedef struct _tag_SR_LTRParam_
{
    SR_UUID_STR chUUID; //����UUID
    SR_LIDM_NAME_STR chName;    //��������
    SR_FILE ListFile;   //�������������������������б��ļ�����
    CFastList<SR_FILE, SR_FILE&> WavLidfFileList;
                        //���������ļ��б� �� �������������ļ��б�
    SR_FILE chLidFile;  //����ģ���ļ�
}SR_LTRPARAM, *LPSR_LTRPARAM;
#endif    //_SR_LTRPARAM_

//������ֵ�ѵ������
//˵����
//    1.nInputTypeȡֵ˵����1��ʾ����Ϊ�����ļ���2��ʾ����Ϊ�����ļ�(*.ltrf)
//    2.nLtrNum <= SR_MAX_LIDM_NUM
#ifndef _SR_LTRPARAMS_
#define _SR_LTRPARAMS_
typedef struct _tag_SR_LTRParams_
{
    int     nInputType;     //��������
    int     nThreadNum;     //����ѵ�����߳���Ŀ
    SR_FILE OutputPath;     //����ʶ��ģ�����Ŀ¼
    int     nLtrNum;        //������Ŀ
    LPSR_LTRPARAM LTRParams[SR_MAX_LIDM_NUM]; //�������ֵ�ѵ������
}SR_LTRPARAMS, *LPSR_LTRPARAMS;
#endif //_SR_LTRPARAMS_

//���ƣ���ʼ������SR_LTR_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_LTR_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_LTR_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_LTR_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_LTR_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_LTR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�д����ѵ������SR_LTR_WriteParams()
//���ܣ�
//    1.д����ѵ��������
//������
//    LTRParams ���� ���룺����ѵ������
//    LTRFile   ���� ���룺����ѵ�������ļ�����
//              ���� ���������ѵ�������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_LTR_WriteParams(const SR_LTRPARAMS& LTRParams, 
    const SR_FILE& LTRFile);

//���ƣ�������ѵ������SR_LTR_ReadParams()
//���ܣ�
//    1.������ѵ��������
//������
//    LTRFile   ���� ���룺����ѵ�������ļ�
//    LTRParams ���� ���������ѵ������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_LTR_ReadParams(const SR_FILE& LTRFile, SR_LTRPARAMS& LTRParams);

//���ƣ�����ѵ��������ȡSR_LTR_GetFea_...()
//���ܣ�
//    1.����ѵ��������ȡ��
//������
//    handle   ���� ���룺������
//    WavBuf   ���� ���룺��������
//    WavFile  ���� ���룺�����ļ�
//    LtrfFile ���� ���룺�����ļ�����
//             ���� ����������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_LTR_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const SR_FILE& LtrfFile);

SR_API bool SR_LTR_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const SR_FILE& LtrfFile);

//���ƣ�����ģ��ѵ��SR_LTR()
//���ܣ�
//    1.����ģ��ѵ����
//������
//    handle    ���� ���룺������
//    LTRParams ���� ���룺����ѵ������
//    LTRParams.LTRParams[x].chLidFile ���� ���������ģ���ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_LTR(SR_HANDLE handle, SR_LTRPARAMS& LTRParams);

////////////////////////////////////////////////////////////////////////////////
//����ʶ��ӿ�
////////////////////////////////////////////////////////////////////////////////

//��������ʶ����
//˵����
//    1.nLIDScore = INT(ʵ�ʵ÷֡�10000 + 0.9999)
//      ����INT()��ȡ�����������ǽ�nLIDScore��Ϊint��������
#ifndef _SR_LID_Rst_
#define _SR_LID_Rst_
typedef struct _tag_SR_LID_Rst_
{
    SR_UUID_STR chUUID;     //����UUID
    SR_LIDM_NAME_STR chName;//��������
    int nLIDScore;          //���Ŷȵ÷�
}SR_LIDRST, *LPSR_LIDRST;
#endif //_SR_LID_Rst_

//�������ʶ����
//˵����
//    1.nRstNum <= SR_MAX_LIDM_NUM
#ifndef _SR_LID_Rsts_
#define _SR_LID_Rsts_
typedef struct _tag_SR_LID_Rsts_
{
    int nRstNum;                      //����ʶ������Ŀ
    SR_LIDRST LIDRst[SR_MAX_LIDM_NUM];   //������ʶ����
}SR_LIDRSTS, *LPSR_LIDRSTS;
#endif //_SR_LID_Rsts_

//���ƣ���ʼ������SR_LID_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_LID_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_LID_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_LID_GetLastError()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�����ʶ��SR_LID_...()
//���ܣ�
//    1.����ʶ��
//������
//    handle  ���� ���룺������
//    WavBuf  ���� ���룺��������
//    WavFile ���� ���룺�����ļ�
//    Seg     ���� ���룺����Ƭ��(Ԥ������)
//    LidRsts ���� �����������ʶ����
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);

SR_API bool SR_LID_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts);

////////////////////////////////////////////////////////////////////////////////
//����ѵ���Ϳ���ʶ���ö���
////////////////////////////////////////////////////////////////////////////////

//����ģ�������Ŀ
#ifndef SR_MAX_AIDM_NUM
#define SR_MAX_AIDM_NUM     1000
#endif //SR_MAX_AIDM_NUM

//����ģ����������ֽ���
#ifndef SR_AIDM_NAME_BYTES
#define SR_AIDM_NAME_BYTES    40
#endif //SR_AIDM_NAME_BYTES

#ifndef SR_AIDM_NAME_LEN
#define SR_AIDM_NAME_LEN    (SR_AIDM_NAME_BYTES + 1)
#endif //SR_AIDM_NAME_LEN

//����ģ�������ַ���
#ifndef _SR_AIDM_NAME_STR_
#define _SR_AIDM_NAME_STR_
typedef SR_CHAR SR_AIDM_NAME_STR[SR_LIDM_NAME_LEN];
#endif //_SR_AIDM_NAME_STR_

////////////////////////////////////////////////////////////////////////////////
//����ѵ���ӿ�
////////////////////////////////////////////////////////////////////////////////

//����������ѵ������
//˵����
//    1.chAidFile��ʽΪ"SR_ATRPARAMS.chOutputPath\chUUID_chName.aidm"
#ifndef _SR_ATRPARAM_
#define _SR_ATRPARAM_
typedef struct _tagSR_ATRParam_
{
    SR_UUID_STR chUUID;  //����UUID
    SR_AIDM_NAME_STR chName;  //��������
    SR_FILE ListFile;   //������������������������б��ļ�����
    CFastList<SR_FILE, SR_FILE&> WavAidfFileList;
                        //���������ļ��б� �� �������������ļ��б�
    SR_FILE chAidFile;  //����ģ���ļ�
}SR_ATRPARAM, *LPSR_ATRPARAM;
#endif    //_SR_ATRPARAM_

//���������ѵ������
//˵����
//    1.nInputTypeȡֵ˵����1��ʾ����Ϊ�����ļ���2��ʾ����Ϊ�����ļ�(*.atrf)��
//    2.nAtrNum <= SR_MAX_AIDM_NUM��
#ifndef _SR_ATRPARAMS_
#define _SR_ATRPARAMS_
typedef struct _tag_SR_ATRParams_
{
    int     nInputType; //��������
    int     nThreadNum; //����ѵ�����߳���Ŀ
    SR_FILE OutputPath; //����ʶ��ģ�����Ŀ¼
    int     nAtrNum;    //������Ŀ
    LPSR_ATRPARAM ATRParams[SR_MAX_AIDM_NUM]; //����������ѵ������
}SR_ATRPARAMS, *LPSR_ATRPARAMS;
#endif //_SR_ATRPARAMS_

//���ƣ���ʼ������SR_ATR_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_ATR_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_ATR_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_ATR_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_ATR_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_ATR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�д����ѵ������SR_ATR_WriteParams()
//���ܣ�
//    1.д����ѵ��������
//������
//    ATRParams ���� ���룺����ѵ������
//    ATRFile   ���� ���룺����ѵ�������ļ�����
//              ���� ���������ѵ�������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_ATR_WriteParams(const SR_ATRPARAMS& ATRParams,
    const SR_FILE& ATRFile);

//���ƣ�������ѵ������SR_ATR_ReadParams()
//���ܣ�
//    1.������ѵ��������
//������
//    ATRFile   ���� ���룺����ѵ�������ļ�
//    ATRParams ���� ���������ѵ������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_ATR_ReadParams(const SR_FILE& ATRFile, SR_ATRPARAMS& ATRParams);

//���ƣ�����ѵ��������ȡSR_ATR_GetFea_...()
//���ܣ�
//    1.����ѵ��������ȡ��
//������
//    handle   ���� ���룺������
//    WavBuf   ���� ���룺��������
//    WavFile  ���� ���룺�����ļ�
//    AtrfFile ���� ���룺�����ļ�����
//             ���� ����������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_ATR_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const SR_FILE& AtrfFile);

SR_API bool SR_ATR_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
    const SR_FILE& AtrfFile);

//���ƣ�����ģ��ѵ��SR_ATR()
//���ܣ�
//    1.����ģ��ѵ����
//������
//    handle    ���� ���룺������
//    ATRParams ���� ���룺����ѵ������
//    ATRParams.ATRParams[x].chAidFile ���� ���������ģ���ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_ATR(SR_HANDLE handle, SR_ATRPARAMS& ATRParams);

////////////////////////////////////////////////////////////////////////////////
//����ʶ��ӿ�
////////////////////////////////////////////////////////////////////////////////

//��������ʶ����
//˵����
//    1.nAIDScore = INT(ʵ�ʵ÷֡�10000 + 0.9999)
//      ����INT()��ȡ�����������ǽ�nAIDScore��Ϊint��������
#ifndef _SR_AID_Rst_
#define _SR_AID_Rst_
typedef struct _tag_SR_AID_Rst_
{
    SR_UUID_STR chUUID;     //����UUID
    SR_AIDM_NAME_STR chName;//��������
    int nAIDScore;          //���Ŷȵ÷�
}SR_AIDRST, *LPSR_AIDRST;
#endif //_SR_AID_Rst_

//�������ʶ����
//˵����
//    1.nRstNum <= SR_MAX_AIDM_NUM
#ifndef _SR_AID_Rsts_
#define _SR_AID_Rsts_
typedef struct _tag_SR_AID_Rsts_
{
    int nRstNum;                      //����ʶ������Ŀ
    SR_AIDRST AIDRst[SR_MAX_AIDM_NUM];   //������ʶ����
}SR_AIDRSTS, *LPSR_AIDRSTS;
#endif //_SR_AID_Rsts_

//���ƣ���ʼ������SR_AID_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_AID_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_AID_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_AID_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_AID_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_AID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�����ʶ��SR_AID_...()
//���ܣ�
//    1.����ʶ��
//������
//    handle  ���� ���룺������
//    WavBuf  ���� ���룺��������
//    WavFile ���� ���룺�����ļ�
//    Seg     ���� ���룺����Ƭ��(Ԥ������)
//    AidRsts ���� �����������ʶ����
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_AID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_AIDRSTS& AidRsts);

SR_API bool SR_AID_File(SR_HANDLE handle, SR_FILE WavFile,
    const CFastList<SR_SEG, SR_SEG&>& Seg, SR_AIDRSTS& AidRsts);

////////////////////////////////////////////////////////////////////////////////
//˵����ʶ��ӿ�
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//˵����ʶ��걾����ֽ���
#ifndef SR_MAX_SPECIMEN_DATA_LEN
#define SR_MAX_SPECIMEN_DATA_LEN    65536  //64KB
#endif //SR_MAX_SPECIMEN_DATA_LEN

//˵����ʶ��걾����
#ifndef _SR_SPECIMEN_DATA_
#define _SR_SPECIMEN_DATA_
typedef unsigned char SR_SPECIMEN_DATA[SR_MAX_SPECIMEN_DATA_LEN];
#endif //_SR_SPECIMEN_DATA_

//˵����ʶ��걾
#ifndef _SR_SPECIMEN_
#define _SR_SPECIMEN_
typedef __declspec(align(16)) struct _tag_SR_Specimen_
{
	SR_SPECIMEN_DATA pData; //�걾����
	int nLen;               //�걾���ݳ���
}SR_SPECIMEN, *LPSR_SPECIMEN;
#endif //_SR_SPECIMEN_

//------------------------------------------------------------------------------
//˵����ʶ����Ĭ����������ֽ���
#ifndef SR_MAX_DEFAULT_FEA_DATA_LEN
#define SR_MAX_DEFAULT_FEA_DATA_LEN		65536  //64KB
#endif //SR_MAX_DEFAULT_FEA_DATA_LEN

//˵����ʶ����Ĭ����������
#ifndef _SR_DEFAULT_FEA_DATA_
#define _SR_DEFAULT_FEA_DATA_
typedef unsigned char SR_DEFAULT_FEA_DATA[SR_MAX_DEFAULT_FEA_DATA_LEN];
#endif //_SR_DEFAULT_FEA_DATA_

//˵����ʶ����Ĭ������
#ifndef _SR_DEFAULT_FEA_
#define _SR_DEFAULT_FEA_
typedef __declspec(align(16))  struct _tag_SR_DEFAULT_Fea_
{
	SR_DEFAULT_FEA_DATA pData;		//Ĭ����������
	int nLen;                       //Ĭ���������ݳ���
}SR_DEFAULT_FEA, *LPSR_DEFAULT_FEA;
#endif //_SR_DEFAULT_FEA_

//------------------------------------------------------------------------------
//˵����ʶ���˸�����������ֽ���
#ifndef SR_MAX_ADDITIONAL_FEA_DATA_LEN
#define SR_MAX_ADDITIONAL_FEA_DATA_LEN      1024//1KB
#endif //SR_MAX_ADDITIONAL_FEA_DATA_LEN

//˵����ʶ���˸�����������
#ifndef _SR_ADDITIONAL_FEA_DATA_
#define _SR_ADDITIONAL_FEA_DATA_
typedef unsigned char SR_ADDITIONAL_FEA_DATA[SR_MAX_ADDITIONAL_FEA_DATA_LEN];
#endif //_SR_ADDITIONAL_FEA_DATA_

//˵����ʶ���˸�������
#ifndef _SR_ADDITIONAL_FEA_
#define _SR_ADDITIONAL_FEA_
typedef __declspec(align(16))  struct _tag_SR_ADDITIONAL_Fea_
{
	SR_ADDITIONAL_FEA_DATA pData;		//������������
	int nLen;               				//�����������ݳ���
}SR_ADDITIONAL_FEA, *LPSR_ADDITIONAL_FEA;
#endif //_SR_ADDITIONAL_FEA_

//˵����ѵ������ģʽ
#ifndef _SR_TRAINTYPE_
#define _SR_TRAINTYPE_
typedef enum _tag_SR_TrainType_
{
	SR_AUTOSID_MERGEDSPEECHTRAIN,          //��·����ѵ��
	SR_AUTOSID_SEPARATEDSPEECHTRAIN,       //��·����ѵ��
	SR_AUTOSID_SEPARATEDSPEECHANDSEGTRAIN  //��·������������Ϣ����ѵ��(�˹��������)
}SR_TRAINTYPE;
#endif 

//------------------------------------------------------------------------------
//���ƣ���ʼ������SR_SID_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_SID_Init(const SR_FILE& Dir);

//------------------------------------------------------------------------------
//���ƣ��ͷ�����SR_SID_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_SID_Release(SR_HANDLE handle);

//------------------------------------------------------------------------------
//���ƣ���ȡ��������ϢSR_SID_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_SID_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//------------------------------------------------------------------------------
//���ƣ�˵����������ȡSR_SID_GetFea_...()
//���ܣ�
//    1.˵����������ȡ��
//������
//    handle		     ���� ���룺������
//    WavBuf		     ���� ���룺��������
//    WavFile		     ���� ���룺�����ļ�
//    Seg			       ���� ���룺����Ƭ��(˵���˷��������)
//    DefaultFea1    ���� �����˵����1��Ĭ������GS
//    DefaultFea2    ���� �����˵����2��Ĭ������GS
//    AdditionalFea1 ���� �����˵����1�ĸ�������T
//    AdditionalFea2 ���� �����˵����2�ĸ�������T
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.���ڶ�̬����õ��Ķ��˵���������ɰ�Seg.nType��ͬ��������á�
SR_API bool SR_SID_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2);

SR_API bool SR_SID_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2,
	SR_ADDITIONAL_FEA& AdditionalFea1, SR_ADDITIONAL_FEA& AdditionalFea2);

//���ƣ�˵���������ȶԼ��Ա�ʶ��SR_SID_CompFea_...()
//���ܣ�
//    1.˵���������ȶԡ�
//������
//    handle            ���� ���룺������
//    nSpecimenNum      ���� ���룺�걾��Ŀ
//    pSpecimens        ���� ���룺����걾
//    DefaultFea1		    ���� ���룺˵����1��Ĭ������GS
//    DefaultFea2		    ���� ���룺˵����2��Ĭ������GS
//    AdditionalFea1	  ���� ���룺˵����1�ĸ�������T
//    AdditionalFea2	  ���� ���룺˵����2�ĸ�������T
//    FeaFile           ���� ���룺�����ļ�
//    nFeaDataOffset    ���� ���룺�����������ļ��е����ֽ�ƫ����
//    nFeaDataNum       ���� ���룺������Ŀ
//    pnResult          ���� �������ÿ��ģ�ͱȶԵ�ʶ�����÷�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.SR_SID_CompFea_File()���걾��FeaFile�����ļ��С���ʼλ��ΪnFeaDataOffset
//      �ġ�nFeaDataNum���������бȶԡ�nFeaDataNum = 1��2��

//˵���˸��������ȶ�
SR_API bool SR_SID_CompFea_AdditionalBuf(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	const SR_ADDITIONAL_FEA& AdditionalFea1, const SR_ADDITIONAL_FEA& AdditionalFea2, 
	int* pnResult);

//˵����Ĭ�������ȶ�
SR_API bool SR_SID_CompFea_DefaultBuf(SR_HANDLE handle,
	int nSpecimenNum, SR_SPECIMEN* pSpecimens,
	SR_DEFAULT_FEA& DefaultFea1, SR_DEFAULT_FEA& DefaultFea2, 
	int* pnResult);

//˵���˸��������ļ��ȶ�
SR_API bool SR_SID_CompFea_AdditionalFeaFile(SR_HANDLE handle, 
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile, int nFeaDataOffset, int nFeaDataNum, 
	int* pnResult);

//˵����Ĭ�������ļ��ȶ�
SR_API bool SR_SID_CompFea_DefaultFeaFile(SR_HANDLE handle, 
	int nSpecimenDataNum, SR_SPECIMEN* pSpecimens,
	const SR_FILE& FeaFile, int nFeaDataOffset, int nFeaDataNum, 
	int* pnResult);

//���ƣ�˵�����Զ�������걾ѵ��SR_SID_ModelOREdit_...()
//���ܣ�
//    1.˵���˱걾���ɻ��������Զ�����
//������
//    handle            ���� ���룺������
//    WavBufList        ���� ���룺�����б�
//    FileList          ���� ���룺�����ļ��б�
//    summed		        ���� ���룺false��ʾ���˹�����;true��ʾ�Զ�����
//    dir	              ���� ���룺�Զ���������������Ŀ¼=>��Ŀ¼��
//    pSpecimens		    ���� ������걾
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    
SR_API bool SR_SID_ModelOREdit_Bufs(SR_HANDLE handle, const CFastList<SR_WAVBUF, SR_WAVBUF&>& WavBufList, 
	const CFastList<SR_FILE, SR_FILE&>& WavBufName, SR_SPECIMEN& pSpecimens, SR_FILE& dir, SR_TRAINTYPE TrainType); 

SR_API bool SR_SID_ModelOREdit_Files(SR_HANDLE handle, const CFastList<SR_FILE, SR_FILE&>& FileList, 
	SR_SPECIMEN& pSpecimens, SR_FILE& dir, SR_TRAINTYPE TrainType);



////////////////////////////////////////////////////////////////////////////////
//�ؼ���ʶ�����������ʶ���ö���
////////////////////////////////////////////////////////////////////////////////

//�ؼ�������ֽ���
#ifndef SR_MAX_WORD_BYTES
#define SR_MAX_WORD_BYTES 255
#endif //SR_MAX_WORD_BYTES

#ifndef SR_MAX_WORD_LEN
#define SR_MAX_WORD_LEN (SR_MAX_WORD_BYTES + 1)
#endif //SR_MAX_WORD_LEN

//�ؼ����ַ���
#ifndef _SR_WORD_STR_
#define _SR_WORD_STR_
typedef SR_CHAR SR_WORD_STR[SR_MAX_WORD_LEN];
#endif //_SR_WORD_STR_

//�ؼ�����������ֽ���
#ifndef SR_MAX_PHONEME_BYTES
#define SR_MAX_PHONEME_BYTES 1023
#endif //SR_MAX_PHONEME_BYTES

#ifndef SR_MAX_PHONEME_LEN
#define SR_MAX_PHONEME_LEN (SR_MAX_PHONEME_BYTES + 1)
#endif //SR_MAX_PHONEME_LEN

//�ؼ��������ַ���
#ifndef _SR_PHONEME_STR_
#define _SR_PHONEME_STR_
typedef SR_CHAR SR_PHONEME_STR[SR_MAX_PHONEME_LEN];
#endif //_SR_PHONEME_STR_

//�ؼ����������������
#ifndef SR_MAX_WORD_WAV_BUF_NUM
#define SR_MAX_WORD_WAV_BUF_NUM 10    
#endif //SR_MAX_WORD_WAV_BUF_NUM

//�ؼ��ʼ����߼����ʽ����ֽ���
#ifndef SR_MAX_LOGIC_EXP_BYTES
#define SR_MAX_LOGIC_EXP_BYTES 2047
#endif //SR_MAX_LOGIC_EXP_BYTES

#ifndef SR_MAX_LOGIC_EXP_LEN
#define SR_MAX_LOGIC_EXP_LEN (SR_MAX_LOGIC_EXP_BYTES + 1)
#endif //SR_MAX_LOGIC_EXP_LEN

//�ؼ��ʼ����߼����ʽ�ַ���
#ifndef _SR_LOGIC_EXP_STR_
#define _SR_LOGIC_EXP_STR_
typedef SR_CHAR SR_LOGIC_EXP_STR[SR_MAX_LOGIC_EXP_LEN];
#endif //_SR_LOGIC_EXP_STR_

//�ؼ���
//˵����
//    1.�ؼ���SRWORD�����洢ϵͳ�йؼ�����Ϣ��
//    2.�ؼ���UUID�Ǹô��ڴ洢ϵͳ�йؼ��ʵ�Ψһ��š�
//    3.nInputType = 1������ô����ı�����Ĺؼ��ʣ�
//      nInputType = 2������ô�����������Ĺؼ��ʣ�
//      nInputType = 3������ô�����������Ĺؼ��ʡ�
//    4.��nInputType = 1ʱ��chWord���ǹؼ������ƣ����ǹؼ����ı���
//      ��nInputType = 2��3ʱ��chWord������ؼ������ơ�
//    5.chPhoneme�Ǳ��������ʵ�Ψһ��ʶ��
//    6.���ؼ����������ֵ�����Ϊ������ͨ��ʱ���ؼ��������ǿո�ָ��Ĵ�������
//      ����ƴ����ÿ���ֵ�ƴ�����һ��0-4�����֣���ʾ��Ӧ��������0��ʾ������
//      1-4��Ӧ�ڵ�1-4�������磺��zhong1 hua2 ren2 min2 gong4 he2 guo2����
//      ���ؼ����������ֵ�����ΪӢ��ʱ���ؼ��������ǿո�ָ���Ӣ�����ꡣ
//      ���ؼ����������ֵ�����Ϊ��������ʱ�����ж��塣
//    7.��nInputType = 3ʱ��nWavBufNum��WavBuf��Ч��
//    8.nWavBufNum <= SR_MAX_WORD_WAV_BUF_NUM��
//    9.nThreadhold1��nThreadhold2�Ǵ洢ϵͳ�б���Ĺؼ�����ֵ��
//      ȡֵ��Χ��[1,100]��
#ifndef _SR_Word_
#define _SR_Word_
typedef struct _tag_SR_Word_
{
    SR_UUID_STR      chUUID;        //�ؼ���UUID,����û�д洢guid���洢���ǹؼ��ʱ��ؿ�ID
    SR_UUID_STR      chLidUUID;     //�ؼ����������ֵ�UUID
    SR_LIDM_NAME_STR chLidName;     //�ؼ����������ֵ�����
    int              nInputType;    //�ؼ�����������
    SR_WORD_STR      chWord;        //�ؼ����ı������ƣ�
    SR_PHONEME_STR   chPhoneme;     //�ؼ������أ��ո�ָ���
    int              nWavBufNum;    //�ؼ�������������Ŀ
    SR_WAVBUF        WavBuf[SR_MAX_WORD_WAV_BUF_NUM]; //�ؼ�����������
    int              nThreadhold1;  //ʵʱ�б���ֵ
    int              nThreadhold2;  //���ڼ�����ֵ
}SR_WORD, *LPSR_WORD;
#endif //_SR_Word_

//����������
//˵����
//    1.����������SR_SEARCHWORD�����ڼ���ʱÿ���ؼ��ʵ���Ϣ��
//    2.chUUID�����ڻ�дʶ������
//    3.chWord�����ڻ�дʶ�����ͽ�����ʾ��
//    4.�����ʽ�������һ�µĹؼ����������бȶԣ����б������ǣ�
//      chLidUUID��ͬ��
//      chLidUUIDΪ��ʱ�������ʽ�����޶����ֵĹؼ����������бȶԡ�
//    5.chPhoneme���Ǳ��������ʵ�Ψһ��ʶ��
//    6.nThreadhold��
//      ��ʵʱ����ʱ��Ӧ��ϵͳ����nThreadhold = SR_WORD.nThreadhold1��
//      �ں��ڼ���ʱ��Ӧ��ϵͳ����nThreadhold = SR_WORD.nThreadhold2��
//    7.�������������еĲ����㷶ΧΪ[nStart,nEnd)��
#ifndef _SR_SearchWord_
#define _SR_SearchWord_
typedef struct _tag_SR_SearchWord_
{
    SR_UUID_STR    chUUID;      //������UUID
    SR_WORD_STR    chWord;      //����������
    SR_UUID_STR    chLidUUID;   //�������������ֵ�UUID
    SR_PHONEME_STR chPhoneme;   //����������
    int            nThreadhold; //��������ֵ
    int            nStart;      //�������������еķ�Χ
    int            nEnd;        //�������������еķ�Χ
}SR_SEARCHWORD, *LPSR_SEARCHWORD;
#endif //_SR_SearchWord_

//�����������
//˵����
//    1.�ؼ����������еĲ����㷶ΧΪ[nStart,nEnd)��
//    2.���Ŷȵ÷֣�ȡֵ��ΧΪ[1,100]��
#ifndef _SR_SearchRst_
#define _SR_SearchRst_
typedef struct _tag_SR_SearchRst_
{
    __int64     nFileID; //�ļ�ID
    SR_UUID_STR chUUID;  //������UUID
    SR_WORD_STR chWord;  //����������
    int         nStart;  //�ؼ����������еķ�Χ
    int         nEnd;    //�ؼ����������еķ�Χ
    int         nScore;  //���Ŷȵ÷�
}SR_SEARCHRST, *LPSR_SEARCHRST;
#endif //_SR_SearchWords_

////////////////////////////////////////////////////////////////////////////////
//�ؼ���ʶ��ӿ�
////////////////////////////////////////////////////////////////////////////////

//���ƣ���ʼ������SR_KWS_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_KWS_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_KWS_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_KWS_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_KWS_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_KWS_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�����ģ��SR_KWS_LoadMod()
//���ܣ�
//    1.����ģ�͡������̼乲����ڴ��ģ�ͣ���߶������ʵ����ʼ���ٶȡ�
//������
//    handle  ���� ���룺������
//    Dir     ���� ���룺ģ������Ŀ¼
//    LidUUID ���� ���룺ģ������Ӧ�����֣�Ҳ����ģ�͵�Ψһ���
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_KWS_LoadMod(SR_HANDLE handle, const SR_FILE& Dir,
    const SR_UUID_STR& LidUUID);

//���ƣ�ѡ��ģ��SR_KWS_UseMod()
//���ܣ�
//    1.ѡ��ģ�͡�
//������
//    handle  ���� ���룺��ǰ������
//    LidUUID ���� ���룺ģ������Ӧ�����֣�Ҳ����ģ�͵�Ψһ���
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_KWS_UseMod(SR_HANDLE handle, const SR_UUID_STR& LidUUID);

//���ƣ��ͷ�ģ��SR_KWS_ReleaseMod()
//���ܣ�
//    1.�ͷ�ģ�͡�
//������
//    handle ���� ���룺������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_KWS_ReleaseMod(SR_HANDLE handle);

//���ƣ���ùؼ�������SR_KWS_GetPhoneme()
//���ܣ�
//    1.��ùؼ������ء�
//������
//    handle ���� ���룺������
//    pWord  ���� ���룺�ؼ���
//           ���� �����pWord->chPhoneme
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.��pWord->nInputType=1ʱ��
//      ����pWord->chWord�õ�pWord->chPhoneme��
//      ��pWord->nInputType=2ʱ��
//      ���pWord->chPhoneme�Ϸ��ԣ�
//      ��pWord->nInputType=3ʱ��
//      ����pWord->nWavBufNum��pWord->WavBuf�õ�pWord->chPhoneme��
SR_API bool SR_KWS_GetPhoneme(SR_HANDLE handle, SR_WORD& Word);

//���ƣ��ؼ���������ȡSR_KWS_GetFea_...()
//���ܣ�
//    1.�ؼ���������ȡ��
//������
//    handle     ���� ���룺������
//    WavBuf     ���� ���룺��������
//    WavFile    ���� ���룺�����ļ�
//    Seg        ���� ���룺����Ƭ��(Ԥ������)
//    nFeaBufLen ���� ����������ֽ���
//    pFeaBuf    ���� ���������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_KWS_GetFea_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int &nFeaBufLen, void* &pFeaBuf);

SR_API bool SR_KWS_GetFea_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int &nFeaBufLen, void* &pFeaBuf);

//���ƣ�����ؼ�������SR_KWS_WriteFea()
//���ܣ�
//    1.����ؼ���������
//������
//    handle     ���� ���룺������
//    nFileID    ���� ���룺�����ļ��ڴ洢ϵͳ�е�Ψһ���
//    nFeaBufLen ���� ���룺�����ֽ���
//    pFeaBuf    ���� ���룺����
//    FeaFile    ���� ���룺�����ļ�����
//               ���� ����������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
SR_API bool SR_KWS_WriteFea(SR_HANDLE handle, __int64 nFileID,
	int nFeaBufLen, void *pFeaBuf, const SR_FILE& FeaFile);

//���ƣ����ؼ�������SR_KWS_ReadFea()
//���ܣ�
//    1.���ؼ���������
//������
//    handle     ���� ���룺������
//    FeaFile    ���� ���룺�����ļ�����
//    nFileID    ���� ����������ļ��ڴ洢ϵͳ�е�Ψһ���
//    nFeaBufLen ���� ����������ֽ���
//    pFeaBuf    ���� ���������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
SR_API bool SR_KWS_ReadFea(SR_HANDLE handle, const SR_FILE& FeaFile,
    __int64 &nFileID, int &nFeaBufLen, void* &pFeaBuf);

//���ƣ������ؼ�������SR_KWS_AddFeaToIdx_...()
//���ܣ�
//    1.�����ؼ���������
//������
//    handle       ���� ���룺������
//    nFileID      ���� ���룺�����ļ��ڴ洢ϵͳ�е�Ψһ���
//    nFeaBufLen   ���� ���룺�����ֽ���
//    pFeaBuf      ���� ���룺����
//    FeaFile      ���� ���룺�����ļ�
//    pFeaFileList ���� ���룺��������ļ�
//    IdxFile      ���� ���룺�����ļ�����
//                 ���� ����������ļ�
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_KWS_AddFeaToIdx_Buf(SR_HANDLE handle,
    __int64 nFileID, int nFeaBufLen, void *pFeaBuf, const SR_FILE& IdxFile);

SR_API bool SR_KWS_AddFeaToIdx_File(SR_HANDLE handle,
    const SR_FILE& FeaFile, const SR_FILE& IdxFile);

SR_API bool SR_KWS_AddFeaToIdx_Files(SR_HANDLE handle,
	const CFastList<SR_FILE, SR_FILE&>& FeaFileList, const SR_FILE& IdxFile);

//���ƣ��ؼ��ʼ���SR_KWS_Search_...()
//���ܣ�
//    1.�ؼ��ʼ�����
//������
//    handle         ���� ���룺������
//    nSearchType    ���� ���룺����ģʽ
//    SearchWordList ���� ���룺���м�����
//    LogicExp       ���� ���룺�����߼����ʽ
//    FeaBufLen      ���� ���룺�����ֽ���
//    pFeaBuf        ���� ���룺����
//    FeaFileList    ���� ���룺��������ļ�
//    IdxFileList    ���� ���룺��������ļ�
//    SearchRstList  ���� ������������
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.����ģʽnSearchType��ȡֵ���������£�
//      1-���󱨡���ȷ�ȶԼ���ģʽ��
//      2-���󱨡�ģ���ȶԼ���ģʽ��
//      3-��©������ȷ�ȶԼ���ģʽ��
//      4-��©����ģ���ȶԼ���ģʽ��
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
//��������ʶ��ӿ�
////////////////////////////////////////////////////////////////////////////////

/////////////// ѵ������

//ѵ���ض���ģ��
//˵����
//    1.�ؼ���SRWORD�����洢ϵͳ�йؼ�����Ϣ��
#ifndef _SR_Utterance_
#define _SR_Utterance_
typedef struct _tag_SR_Utterance_
{
	SR_WORD_STR      Sentence;        //��ע�ı�
	SR_WAVBUF        WavBuf; //��������
}SR_UTTERANCE, *LPSR_UTTERANCE;
#endif //_SR_Utterance_

//���ƣ��ض���ģ��ѵ��SR_CSR_Train()
//���ܣ�
//    1.����ģ�͡������̼乲����ڴ��ģ�ͣ���߶������ʵ����ʼ���ٶȡ�
//������
//    Dir            ���� ���룺ģ������Ŀ¼
//    Utterances     ���� ���룺ѵ�������ͱ�ע�б�
//    Model          ���� �����ģ���ļ�
//    Error          ���� �����������Ϣ������������falseʱ��
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_CSR_Train(const SR_FILE& Dir,
	CFastList<SR_UTTERANCE, SR_UTTERANCE&> Utterances,
	const SR_FILE& Model,
	SR_ERROR& Error
	);

////////////////////////////////////////////////////////////////////////////////

//�ֻ򵥴ʵ�����ֽ���
#ifndef SR_CSR_MAX_WORD_BYTES
#define SR_CSR_MAX_WORD_BYTES   255
#endif //SR_CSR_MAX_WORD_BYTES

#ifndef SR_CSR_MAX_WORD_LEN
#define SR_CSR_MAX_WORD_LEN   (SR_CSR_MAX_WORD_BYTES + 1)
#endif //SR_CSR_MAX_WORD_LEN

//�ֻ򵥴��ַ���
#ifndef _SR_CSR_WORD_STR_
#define _SR_CSR_WORD_STR_
typedef SR_CHAR SR_CSR_WORD_STR[SR_CSR_MAX_WORD_LEN];
#endif //_SR_CSR_WORD_STR_

//�ֻ򵥴ʵ���������ʶ����
//˵����
//    1.���Ŷȵ÷�nScore��ȡֵ��Χ��[1,100]��
#ifndef _SR_CSR_WordRst_
#define _SR_CSR_WordRst_
typedef struct _tag_SR_CSR_WordRst_
{
	SR_CSR_WORD_STR chWord; //�ֻ򵥴�
	int nScore;             //���Ŷȵ÷�
}SR_CSR_WORD_RST, *LPSR_CSR_WORD_RST;
#endif //_SR_CSR_WordRst_

//���ӵ���������ʶ����
//˵����
//    1.�����������еĲ����㷶ΧΪ[nStart,nEnd)��
#ifndef _SR_CSR_SentenceRst_
#define _SR_CSR_SentenceRst_
typedef struct _tag_SR_CSR_SentenceRst_
{
	int nStart;			//�����������еķ�Χ
	int nEnd; 			//�����������еķ�Χ
	CFastList<SR_CSR_WORD_RST, SR_CSR_WORD_RST&> Sentence; //���ӵ�ʶ����
}SR_CSR_SENTENCE_RST, *LPSR_SR_CSR_SENTENCE_RST;
#endif //_SR_CSR_SentenceRst_

//���ƣ���ʼ������SR_CSR_Init()
//���ܣ�
//    1.��ʼ�����档
//������
//    Dir ���� ���룺���漰�������ڵ�Ŀ¼
//����ֵ��
//    �ɹ����������������򷵻�NULL��
SR_API SR_HANDLE SR_CSR_Init(const SR_FILE& Dir);

//���ƣ��ͷ�����SR_CSR_Release()
//���ܣ�
//    1.�ͷ����档
//������
//    handle ���� ���룺������
SR_API void SR_CSR_Release(SR_HANDLE handle);

//���ƣ���ȡ��������ϢSR_CSR_GetLastError()
//���ܣ�
//    1.��ȡ��������Ϣ��
//������
//    handle ���� ���룺������
//    Error  ���� �������������Ϣ
SR_API void SR_CSR_GetLastError(SR_HANDLE handle, SR_ERROR& Error);

//���ƣ�����ģ��SR_CSR_LoadMod()
//���ܣ�
//    1.�����ض���ģ��
//������
//    handle  ���� ���룺������
//    Model   ���� ���룺ģ���ļ�
//    SpkID   ���� ���룺ģ������Ӧ���ض��ˣ�Ҳ����ģ�͵�Ψһ���
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_CSR_LoadMod(SR_HANDLE handle, const SR_FILE& Model, int SpkID);

//���ƣ��ͷ�ģ��SR_CSR_ReleaseMod()
//���ܣ�
//    1.�ͷ�ģ�͡�
//������
//    handle     ���� ���룺������
//    SpkID      ���� ���룺�ͷ��ض���ģ�͵�SpkID
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
SR_API bool SR_CSR_ReleaseMod(SR_HANDLE handle, int SpkID);

//���ƣ���������ʶ��SR_CSR_...()
//���ܣ�
//    1.��������ʶ��
//������
//    handle  ���� ���룺������
//    WavBuf  ���� ���룺��������
//    WavFile ���� ���룺�����ļ�
//    Seg     ���� ���룺����Ƭ��(Ԥ������)
//    nType   ���� ���룺ʶ�������ģʽ
//    CsrRst  ���� �������������ʶ����
//����ֵ��
//    �ɹ�����true��ʧ�ܷ���false��
//˵����
//    1.nType��ȡֵ��Χ�ǣ�0-��������Ŷȵ÷֣�1-������Ŷȵ÷֡�
//    2.SR_SEG Seg.nType: SpkID,��װ��ģ�͵�SpkID��Ӧ,
//      ȡֵ��Χ��0-δ֪˵����
SR_API bool SR_CSR_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int nType,
	CFastList<SR_CSR_SENTENCE_RST, SR_CSR_SENTENCE_RST&>& CsrRst);

SR_API bool SR_CSR_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, int nType,
	CFastList<SR_CSR_SENTENCE_RST, SR_CSR_SENTENCE_RST&>& CsrRst);
	*/
#endif //_NJ841_SR_H_