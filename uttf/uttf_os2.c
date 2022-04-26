/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Os2_Open( Uttf_Os2_t*      table_ptr,
               uint32_t         length,
               Uttf_Os2_Info_t* info_ptr )
{
    info_ptr->os2Ptr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
