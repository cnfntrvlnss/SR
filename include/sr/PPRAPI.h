typedef HANDLE (*fun_OpenPPR)(char* szWorkDir, char* szLog);
typedef void (*fun_ClosePPR)(HANDLE hPPR);
typedef int (*fun_DoPreprocess)(HANDLE hPPR, short* pData, int nDataLen, short *pDataOut, int &nDataLenOut, char *outTimeStampFile);