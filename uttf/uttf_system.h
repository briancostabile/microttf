/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_SYSTEM_H
#define UTTF_SYSTEM_H

#include "uttf_log.h"

typedef enum {
    UTTF_STATUS_FAILURE  = -1,
    UTTF_STATUS_NO_ERROR = 0
} Uttf_Status_t;

typedef uint32_t Uttf_CharCode_t;
typedef uint32_t Uttf_GlyphIdx_t;


#define PACKED_STRUCT( _name ) struct __attribute__ ((__packed__)) _name
#define PACKED_UNION( _name ) union __attribute__ ((__packed__)) _name
#define UTTF_ASSERT( _cond ) if(!(_cond)){ UTTF_LOG_ERR("Assert:%s\n", #_cond); }
#define UTTF_ARRAY_CNT( _a ) (sizeof((_a))/(sizeof((_a)[0])))
#endif
