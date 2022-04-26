/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"
#include "uttf_name.h"

/*****************************************************************************/
Uttf_Name_Rec_t*
uttf_Name_RecordFind( Uttf_Name_Info_t* info_ptr,
                      uint16_t          name_id )
{
    uint16_t count = UTTF_BE16TOH(info_ptr->namePtr->count);

    // better to convert the passed in name to BigEndian instead of converting
    // each record's name to HostEndian
    uint16_t name_id_be = UTTF_H16TOBE(name_id); 

    for( uint16_t i=0; i < count; i++ )
    {
        if( name_id_be == info_ptr->namePtr->nameRecords[i].nameID )
        {
            return( &(info_ptr->namePtr->nameRecords[i]) );
        }
    }

    return( NULL );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Name_StringGet( Uttf_Name_Info_t* info_ptr,
                     uint16_t          name_id,
                     uint16_t*         str_len_ptr,
                     char**            str_ptr_ptr )
{
    Uttf_Name_Rec_t* rec_ptr;

    // Assume it's not found
    *str_len_ptr = 0;
    *str_ptr_ptr = NULL;
    rec_ptr = NULL;

    switch( name_id )
    {
        case UTTF_NAME_ID_FONT_FAMILY:
            rec_ptr = info_ptr->fontFamilyRecPtr;
        break;
        
        case UTTF_NAME_ID_FONT_SUBFAMILY:
            rec_ptr = info_ptr->fontSubFamilyRecPtr;
        break;
        
        case UTTF_NAME_ID_FULL_FONT_NAME:
            rec_ptr = info_ptr->fontNameRecPtr;
        break;

        case UTTF_NAME_ID_POSTSCRIPT_NAME:
            rec_ptr = info_ptr->psNameRecPtr;
        break;

        default:
            rec_ptr = uttf_Name_RecordFind( info_ptr, name_id );
    }

    if( rec_ptr != NULL )
    {
        *str_len_ptr = UTTF_BE16TOH(rec_ptr->length);
        *str_ptr_ptr = (char*)((char*)(info_ptr->namePtr) + UTTF_BE16TOH(info_ptr->namePtr->stringOffset) + UTTF_BE16TOH(rec_ptr->offset));
    }

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Name_Open( Uttf_Name_t*      table_ptr,
                uint32_t          length,
                Uttf_Name_Info_t* info_ptr )
{
    info_ptr->namePtr = table_ptr;

    // cache lookups of the most used records
    info_ptr->fontFamilyRecPtr    = uttf_Name_RecordFind( info_ptr, UTTF_NAME_ID_FONT_FAMILY );
    info_ptr->fontSubFamilyRecPtr = uttf_Name_RecordFind( info_ptr, UTTF_NAME_ID_FONT_SUBFAMILY );
    info_ptr->fontNameRecPtr      = uttf_Name_RecordFind( info_ptr, UTTF_NAME_ID_FULL_FONT_NAME );
    info_ptr->psNameRecPtr        = uttf_Name_RecordFind( info_ptr, UTTF_NAME_ID_POSTSCRIPT_NAME );

    return( UTTF_STATUS_NO_ERROR );
}
