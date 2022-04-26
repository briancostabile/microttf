/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "uttf.h"
#include "uttf_loca.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Loca_GlyphOffsetGet( Uttf_Loca_Info_t* info_ptr,
                          Uttf_GlyphIdx_t   idx,
                          uint32_t*         offset_ptr )
{
    *offset_ptr = 0;
    
    if( info_ptr->locaShortPtr != NULL )
    {
        *offset_ptr = (UTTF_BE16TOH(info_ptr->locaShortPtr[idx]) * 2);
    }
    else if( info_ptr->locaLongPtr != NULL )
    {
        *offset_ptr = UTTF_BE32TOH(info_ptr->locaLongPtr[idx]);
    }

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Loca_Open( void*              table_ptr,
                uint32_t           length,
                Uttf_Loca_Info_t*  info_ptr,
                Uttf_Loca_format_t format )
{
    memset( info_ptr, 0, sizeof(Uttf_Loca_Info_t) );

    if( format == UTTF_LOCA_FORMAT_SHORT )
    {
        info_ptr->locaShortPtr = table_ptr;
    }
    else if( format == UTTF_LOCA_FORMAT_LONG )
    {
        info_ptr->locaLongPtr = table_ptr;
    }

    return( UTTF_STATUS_NO_ERROR );
}
