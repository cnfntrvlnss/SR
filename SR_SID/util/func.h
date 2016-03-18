/**********************************************************************************************//**
 * @file		func.h
 * @brief		一些数学函数.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/11/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** @brief	pi. */
const double PI = 3.14159265358979323846;
/** @brief	2 * pi. */
const double TPI = 6.28318530717958647692;
/** @brief	pi / 2. */
const double PI2 = 1.57079632679489661923;
/** @brief	pi / 4. */
const double PI4 = 0.78539816339744830961;
/** @brief	pi / 180. */
const double PI180 = 0.01745329251994329577;
/** @brief	sqrt(2). */
const double SQRT2 = 1.41421356237309504880;
/** @brief	sqrt(3). */
const double SQRT3 = 1.73205080756887729353;
/** @brief	ln(2). */
const double LN2 = 0.69314718055994530942;
/** @brief	ln(3). */
const double LN3 = 1.09861228866810969139;
/** @brief	ln(2 * pi). */
const double LN2PI = 1.83787706640934548356;
/** @brief	ln(0). */
const double LZERO = -1.0E10;
/** @brief	ln values < LSMALL are set to LZERO. */
const double LSMALL = -0.5E10;
const double MINLOGEXP = -log(-LZERO);
/** @brief	lowest ln() arg  = exp(MINEARG). */
const double MINLARG = 2.45E-308;

/**********************************************************************************************//**
 * @fn		inline double LogAdd(double x, double y);
 * @brief	在自然对数域相加.
 * @return	ln(a + b).
 * @param	x	ln(a).
 * @param	y	ln(b).
 **************************************************************************************************/
inline double LogAdd(double x, double y)
{
    if (x < y)
    {
        double temp = x;
        x = y;
        y = temp;
    }
    double diff = y - x;
    if (diff < MINLOGEXP)
    {
        return  (x < LSMALL) ? LZERO : x;
    }
    else
    {
        return x + log(1.0 + exp(diff));
    }
}

/**********************************************************************************************//**
 * @fn	    inline double LogSub(double x, double y);
 * @brief	在自然对数域相减.
 * @return	ln(a - b).
 * @param	x	ln(a).
 * @param	y	ln(b).
 **************************************************************************************************/
inline double LogSub(double x, double y)
{
    if (x < y)
    {
        fprintf(stderr, "Error usage of LogSub : x(%lf) < y(%lf).\n", x, y);
        abort();
    }
    double diff = y - x;
    if (diff < MINLOGEXP)
    {
        return  (x < LSMALL) ? LZERO : x;
    }
    else
    {
        double z = 1.0 - exp(diff);
        return (z < MINLARG) ? LZERO : x + log(z);
    }
}