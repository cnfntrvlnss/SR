#define SR_EXPORTS

#include "common\port_zsr.h"
#include "sr/FastList_Ex.h"
#include "sr/sr.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

//�����ļ����ʽӿ� -301 �� -400 
SR_ERROR g_SR_SpeechSeg_err = { 0, { '\0' } };
void SR_SS_GetLastError(SR_HANDLE handle, SR_ERROR& Error)
{
	Error = g_SR_SpeechSeg_err;
}

bool SR_SS_ReadSegFile(const SR_FILE& File, CFastList<SR_SEG, SR_SEG&>& Seg)
{
	string strFile = WCsToGB2312s(File.PathName);
	FILE *fp = fopen(strFile.c_str(), "r");
	if (fp == NULL){
		return false;
	}
	Seg.RemoveAll();
	SR_SEG curseg;
	char tmpLine[1024];
	while (fgets(tmpLine, 1024, fp) != NULL)
	{
		char *curTok = strtok(tmpLine, ",\n");
		int idx = 0;
		while (idx < 4 && curTok != NULL){
			switch (idx){
			case 0:
				curseg.nFileID = atoi(curTok); 
				break;
			case 1:
				curseg.nStart = atoi(curTok);
				break;
			case 2:
				curseg.nEnd = atoi(curTok);
				break;
			case 3:
				curseg.nType = atoi(curTok);
				break;
			default:
				break;
			}
			idx++;
			curTok = strtok(NULL, ",\n");
		}
		if (idx == 4){
			curseg.nState = 1;
			Seg.AddTail(curseg);
		}
	}
	fclose(fp);
	return true;
}

bool SR_SS_WriteSegFile(const CFastList<SR_SEG, SR_SEG&>& Seg, const SR_FILE& File)
{
	string strFile = WCsToGB2312s(File.PathName);
	FILE *fp = fopen(strFile.c_str(), "w");
	if (fp == NULL){
		return false;
	}
	POSITION pos = Seg.GetHeadPosition();
	for (unsigned idx = 0; idx < Seg.GetCount(); idx++){
		const SR_SEG& refSeg = Seg.GetNext(pos);
		fprintf(fp, "%d,%d,%d,%d\n", refSeg.nFileID, refSeg.nStart, refSeg.nEnd, refSeg.nType);
	}
	fclose(fp);
	return true;
}

static inline bool startCmp4SR_SEG(const SR_SEG& seg1, const SR_SEG& seg2)
{
	if (seg1.nStart < seg2.nStart) return true;
	else return false;
}

static inline void ExtendDataBuffer(short* desBuf, unsigned desSize, int& desLen, short* srcBuf, unsigned srcSize, int stIdx, int newLen)
{
	assert(stIdx + newLen <= srcSize);
	assert(desLen + newLen <= desSize);
	memcpy(desBuf + desLen, &srcBuf[stIdx], sizeof(short)* newLen);
	desLen += newLen;
}

/**
�ӿں���δ����⣬��ǰ����Seg�е�Ƭ����Ϣ���Ǵ�WavBufIn�б�ע�����ӿ����Seg��Χ�ڵ����ݣ�ͨ��������Ƭ��ƴװ���ã����������WavBufOut�С�
*/
bool SR_SS_MergeSegWavBuf(const SR_WAVBUF& WavBufIn, const CFastList<SR_SEG, SR_SEG&>& Seg, SR_WAVBUF& WavBufOut)
{
	if (Seg.GetCount() == 0){
		WavBufOut.nWavBufLen = 0;
		return true;
	}

	WavBufOut.wf = WavBufIn.wf;
	WavBufOut.pWavBuf = (short*)malloc(sizeof(short)* WavBufIn.nWavBufLen);
	unsigned bufSize = WavBufIn.nWavBufLen;

	CFastList<SR_SEG, SR_SEG&> seg2;
	cfastlist_sort_copy(Seg, seg2, startCmp4SR_SEG);
	POSITION pos = seg2.GetHeadPosition();
	SR_SEG& curseg = seg2.GetAt(pos);
	while (true){
		int nSt = curseg.nStart;
		int nEd = curseg.nEnd;
		if (pos == seg2.GetTailPosition()){
			//append  wave data.
			ExtendDataBuffer(WavBufOut.pWavBuf, bufSize, WavBufOut.nWavBufLen, WavBufIn.pWavBuf, WavBufIn.nWavBufLen, nSt, nEd - nSt);
			break;
		}
		bool bFinish = false;
		while (true){
			seg2.GetNext(pos);	
			SR_SEG& nextseg = seg2.GetAt(pos);
			if (nextseg.nStart > nEd){
				//append wave data.
				ExtendDataBuffer(WavBufOut.pWavBuf, bufSize, WavBufOut.nWavBufLen, WavBufIn.pWavBuf, WavBufIn.nWavBufLen, nSt, nEd - nSt);
				curseg = nextseg;
				break;
			}
			else{
				if (nextseg.nEnd > nEd){
					nEd = nextseg.nEnd;
				}
				if (pos == seg2.GetTailPosition()){
					//append wave data.
					ExtendDataBuffer(WavBufOut.pWavBuf, bufSize, WavBufOut.nWavBufLen, WavBufIn.pWavBuf, WavBufIn.nWavBufLen, nSt, nEd - nSt);
					bFinish = true;
					break;
				}
				
			}
		}
		if (bFinish) break;
	}

	if (WavBufOut.nWavBufLen == 0){
		free(WavBufOut.pWavBuf);
		WavBufOut.pWavBuf = NULL;
	}
	return true;
}

bool SR_SS_CalSegOffset(const CFastList<SR_SEG, SR_SEG&>& AllAbsSeg, const CFastList<SR_SEG, SR_SEG&>& SegOppSeg, CFastList<SR_SEG, SR_SEG&>& SegAbsSeg)
{
	fprintf(stderr, "unimplemented function SR_SS_CalSegOffset.\n");
	return false;
}