/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"
#include "uttf_head.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Head_Open( Uttf_Head_t*      table_ptr,
                uint32_t          table_len,
                Uttf_Head_Info_t* info_ptr )
{
    info_ptr->headPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
