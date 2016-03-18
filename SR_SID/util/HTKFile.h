/**********************************************************************************************//**
 * @file		HTKFile.h
 * @brief		加载及保存 HTK 格式的文件.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/7/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/ /
#pragma once
#include <cstdio>
#include <string>
#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include <armadillo>
#pragma warning(pop)
 using namespace std;
 using namespace arma;

 /**********************************************************************************************//**
  * @struct  HTKHeader
  * @brief   HTK 文件头.
  **************************************************************************************************/
 struct HTKHeader
 {
     /** @brief   样点数. */
     unsigned int    nsamples;
     /** @brief   采样周期. */
     unsigned int    sampperiod;
     /** @brief   采样点大小, 字节数. */
     short	        sampsize;
     /** @brief   参数类型. */
     short	        paramkind;
 };

 /**********************************************************************************************//**
  * @fn      inline void swap4b(void *t);
  * @brief   交换字节顺序(4个字节)
  * @param [in,out]  t   待处理数据.
  * @note    不检查 t 是否为空指针.
  **************************************************************************************************/
 inline void swap4b(void *t)
 {
     char *p = (char *)t;
     char c;
     c = p[0]; p[0] = p[3]; p[3] = c;
     c = p[1]; p[1] = p[2]; p[2] = c;
 }

 /**********************************************************************************************//**
  * @fn      inline void swap2b(void *t);
  * @brief   交换字节顺序(2个字节)
  * @param [in,out]  t   待处理数据.
  * @note    不检查 t 是否为空指针.
  **************************************************************************************************/
 inline void swap2b(void *t)
 {
     char *p = (char *)t;
     char c;
     c = p[0]; p[0] = p[1]; p[1] = c;
 }

 /**********************************************************************************************//**
  * @fn      inline bool LoadHTKFile(const string &fpath, HTKHeader &head, fmat &buf);
  * @brief   加载 HTK 文件.
  * @return  成功返回 true, 失败返回 false.
  * @param [in]      fpath   文件路径.
  * @param [in,out]  head    文件头.
  * @param [in,out]  buf     矩阵.
  **************************************************************************************************/
 inline bool LoadHTKFile(const string &fpath, HTKHeader &head, fmat &buf)
 {
     ifstream ifs(fpath.c_str(), ifstream::binary);
     if (!ifs)
     {
         fprintf(stderr, "Cannot open(rb) HTK file : \"%s\".\n", fpath.c_str());
         return false;
     }
     if (!ifs.read((char *)&head, sizeof(HTKHeader)))
     {
         fprintf(stderr, "Invalid HTK file : \"%s\".\n", fpath.c_str());
         ifs.close();
         return false;
     }
     swap4b(&head.nsamples);
     swap4b(&head.sampperiod);
     swap2b(&head.sampsize);
     swap2b(&head.paramkind);
     buf = zeros<fmat>(head.sampsize / sizeof(float), head.nsamples);
     if (!ifs.read((char *)buf.memptr(), head.nsamples * head.sampsize))
     {
         fprintf(stderr, "Invalid HTK file : \"%s\".\n", fpath.c_str());
         ifs.close();
         return false;
     }
     ifs.close();
     for (uword i = 0; i < buf.n_elem; i++)
     {
         swap4b(&buf(i));
     }
     return true;
 }

 /**********************************************************************************************//**
  * @fn      inline bool SaveHTKFile(const string &fpath, const HTKHeader &head, const fmat &buf);
  * @brief   保存为 HTK 文件.
  * @return  成功返回 true, 失败返回 false.
  * @param [in]  fpath   文件路径.
  * @param [in]  head    文件头.
  * @param [in]  buf     矩阵.
  **************************************************************************************************/
 inline bool SaveHTKFile(const string &fpath, const HTKHeader &head, const fmat &buf)
 {
     if ((buf.n_cols != head.nsamples) || (buf.n_rows * sizeof(float) != head.sampsize))
     {
         fprintf(stderr, "HTK header does not match with buffer : \"%s\".\n", fpath.c_str());
         return false;
     }
     ofstream ofs(fpath.c_str(), ofstream::binary);
     if (!ofs)
     {
         fprintf(stderr, "Cannot open(wb) HTK file : \"%s\".\n", fpath.c_str());
         return false;
     }

     fmat tmpbuf = buf;
     for (uword i = 0; i < tmpbuf.n_elem; i++)
     {
         swap4b(&tmpbuf(i));
     }
     HTKHeader tmphead;
     memcpy(&tmphead, &head, sizeof(HTKHeader));
     swap4b(&tmphead.nsamples);
     swap4b(&tmphead.sampperiod);
     swap2b(&tmphead.sampsize);
     swap2b(&tmphead.paramkind);

     if (!ofs.write((char *)&tmphead, sizeof(HTKHeader)) ||
         !ofs.write((char *)tmpbuf.memptr(), head.nsamples * head.sampsize))
     {
         fprintf(stderr, "Error writing HTK file : \"%s\".\n", fpath.c_str());
         ofs.close();
         remove(fpath.c_str());
         return false;
     }
     ofs.close();
     return true;
 }