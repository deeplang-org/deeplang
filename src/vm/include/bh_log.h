/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */
/**
 * @file   bh_log.h
 * @date   Tue Nov  8 18:19:10 2011
 *
 * @brief This log system supports wrapping multiple outputs into one
 * log message.  This is useful for outputting variable-length logs
 * without additional memory overhead (the buffer for concatenating
 * the message), e.g. exception stack trace, which cannot be printed
 * by a single log calling without the help of an additional buffer.
 * Avoiding additional memory buffer is useful for resource-constraint
 * systems.  It can minimize the impact of log system on applications
 * and logs can be printed even when no enough memory is available.
 * Functions with prefix "_" are private functions.  Only macros that
 * are not start with "_" are exposed and can be used.
 */

#ifndef _BH_LOG_H
#define _BH_LOG_H

#include "bh_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

void log_printf (const char* pFileName, unsigned int uiLine, const char* pFuncName,char *LogFmtBuf, ...);
void log_data(const char *pFileName, unsigned int uiLine, const char* pFuncName, const char *pcStr,unsigned char *pucBuf,unsigned int usLen);


#define debug(...) 							log_printf(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__)
#define dump(pcStr,pucBuf,usLen)			log_data(__FILE__, __LINE__,__FUNCTION__,pcStr,pucBuf,usLen)
#define LOG_FATAL(...)   					log_printf(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__)
#define LOG_ERROR(...)   					log_printf(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__)
#define LOG_WARNING(...) 					log_printf(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__)
#define LOG_DEBUG(...)						//log_printf(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__)
#define LOG_VERBOSE(...) 					//log_printf(__FILE__, __LINE__,__FUNCTION__,__VA_ARGS__)



#ifdef __cplusplus
}
#endif

#endif  /* _BH_LOG_H */
