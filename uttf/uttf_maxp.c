/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"
#include "uttf_maxp.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Maxp_Open( Uttf_Maxp_t*      table_ptr,
                uint32_t          length,
                Uttf_Maxp_Info_t* info_ptr )
{
    info_ptr->maxpPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
