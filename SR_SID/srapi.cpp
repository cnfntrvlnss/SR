/**********************************************************************************************//**
 * @file		srapi.h
 * @brief		说话人识别引擎接口.
 * @author		许云飞 (kindapple@163.com)
 * @version		1.0
 * @date		7/28/2015
 * @copyright	2010-2015 中国科学院声学研究所语言声学与内容理解重点实验室
 **************************************************************************************************/
#define EXPORT_SDKAPI
#include "srapi.h"
#include "MFCC.h"
#include "DiagGMM.h"
#include "IVec.h"
#include "gplda.h"
#include "cfg.h"
#include "file.h"

static MFCC *g_feat = NULL;
static DiagGMM *g_UBM = NULL;
static IVector *g_T = NULL;
static GaussPLDA *g_PLDA = NULL;
static unsigned int g_t_rank = 0;

#ifdef __cplusplus
//extern "C" {
#endif

    SDKAPI RetCode TIT_SR_Intialize(const char *syspath, SRConfig &syscfg)
    {
        // 加载配置文件
        Config cfg;
        if (!cfg.Load(JoinPath(syspath, "SpkAPI.cfg")))
        {
            return StsErrCfgFile;
        }

        // 特征
        CfgMFCC cfgfeat;
        if (!cfg.Get("MFCC", "SampleRate", cfgfeat.samplerate) ||
            !cfg.Get("MFCC", "FeatType", cfgfeat.feattype) ||
            !cfg.Get("MFCC", "FrameSize", cfgfeat.framesize) ||
            !cfg.Get("MFCC", "FrameRate", cfgfeat.framerate) ||
            !cfg.Get("MFCC", "ZeroGlobalMean", cfgfeat.removedc) ||
            !cfg.Get("MFCC", "CepLifter", cfgfeat.ceplifter) ||
            !cfg.Get("MFCC", "ChannelNum", cfgfeat.chlnum) ||
            !cfg.Get("MFCC", "CepNum", cfgfeat.cepnum) ||
            !cfg.Get("MFCC", "LowPass", cfgfeat.lowpass) ||
            !cfg.Get("MFCC", "HighPass", cfgfeat.highpass) ||
            !cfg.Get("MFCC", "NormEnergy", cfgfeat.normenergy) ||
            !cfg.Get("MFCC", "EnergyScale", cfgfeat.energyscale) ||
            !cfg.Get("MFCC", "SilFloor", cfgfeat.silfloor) ||
            !cfg.Get("MFCC", "DoCMN", cfgfeat.docmn) ||
            !cfg.Get("MFCC", "DoCVN", cfgfeat.docvn) ||
            !cfg.Get("MFCC", "DoRASTA", cfgfeat.dorasta))
        {
            return StsErrCfgItem;
        }
        g_feat = new MFCC();
        if (!g_feat->Initialize(cfgfeat))
        {
            delete g_feat; g_feat = NULL;
            return StsErrModel;
        }

        unsigned int featdim, mixnum, trank;

        // 混合高斯-通用背景模型
        string ubmfile;
        if (!cfg.Get("Model", "UBMModel", ubmfile) ||
            !cfg.Get("Model", "FeatDim", featdim) ||
            !cfg.Get("Model", "MixNum", mixnum))
        {
            delete g_feat; g_feat = NULL;
            return StsErrCfgItem;
        }
        g_UBM = new DiagGMM();
        if (!g_UBM->Load(ubmfile.c_str()))
        {
            delete g_feat; g_feat = NULL;
            delete g_UBM; g_UBM = NULL;
            return StsErrModel;
        }
        if ((g_UBM->GetFeatDim() != featdim) || (g_UBM->GetMixNum() != mixnum))
        {
            fprintf(stderr, "Information of UBM is wrong : FeatDim(%d != %d), MixNum(%d, %d).\n", g_UBM->GetFeatDim(), featdim, g_UBM->GetMixNum(), mixnum);
            delete g_feat; g_feat = NULL;
            delete g_UBM; g_UBM = NULL;
            return StsErrModel;
        }

        // 总变化因子 T 模型
        string tfile;
        if (!cfg.Get("Model", "TModel", tfile) ||
            !cfg.Get("Model", "TRank", trank))
        {
            delete g_feat; g_feat = NULL;
            delete g_UBM; g_UBM = NULL;
            return StsErrCfgItem;
        }
        g_T = new IVector(g_UBM);
        if (!g_T->Load(tfile.c_str()))
        {
            delete g_feat; g_feat = NULL;
            delete g_UBM; g_UBM = NULL;
            delete g_T; g_T = NULL;
            return StsErrModel;
        }

        // Gaussian PLDA 模型
        string pldafile;
        if (!cfg.Get("Model", "PLDAModel", pldafile))
        {
            delete g_feat; g_feat = NULL;
            delete g_UBM; g_UBM = NULL;
            delete g_T; g_T = NULL;
            return StsErrCfgItem;
        }
        g_PLDA = new GaussPLDA();
        if (!g_PLDA->Load(pldafile.c_str()))
        {
            delete g_feat; g_feat = NULL;
            delete g_UBM; g_UBM = NULL;
            delete g_T; g_T = NULL;
            delete g_PLDA; g_PLDA = NULL;
            return StsErrModel;
        }

        syscfg.modelsize = syscfg.featsize = sizeof(float) * (trank + 1);
        g_t_rank = trank;
        return StsNoErr;
    }

    SDKAPI RetCode TIT_SR_Enroll(const short *wavbuf, unsigned int wavlen, unsigned int smprate, void *model)
    {
        // 提取特征
        float *featbuf; FeatInfo featinfo;
        if (!g_feat->DoExtract(wavbuf, wavlen, smprate, featbuf, featinfo))
        {
            return StsErrModel;
        }

        // 计算统计量
        DiagStat2 dstat(g_UBM);
        if (!dstat.Compute(featbuf, featinfo, NULL))
        {
            FreeFeat(featbuf);
            return StsErrModel;
        }
        FreeFeat(featbuf);
        dstat.Centralize();     // 需要中心归一化

        // 提取总变化因子
        fvec ivec;
        g_T->Extract(dstat, ivec);
        if (ivec.n_elem != g_t_rank)
        {
            return StsErrModel;
        }

        // 长度规整
        ivec /= norm(ivec, 2);

        // PLDA 注册
        frowvec fmodel((float *)model, ivec.n_elem + 1, false, true);
        if (!g_PLDA->Enroll(ivec, fmodel))
        {
            return StsErrModel;
        }
        return StsNoErr;
    }

    SDKAPI RetCode TIT_SR_ExFeat(const short *wavbuf, unsigned int wavlen, unsigned int smprate, void *feat)
    {
        // 提取特征
        float *featbuf; FeatInfo featinfo;
        if (!g_feat->DoExtract(wavbuf, wavlen, smprate, featbuf, featinfo))
        {
            return StsErrModel;
        }

        // 计算统计量
        DiagStat2 dstat(g_UBM);
        if (!dstat.Compute(featbuf, featinfo, NULL))
        {
            FreeFeat(featbuf);
            return StsErrModel;
        }
        FreeFeat(featbuf);
        dstat.Centralize();     // 需要中心归一化

        // 提取总变化因子
        fvec ivec;
        g_T->Extract(dstat, ivec);
        if (ivec.n_elem != g_t_rank)
        {
            return StsErrModel;
        }

        // 长度规整
        ivec /= norm(ivec, 2);

        // PLDA 提特征
        fvec ffeat((float *)feat, ivec.n_elem + 1, false, true);
        if (!g_PLDA->ExFeat(ivec, ffeat))
        {
            return StsErrModel;
        }
        return StsNoErr;
    }

    SDKAPI RetCode TIT_SR_Match(const void *feat, const void *model, float *score)
    {
        if ((feat == NULL) || (model == NULL))
        {
            return StsNullPtr;
        }
        fvec ffeat((float *)feat, g_t_rank + 1, false, true);
        frowvec fmodel((float *)model, g_t_rank + 1, false, true);
        *score = g_PLDA->Match(fmodel, ffeat);
        return StsNoErr;
    }

    SDKAPI RetCode TIT_SR_Unintialize()
    {
        if (g_feat != NULL)
        {
            delete g_feat; g_feat = NULL;
        }
        if (g_UBM != NULL)
        {
            delete g_UBM; g_UBM = NULL;
        }
        if (g_T != NULL)
        {
            delete g_T; g_T = NULL;
        }
        if (g_PLDA != NULL)
        {
            delete g_PLDA; g_PLDA = NULL;
        }
        g_t_rank = 0;
        return StsNoErr;
    }

#ifdef __cplusplus
//}
#endif