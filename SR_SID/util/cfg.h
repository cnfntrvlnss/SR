/**********************************************************************************************//**
 * @file		cfg.h
 * @brief		�����ļ���.
 * @author		���Ʒ� (kindapple@163.com)
 * @version		1.0
 * @date		6/12/2015
 * @copyright	2010-2015 �й���ѧԺ��ѧ�о���������ѧ����������ص�ʵ����
 **************************************************************************************************/
#pragma once
#include "str.h"
#include <map>
#include <fstream>

/**********************************************************************************************//**
 * @class	Config
 * @brief	��д������.
 * @note	1. ����ע�ͷ� '\%' �������. 2. ֻȥ���������ߵĿհ�. 3. ���������� true �� false ��ʾ, �����ִ�Сд. 4. ��֧�� C �����ַ�������.
 **************************************************************************************************/
class Config
{
public:
    /**********************************************************************************************//**
     * @fn      bool Config::Load(const string &cfgfile);
     * @brief	��������, ��ӷ�ʽ.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @param [in]	cfgfile		�����ļ�·��.
     **************************************************************************************************/
    bool Load(const string &cfgfile);

    /**********************************************************************************************//**
     * @fn      bool Config::Get(const string &section, const string &key, T &value) const;
     * @brief	��ȡ����.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @tparam	T	���Ͳ���.
     * @param [in]		section		��.
     * @param [in]		key	   		��.
     * @param [inout]	value  		ֵ.
     **************************************************************************************************/
    template<typename T>
    bool Get(const string &section, const string &key, T &value) const;

    /**********************************************************************************************//**
     * @fn      bool Config::Set(const string &section, const string &key, const T &value);
     * @brief	�趨����.
     * @return	�ɹ����� true, ʧ�ܷ��� false.
     * @tparam	T	���Ͳ���.
     * @param [in]	section		��.
     * @param [in]	key	   		��.
     * @param [in]	value  		ֵ.
     * @note	����Ѵ���, �򸲸�; ���������, ������.
     **************************************************************************************************/
    template<typename T>
    bool Set(const string &section, const string &key, const T &value);

private:
    /** @brief	������, <section.key, value>. */
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
        // ȥ��ע��
        if (string::npos != (pos = line.find("%")))
        {
            line.erase(pos);
        }
        // ȥ���հ�
        Trim(line);
        // ע���л�հ���
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