// sr_start.cpp : 定义控制台应用程序的入口点。
//
#include "common/port_zsr.h"
#include "sr/FastList_Ex.h"
#include "sr/sr.h"

#include "stdafx.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <locale.h>

using std::string;

#include "gtest/gtest.h"
#include "gmock/gmock.h"

/*
===========test cfastlist========================
*/
template<class T, class K>
static inline string fastlist_to_string(const CFastList<T, K> &li)
{
	std::ostringstream oss;
	oss << "[";
	for (size_t s = 0; s < li.GetCount(); s++){
		oss << li[s] << ",";
	}
	string retstr = oss.str();
	if (retstr.size() > 1) retstr[retstr.size() - 1] = ']';
	return retstr;
}

TEST(fastlist, baseop){
	CFastList<int, int> cl;
	cl.AddHead(10);
	cl.AddHead(0);
	cl.AddTail(20);
	const int& a = cl.GetHead();// cl contains 0,10,20.
	ASSERT_EQ(0, a) << "head node of cl contains other than " << 0;
	cl.InsertAfter(2, 40);
	cl.InsertBefore(3, 30);
	cl.InsertBefore(4, 50);
	cl.RemoveAt(4);
	const int &b = cl.GetTail();// cl contains 0, 10, 20, 30, 40
	ASSERT_EQ(40, b) << "tail node of cl contains other than " << 40;
	//ASSERT_EQ(5, cl.GetCount()) << "current size of cl is other than " << 5;

	POSITION pt = cl.GetHeadPosition();// cl contains 0, 10, 20, 30, 40
	int val = 0;
	while (pt != NULL){
		int curVal = cl.GetNext(pt);
		ASSERT_EQ(val, curVal);
		val += 10;
	}
	val -= 10;
	pt = cl.GetTailPosition();
	while (pt != NULL){
		int curVal = cl.GetPrev(pt);
		ASSERT_EQ(val, curVal);
		val -= 10;
	}
	pt = cl.FindIndex(2);
	ASSERT_EQ(20, cl.GetAt(pt));

	while (cl.GetCount() > 0){
		cl.RemoveHead();
	}
	cl.RemoveAll();
	cl.AddTail(0);
	cl.AddTail(10);
	cl.AddTail(20);
	cl.AddTail(30);
	cl.AddTail(40);
	cl.RemoveAll();
	cl.AddTail(0);
	cl.AddTail(10);
	cl.AddTail(20);
	cl.AddTail(30);
	cl.AddTail(40);
	ASSERT_EQ(30, cl.GetAt(cl.Find(30, 3)));
	POSITION pos = cl.Find(20, 2);
	ASSERT_EQ(pos, cl.Find(20, pos));
}

/*
=================test character encoding====================
*/
TEST(wchar, chinese){
	std::string greetingcn = "郑树锐，你好";
	std::string greetingen = "hello, zhengshurui";

	wchar_t * wstrTemp = GB2312sToWCs(greetingcn.c_str());
	ASSERT_NE(nullptr, wstrTemp)<< "fail to convert to wchar.";
	/* error: 向控制台写宽字符，控制台没显示。
	fputws(L"error string: ", stderr);
	fputws(wstrTemp, stderr);
	fwprintf(stderr, L"(%u) ", wcslen(wstrTemp));
	fputws(L"\n", stderr);
	*/
	char *strTemp = WCsToGB2312s(wstrTemp);
	//fprintf(stderr, "error string:: %s\n", strTemp);
	ASSERT_EQ(0, strcmp(greetingcn.c_str(), strTemp))<<"fail to get back original string of greetingcn  by transforming from ansi to wchar to ansi.";
	free(const_cast<wchar_t*>(wstrTemp));
	free(strTemp);
	wstrTemp = GB2312sToWCs(greetingen.c_str());
	strTemp = WCsToGB2312s(wstrTemp);
	ASSERT_EQ(0, strcmp(greetingen.c_str(), strTemp)) << "fail to get back original string of greetingen  by transforming from ansi to wchar to ansi.";
	free(wstrTemp);
	free(strTemp);

}

/**
=========================test SR_FileList========================
*/
TEST(SR_FileList, simple1)
{
	SR_FILE tmpFile;
	STRCPY(tmpFile.PathName, _T("testdata\\文件列表临时文件"));
	CFastList<SR_FILE, SR_FILE&> oriList;
	CFastList<SR_FILE, SR_FILE&> desList;
	SR_FILE file1 = {_T("郑树锐")};
	oriList.AddTail(file1);
	file1 = { _T("刘双君") };
	oriList.AddTail(file1);
	ASSERT_EQ(true, SR_FL_WriteListFile(oriList, tmpFile));
	ASSERT_EQ(true, SR_FL_ReadListFile(tmpFile, desList));
	auto tmpcomp = [](const SR_FILE& a, const SR_FILE& b) {return STRCMP(a.PathName, b.PathName) < 0 ? true : false; };
	cfastlist_sort(oriList, tmpcomp);
	cfastlist_sort(desList, tmpcomp);
	ASSERT_EQ(oriList.GetCount(), desList.GetCount());
	POSITION posd = desList.GetHeadPosition();
	POSITION pos = oriList.GetHeadPosition();
	while (pos != NULL)
	{
		ASSERT_EQ(0, STRCMP(oriList.GetNext(pos).PathName, desList.GetNext(posd).PathName));
	}

}

/**
===================================test SR_WaveFile=====================================
*/
inline void SR_WAVBUF_Init(SR_WAVBUF &buf)
{
	buf.nWavBufLen = 0;
	buf.pWavBuf = 0;
	buf.wf = {};
}
TEST(SR_WaveFile, first)
{
	SR_FILE tmpfile, tmpfile2;
	STRCPY(tmpfile.PathName, _T("testdata\\0.wav"));
	STRCPY(tmpfile2.PathName, _T("testdata\\1.wav"));
	char *tmpfilegb = WCsToGB2312s(tmpfile.PathName);
	char *tmpfile2gb = WCsToGB2312s(tmpfile2.PathName);
	SR_WAVBUF buf, buf2;
	SR_WAVBUF_Init(buf);
	SR_WAVBUF_Init(buf2);
	ASSERT_EQ(true, SR_WF_ReadWavFile(tmpfile, buf)) << "fail to read test wave file " << tmpfilegb;;
	ASSERT_EQ(true, SR_WF_WriteWavFile(buf, tmpfile2)) << "fail to write test wave file.";
	ASSERT_EQ(true, SR_WF_ReadWavFile(tmpfile2, buf2)) << "fail to read test wave file " << tmpfile2gb;
	ASSERT_EQ(buf.nWavBufLen, buf2.nWavBufLen);
#define MY_SNIPPET_1(n) 	int len##n = buf.nWavBufLen - (n)*8000 > 8000? 8000 : buf.nWavBufLen - (n) * 8000;\
	ASSERT_EQ(0, memcmp(buf.pWavBuf + (n)* 8000, buf2.pWavBuf + (n)* 8000, len##n));
	MY_SNIPPET_1(0);
	MY_SNIPPET_1(10);
	MY_SNIPPET_1(100);
}

/***
=====================================test SR_SpeechSeg=======================================
*/
bool SR_SEG_LessThan(SR_SEG segr, SR_SEG segl)
{
	return segr.nFileID < segl.nFileID ||
		segr.nFileID == segl.nFileID && segr.nStart < segl.nStart ||
		segr.nFileID == segl.nFileID && segr.nStart == segl.nStart && segr.nEnd < segr.nEnd; //&& segr.nStart < segl.nStart && segr.nEnd < segl.nEnd
}
bool SR_SEG_EqualWith(SR_SEG segr, SR_SEG segl)
{
	return !SR_SEG_LessThan(segr, segl) && !SR_SEG_LessThan(segl, segr);
}
/**
在内存中构造一个3行的片段信息列表，执行写、读操作，最终的结果与开始处构造的片段信息列表是一样的。
*/
TEST(SR_SpeechSeg, simpleReadAndWrite)
{
	SR_SEG seg1 = {173, 8000, 80000, 0}; //1s ~ 10s
	SR_SEG seg2 = { 173, 40000, 64000, 0 };//5s ~ 8s
	SR_SEG seg3 = { 173, 160000, 240000, 0 };//20s ~ 25s
	CFastList<SR_SEG, SR_SEG&> srcLi, desLi;
	srcLi.AddTail(seg1);
	srcLi.AddTail(seg2);
	srcLi.AddTail(seg3);
	SR_FILE myFile = {_T("testdata\\语音173的分段信息.list")};
	ASSERT_TRUE(SR_SS_WriteSegFile(srcLi, myFile));
	ASSERT_TRUE(SR_SS_ReadSegFile(myFile, desLi));
	if (srcLi.GetCount() > 0){
		POSITION pos = srcLi.GetHeadPosition();
		do{
			POSITION posIn = desLi.GetHeadPosition();
			int idx = 0;
			for (idx = 0; idx < desLi.GetCount(); idx++){
				if (SR_SEG_EqualWith(srcLi.GetNext(pos), desLi.GetNext(posIn))){
					break;
				}
			}
			ASSERT_FALSE(idx == desLi.GetCount())<< "the result of list is not equal with the initial list.";
		} while (pos == srcLi.GetTailPosition());
	}
}
/**
准备一个音频文件，用不同的片段信息进行片段拼接操作，对结果进行验证。
*/
TEST(SR_SpeechSeg, simpleMerge)
{
	SR_SEG seg1 = { 173, 8000, 88000, 0 }; //1s ~ 11s
	SR_SEG seg2 = { 173, 40000, 64000, 0 };//5s ~ 8s
	SR_SEG seg3 = { 173, 160000, 240000, 0 };//20s ~ 30s
	CFastList<SR_SEG, SR_SEG&> srcLi;
	srcLi.AddTail(seg1);
	srcLi.AddTail(seg2);
	srcLi.AddTail(seg3);
	SR_WAVBUF bufIn, bufOut;
	SR_WAVBUF_Init(bufIn);
	SR_WAVBUF_Init(bufOut);
	SR_WF_ReadWavFile({_T("testdata\\0.wav")}, bufIn);
	ASSERT_LT(30 * 8000, bufIn.nWavBufLen);
	ASSERT_TRUE(SR_SS_MergeSegWavBuf(bufIn, srcLi, bufOut));
	ASSERT_EQ(20 * 8000, bufOut.nWavBufLen);
}

int main(int argc, char **argv) {
	printf("Running main() from gtest_main.cc\n");
	//printf("%s\n", getenv("PATH"));
	//system("pause");
	setlocale(LC_ALL, "");
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;

}