/**********************************************************************************************//**
 * @file		cfg.h
 * @brief		配置文件类.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/12/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "str.h"
#include <map>
#include <fstream>

/**********************************************************************************************//**
 * @class	Config
 * @brief	读写配置项.
 * @note	1. 忽略注释符 '\%' 后的内容. 2. 只去除左右两边的空白. 3. 布尔类型用 true 和 false 表示, 不区分大小写. 4. 不支持 C 语言字符串类型.
 **************************************************************************************************/
class Config
{
public:
    /**********************************************************************************************//**
     * @fn      bool Config::Load(const string &cfgfile);
     * @brief	加载配置, 添加方式.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]	cfgfile		配置文件路径.
     **************************************************************************************************/
    bool Load(const string &cfgfile);

    /**********************************************************************************************//**
     * @fn      bool Config::Get(const string &section, const string &key, T &value) const;
     * @brief	获取配置.
     * @return	成功返回 true, 失败返回 false.
     * @tparam	T	类型参数.
     * @param [in]		section		段.
     * @param [in]		key	   		键.
     * @param [inout]	value  		值.
     **************************************************************************************************/
    template<typename T>
    bool Get(const string &section, const string &key, T &value) const;

    /**********************************************************************************************//**
     * @fn      bool Config::Set(const string &section, const string &key, const T &value);
     * @brief	设定配置.
     * @return	成功返回 true, 失败返回 false.
     * @tparam	T	类型参数.
     * @param [in]	section		段.
     * @param [in]	key	   		键.
     * @param [in]	value  		值.
     * @note	如果已存在, 则覆盖; 如果不存在, 则增加.
     **************************************************************************************************/
    template<typename T>
    bool Set(const string &section, const string &key, const T &value);

private:
    /** @brief	配置项, <section.key, value>. */
    map<string, string>  m_items;
};

inline bool Config::Load(const string &cfgfile)
{
    ifstream ifs(cfgfile.c_str());
    if (!ifs)
    {
        fprintf(stderr, "Cannot open(rt) configure file : \"%s\".\n", cfgfile.c_str());
        return false;
    }
    string::size_type pos;
    string section, line;
    while (getline(ifs, line))
    {
        // 去掉注释
        if (string::npos != (pos = line.find("%")))
        {
            line.erase(pos);
        }
        // 去掉空白
        Trim(line);
        // 注释行或空白行
        if (line.empty())
        {
            continue;
        }
        if ((line[0] == '<') && (line[line.size() - 1] == '>'))
        {
            section = line.substr(1, line.size() - 2);
        }
        else if (string::npos != (pos = line.find('=')))
        {
            m_items[section + '.' + line.substr(0, pos)] = line.substr(pos + 1);
        }
    }
    ifs.close();
    return true;
}

template<typename T>
inline bool Config::Get(const string &section, const string &key, T &value) const
{
    map<string, string>::const_iterator it = m_items.find(section + '.' + key);
    if (it != m_items.end())
    {
        if (Str2T(it->second, value))
        {
            return true;
        }
    }
    fprintf(stderr, "Cannot get configure item : <%s><%s>=<?>.\n", section.c_str(), key.c_str());
    return false;
}

template<>
inline bool Config::Get<bool>(const string &section, const string &key, bool &value) const
{
    map<string, string>::const_iterator it = m_items.find(section + '.' + key);
    if (it != m_items.end())
    {
        string tmp(it->second);
        StrLower(tmp);
        if (!tmp.compare("true"))
        {
            value = true;
            return true;
        }
        else if (!tmp.compare("false"))
        {
            value = false;
            return true;
        }
    }
    fprintf(stderr, "Cannot get configure item : <%s><%s>=<?>.\n", section.c_str(), key.c_str());
    return false;
}

template<>
inline bool Config::Get<string>(const string &section, const string &key, string &value) const
{
    map<string, string>::const_iterator it = m_items.find(section + '.' + key);
    if (it != m_items.end())
    {
        value = it->second;
        return true;
    }
    fprintf(stderr, "Cannot get configure item : <%s><%s>=<?>.\n", section.c_str(), key.c_str());
    return false;
}

template<typename T>
inline bool Config::Set(const string &section, const string &key, const T &value)
{
    if (!T2Str(value, m_items[section + '.' + key]))
    {
        fprintf(stderr, "Cannot set configure item : <%s><%s>=<?>.\n", section.c_str(), key.c_str());
    }
    return true;
}

template<>
inline bool Config::Set<bool>(const string &section, const string &key, const bool &value)
{
    if (value)
    {
        m_items[section + '.' + key] = "true";
    }
    else
    {
        m_items[section + '.' + key] = "false";
    }
    return true;
}