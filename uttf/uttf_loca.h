/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_LOCA_H
#define UTTF_LOCA_H

#include <stdint.h>
#include "uttf_system.h"

typedef uint32_t Uttf_Loca_LongElement_t;
typedef uint16_t Uttf_Loca_ShortElement_t;

typedef enum Uttf_Loca_format_e
{
    UTTF_LOCA_FORMAT_SHORT = 0,
    UTTF_LOCA_FORMAT_LONG  = 1
} Uttf_Loca_format_t;

typedef struct {
    uint16_t* locaShortPtr;
    uint32_t* locaLongPtr;
} Uttf_Loca_Info_t;

/*****************************************************************************/
Uttf_Status_t
uttf_Loca_GlyphOffsetGet( Uttf_Loca_Info_t* info_ptr,
                          Uttf_GlyphIdx_t   idx,
                          uint32_t*         offset_ptr );

/*****************************************************************************/
Uttf_Status_t
uttf_Loca_Open( void*              table_ptr,
                uint32_t           table_len,
                Uttf_Loca_Info_t*  info_ptr,
                Uttf_Loca_format_t format );
#endif
