#define SR_EXPORTS
#include "common/port_zsr.h"
#include "sr/FastList_Ex.h"
#include "sr/sr.h"

#include "TLI_API.h"
#include "config.h"
#include <vector>
#include <map>
#include <utility>
using std::vector;
using std::map;

#define SAMPLESPERSEC 8000

/*
ģ����ز�����
֧�֣��ڽ��������ڼ䣬���Ը���ģ�ͣ�ǰ����֮ǰ�򿪵�ģ��Ҫ�رա�
*/
struct LIDEngineCfg{
	LIDEngineCfg():
	uTemplateNum(0), arrResLangs(NULL), allTemplateIDs(NULL), allTemplateLocations(NULL)
	{}
	~LIDEngineCfg(){
		clear();
	}
	void clear(){
		if (arrResLangs != NULL){
			free(arrResLangs);
			arrResLangs = NULL;
		}
		if (allTemplateIDs != NULL){
			free(allTemplateIDs);
			allTemplateIDs = NULL;
		}
		if (allTemplateLocations != NULL){
			for (int i = 0; i < uTemplateNum; i++){
				free(allTemplateLocations[i]);
			}
			free(allTemplateLocations);
			allTemplateLocations = NULL;
		}
		uTemplateNum = 0;
		nMaxSpeechSec = 0;
	}
	unsigned uTemplateNum;
	SR_LIDRST *arrResLangs; //length: uTemplateNum + 1.
	int *allTemplateIDs; // length: uTemplateNum.
	char** allTemplateLocations;

	int nMaxSpeechSec;

private:
	LIDEngineCfg(const LIDEngineCfg&);
	LIDEngineCfg& operator=(const LIDEngineCfg&);
};

struct SessionData{
	SessionData()
	{
		InitializeCriticalSection(&cs);
		err.nError = 0;
		err.chError[0] = L'\0';
	}
	~SessionData()
	{
		DeleteCriticalSection(&cs);
	}
	TLI_HANDLE hdl;
	bool isOpen;
	SR_ERROR err;
	CRITICAL_SECTION cs;
};
static LIDEngineCfg g_lid;
//static map<unsigned int, int> g_mSRHandlers;
//static unsigned g_uLidAssignedNum = 0;
const unsigned g_uSessionLimit = 32;
const unsigned g_sessArrLen = g_uSessionLimit + 1;
//����0 ������session�޹ص����ݣ�����0������Ӧsession�µ����ݡ�
SessionData g_allSess[g_sessArrLen];
unsigned g_uSessionNum = 0;
CRITICAL_SECTION g_csLid;

// ��һ�����õ�error�������Բ�����ʱ�����Կ��Ǳ���̱߳��صģ����Ƶ�handle���档
//-1301 --> -1400
static inline void setLIDError(int idx, int errNum, const wchar_t *strfmt, ...)
{
	EnterCriticalSection(&g_allSess[idx].cs);
	va_list arglist;
	va_start(arglist, strfmt);
	vswprintf(g_allSess[idx].err.chError, strfmt, arglist);
	g_allSess[idx].err.nError = errNum;
	va_end(arglist);
	LeaveCriticalSection(&g_allSess[idx].cs);
}
static inline void getLIDError(int idx, SR_ERROR& Error)
{
	EnterCriticalSection(&g_allSess[idx].cs);
	Error = g_allSess[idx].err;
	LeaveCriticalSection(&g_allSess[idx].cs);
}
class SetUpLogic{
	SetUpLogic(){
		InitializeCriticalSection(&g_csLid);
		for (int i = 1; i < g_sessArrLen; i++){
			g_allSess[i].hdl = i - 1;
			g_allSess[i].isOpen = false;
		}
	}
	~SetUpLogic(){
		DeleteCriticalSection(&g_csLid);

	}
	static SetUpLogic onlyOne;
};
SetUpLogic SetUpLogic::onlyOne;


static bool LoadLangList(const wchar_t *langListFile)//��ȫ�ֱ�������ֵ
{
	struct LangPair
	{
		char ID[50];
		char LangName[50];
	};
	FILE *fpList;
	string tmpPath = WCsToMBs(langListFile);
	if (!(fpList = fopen(tmpPath.c_str(), "rb")))
	{
		setLIDError(0, -1301, L"CfgError failed to open file %ls", langListFile);
		return false;
	}
	const unsigned MaxLineLen = 256;
	char Line[MaxLineLen];
	vector<LangPair> veclangpair;
	while (!feof(fpList))
	{
		char seps[] = " \t";
		LangPair langpair;
		if (!fgets(Line, MaxLineLen, fpList))
		{
			continue;
		}
		int len = strlen(Line) - 1;
		while (len >=0 && (Line[len] == '\r' || Line[len] == '\n'))
		{
			Line[len--] = '\0';
		}
		len = len + 1;
		if (len == 0) continue;
		char *token = strtok(Line, seps);
		strcpy(langpair.ID, token);
		token = strtok(NULL, seps);
		strcpy(langpair.LangName, token);
		if (langpair.ID == NULL || langpair.LangName == NULL){
			setLIDError(0, -1301, L"CfgError wrong format file %ls", langListFile);
			fclose(fpList);
			return false;
		}
		veclangpair.push_back(langpair);
	}
	fclose(fpList);

	g_lid.arrResLangs = static_cast<SR_LIDRST *>(malloc((veclangpair.size() + 1) * sizeof(SR_LIDRST)));
	for (int i = 0; i < veclangpair.size(); i++){
		wcsncpy(g_lid.arrResLangs[i].chName, MBsToWCs(veclangpair[i].LangName).c_str(), SR_LIDM_NAME_BYTES);
		wcsncpy(g_lid.arrResLangs[i].chUUID, MBsToWCs(veclangpair[i].ID).c_str(), SR_UUID_BYTES);
		g_lid.arrResLangs[i].nLIDScore = 1;
	}
	wcsncpy(g_lid.arrResLangs[veclangpair.size()].chName, L"reject", SR_LIDM_NAME_BYTES);
	wcsncpy(g_lid.arrResLangs[veclangpair.size()].chUUID, L"��ʶ", SR_UUID_BYTES);
	g_lid.arrResLangs[veclangpair.size()].nLIDScore = 1;

	g_lid.uTemplateNum = veclangpair.size();
	g_lid.allTemplateIDs = (int *)malloc(g_lid.uTemplateNum * sizeof(int));
	g_lid.allTemplateLocations = (char**)malloc(g_lid.uTemplateNum * sizeof(char*));
	for (int i = 0; i<g_lid.uTemplateNum; i++)
	{
		g_lid.allTemplateIDs[i] = i + 1;
		g_lid.allTemplateLocations[i] = (char*)malloc(sizeof(char)* 6);
		sprintf(g_lid.allTemplateLocations[i], "%d", i + 1);
	}

	return true;
}

static void LoadReportList(const wchar_t *reportfile)
{
	FILE *fpList;
	string tmpPath = WCsToMBs(reportfile);
	if (!(fpList = fopen(tmpPath.c_str(), "rb")))
	{
		setLIDError(0, -1301, L"CfgWarn failed to open file %ls", reportfile);
		return;
	}
	//���ɹ����ϱ������ļ�����ֻ�ϱ�������Ҫ������֡�
	for (int idx = 0; idx < g_lid.uTemplateNum + 1; idx++){
		g_lid.arrResLangs[idx].nLIDScore = 0;
	}
#define MAX_LINE 1024
	char Line[MAX_LINE];
	while (!feof(fpList))
	{
		int langID;
		char strID[100];
		char strName[100];
		if (!fgets(Line, MAX_LINE, fpList))
		{
			continue;
		}
		int len = strlen(Line) - 1;
		while (len >= 0 && (Line[len] == '\r' || Line[len] == '\n'))
		{
			Line[len--] = '\0';
		}
		len = len + 1;
		if (len == 0) continue;
		int retNum = sscanf(Line, "%d %*s %*s %s %s", &langID, strID, strName);
		if (retNum > 1){
			wcsncpy(g_lid.arrResLangs[langID].chUUID, MBsToWCs(strID).c_str(), SR_UUID_BYTES);
			g_lid.arrResLangs[langID].nLIDScore = 1;
			if (retNum > 2){
				wcsncpy(g_lid.arrResLangs[langID].chName, MBsToWCs(strName).c_str(), SR_LIDM_NAME_BYTES);
			}
		}

	}
	fclose(fpList);
}

class LocalScopeLock{
public:
	LocalScopeLock(CRITICAL_SECTION &cs):
		cs(cs)
	{
		EnterCriticalSection(&cs);
	}
	~LocalScopeLock(){
		LeaveCriticalSection(&cs);
	}
private:
	LocalScopeLock(const LocalScopeLock&);
	LocalScopeLock& operator = (const LocalScopeLock&);
	CRITICAL_SECTION &cs;
};

//=====================================SR functions====================================
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{
	getLIDError(handle, Error);
	return;
}

/**
* ����Init �� close session, ��close ����Init���ص�session; �����ŵ�����ʱ�޸�ȫ�ֱ���������,init��һ·ʱ�ĳ�ʼ������������close���һ·ʱ���ͷŹ���������������ǰsession�ĸ����ȵȡ�
*
*/
SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir)
{
	if (ACCESS(WCsToGB2312s(Dir.PathName).c_str()) != 0){
		setLIDError(0, -1301, L"ParamError ����ģ��Ŀ¼������");
		return (SR_HANDLE)0;
	}

	bool bAlloc = false;
	LocalScopeLock initLock(g_csLid);
	if (g_lid.uTemplateNum == 0){
		wstring langFile = Path_JoinPath(Dir.PathName, L"lang.list");
		if (!LoadLangList(langFile.c_str())){
			return (SR_HANDLE)0;
		}
		LoadReportList(L"lang - ����.list");
		wstring decodeFile = Path_JoinPath(Dir.PathName, L"decoder.cfg");
		string strFile = WCsToGB2312s(decodeFile.c_str());
		if (ACCESS(strFile.c_str()) != 0)
		{
			setLIDError(0, -1301, L"CfgError �Ҳ���decode.cfg %ls", decodeFile.c_str());
			g_lid.clear();
			return (SR_HANDLE)0;
		}
		Config cfg(const_cast<char*>(strFile.c_str()));
		cfg.ReadConfig("MaxSpeechSec", g_lid.nMaxSpeechSec);
		if (g_lid.nMaxSpeechSec == 0){
			g_lid.nMaxSpeechSec = 3600;
		}

		string cfgdir = WCsToGB2312s(Dir.PathName);
		int nRst = TLI_Init(const_cast<char*>(cfgdir.c_str()), g_lid.allTemplateIDs, g_lid.allTemplateLocations, g_lid.uTemplateNum, g_uSessionLimit);
		if (nRst != 0){
			switch (nRst){
			case(-1) :
				setLIDError(0, -1301, L"InitError ģ���ļ�·������");
				break;
			case(-2) :
				setLIDError(0, -1301, L"InitError ��Ȩʧ��");
				break;
			case(-3) :
				setLIDError(0, -1301, L"InitError �߳������ô���");
				break;
			case(-4) :
				setLIDError(0, -1301, L"InitError ģ���ļ�ȱʧ");
				break;
			case(-10) :
			default:
				setLIDError(0, -1301, L"InitError ��������");
				break;
			}
			g_lid.clear();
			return (SR_HANDLE)0;
		}
		bAlloc = true;
	}


	TLI_HANDLE hTLI;
	int nRst = TLI_Open(hTLI);
	if (nRst != 0){
		setLIDError(0, -1301, L"OpenError ��һ·ʧ��");
		if (bAlloc){
			g_lid.clear();
			TLI_Exit();
		}
		return (SR_HANDLE)0;
	}

	//TLI_Open���ص���[0, g_uSessLimit) �е�һ������������û�д򿪵ġ�
	int sessIdx = hTLI + 1;
	EnterCriticalSection(&g_allSess[sessIdx].cs);
	g_allSess[sessIdx].hdl = hTLI;
	assert(!g_allSess[sessIdx].isOpen);
	g_allSess[sessIdx].isOpen = true;
	LeaveCriticalSection(&g_allSess[sessIdx].cs);

	g_uSessionNum += 1;
	return sessIdx;
}

SR_API void SR_LID_Release(SR_HANDLE handle)
{
	assert(handle > 0 && handle <= g_uSessionLimit);
	LocalScopeLock initLock(g_csLid);
	bool bclose = false;
	EnterCriticalSection(&g_allSess[handle].cs);
	if (g_allSess[handle].isOpen){
		int nRst = TLI_Close(g_allSess[handle].hdl);
		if (nRst != 0){
			setLIDError(handle, -1301, L"CloseError �ر�һ·ʧ��");
		}
		else{
			g_allSess[handle].isOpen = false;
			bclose = true;
		}

	}
	LeaveCriticalSection(&g_allSess[handle].cs);

	if (bclose){
		g_uSessionNum -= 1;
		if (g_uSessionNum == 0){
			g_lid.clear();
			TLI_Exit();
		}
	}

	return;
}

SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts)
{
	assert(handle > 0 && handle <= g_uSessionLimit);

	LidRsts.nRstNum = 0;
	SR_WAVBUF realBuf;
	realBuf.nWavBufLen = 0;
	realBuf.pWavBuf = NULL;
	SR_SS_MergeSegWavBuf(WavBuf, Seg, realBuf);
	if (realBuf.nWavBufLen == 0){
		setLIDError(handle, -1301, L"ParamError no segment of wave data to recognize.");
		return false;
	}
	
	int inputSampleNum = realBuf.nWavBufLen;
	if (inputSampleNum > g_lid.nMaxSpeechSec * SAMPLESPERSEC){
		inputSampleNum = g_lid.nMaxSpeechSec * SAMPLESPERSEC;
	}

	int nRst = TLI_Recognize(g_allSess[handle].hdl, g_lid.allTemplateIDs, g_lid.uTemplateNum, static_cast<void*>(realBuf.pWavBuf), inputSampleNum * sizeof(short), -1, -1);
	free(realBuf.pWavBuf);
	if (nRst != 0){
		switch (nRst){
		case(-1) :
			setLIDError(handle, -1301, L"RecogError �������");
			break;
		case(-2) :
			setLIDError(handle, -1301, L"RecogError ���߳�û�б���ʼ��");
			break;
		case(-3) :
			setLIDError(handle, -1301, L"RecogError ���б�����ID���������");
			break;
		case(-4) :
			setLIDError(handle, -1301, L"RecogError �����ڴ����");
			break;
		case(-5) :
			setLIDError(handle, -1301, L"RecogError ��������Ƿ�");
			break;
		case(-6) :
			setLIDError(handle, -1301, L"RecogError ��������̫��");
			break;
		case(-7) :
			setLIDError(handle, -1301, L"RecogError VADʧ��");
			break;
		case(-8) :
			setLIDError(handle, -1301, L"RecogError VAD����Ч����̫��");
			break;
		case(-9) :
			setLIDError(handle, -1301, L"RecogError ���ּ��ʧ��");
			break;
		case(-10) :
			setLIDError(handle, -1301, L"RecogError ���ּ�����Ч����̫��");
			break;
		default:
			setLIDError(handle, -1301, L"RecogError ��������");
		}
		return false;
	}
	int arrLen = (g_lid.uTemplateNum + 1);
	float *arrScore = (float*)malloc(sizeof(float)* arrLen);
	if (arrScore == NULL){
		setLIDError(handle, -1301, L"MemoryError failed to malloc size: %d.", sizeof(float)* arrLen);
		return false;
	}
	if (TLI_GetResult(g_allSess[handle].hdl, arrScore, arrLen) == -1){
		setLIDError(handle, -1301, L"LogicError ��ȡ�÷�ʧ�� .");
		free(arrScore);
		return false;
	}
	float maxScore = arrScore[0];
	int maxIdx = 0;
	for (int i = 1; i < arrLen; i++){
		if (arrScore[i] > maxScore) {
			maxScore = arrScore[i];
			maxIdx = i;
		}
	}
	if (g_lid.arrResLangs[maxIdx].nLIDScore > 0){
		LidRsts.nRstNum = 1;
		LidRsts.LIDRst[0] = g_lid.arrResLangs[maxIdx];
		LidRsts.LIDRst[0].nLIDScore = int(maxScore * 10000 + 0.9999);
	}
	free(arrScore);
	return true;
}

SR_API bool SR_LID_File(SR_HANDLE handle, const SR_FILE& WavFile,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts)
{
	SR_WAVBUF wavBuf;
	if (!SR_WF_ReadWavFile(WavFile, wavBuf)){
		setLIDError(handle, -1301, L"FileError ���ļ�ʧ�� %ls.", WavFile.PathName);
		return false;
	}
	bool retb = SR_LID_Buf(handle, wavBuf, Seg, LidRsts);
	free(wavBuf.pWavBuf);
	return retb;
}