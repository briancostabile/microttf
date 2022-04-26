/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"
#include "uttf_config.h"
#include "uttf_post.h"

/**
 * Define the minimum index value before showing up in the glyphNameIndex table
 * glyph indexes less than this have required name mappings to be compatible
 * with older Macintosh systems
 */
#define UTTF_POST_MAC_TTF_NUM_GLYPHS 258
#define UTTF_POST_FMT2_MAPPING_IDX_MIN UTTF_POST_MAC_TTF_NUM_GLYPHS

#if defined(UTTF_CONFIG_POST_FMT2_ENABLE)
/*****************************************************************************/
static char*
uttf_Post_NameFindFmt2( Uttf_Post_SubtableFmt2_t* subtable_ptr,
                        Uttf_GlyphIdx_t           glyph_idx,
                        uint8_t*                  name_len_ptr )
{
    uint16_t numGlyphs = UTTF_BE16TOH(subtable_ptr->numGlyphs);
    uint8_t* string_table_ptr = (uint8_t*)&(subtable_ptr->glyphNameIndex[numGlyphs]);
    uint8_t* string_ptr = string_table_ptr;
    uint16_t string_idx = 0;
    
    if( glyph_idx < UTTF_POST_FMT2_MAPPING_IDX_MIN )
    {
        string_idx = glyph_idx;
    }
    else
    {
        string_idx = UTTF_BE16TOH( subtable_ptr->glyphNameIndex[(glyph_idx - UTTF_POST_FMT2_MAPPING_IDX_MIN)] );
    }

    // Skip past the strings one-by-one. No better way to do this without building
    // a table in RAM (sadpanda)
    for( int idx=0; idx<string_idx; idx++ )
    {
        string_ptr += (*string_ptr + 1);
    }

    // Copy the length out and point to the first char of the string
    *name_len_ptr = *string_ptr;
    string_ptr += 1;

    return( (char*)string_ptr );
}


/*****************************************************************************/
static uint16_t
uttf_Post_NameCountGetFmt2( Uttf_Post_SubtableFmt2_t* subtable_ptr )
{
    return( UTTF_BE16TOH(subtable_ptr->numGlyphs) );
}
#endif


#if defined(UTTF_CONFIG_POST_FMT1_ENABLE)
/*****************************************************************************/
#define UTTF_POST_FMT1_ELEMENT( _str ) {sizeof(_str), (_str)}

/*****************************************************************************/
typedef struct Uttf_Post_ElementFmt1_s {
    uint8_t len;
    char*   str;
} Uttf_Post_ElementFmt1_t;

/*****************************************************************************/
static const Uttf_Post_ElementFmt1_t uttf_Post_NameTableFmt1[] =
{
    UTTF_POST_FMT1_ELEMENT(".notdef"),
    UTTF_POST_FMT1_ELEMENT(".null")
};


/*****************************************************************************/
static char*
uttf_Post_NameFindFmt1( Uttf_GlyphIdx_t glyph_idx,
                        uint8_t*       name_len_ptr )
{
    char* str = NULL;
    *name_len_ptr = 0;

    if( glyph_idx < UTTF_ARRAY_CNT(uttf_Post_NameTableFmt1) )
    {
        *name_len_ptr = uttf_Post_NameTableFmt1[glyph_idx].len;
        str = (char*)uttf_Post_NameTableFmt1[glyph_idx].str;
    }
    return( str );
}


/*****************************************************************************/
static uint16_t
uttf_Post_NameCountGetFmt1( void )
{
    return( UTTF_ARRAY_CNT(uttf_Post_NameTableFmt1) );
}
#endif


/*****************************************************************************/
Uttf_Status_t
uttf_Post_NameFind( Uttf_Post_Info_t* info_ptr,
                    Uttf_GlyphIdx_t    glyph_idx,
                    uint8_t*          name_len_ptr,
                    char**            name_ptr_ptr )
{
    Uttf_Status_t status = UTTF_STATUS_NO_ERROR;
    uint32_t format      = UTTF_BE32TOH(info_ptr->postPtr->format);

    switch( format )
    {
#if defined(UTTF_CONFIG_POST_FMT1_ENABLE)
        case UTTF_POST_TABLE_FORMAT_1:
        {
            // There is no subtable so the names are predetermined and included
            // here. This takes a lot of code space. Probably not worth it
            *name_ptr_ptr = uttf_Post_NameFindFmt1( glyph_idx, name_len_ptr );
        }
        break;
#endif
#if defined(UTTF_CONFIG_POST_FMT2_ENABLE)
        case UTTF_POST_TABLE_FORMAT_2:
        {
            // The subtable immediately follows the fixed size structure at the
            // beginning of the post table
            *name_ptr_ptr = uttf_Post_NameFindFmt2( (Uttf_Post_SubtableFmt2_t*)&(((uint8_t*)(info_ptr->postPtr))[sizeof(*info_ptr->postPtr)]),
                                                    glyph_idx, name_len_ptr );
        }
        break;
#endif
#if defined(UTTF_CONFIG_POST_FMT3_ENABLE)
        case UTTF_POST_TABLE_FORMAT_3:
        {
            // No names in this format
            *name_len_ptr = 0;
            *name_ptr_ptr = NULL;
        }
        break;
#endif
        default:
            status = UTTF_STATUS_FAILURE;
            UTTF_LOG_WARN( "post: unsupported format: 0x%08X\n", format );
    }

    return( status );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Post_NameCountGet( Uttf_Post_Info_t* info_ptr,
                        uint16_t*         num_names_ptr )
{
    Uttf_Status_t status = UTTF_STATUS_NO_ERROR;
    uint32_t format      = UTTF_BE32TOH(info_ptr->postPtr->format);

    switch( format )
    {
#if defined(UTTF_CONFIG_POST_FMT1_ENABLE)
        case UTTF_POST_TABLE_FORMAT_1:
        {
            *num_names_ptr = uttf_Post_NameCountGetFmt1();
        }
#endif
#if defined(UTTF_CONFIG_POST_FMT2_ENABLE)
        case UTTF_POST_TABLE_FORMAT_2:
        {
            *num_names_ptr = uttf_Post_NameCountGetFmt2( (Uttf_Post_SubtableFmt2_t*)(((uint8_t*)info_ptr->postPtr) + sizeof(*(info_ptr->postPtr))) );
        }
#endif
#if defined(UTTF_CONFIG_POST_FMT3_ENABLE)
        case UTTF_POST_TABLE_FORMAT_3:
            // Nothing to do, there is no subtable for format 3
        break;
#endif
        default:
            status = UTTF_STATUS_FAILURE;
            UTTF_LOG_WARN( "post: unsupported format: 0x%08X\n", format );
    }

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Post_Open( Uttf_Post_t*      table_ptr,
                uint32_t          length,
                Uttf_Post_Info_t* info_ptr )
{
    info_ptr->postPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
