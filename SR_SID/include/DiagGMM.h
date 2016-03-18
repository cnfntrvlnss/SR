/**********************************************************************************************//**
 * @file		DiagGMM.h
 * @brief		对角型混合高斯模型.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		6/26/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#pragma once
#include "feat.h"
#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include <armadillo>
#pragma warning(pop)
using namespace arma;

/**********************************************************************************************//**
 * @class   DiagGMM
 * @brief   对角型混合高斯模型.
 **************************************************************************************************/
class DiagGMM
{
public:
    friend class DiagStat2;
    friend class DiagStat3;
    friend bool ScoreOnUBM(const DiagGMM &ubm, const DiagGMM &gmm, const float *featbuf, const FeatInfo &featinfo, float &score, unsigned int topmix);

public:
    /**********************************************************************************************//**
     * @fn      DiagGMM::DiagGMM();
     * @brief   默认构造函数.
     **************************************************************************************************/
    DiagGMM();

    /**********************************************************************************************//**
     * @fn      DiagGMM::DiagGMM(const DiagGMM &gmm);
     * @brief   复制构造函数.
     * @param [in]   gmm     混合高斯模型.
     **************************************************************************************************/
    DiagGMM(const DiagGMM &gmm);

    /**********************************************************************************************//**
     * @fn      DiagGMM::~DiagGMM();
     * @brief   析构函数.
     **************************************************************************************************/
    ~DiagGMM();

    /**********************************************************************************************//**
     * @fn      DiagGMM & DiagGMM::operator=(const DiagGMM &gmm);
     * @brief   重载赋值操作符.
     * @param   gmm     混合高斯模型.
     **************************************************************************************************/
    DiagGMM & operator=(const DiagGMM &gmm);

    /**********************************************************************************************//**
     * @fn      bool DiagGMM::Load(const char *modelpath);
     * @brief   加载模型.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]   modelpath   模型路径.
     * @note	导致失败的原因可能有: 1. 模型路径不对; 2. 错误模型; 3. 内存不足.
     **************************************************************************************************/
    bool Load(const char *modelpath);

    /**********************************************************************************************//**
     * @fn      bool DiagGMM::Save(const char *modelpath) const;
     * @brief   保存模型.
     * @return	成功返回 true, 失败返回 false.
     * @param   modelpath   模型路径.
     * @note    导致失败的原因可能有: 1. 模型路径不对; 2. 内存不足.
     **************************************************************************************************/
    bool Save(const char *modelpath) const;

    /**********************************************************************************************//**
     * @fn      bool DiagGMM::Initialze(unsigned int dim, unsigned int mix, const float *weights, const float *means, const float *variances);
     * @brief   指定权重, 均值, 方差初始化.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]   dim         维数.
     * @param [in]   mix         混合数.
     * @param [in]   weights     权重.
     * @param [in]   means       均值.
     * @param [in]   variances   (对角)协方差.
     * @note    该函数不能与 @ref Load 重复使用.
     **************************************************************************************************/
    bool Initialze(unsigned int dim, unsigned int mix, const float *weights, const float *means, const float *variances);

    /**********************************************************************************************//**
     * @fn      bool DiagGMM::MAPAdapt(const float *featbuf, const FeatInfo &featinfo, float meanfactor, float occfloor, float iterfactor) const;
     * @brief   最大后验自适应.
     * @return	成功返回 true, 失败返回 false.
     * @param [in]   featbuf     特征内存.
     * @param [in]   featinfo    特征信息.
     * @param [in]   meanfactor  自适应因子.
     * @param [in]   occfloor    更新大于门限的高斯分量.
     * @param [in]   iterfactor  控制说话人自适应迭代次数.
     **************************************************************************************************/
    bool MAPAdapt(const float *featbuf, const FeatInfo &featinfo, float meanfactor, float occfloor, float iterfactor) const;

    /**********************************************************************************************//**
     * @fn      bool DiagGMM::LogLikelihood(const float *featbuf, const FeatInfo &featinfo, float *aveprob) const;
     * @brief   计算平均对数似然.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]      featbuf     特征缓冲区.
     * @param [in]      featinfo    特征信息.
     * @param [in,out]  aveprob     平均对数似然
     * @note    如果 aveprob == NULL, 则不计算.
     **************************************************************************************************/
    bool LogLikelihood(const float *featbuf, const FeatInfo &featinfo, float *aveprob) const;

    /**********************************************************************************************//**
     * @fn      float DiagGMM::ModelDist(const float *SV1, const float *SV2) const;
     * @brief   计算两个高斯超矢量的距离.
     * @return  距离.
     * @param [in]  SV1     高斯超矢量 1.
     * @param [in]  SV2     高斯超矢量 2.
     * @note    不检查 SV1 和 SV2 是否为空.
     **************************************************************************************************/
    float ModelDist(const float *SV1, const float *SV2) const;

    /**********************************************************************************************//**
     * @fn      bool DiagGMM::ComputePos(const float *featbuf, const FeatInfo &featinfo, fmat &pos) const;
     * @brief   计算在混合高斯模型上的后验概率.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]      featbuf     特征内存.
     * @param [in]      featinfo    特征信息.
     * @param [in,out]  pos         后验概率.
     **************************************************************************************************/
    bool ComputePos(const float *featbuf, const FeatInfo &featinfo, fmat &pos) const;

    /**********************************************************************************************//**
     * @fn      unsigned int DiagGMM::GetMixNum() const
     * @brief   获取混合高斯模型的高斯数目.
     * @return  高斯数目.
     **************************************************************************************************/
    unsigned int GetMixNum() const { return m_mix; };

    /**********************************************************************************************//**
     * @fn      unsigned int DiagGMM::GetFeatDim() const
     * @brief   获取训练混合高斯模型所使用的特征的维数.
     * @return  特征的维数.
     **************************************************************************************************/
    unsigned int GetFeatDim() const { return m_dim; };

    /**********************************************************************************************//**
     * @fn      unsigned int DiagGMM::GetFeatKind() const
     * @brief   获取训练混合高斯模型所使用的特征的类型.
     * @return  特征的类型.
     **************************************************************************************************/
    unsigned int GetFeatKind() const { return m_featkind; };

    /**********************************************************************************************//**
     * @fn      float* DiagGMM::GetWeights()
     * @brief   获取权重首地址.
     * @return  成功返回权重首地址, 失败返回 NULL.
     **************************************************************************************************/
    float * GetWeights() { return m_weights; };

    /**********************************************************************************************//**
     * @copydoc GetWeights()
     **************************************************************************************************/
    const float * GetWeights() const { return m_weights; };

    /**********************************************************************************************//**
     * @fn      float* DiagGMM::GetMeans()
     * @brief   获取均值首地址.
     * @return  成功返回均值首地址, 失败返回 NULL.
     **************************************************************************************************/
    float * GetMeans() { return m_mus; };

    /**********************************************************************************************//**
     * @copydoc GetMeans()
     **************************************************************************************************/
    const float * GetMeans() const { return m_mus; };

    /**********************************************************************************************//**
     * @fn      float* DiagGMM::GetVars()
     * @brief   获取协方差的逆首地址.
     * @return  成功返回协方差的逆首地址, 失败返回 NULL.
     **************************************************************************************************/
    float * GetVars() { return m_vars; };

    /**********************************************************************************************//**
     @copydoc GetVars()
     **************************************************************************************************/
    const float * GetVars() const { return m_vars; };

    /**********************************************************************************************//**
     * @fn      float* DiagGMM::GetDMats()
     * @brief   获取常量首地址.
     * @return  成功返回常量首地址, 失败返回 NULL.
     **************************************************************************************************/
    float * GetDMats() { return m_dmats; };

    /**********************************************************************************************//**
     @copydoc GetDMats()
     **************************************************************************************************/
    const float * GetDMats() const { return m_dmats; };

protected:
    /** @brief	权重. */
    float *         m_weights;
    /** @brief	均值. */
    float *         m_mus;
    /** @brief	协方差的逆. */
    float *         m_vars;
    /** @brief	常量, 加速. */
    float *         m_dmats;
    /** @brief	维数. */
    unsigned int    m_dim;
    /** @brief	混合数. */
    unsigned int    m_mix;
    /** @brief	特征类型. */
    unsigned int    m_featkind;
};

/**********************************************************************************************//**
 * @fn      bool ScoreOnUBM(const DiagGMM &ubm, const DiagGMM &gmm, const float *featbuf, const FeatInfo &featinfo, float &score, unsigned int topmix = 4);
 * @brief   基于混合高斯-通用背景模型的得分计算方法.
 * @return  成功返回 true, 失败返回 false.
 * @param [in]      ubm             混合高斯-通用背景模型.
 * @param [in]      gmm             特定混合高斯模型.
 * @param [in]      featbuf         特征缓冲区.
 * @param [in]      featinfo        特征信息.
 * @param [in,out]  score           得分.
 * @param [in]      tommix          选取似然值最大的高斯数目
 * @note    ubm 和 gmm 两个模型必须一致(如维数, 混合数必须相等).
 **************************************************************************************************/
bool ScoreOnUBM(const DiagGMM &ubm, const DiagGMM &gmm, const float *featbuf, const FeatInfo &featinfo, float &score, unsigned int topmix = 4);

/**********************************************************************************************//**
 * @class   NormGaussSV
 * @brief   对混合高斯超向量规整.
 **************************************************************************************************/
class NormGaussSV
{
public:
    /**********************************************************************************************//**
     * @fn      NormGaussSV::NormGaussSV(const DiagGMM &gmm);
     * @brief   构造函数.
     * @param [in]  gmm     混合高斯模型.
     * @note    请确保混合高斯模型的有效性.
     **************************************************************************************************/
    NormGaussSV(const DiagGMM &gmm);

    /**********************************************************************************************//**
     * @fn      NormGaussSV::~NormGaussSV();
     * @brief   析构函数.
     **************************************************************************************************/
    ~NormGaussSV();

    /**********************************************************************************************//**
     * @fn      void NormGaussSV::DoNorm(float *svec);
     * @brief   执行规整操作.
     * @param [in,out]  svec    混合高斯超向量.
     * @note    不检查 svec 是否为空指针和其长度
     **************************************************************************************************/
    void DoNorm(float *svec);

private:
    /**********************************************************************************************//**
     * @fn      NormGaussSV::NormGaussSV(const NormGaussSV &ngsv);
     * @brief   禁用复制构造函数.
     * @param [in]   ngsv    规整对象.
     **************************************************************************************************/
    NormGaussSV(const NormGaussSV &ngsv);

    /**********************************************************************************************//**
     * @fn      NormGaussSV & NormGaussSV::operator=(const NormGaussSV &ngsv);
     * @brief   禁用赋值操作符.
     * @return  该对象的一份浅拷贝
     * @param [in]  ngsv    规整对象.
     **************************************************************************************************/
    NormGaussSV & operator=(const NormGaussSV &ngsv);

private:
    /** @brief   维数. */
    unsigned int    m_dim;
    /** @brief   混合数. */
    unsigned int    m_mix;
    /** @brief   使用权重和方差规整(from MIT). */
    float *		    m_w_var;
};

/**********************************************************************************************//**
 * @class   DiagStat2
 * @brief   计算对角型混合高斯模型统计量.
 * @note    计算零阶, 一阶统计量.
 **************************************************************************************************/
class DiagStat2
{
public:
    /**********************************************************************************************//**
     * @fn      DiagStat2::DiagStat2();
     * @brief   默认构造函数.
     **************************************************************************************************/
    DiagStat2();

    /**********************************************************************************************//**
     * @fn      DiagStat2::DiagStat2(const DiagGMM *dgmm);
     * @brief   构造函数.
     * @param [in]   dgmm    混合高斯模型.
     * @note    给定混合高斯模型, 进行初始化.
     **************************************************************************************************/
    DiagStat2(const DiagGMM *dgmm);

    /**********************************************************************************************//**
     * @fn      bool DiagStat2::Compute(const float *featbuf, const FeatInfo &featinfo, float *aveprob);
     * @brief   计算混合高斯模型统计量.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]      featbuf     特征缓冲区.
     * @param [in]      featinfo    特征信息.
     * @parma [in,out]  aveprob     平均对数似然
     * @note    1. 结果存放到 @ref N 和 @ref F 两个变量中. 2. 如果 aveprob == NULL, 则不计算.
     **************************************************************************************************/
    bool Compute(const float *featbuf, const FeatInfo &featinfo, float *aveprob);

    /**********************************************************************************************//**
     * @fn      void DiagStat2::Centralize;
     * @brief   中心归一化.
     * @note    1. 变量 @ref F 的值会改变. 2. 调用 @ref Compute 成功后, 调用该函数才有意义.
     **************************************************************************************************/
    void Centralize();

    /**********************************************************************************************//**
     * @fn      bool DiagStat2::Load(const char *fpath);
     * @brief   加载统计量.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]   fpath   统计量路径.
     **************************************************************************************************/
    bool Load(const char *fpath);

    /**********************************************************************************************//**
     * @fn      bool DiagStat2::Save(const char *fpath) const;
     * @brief   保存统计量.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]   fpath   统计量路径.
     **************************************************************************************************/
    bool Save(const char *fpath) const;

    /** @brief   零阶统计量. */
    fvec        N;
    /** @brief   一阶统计量. */
    fmat        F;

private:
    /** @brief   混合高斯模型(指向). */
    const DiagGMM *   m_dgmm;
};

/**********************************************************************************************//**
 * @class   DiagStat3
 * @brief   计算对角型混合高斯模型统计量.
 * @note    计算零阶, 一阶, 二阶统计量.
 **************************************************************************************************/
class DiagStat3
{
public:
    /**********************************************************************************************//**
     * @fn      friend DiagStat3 DiagStat3::operator+(const DiagStat3 &obj1, const DiagStat3 &obj2);
     * @brief   重载 "+" 操作符.
     * @return  相加后的结果.
     * @param [in]  obj1    统计量一.
     * @param [in]  obj2    统计量二.
     **************************************************************************************************/
    friend DiagStat3 operator+(const DiagStat3 &obj1, const DiagStat3 &obj2);

public:
    /**********************************************************************************************//**
     * @fn      DiagStat3::DiagStat3();
     * @brief   默认构造函数.
     **************************************************************************************************/
    DiagStat3();

    /**********************************************************************************************//**
     * @fn      DiagStat3::DiagStat3(const DiagGMM *dgmm);
     * @brief   构造函数.
     * @param [in]   dgmm    混合高斯模型.
     * @note    给定混合高斯模型, 进行初始化.
     **************************************************************************************************/
    DiagStat3(const DiagGMM *dgmm);

    /**********************************************************************************************//**
     * @fn      DiagStat3 & DiagStat3::operator+=(const DiagStat3 &obj)
     * @brief   重载 "+=" 运算符.
     * @return  相加后的结果.
     * @param [in]   obj    统计量.
     **************************************************************************************************/
    DiagStat3 & operator+=(const DiagStat3 &obj){
        N += obj.N;
        F += obj.F;
        S += obj.S;
        return *this;
    };

    /**********************************************************************************************//**
     * @fn      bool DiagStat3::Compute(const float *featbuf, const FeatInfo &featinfo, float *aveprob);
     * @brief   计算混合高斯模型统计量.
     * @return  成功返回在该模型上的平均似然, 失败返回 FLT_MIN.
     * @param [in]  featbuf     特征缓冲区.
     * @param [in]  featinfo    特征信息.
     * @parma [in,out]  aveprob     平均对数似然
     * @note    1. 结果存放到 @ref N, @ref F 和 @ref S 三个变量中. 2. 如果 aveprob == NULL, 则不计算.
     **************************************************************************************************/
    bool Compute(const float *featbuf, const FeatInfo &featinfo, float *aveprob);

    /**********************************************************************************************//**
     * @fn      bool DiagStat3::Load(const char *fpath);
     * @brief   加载统计量.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]   fpath   统计量路径.
     **************************************************************************************************/
    bool Load(const char *fpath);

    /**********************************************************************************************//**
     * @fn      bool DiagStat3::Save(const char *fpath) const;
     * @brief   保存统计量.
     * @return  成功返回 true, 失败返回 false.
     * @param [in]   fpath   统计量路径.
     **************************************************************************************************/
    bool Save(const char *fpath) const;

    /** @brief   零阶统计量. */
    fvec        N;
    /** @brief   一阶统计量. */
    fmat        F;
    /** @brief   二阶统计量. */
    fmat        S;

private:
    /** @brief   混合高斯模型(指向). */
    const DiagGMM *   m_dgmm;
};