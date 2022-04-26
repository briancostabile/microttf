/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_LOG_H
#define UTTF_LOG_H

#include <stdio.h>

#define UTTF_LOG_LEVEL_NONE 0
#define UTTF_LOG_LEVEL_ERR  1
#define UTTF_LOG_LEVEL_WARN 2
#define UTTF_LOG_LEVEL_INFO 3

#ifndef UTTF_LOG_LEVEL
#define UTTF_LOG_LEVEL UTTF_LOG_LEVEL_INFO
#endif

#if (UTTF_LOG_LEVEL >= UTTF_LOG_LEVEL_INFO)
#define UTTF_LOG_INFO( ... ) printf( __VA_ARGS__ )
#else
#define UTTF_LOG_INFO( ... )
#endif

#if (UTTF_LOG_LEVEL >= UTTF_LOG_LEVEL_WARN)
#define UTTF_LOG_WARN( ... ) printf( __VA_ARGS__ )
#else
#define UTTF_LOG_WARN( ... )
#endif

#if (UTTF_LOG_LEVEL >= UTTF_LOG_LEVEL_ERR)
#define UTTF_LOG_ERR( ... ) printf( __VA_ARGS__ )
#else
#define UTTF_LOG_ERR( ... )
#endif

#endif
