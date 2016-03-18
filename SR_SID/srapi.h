/**********************************************************************************************//**
 * @file		srapi.h
 * @brief		说话人识别引擎接口.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/28/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#include "def.h"

/**********************************************************************************************//**
 * @struct  SRConfig
 * @brief   说话人引擎配置参数.
 * @note    返回给调用者使用.
 **************************************************************************************************/
typedef struct
{
    /** @brief   模型大小. */
    unsigned int    modelsize;
    /** @brief   特征大小. */
    unsigned int    featsize;
} SRConfig;

#ifdef __cplusplus
extern "C" {
#endif

    /**********************************************************************************************//**
     * @fn      SDKAPI RetCode TIT_SR_Intialize(const char *syspath, SRConfig &syscfg);
     * @brief	引擎初始化.
     * @return	无法加载配置文件, 返回 StsErrCfgFile.
     * @return  无法读取相应的配置项, 返回 StsErrCfgItem.
     * @return  模型或配置参数有误, 返回 StsErrModel
     * @return  成功初始化, 返回 StsNoErr
     * @param [in]		syspath		引擎路径.
     * @param [in,out]  syscfg		引擎配置.
     * @note	不可多次调用该函数, 否者会造成内存泄露.
     * @note	该函数会占用资源, 需调用 @ref TIT_SR_Unintialize 释放.
     **************************************************************************************************/
    SDKAPI RetCode TIT_SR_Intialize(const char *syspath, SRConfig &syscfg);

    /**********************************************************************************************//**
     * @fn      SDKAPI RetCode TIT_SR_Enroll(const short *wavbuf, unsigned int wavlen, unsigned int smprate, void *model);
     * @brief	注册说话人模型.
     * @return  成功返回 StsNoErr, 失败返回 StsErrModel.
     * @param [in]		wavbuf		音频缓存.
     * @param [in]      wavlen		音频点数.
     * @param [in]      smprate		采样率.
     * @param [in]      model		模型地址.
     * @note	模型内存需要调用者自己开辟.
     **************************************************************************************************/
    SDKAPI RetCode TIT_SR_Enroll(const short *wavbuf, unsigned int wavlen, unsigned int smprate, void *model);

    /**********************************************************************************************//**
     * @fn      SDKAPI RetCode TIT_SR_ExFeat(const short *wavbuf, unsigned int wavlen, unsigned int smprate, void *feat);
     * @brief	提取特征, 用于建索引, 历史检索.
     * @return  成功返回 StsNoErr, 失败返回 StsErrModel.
     * @param [in]		wavbuf		音频缓存.
     * @param [in]      wavlen		音频点数.
     * @param [in]      smprate		采样率.
     * @param [in]      feat		特征地址.
     * @note	特征内存需要调用者自己开辟.
     **************************************************************************************************/
    SDKAPI RetCode TIT_SR_ExFeat(const short *wavbuf, unsigned int wavlen, unsigned int smprate, void *feat);

    /**********************************************************************************************//**
     * @fn      SDKAPI RetCode TIT_SR_Match(const void *feat, const void *model, float *score);
     * @brief	计算特征和模型间的相似度.
     * @return  成功, 返回 StsNoErr.
     * @return  无效输入, 返回 StsNullPtr.
     * @param [in]		feat		特征地址.
     * @param [in]      model		模型地址.
     * @param [in,out]  score		相似度.
     * @note	得分 score 的值越大, 相似度越高.
     **************************************************************************************************/
    SDKAPI RetCode TIT_SR_Match(const void *feat, const void *model, float *score);

    /**********************************************************************************************//**
     * @fn      SDKAPI RetCode TIT_SR_Unintialize();
     * @brief	结束, 释放资源.
     * @return  成功, 永远返回 StsNoErr.
    **************************************************************************************************/
    SDKAPI RetCode TIT_SR_Unintialize();

#ifdef __cplusplus
}
#endif