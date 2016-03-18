/**********************************************************************************************//**
 * @file		file.h
 * @brief		文件和目录处理.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/13/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "str.h"
#include <omp.h>
#include <stdio.h>
#include <fstream>
#include <iterator>
#include <algorithm>

// Windows 和 Linux 跨平台定义
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <direct.h>
#define ACCESS _access
#define MKDIR(d) _mkdir((d))
#define FILE_SEP '\\'
#else
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#define ACCESS access
#define MKDIR(d) mkdir((d), S_IRWXU)
#define FILE_SEP '/'
#endif

/**********************************************************************************************//**
 * @fn      inline string Path2Name(const string &fpath);
 * @brief   从文件路径中解析出文件名, 不包含后缀.
 * @return  不包含后缀的文件名.
 * @param [in]   fpath   文件路径.
 * @note    ".\root\hello.txt" -> "hello".
 **************************************************************************************************/
inline string Path2Name(const string &fpath)
{
    string::size_type beg, end;
    beg = fpath.rfind(FILE_SEP) + 1;
    end = fpath.rfind('.');
    if (string::npos != end)
    {
        return fpath.substr(beg, end - beg);
    }
    else
    {
        return fpath.substr(beg);
    }
}

/**********************************************************************************************//**
 * @fn      inline string Path2FName(const string &fpath);
 * @brief   从文件路径中解析出文件名, 包含后缀.
 * @return  包含后缀的文件名.
 * @param [in]   fpath   文件路径.
 * @note    ".\root\hello.txt" -> "hello.txt".
 **************************************************************************************************/
inline string Path2FName(const string &fpath)
{
    return fpath.substr(fpath.rfind(FILE_SEP) + 1);
}

/**********************************************************************************************//**
 * @fn      inline string JoinPath(const string &dpath, const string &fname);
 * @brief   将目录路径和文件名拼接成一个完整的文件路径.
 * @return  文件路径.
 * @param [in]  dpath   目录路径.
 * @param [in]  fname   文件名.
 * @note    ".\root" + "hello.txt" -> ".\root\hello.txt".
 **************************************************************************************************/
inline string JoinPath(const string &dpath, const string &fname)
{
    if (dpath[dpath.size() - 1] != FILE_SEP)
    {
        return dpath + FILE_SEP + fname;
    }
    return dpath + fname;
}

/**********************************************************************************************//**
 * @fn      inline bool IsFile(const string &fpath);
 * @brief   指定路径是否存在且为一个文件.
 * @return  存在返回 true, 否则返回 false.
 * @param [in]   fpath   文件路径.
 * @note    只判断不创建.
 **************************************************************************************************/
inline bool IsFile(const string &fpath)
{
    return (ACCESS(fpath.c_str(), 0) == 0);
}

/**********************************************************************************************//**
 * @fn      inline bool IsDir(const string &dpath);
 * @brief   指定路径是否存在且为一个目录.
 * @return  存在返回 true, 否则返回 false.
 * @param [in]   dpath   目录路径.
 * @note    只判断不创建.
 **************************************************************************************************/
inline bool IsDir(const string &dpath)
{
    string tmpdir(dpath);
    if (dpath[dpath.size() - 1] == FILE_SEP)
    {
        tmpdir = dpath.substr(0, dpath.size() - 1);
    }

#if defined(_WIN32) || defined(_WIN64)

    _finddata_t findinfo;
    intptr_t handle = _findfirst(tmpdir.c_str(), &findinfo);
    if (handle == -1)
    {
        return false;
    }
    if (findinfo.attrib & _A_SUBDIR)
    {
        _findclose(handle);
        return true;
    }
    else
    {
        _findclose(handle);
        return false;
    }

#else

    struct stat st;
    if (-1 == stat(tmpdir.c_str(), &st))
    {
        return false;
    }
    if (S_ISDIR(st.st_mode))
    {
        return true;
    }
    else
    {
        return false;
    }

#endif
}

/**********************************************************************************************//**
 * @fn      inline bool MakeDir(const string &dpath);
 * @brief   创建目录.
 * @return  成功返回 true, 失败返回 false.
 * @param [in]   dpath   目录路径.
 * @note    1. 不嵌套创建目录. 2. 通常配合 @ref IsDir 函数使用
 **************************************************************************************************/
inline bool MakeDir(const string &dpath)
{
    if (MKDIR(dpath.c_str()) == 0)
    {
        return true;
    }
    else
    {
        fprintf(stderr, "Cannot create directory : \"%s\".\n", dpath.c_str());
        return false;
    }
}

/**********************************************************************************************//**
 * @fn      inline bool CheckDir(const string &dpath);
 * @brief   检查目录, 如果不存在则创建.
 * @return  目录不存在且创建失败返回 false, 否则返回 true.
 * @param [in]   dpath   目录路径.
 **************************************************************************************************/
inline bool CheckDir(const string &dpath)
{
    if (!IsDir(dpath) && !MakeDir(dpath))
    {
        return false;
    }
    return true;
}

/**********************************************************************************************//**
 * @typedef vector<string> FList
 * @brief   文件列表.
 **************************************************************************************************/
typedef vector<string>		FList;

/**********************************************************************************************//**
 * @fn      inline void MergeFList(const FList &src1, const FList &src2, FList &dst);
 * @brief   合并文件列表.
 * @param [in]      src1    待合并文件列表对象 1.
 * @param [in]      src2    待合并文件列表对象 2.
 * @param [in,out]  dst     合并后的文件列表对象.
 * @note    1. 自动移除 src1 和 src2 中相同的项. 2. 添加到 dst 末端.
 **************************************************************************************************/
inline void MergeFList(const FList &src1, const FList &src2, FList &dst)
{
    vector<string> tmp1(src1), tmp2(src2);
    sort(tmp1.begin(), tmp1.end());
    sort(tmp2.begin(), tmp2.end());
    set_union(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), back_inserter(dst));
}

/**********************************************************************************************//**
 * @fn      inline bool LoadFList(const string &fpath, FList &flist);
 * @brief   加载文件列表.
 * @return  成功打开文件返回 true, 否则返回 false.
 * @param [in]      fpath   列表文件路径.
 * @param [in,out]  flist   文件列表对象.
 * @note    1. 忽略空白行. 2. 添加方式.
 **************************************************************************************************/
inline bool LoadFList(const string &fpath, FList &flist)
{
    ifstream ifs(fpath.c_str());
    if (!ifs)
    {
        fprintf(stderr, "Cannot open(rt) file list : \"%s\".\n", fpath.c_str());
        return false;
    }
    string line;
    while (getline(ifs, line))
    {
        // 去除首尾的空格
        Trim(line);
        // 如果为空, 说明这一行全部是空格
        if (!line.empty())
        {
            flist.push_back(line);
        }
    }
    ifs.close();
    return true;
}

/**********************************************************************************************//**
 * @struct  Speech
 * @brief   每个对象代表一段语音.
 **************************************************************************************************/
struct Speech
{
    /** @brief   名称. */
    string name;
    /** @brief   路径. */
    string path;
};

/**********************************************************************************************//**
 * @typedef vector<Speech> SpeechList
 * @brief   语音列表.
 **************************************************************************************************/
typedef vector<Speech>      SpeechList;

/**********************************************************************************************//**
 * @fn      inline bool LoadSphList(const string &fpath, SphList &utts);
 * @brief   从文件列表加载所有语音.
 * @return  成功打开文件返回 true, 否则返回 false.
 * @param [in]      fpath   语音文件列表.
 * @param [in,out]  utts    所有语音.
 * @note    加载前会清空.
 **************************************************************************************************/
inline bool LoadSphList(const string &fpath, SpeechList &utts)
{
    FList flist;
    if (!LoadFList(fpath, flist))
    {
        return false;
    }
    utts.resize(flist.size());
#pragma omp parallel for
    for (int i = 0; i < (int)flist.size(); i++)
    {
        utts[i].path = flist[i];
        utts[i].name = Path2Name(flist[i]);
    }
    return true;
}
