/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "uttf.h"

/*****************************************************************************/
Uttf_Status_t
uttf_Open( Uttf_FileInfo_t* file_info_ptr,
           uint8_t*         file_ptr,
           size_t           file_size )
{
    void* pending_loca_ptr = NULL;
    uint32_t pending_loca_len = 0;
    void* pending_hmtx_ptr = NULL;
    uint32_t pending_hmtx_len = 0;

    UTTF_ASSERT( file_info_ptr != NULL );

    UTTF_LOG_INFO( "Open: size:%zu\n", file_size );
    
    // Set all data to 0/Null
    memset(file_info_ptr,0,sizeof(*file_info_ptr));

    file_info_ptr->filePtr        = file_ptr;
    file_info_ptr->eofPtr         = (file_ptr + file_size);
    file_info_ptr->offsetTablePtr = (Uttf_OffsetTable_t *)file_ptr;

    size_t num_tables = UTTF_BE16TOH( file_info_ptr->offsetTablePtr->numTables );
    for( int i=0; i < num_tables; i++ )
    {
        Uttf_OffsetTableRec_t* offset_table_rec_ptr = &(file_info_ptr->offsetTablePtr->tableArray[i]);
        uint32_t tag = UTTF_BE32TOH( offset_table_rec_ptr->tag );

        switch( tag )
        {
            case UTTF_OFFSET_TABLE_REC_TAG_OS2:
                UTTF_LOG_INFO( "OS/2 Table\n" );
                uttf_Os2_Open( (Uttf_Os2_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                               UTTF_BE32TOH( offset_table_rec_ptr->length ),
                               &(file_info_ptr->os2Info) );
            break;

            case UTTF_OFFSET_TABLE_REC_TAG_CMAP:
                UTTF_LOG_INFO( "CMAP Table\n" );
                uttf_Cmap_Open( (Uttf_Cmap_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->cmapInfo) );
            break;

            case UTTF_OFFSET_TABLE_REC_TAG_MAXP:
                UTTF_LOG_INFO( "MAXP Table\n" );
                uttf_Maxp_Open( (Uttf_Maxp_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->maxpInfo) );
                                
                if( (pending_hmtx_ptr != NULL) && (file_info_ptr->hheaInfo.hheaPtr != NULL) )
                {
                    UTTF_LOG_INFO( "HMTX Table\n" );
                    uttf_Hmtx_Open( pending_hmtx_ptr,
                                    pending_hmtx_len,
                                    &(file_info_ptr->hmtxInfo),
                                    UTTF_BE16TOH(file_info_ptr->hheaInfo.hheaPtr->numOfLongHorMetrics),
                                    UTTF_BE16TOH(file_info_ptr->maxpInfo.maxpPtr->v1.numGlyphs) );
                    pending_hmtx_ptr = NULL;
                }
            break;
            
            case UTTF_OFFSET_TABLE_REC_TAG_HEAD:
                UTTF_LOG_INFO( "HEAD Table\n" );
                uttf_Head_Open( (Uttf_Head_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->headInfo) );
                if( pending_loca_ptr != NULL )
                {
                    UTTF_LOG_INFO( "LOCA Table\n" );
                    uttf_Loca_Open( pending_loca_ptr,
                                    pending_loca_len,
                                    &(file_info_ptr->locaInfo),
                                    UTTF_BE16TOH(file_info_ptr->headInfo.headPtr->indexToLocFormat) );
                    pending_loca_ptr = NULL;              
                }
            break;
            
            case UTTF_OFFSET_TABLE_REC_TAG_LOCA:
                if( file_info_ptr->headInfo.headPtr == NULL )
                {
                    UTTF_LOG_INFO( "LOCA Table Pending HEAD\n" );
                    pending_loca_ptr = (void *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset ));
                    pending_loca_len = UTTF_BE32TOH( offset_table_rec_ptr->length );
                }
                else
                {
                    UTTF_LOG_INFO( "LOCA Table\n" );
                    uttf_Loca_Open( (void *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                    UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                    &(file_info_ptr->locaInfo),
                                    UTTF_BE16TOH(file_info_ptr->headInfo.headPtr->indexToLocFormat) );
                    pending_loca_ptr = NULL;
                }
            break;
            
            case UTTF_OFFSET_TABLE_REC_TAG_HHEA:
                UTTF_LOG_INFO( "HHEA Table\n" );
                uttf_Hhea_Open( (Uttf_Hhea_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->hheaInfo) );

                if( (pending_hmtx_ptr != NULL) && (file_info_ptr->maxpInfo.maxpPtr != NULL) )
                {
                    UTTF_LOG_INFO( "HMTX Table\n" );
                    uttf_Hmtx_Open( pending_hmtx_ptr,
                                    pending_hmtx_len,
                                    &(file_info_ptr->hmtxInfo),
                                    UTTF_BE16TOH(file_info_ptr->hheaInfo.hheaPtr->numOfLongHorMetrics),
                                    UTTF_BE16TOH(file_info_ptr->maxpInfo.maxpPtr->v1.numGlyphs) );
                    pending_hmtx_ptr = NULL;
                }
            break;
            
            case UTTF_OFFSET_TABLE_REC_TAG_HMTX:
                if( (file_info_ptr->headInfo.headPtr == NULL) || (file_info_ptr->maxpInfo.maxpPtr == NULL) )
                {
                    UTTF_LOG_INFO( "HMTX Table Pending HEAD or MAXP\n" );
                    pending_hmtx_ptr = (void *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset ));
                    pending_hmtx_len = UTTF_BE32TOH( offset_table_rec_ptr->length );
                }
                else
                {
                    UTTF_LOG_INFO( "HMTX Table\n" );
                    uttf_Hmtx_Open(  (void *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                    UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                    &(file_info_ptr->hmtxInfo),
                                    UTTF_BE16TOH(file_info_ptr->hheaInfo.hheaPtr->numOfLongHorMetrics),
                                    UTTF_BE16TOH(file_info_ptr->maxpInfo.maxpPtr->v1.numGlyphs) );
                    pending_hmtx_ptr = NULL;
                }
            break;
            
            case UTTF_OFFSET_TABLE_REC_TAG_POST:
                UTTF_LOG_INFO( "POST Table\n" );
                uttf_Post_Open( (Uttf_Post_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->postInfo) );
            break;

            case UTTF_OFFSET_TABLE_REC_TAG_NAME:
                UTTF_LOG_INFO( "NAME Table\n" );
                uttf_Name_Open( (Uttf_Name_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->nameInfo) );
            break;

            case UTTF_OFFSET_TABLE_REC_TAG_GLYF:
                UTTF_LOG_INFO( "GLYF Table\n" );
                uttf_Glyf_Open( (Uttf_Glyf_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->glyfInfo) );
            break;

            case UTTF_OFFSET_TABLE_REC_TAG_GDEF:
                UTTF_LOG_INFO( "GDEF Table\n" );
                uttf_Gdef_Open( (Uttf_Gdef_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->gdefInfo) );
            break;

            case UTTF_OFFSET_TABLE_REC_TAG_GPOS:
                UTTF_LOG_INFO( "GPOS Table\n" );
                uttf_Gpos_Open( (Uttf_Gpos_t *)(file_info_ptr->filePtr + UTTF_BE32TOH( offset_table_rec_ptr->offset )),
                                UTTF_BE32TOH( offset_table_rec_ptr->length ),
                                &(file_info_ptr->gposInfo) );
            break;

            default:
                UTTF_LOG_INFO( "Unsupported Table: %c%c%c%c\n",
                               (char)(tag >> 24), (char)(tag >> 16), (char)(tag >> 8), (char)(tag >> 0) );
        }
    }

    return( UTTF_STATUS_NO_ERROR );
}