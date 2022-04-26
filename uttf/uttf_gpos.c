/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "uttf.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Gpos_Open( Uttf_Gpos_t*      table_ptr,
                uint32_t          length,
                Uttf_Gpos_Info_t* info_ptr )
{
    info_ptr->gposPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
