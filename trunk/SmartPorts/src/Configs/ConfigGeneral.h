/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
/*
 * ConfigGeneral.h - _explain_
 *
 * Copyright (C) 2011 ezlibs.com, All Rights Reserved.
 *
 * $Id: ConfigGeneral.h 5884 2012-07-02 09:15:15Z WuJunjie $
 *
 *  Explain:
 *     -explain-
 *
 *  Update:
 *     2012-06-25 10:17:36
 */
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
#ifndef __CONFIGGENERAL_H__
#define __CONFIGGENERAL_H__

#include "ConfigBase.h"
//!	普通配置
typedef struct tagCONFIG_GENERAL
{
    int iLocalNo;
    std::string  strMachineName; // 机器名，用户可修改  建议 长度为1-256之间
    std::string strProductID; // 用户自定义产品id
    std::string strVendor;
    std::string strSerialNumber; // 产品序列号， 一般厂商定
    std::string strIEEI; //
    std::string strVersion;// 

    // log
    // 日志文件路径
    std::string strLogFilePath;
    // 日志文件名 如果长度为0， 则输出到屏幕
    std::string strLogFileName;
    int maxFileSize;
    int maxBackupIndex;

    int iLanguage;
    int iLanguageSupport;

    int iTimeZone;
    int iDateTimeFormat;
}
CONFIG_GENERAL;

//1 -结构数目
//4 -观察者最大数目
typedef TConfig<CONFIG_GENERAL, 1, 4> CConfigGeneral;

#endif //__CONFIGGENERAL_H__
