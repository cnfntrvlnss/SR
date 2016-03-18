/**********************************************************************************************//**
 * @file		str.h
 * @brief		字符串处理.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/11/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/**********************************************************************************************//**
 * @fn		inline void TrimL(string &str);
 * @brief	去除字符串左边的空白.
 * @param [in,out]	str	待处理的字符串.
 * @note	" Hello, World! " -> "Hello, World! "
 **************************************************************************************************/
inline void TrimL(string &str)
{
    size_t len = str.size();    // 字符串长度
    for (size_t i = 0; i < len; i++)
    {
        // 从左向右找到第一个不为空白的字符
        if (!isspace(str[i]))
        {
            str = str.substr(i);
            return;
        }
    }
    str.clear();    // 全部为空白字符
}

/**********************************************************************************************//**
 * @fn		inline void TrimR(string &str);
 * @brief	去除字符串右边的空白.
 * @param [in,out]	str	待处理的字符串.
 * @note	" Hello, World! " -> " Hello, World!"
 **************************************************************************************************/
inline void TrimR(string &str)
{
    // 从右向左找到第一个不为空白的字符
    for (size_t i = str.size(); i > 0;)
    {
        if (!isspace(str[--i]))
        {
            str = str.erase(i + 1);
            return;
        }
    }
    str.clear();    // 全部为空白字符
}

/**********************************************************************************************//**
 * @fn		inline void Trim(string &str);
 * @brief	去除字符串两边的空白.
 * @param [in,out]	str	待处理的字符串.
 * @note	" Hello, World! " -> "Hello, World!"
 **************************************************************************************************/
inline void Trim(string &str)
{
    TrimL(str);
    TrimR(str);
}

/**********************************************************************************************//**
 * @fn		inline void StrLower(string &str);
 * @brief	将一个字符串变为小写.
 * @param [in,out]	str	待处理的字符串.
 * @note	"Hello, World!" -> "hello, world!"
 **************************************************************************************************/
inline void StrLower(string &str)
{
    size_t len = str.size();
    for (size_t i = 0; i < len; i++)
    {
        str[i] = (char)tolower(str[i]);
    }
}

/**********************************************************************************************//**
 * @fn		inline void StrUpper(string &str);
 * @brief	将一个字符串变为大写.
 * @param [in,out]	str	待处理的字符串.
 * @note	"Hello, World!" -> "HELLO, WORLD!"
 **************************************************************************************************/
inline void StrUpper(string &str)
{
    size_t len = str.size();
    for (size_t i = 0; i < len; i++)
    {
        str[i] = (char)toupper(str[i]);
    }
}

/**********************************************************************************************//**
 * @fn		inline void StrSplit(const string &str, const string &sep, vector<string> &sseq);
 * @brief	用分隔符将一个字符串分割成字符串序列.
 * @param [in]		str		待分割字符串.
 * @param [in]		sep		分隔符.
 * @param [in,out]	sseq	字符串序列.
 * @note	1. 用空格分割 "Hello World!", 得到 ("Hello","World!"). 2. 在末端以添加方式压入容器.
 **************************************************************************************************/
inline void StrSplit(const string &str, const string &sep, vector<string> &sseq)
{
    size_t len = sep.size();    // 分隔符的长度
    string::size_type beg = 0, end = 0;
    while (string::npos != (end = str.find(sep, beg)))
    {
        sseq.push_back(str.substr(beg, end - beg));
        beg = end + len;
    }
    sseq.push_back(str.substr(beg));
}

/**********************************************************************************************//**
 * @fn		inline bool Str2T(const string &str, T &d);
 * @brief	将字符串转换为相应的数据类型.
 * @return	成功返回 true, 失败返回 false.
 * @tparam	T	类型参数.
 * @param [in]		str		转换前的字符串.
 * @param [in,out]	d		转换后的数据类型.
 * @note	1. (string)"3.1415926" -> (double)3.1415926. 2. 模板参数必须为 C++ 基本数据类型, 否者必须特化.
 **************************************************************************************************/
template<typename T>
inline bool Str2T(const string &str, T &d)
{
    istringstream iss(str);
    if (iss >> d)
    {
        return true;
    }
    return false;
}

/**********************************************************************************************//**
 * @fn		inline bool T2Str(const T &d, string &str);
 * @brief	将相应的数据类型转换为字符串.
 * @return	成功返回 true, 失败返回 false.
 * @tparam	T	类型参数.
 * @param [in]		d		转换前的数据类型.
 * @param [in,out]	str		转换后的字符串.
 * @note	1. (int)10086 -> (string)"10086". 2. 模板参数必须为 C++ 基本数据类型, 否者必须特化.
 **************************************************************************************************/
template<typename T>
inline bool T2Str(const T &d, string &str)
{
    ostringstream oss;
    if (oss << d)
    {
        str.assign(oss.str());
        return true;
    }
    return false;
}