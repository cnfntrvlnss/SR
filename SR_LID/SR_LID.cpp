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
static LIDEngineCfg g_lid;
static map<unsigned int, int> g_mSRHandlers;
static unsigned g_uLidAssignedNum = 0;
const unsigned g_uConcurrencyLimit = 100;

//-1301 --> -1400
static SR_ERROR g_SR_LID_Error;

/**
若一行的结尾多出一个 + 字符，就代表上报次语种，否则，不上报。
*/
static bool LoadResLangList(const wchar_t *strLangList, unsigned &langNum, SR_LIDRST *&pLidRst)//给全局变量赋初值
{
	struct LangPair
	{
		char ID[50];
		char LangName[50];
		bool breport;
	};
	FILE *fpList;
	string tmpPath = WCsToMBs(strLangList);
	if (!(fpList = fopen(tmpPath.c_str(), "rb")))
	{
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES,  L"CfgError failed to open file %ls", strLangList);
		g_SR_LID_Error.nError = 0;
		return false;
	}
	const unsigned MaxLineLen = 256;
	char Line[MaxLineLen];
	int nLangNum = 0;
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
		if (Line[len - 1] == '+') langpair.breport = true;
		else langpair.breport = false;
		char *token = strtok(Line, seps);
		strcpy(langpair.ID, token);
		token = strtok(NULL, seps);
		strcpy(langpair.LangName, token);
		if (langpair.ID == NULL || langpair.LangName == NULL){
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"CfgError wrong format file %ls", strLangList);
			g_SR_LID_Error.nError = 0;
			fclose(fpList);
			return false;
		}
		veclangpair.push_back(langpair);
		nLangNum++;
	}
	fclose(fpList);

	langNum = nLangNum;
	pLidRst = static_cast<SR_LIDRST *>(malloc((nLangNum + 1) * sizeof(SR_LIDRST)));
	for (int i = 0; i < nLangNum; i++){
		wcsncpy(pLidRst[i].chName, UTF8sToWCs(veclangpair[i].LangName).c_str(), SR_LIDM_NAME_BYTES);
		wcsncpy(pLidRst[i].chUUID, UTF8sToWCs(veclangpair[i].ID).c_str(), SR_UUID_BYTES);
		if (veclangpair[i].breport) pLidRst[i].nLIDScore = 1;
		else pLidRst[i].nLIDScore = 0;
	}
	wcsncpy(pLidRst[nLangNum].chName, L"reject", SR_LIDM_NAME_BYTES);
	wcsncpy(pLidRst[nLangNum].chUUID, L"拒识", SR_UUID_BYTES);
	pLidRst[nLangNum].nLIDScore = 0;
	return true;
}
static inline void initCfg_templates()
{
	g_lid.allTemplateIDs = (int *)malloc(g_lid.uTemplateNum * sizeof(int));
	g_lid.allTemplateLocations = (char**)malloc(g_lid.uTemplateNum * sizeof(char*));
	for (int i = 0; i<g_lid.uTemplateNum; i++)
	{
		g_lid.allTemplateIDs[i] = i + 1;
		g_lid.allTemplateLocations[i] = (char*)malloc(sizeof(char)* 6);
		sprintf(g_lid.allTemplateLocations[i], "%d", i + 1);
	}

}

//=====================================SR functions====================================
SR_API void SR_LID_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{
	Error = g_SR_LID_Error;
	return;
}

SR_API SR_HANDLE SR_LID_Init(const SR_FILE& Dir)
{
	if (ACCESS(WCsToGB2312s(Dir.PathName).c_str()) != 0){
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"ParamError 传人模型目录不存在");
		g_SR_LID_Error.nError = -1301;
		return (SR_HANDLE)0;
	}
	if (g_lid.uTemplateNum == 0){
		//wstring resListFile = Path_JoinPath(Path_GetDir(Dir.PathName), L"lang - 副本.list");
		wstring resListFile = L"lang - 副本.list";
		if (!LoadResLangList(resListFile.c_str(),g_lid.uTemplateNum, g_lid.arrResLangs)){
			return (SR_HANDLE)0;
		}
		initCfg_templates();

		wstring decodeFile = Path_JoinPath(Dir.PathName, L"decoder.cfg");
		string strFile = WCsToGB2312s(decodeFile.c_str());
		if (ACCESS(strFile.c_str()) != 0)
		{
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"CfgError 找不到decode.cfg %ls", decodeFile.c_str());
			g_SR_LID_Error.nError = -1301;
			g_lid.clear();
			return (SR_HANDLE)0;
		}
		Config cfg(const_cast<char*>(strFile.c_str()));
		cfg.ReadConfig("MaxSpeechSec", g_lid.nMaxSpeechSec);
		if (g_lid.nMaxSpeechSec == 0){
			g_lid.nMaxSpeechSec = 3600;
		}

	}
	if (g_mSRHandlers.empty()){
		string cfgdir = WCsToGB2312s(Dir.PathName);
		int nRst = TLI_Init(const_cast<char*>(cfgdir.c_str()), g_lid.allTemplateIDs, g_lid.allTemplateLocations, g_lid.uTemplateNum, g_uConcurrencyLimit);
		if (nRst != 0){
			switch (nRst){
			case(-1) :
				swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"InitError 模型文件路径错误");
				g_SR_LID_Error.nError = -1301;
				break;
			case(-2) :
				swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"InitError 授权失败");
				g_SR_LID_Error.nError = -1301;
				break;
			case(-3) :
				swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"InitError 线程数设置错误");
				g_SR_LID_Error.nError = -1301;
				break;
			case(-4) :
				swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"InitError 模型文件缺失");
				g_SR_LID_Error.nError = -1301;
				break;
			case(-10):
			default:
				swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"InitError 其他错误");
				g_SR_LID_Error.nError = -1301;
				break;
			}
			g_lid.clear();
			return (SR_HANDLE)0;

		}
	}
	TLI_HANDLE hTLI;
	int nRst = TLI_Open(hTLI);
	if (nRst != 0){
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"OpenError 打开一路失败");
		g_SR_LID_Error.nError = -1301;
		if (g_mSRHandlers.empty()){
			g_lid.clear();
			TLI_Exit();
		}
		return (SR_HANDLE)0;
	}
	int retu = ++g_uLidAssignedNum;
	g_mSRHandlers[retu] = hTLI;
	return retu;
}

SR_API void SR_LID_Release(SR_HANDLE handle)
{
	map<unsigned, int>::iterator it = g_mSRHandlers.find(handle);
	if (it == g_mSRHandlers.end()){
		return;
	}
	int nRst = TLI_Close(it->second);
	if (nRst != 0){

	}
	g_mSRHandlers.erase(handle);
	if (g_mSRHandlers.empty()){
		g_lid.clear();
		TLI_Exit();
	}
	return;
}

SR_API bool SR_LID_Buf(SR_HANDLE handle, const SR_WAVBUF& WavBuf,
	const CFastList<SR_SEG, SR_SEG&>& Seg, SR_LIDRSTS& LidRsts)
{
	map<unsigned, int>::iterator it = g_mSRHandlers.find(handle);
	if (it == g_mSRHandlers.end()){
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"ParamError 传人句柄无效");
		g_SR_LID_Error.nError = -1301;
		return false;
	}
	SR_WAVBUF realBuf;
	SR_SS_MergeSegWavBuf(WavBuf, Seg, realBuf);
	if (realBuf.nWavBufLen == 0){
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"ParamError no segment of wave data to recognize.");
		g_SR_LID_Error.nError = -1301;
		return false;
	}
	
	int inputSampleNum = realBuf.nWavBufLen;
	if (inputSampleNum > g_lid.nMaxSpeechSec * SAMPLESPERSEC){
		inputSampleNum = g_lid.nMaxSpeechSec * SAMPLESPERSEC;
	}

	int nRst = TLI_Recognize(it->second, g_lid.allTemplateIDs, g_lid.uTemplateNum, static_cast<void*>(realBuf.pWavBuf), inputSampleNum * sizeof(short), -1, -1);
	free(realBuf.pWavBuf);
	if (nRst != 0){
		switch (nRst){
		case(-1) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 句柄错误");
			break;
		case(-2) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 该线程没有被初始化");
			break;
		case(-3) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 待判别语言ID或个数错误");
			break;
		case(-4) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 申请内存错误");
			break;
		case(-5) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 输入参数非法");
			break;
		case(-6) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 输入语音太短");
			break;
		case(-7) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError VAD失败");
			break;
		case(-8) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError VAD后有效语音太短");
			break;
		case(-9) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 音乐检测失败");
			break;
		case(-10) :
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 音乐检测后有效语音太短");
			break;
		default:
			swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"RecogError 其他错误");
		}
		g_SR_LID_Error.nError = -1301;
		return false;
	}
	int arrLen = (g_lid.uTemplateNum + 1);
	float *arrScore = (float*)malloc(sizeof(float)* arrLen);
	if (arrScore == NULL){
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"MemoryError failed to malloc size: %d.", sizeof(float)* arrLen);
		g_SR_LID_Error.nError = -1301;
		return false;
	}
	if (TLI_GetResult(it->second, arrScore, arrLen) == -1){
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"LogicError 获取得分失败 .");
		g_SR_LID_Error.nError = -1301;
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
	if (maxIdx != g_lid.uTemplateNum && g_lid.arrResLangs[maxIdx].nLIDScore > 0){
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
		swprintf(g_SR_LID_Error.chError, SR_MAX_ERROR_CHAR_BYTES, L"FileError 打开文件失败 %ls.", WavFile.PathName);
		g_SR_LID_Error.nError = -1301;
		return false;
	}
	bool retb = SR_LID_Buf(handle, wavBuf, Seg, LidRsts);
	free(wavBuf.pWavBuf);
	return retb;
}