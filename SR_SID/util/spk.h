/**********************************************************************************************//**
 * @file		spk.h
 * @brief		说话人类.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/7/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "file.h"

/**********************************************************************************************//**
 * @struct  Spk
 * @brief   说话人类.
 * @note    每一个对象代表一个说话人.
 **************************************************************************************************/
struct Spk
{
    /** @brief   说话人的 ID. */
    string			id;
    /** @brief   说话人的所有数据(路径) */
    vector<string>	utts;
};

/**********************************************************************************************//**
 * @typedef vector<Spk> Spks
 * @brief   说话人集合.
 **************************************************************************************************/
typedef vector<Spk>		Spks;

/**********************************************************************************************//**
 * @fn      inline bool LoadSpkTable(const string &spktbl, Spks &spks);
 * @brief   加载说话人表.
 * @return  成功返回 true, 失败返回 false.
 * @param [in]      spktbl      说话人表.
 * @param [in,out]  spks        说话人集合对象.
 * @note    1. 每一行的格式: "id utt1,utt2,...,uttN". 2. 忽略格式不对的行. 3. 添加方式.
 **************************************************************************************************/
inline bool LoadSpkTable(const string &spktbl, Spks &spks)
{
    ifstream ifs(spktbl.c_str());
    if (!ifs)
    {
        fprintf(stderr, "Cannot open(rt) speaker table : \"%s\".\n", spktbl.c_str());
        return false;
    }
    string line; string::size_type pos;
    while (getline(ifs, line))
    {
        pos = line.find(' ');
        if (pos == string::npos)
        {
            fprintf(stderr, "Invalid line of speaker table : \"%s\".\n", line.c_str());
            continue;
        }
        Spk spk;
        spk.id = line.substr(0, pos);
        StrSplit(line.substr(pos + 1), ",", spk.utts);
        spks.push_back(spk);
    }
    ifs.close();
    return true;
}

/**********************************************************************************************//**
 * @fn      inline size_t CountUtt( const Spks &spks )
 * @brief   统计总共的语音数目.
 * @return  语音总数目.
 * @param [in]   spks    说话人集合对象.
 **************************************************************************************************/
inline size_t CountUtt(const Spks &spks)
{
    size_t num = 0, nspk = spks.size();
    for (size_t i = 0; i < nspk; i++)
    {
        num += spks[i].utts.size();
    }
    return num;
}

/**********************************************************************************************//**
 * @fn      inline void SpkTbl2FList( const Spks &spks, FList &flist )
 * @brief   将说话人表转换成文件列表, 抛弃 ID 信息
 * @param [in]      spks    说话人集合对象.
 * @param [in,out]  flist   文件列表对象.
 * @note    1. 该过程不可逆. 2. 添加方式.
 **************************************************************************************************/
inline void SpkTbl2FList(const Spks &spks, FList &flist)
{
    size_t nspk = spks.size();
    for (size_t i = 0; i < nspk; i++)
    {
        flist.insert(flist.end(), spks[i].utts.begin(), spks[i].utts.end());
    }
}