/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"
#include "uttf_hhea.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Hhea_Open( Uttf_Hhea_t*      table_ptr,
                uint32_t          table_len,
                Uttf_Hhea_Info_t* info_ptr )
{
    info_ptr->hheaPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
