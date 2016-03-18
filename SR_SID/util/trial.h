/**********************************************************************************************//**
 * @file		trial.h
 * @brief		测试文件相关.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/8/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "spk.h"
#include <map>
#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include <armadillo>
#pragma warning(pop)
using namespace arma;

/**********************************************************************************************//**
 * @struct  Trials
 * @brief   测试对.
 **************************************************************************************************/
struct Trials
{
    /** @brief   测试语句. */
    SpeechList		tsts;
    /** @brief   目标说话人. */
    Spks			tars;
    /** @brief   是否参与打分, 0: 否, 1: 是. */
    Mat<char>		act;
};

/**********************************************************************************************//**
 * @fn      inline bool LoadTrial1(const string &tstlist, const string &spktbl, const string &trialfile, Trials &trials);
 * @brief   加载测试文件.
 * @return  成功加载返回 true, 否则返回 false.
 * @param [in]  tstlist         测试语音列表.
 * @param [in]  spktbl          目标说话人表.
 * @param [in]  trialfile       测试文件.
 * @param [in,out]  trials      所有测试对对象.
 * @note    说话人表形式.
 **************************************************************************************************/
inline bool LoadTrial1(const string &tstlist, const string &spktbl, const string &trialfile, Trials &trials)
{
    if (!LoadSphList(tstlist, trials.tsts))
    {
        return false;
    }
    if (!LoadSpkTable(spktbl, trials.tars))
    {
        return false;
    }
    trials.act.set_size((uword)trials.tsts.size(), (uword)trials.tars.size());

    if (trialfile.empty())
    {
        trials.act.fill(1);
        return true;
    }
    else
    {
        trials.act.fill(0);
    }

    map<string, uword> tstidx, taridx;
    for (uword i = 0; i < trials.tsts.size(); i++)
    {
        tstidx[trials.tsts[i].name] = i;
    }
    for (uword i = 0; i < trials.tars.size(); i++)
    {
        taridx[trials.tars[i].id] = i;
    }

    ifstream ifs(trialfile.c_str());
    if (!ifs)
    {
        fprintf(stderr, "Cannot open(rt) trial file : \"%s\".\n", trialfile.c_str());
        return false;
    }
    string tst, tars;
    map<string, uword>::const_iterator cit;
    while (ifs >> tst >> tars)
    {
        uword i, j;
        if (tstidx.end() != (cit = tstidx.find(tst)))
        {
            i = cit->second;
        }
        else
        {
            fprintf(stderr, "Cannot find test segment (%s) in \"%s\".\n", tst.c_str(), tstlist.c_str());
            continue;
        }
        vector<string> frag;
        // 去掉两边的括号
        StrSplit(tars.substr(1, tars.size() - 2), ",", frag);
        for (size_t idx = 0; idx < frag.size(); idx++)
        {
            if (taridx.end() != (cit = taridx.find(frag[idx])))
            {
                j = cit->second;
                trials.act(i, j) = 1;
            }
            else
            {
                fprintf(stderr, "Cannot find speaker ID (%s) in \"%s\".\n", frag[idx].c_str(), spktbl.c_str());
            }
        }
    }
    ifs.close();
    return true;
}

/**********************************************************************************************//**
 * @fn      inline bool LoadTrial2(const string &tstlist, const string &spklist, const string &trialfile, Trials &trials);
 * @brief   加载测试文件.
 * @return  成功加载返回 true, 否则返回 false.
 * @param [in]  tstlist         测试语音列表.
 * @param [in]  spklist         模型列表.
 * @param [in]  trialfile       测试文件.
 * @param [in,out]  trials      所有测试对对象.
 * @note    模型列表形式.
 **************************************************************************************************/
inline bool LoadTrial2(const string &tstlist, const string &spklist, const string &trialfile, Trials &trials)
{
    // 临时借用一下
    if (!LoadSphList(spklist, trials.tsts))
    {
        return false;
    }
    trials.tars.resize(trials.tsts.size());
    for (size_t i = 0; i < trials.tsts.size(); i++)
    {
        Spk spk;
        spk.id = trials.tsts[i].name;
        spk.utts.push_back(trials.tsts[i].path);
        trials.tars.push_back(spk);
    }
    trials.tsts.clear();
    if (!LoadSphList(tstlist, trials.tsts))
    {
        return false;
    }
    trials.act.set_size((uword)trials.tsts.size(), (uword)trials.tars.size());

    if (trialfile.empty())
    {
        trials.act.fill(1);
        return true;
    }
    else
    {
        trials.act.fill(0);
    }

    map<string, uword> tstidx, taridx;
    for (uword i = 0; i < trials.tsts.size(); i++)
    {
        tstidx[trials.tsts[i].name] = i;
    }
    for (uword i = 0; i < trials.tars.size(); i++)
    {
        taridx[trials.tars[i].id] = i;
    }

    ifstream ifs(trialfile.c_str());
    if (!ifs)
    {
        fprintf(stderr, "Cannot open(rt) trial file : \"%s\".\n", trialfile.c_str());
        return false;
    }
    string tst, tars;
    map<string, uword>::const_iterator cit;
    while (ifs >> tst >> tars)
    {
        uword i, j;
        if (tstidx.end() != (cit = tstidx.find(tst)))
        {
            i = cit->second;
        }
        else
        {
            fprintf(stderr, "Cannot find test segment (%s) in \"%s\".\n", tst.c_str(), tstlist.c_str());
            continue;
        }
        vector<string> frag;
        // 去掉两边的括号
        StrSplit(tars.substr(1, tars.size() - 2), ",", frag);
        for (size_t idx = 0; idx < frag.size(); idx++)
        {
            if (taridx.end() != (cit = taridx.find(frag[idx])))
            {
                j = cit->second;
                trials.act(i, j) = 1;
            }
            else
            {
                fprintf(stderr, "Cannot find speaker ID (%s) in \"%s\".\n", frag[idx], spklist.c_str());
            }
        }
    }
    ifs.close();
    return true;
}