/** @note   : HangZhou Hikvision Digital Technology Co.,Ltd. All Right Reserved.
 *  @file   : FPModule_SDK.h
 *  @brief  : 指纹采集仪SDK API
 *  @author : heyueming <heyueming@hikvision.com>
 *  @date   : 2017.6.29
 *  @record : 2017.5.9  创建初始版本V1.0.0
              2017.7.10 更新版本为V1.1.0，调整内容如下
                        1、函数命名规则调整为FPModule_XXXXXX()，增加FPModule_函数名称前缀；
                        2、调整录入指纹时的手指按压次数，从4次调整为3~5次；
                        3、增加录入指纹时的消息回调接口 FPModule_InstaltMessageHandler()，用于录入过程中的提示；
                        4、增加设置和获取指纹采集超时和时间接口FPModule_SetTimeout(), FPModule_GetTimeout()；
                        5、调整采集图像接口，增加了两个输出参数，图像宽度和图像高度；
                        6、调整错误代码返回值和对应说明；
              2017.7.14 更新版本为V1.1.1，调整内容如下
                        1、调整录入指纹时的手指按压次数，调整为2~4次；
                        2、增加录入指纹时按手指的灭灯提示
              2017.6.7  更新版本为V1.2.0，调整内容如下
                        1、更新算法库为AS608_FPEngine_vc_20180320.lib
              2018.6.29 更新版本为V2.0.0，调整内容如下
                        1、更新算法库为AS608_FPEngine_vc_20180629.lib
                        2、输出的指纹模板增加末尾2字节校验值
                        3、增加指纹模板比对接口FPModule_MatchTemplate
                        4、调整录入指纹时的手指按压次数，调整为3~4次，优化合成指纹模板策略；
                        5、FPC1011指纹图像拉伸至508DPI时，不再对图像扩充至256x288，使用拉伸后的实际图像大小

 */

#ifndef __HIK_FPMODULE_SDK_H__
#define __HIK_FPMODULE_SDK_H__

/* 函数返回值定义 */
#define FP_SUCCESS              0       // 执行成功
#define FP_CONNECTION_ERR       1       // 通信失败
#define FP_TIMEOUT              2       // 采集超时
#define FP_ENROLL_FAIL          3       // 录入指纹失败
#define FP_PARAM_ERR            4       // 参数错误
#define FP_EXTRACT_FAIL         5       // 提取特征失败
#define FP_MATCH_FAIL           6       // 比对特征失败


/* 消息类型定义 */
typedef enum {
    FP_MSG_PRESS_FINGER,                // 录入指纹 提示按手指
    FP_MSG_RISE_FINGER,                 // 录入指纹 提示抬手指
    FP_MSG_ENROLL_TIME,                 // 录入指纹 次数提示
    FP_MSG_CAPTURED_IMAGE,              // 录入指纹 图像反馈               
}FP_MSG_TYPE_T;

/* 图像反馈数据格式定义*/
typedef struct {
    int dwWidth;
    int dwHeight;
    unsigned char *pbyImage;
}FP_IMAGE_DATA;

/* 消息处理函数定义 */
typedef void (__stdcall *FpMessageHandler)(FP_MSG_TYPE_T enMsgType, void *pMsgData);


/* 兼容老版本接口 */
#define OpenDevice      FPModule_OpenDevice
#define CloseDevice     FPModule_CloseDevice
#define FPEnroll        FPModule_FpEnroll
#define GetQuality      FPModule_GetQuality
#define GetDeviceInfo   FPModule_GetDeviceInfo
#define GetSDKVersion   FPModule_GetSDKVersion


/** @func   : FPModule_OpenDevice
 *  @brief  : 连接设备
 *  @param  : None
 *  @return : 0->连接成功 1->通信失败
 */
int __stdcall FPModule_OpenDevice(void);


/** @func   : FPModule_CloseDevice
 *  @brief  : 断开设备
 *  @param  : None
 *  @return : 0->断开成功 1->通信失败
 */
int __stdcall FPModule_CloseDevice(void);


/** @func   : FPModule_DetectFinger
 *  @brief  : 检测指纹输入状态
 *  @param  : pdwFpstatus[out] -> 0:无指纹输入  1:有指纹输入
 *  @return : 0->执行成功 1->通信失败
 */
int __stdcall FPModule_DetectFinger(int *pdwFpstatus);


/** @func   : FPModule_CaptureImage
 *  @brief  : 采集指纹图像
 *  @param  : pbyImageData[out] -> 指纹图像数据（数据长度为 图像宽度 x 图像高度）
              pdwWidth[out]     -> 指纹图像宽度
              pdwHeight[out]    -> 指纹图像高度
 *  @return : 0->执行成功 1->通信失败
 */
int __stdcall FPModule_CaptureImage(unsigned char *pbyImageData, int *pdwWidth, int *pdwHeight);


/** @func   : FPModule_SetTimeout
 *  @brief  : 设置采集超时时间
 *  @param  : dwSecond[in] -> 超时时间(单位：秒) 可设置值：1秒至60秒
 *  @return : 0->执行成功 1->通信失败 
 */
int __stdcall FPModule_SetTimeout(int dwSecond);


/** @func   : FPModule_GetTimeout
 *  @brief  : 获取采集超时时间
 *  @param  : pdwSecond[out] -> 超时时间 单位：秒
 *  @return : 0->执行成功 1->通信失败 
 */
int __stdcall FPModule_GetTimeout(int *pdwSecond);


/** @func   : FPModule_InstallMessageHandler
 *  @brief  : 设置消息回调函数
 *  @param  : msgHandler[in] -> 消息处理函数
 *  @return : 0->执行成功
 */
int __stdcall FPModule_InstallMessageHandler(FpMessageHandler msgHandler);


/** @func   : FPModule_FpEnroll
 *  @brief  : 录入指纹
 *  @param  : pbyFpTemplate[out] -> 指纹模板(512字节)
 *  @return : 0->执行成功 1->通信失败 2->采集超时 3->录入失败
 */
int __stdcall FPModule_FpEnroll(unsigned char *pbyFpTemplate);


/** @func   : FPModule_GetQuality
 *  @brief  : 获取指纹模板质量分数
 *  @param  : pbyFpTemplate[in] -> 指纹模板(512字节)
 *  @return : 指纹模板分数(0~100) 分数越高，表示模板的质量越好
 */
int __stdcall FPModule_GetQuality(unsigned char *pbyFpTemplate);


/** @func   : FPModule_MatchTemplate
 *  @brief  : 比对两枚指纹模板
 *  @param  : pbyFpTemplate1[in] -> 指纹模板1(512字节)
              pbyFpTemplate2[in] -> 指纹模板2(512字节)
              dwSecurityLevel[in] -> 安全等级（1~5）
 *  @return : 0->比对成功 6->比对失败 4->参数错误
 */
int __stdcall FPModule_MatchTemplate(unsigned char *pbyFpTemplate1, unsigned char *pbyFpTemplate2, int dwSecurityLevel);


/** @func   : FPModule_GetDeviceInfo
 *  @brief  : 获取指纹采集仪版本信息
 *  @param  : pbyDeviceInfo[out] -> 指纹采集仪版本信息(64字节)
 *  @return : 0->执行成功 1->通信失败 
 */
int __stdcall FPModule_GetDeviceInfo(char *pbyDeviceInfo);


/** @func   : FPModule_GetSDKVersion
 *  @brief  : 获取指纹采集仪SDK版本信息
 *  @param  : pbySDKVersion[out] -> 指纹采集仪SDK版本信息(64字节)
 *  @return : 0->执行成功
 */
int __stdcall FPModule_GetSDKVersion(char *pbySDKVersion);


#endif
