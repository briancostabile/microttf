/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "uttf.h"

#define UTTF_CMAP_FMT0_MAX_CODE 0xFF
#define UTTF_CMAP_FMT4_MAX_CODE 0xFFFF

/*****************************************************************************/
/**
 * Define encodings for Macintosh platform Id. 
 */ 
typedef enum Uttf_Cmap_PlatformMacEncodingId_e {
    UTTF_CMAP_PLATFORM_MAC_ENCODING_ID_DEFAULT = 0
} Uttf_Cmap_PlatformMacEncodingId_t;


/*****************************************************************************/
/**
 * Define encodings for Unicode platform Id. 
 */ 
typedef enum Uttf_Cmap_PlatformUniEncodingId_e {
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_DEFAULT      = 0,
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_VER_1p1      = 1,
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_ISO_10646    = 2,
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_UCS_2        = 3,
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_UCS_4        = 4,
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_UTF_8        = 5,
    UTTF_CMAP_PLATFORM_UNI_ENCODING_ID_FULL_UNICODE = 6
} Uttf_Cmap_PlatformUniEncodingId_t;


/*****************************************************************************/
/**
 * Define encodings for Microsoft platform Id. Only UCS (Universal Character Set)
 * is supported. That is on purpose to keep this implementation small. Other encodings
 * will be ignored and issue a warning to indicate that the font file can (should)
 * be reduced.
 */ 
typedef enum Uttf_Cmap_PlatformMsEncodingId_e {
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_SYMBOL    = 0,
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_UCS_2     = 1,
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_SHIFT_JIS = 2,
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_PRC       = 3,
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_BIG_5     = 4,
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_WANSUNG   = 5,
    UTTF_CMAP_PLATFORM_MS_ENCODING_ID_UCS_4     = 6
} Uttf_Cmap_PlatformMsEncodingId_t;


#if (UTTF_CONFIG_CMAP_FMT0 == ENABLE)
/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_ParseSubtableFmt0( Uttf_Cmap_SubtableParsedFmt0_t* parsed_ptr,
                             Uttf_Cmap_SubtableFmt0_t*       subtable_ptr )
{
    parsed_ptr->length       = (UTTF_BE16TOH(subtable_ptr->length) - 6); // Only keep the length of the glyphIdArray
    parsed_ptr->glyphIdArray = subtable_ptr->glyphIdArray;
    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt0( Uttf_Cmap_SubtableFmt0_t* subtable_ptr,
                               Uttf_CharCode_t           code )
{
    Uttf_Cmap_SubtableParsedFmt0_t parsed_subtable;
    Uttf_GlyphIdx_t idx = 0;

    // Parse out the passed in subtable
    uttf_Cmap_ParseSubtableFmt0( &parsed_subtable, subtable_ptr );

    if( code <= parsed_subtable.length ) 
    {
        idx = parsed_subtable.glyphIdArray[code];
    }

    return( idx );
}
#endif


#if (UTTF_CONFIG_CMAP_FMT4 == ENABLE)
/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_ParseSubtableFmt4( Uttf_Cmap_SubtableParsedFmt4_t* parsed_ptr,
                             Uttf_Cmap_SubtableFmt4_t*       subtable_ptr )
{
    parsed_ptr->segCountX2         = UTTF_BE16TOH(subtable_ptr->segCountX2);
    parsed_ptr->endCountArray      = (uint16_t*)((uint8_t*)(subtable_ptr) + sizeof(Uttf_Cmap_SubtableFmt4_t));
    parsed_ptr->startCountArray    = (uint16_t*)((uint8_t*)(parsed_ptr->endCountArray)      + parsed_ptr->segCountX2 + sizeof(uint16_t)); // Extra 2-bytes for reserved word
    parsed_ptr->idDeltaArray       = (uint16_t*)((uint8_t*)(parsed_ptr->startCountArray)    + parsed_ptr->segCountX2);
    parsed_ptr->idRangeOffsetArray = (uint16_t*)((uint8_t*)(parsed_ptr->idDeltaArray)       + parsed_ptr->segCountX2);
    parsed_ptr->glyphIdArray       = (uint16_t*)((uint8_t*)(parsed_ptr->idRangeOffsetArray) + parsed_ptr->segCountX2);
    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt4( Uttf_Cmap_SubtableFmt4_t* subtable_ptr,
                               Uttf_CharCode_t           code )
{
    Uttf_Cmap_SubtableParsedFmt4_t parsed_subtable;
    Uttf_GlyphIdx_t idx = 0;

    // Parse out the passed in subtable
    uttf_Cmap_ParseSubtableFmt4( &parsed_subtable, subtable_ptr );

    uint16_t seg_count = (parsed_subtable.segCountX2 / 2);

    //Binary Search (left,right,middle) the ranges 
    int16_t l = 0;
    int16_t r = (seg_count - 1);
    int16_t m = 0;

    while( l <= r )
    {
        m = l + (r-l)/2;

        uint16_t end_count = UTTF_BE16TOH( parsed_subtable.endCountArray[m] );
        if( end_count >= code )
        {
            uint16_t start_count = UTTF_BE16TOH( parsed_subtable.startCountArray[m] );
            if( start_count <= code )
            {
                uint16_t id_range_offset = UTTF_BE16TOH( parsed_subtable.idRangeOffsetArray[m] );
                if( id_range_offset == 0 )
                {
                    uint16_t id_delta = (int16_t)UTTF_BE16TOH( parsed_subtable.idDeltaArray[m] );
                    // Need to cast to 16-bits to force overflow to wrap back to 0
                    idx = (uint16_t)(code + id_delta);
                }
                else
                {
                    idx = UTTF_BE16TOH( parsed_subtable.idRangeOffsetArray[ m +
                                                                            (UTTF_BE16TOH( parsed_subtable.idRangeOffsetArray[m] ) / 2) +
                                                                            (code - UTTF_BE16TOH( parsed_subtable.startCountArray[m] )) ] );
                } 
                break;
            }
            else
            {   
                r = m - 1; // Range is too high, look in the lower (left) half
            }
        }
        else
        {
            l = m + 1; // Range is too low, look in the upper (right) half
        }
    }

    return( idx );
}
#endif


#if (UTTF_CONFIG_CMAP_FMT6 == ENABLE)
/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_ParseSubtableFmt6( Uttf_Cmap_SubtableParsedFmt6_t* parsed_ptr,
                             Uttf_Cmap_SubtableFmt6_t*       subtable_ptr )
{
    parsed_ptr->firstCode    = UTTF_BE16TOH(subtable_ptr->firstCode);
    parsed_ptr->entryCount   = UTTF_BE16TOH(subtable_ptr->entryCount);
    parsed_ptr->glyphIdArray = subtable_ptr->glyphIdArray;
    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt6( Uttf_Cmap_SubtableFmt6_t* subtable_ptr,
                               Uttf_CharCode_t           code )
{
    Uttf_GlyphIdx_t idx = 0;
    uint16_t first_code = UTTF_BE16TOH(subtable_ptr->firstCode);

    if( (code >= first_code) &&
        ((code - first_code) <= (UTTF_BE16TOH(subtable_ptr->entryCount) - 1)) )
    {
        idx = UTTF_BE16TOH(subtable_ptr->glyphIdArray[(code - first_code)]);
    }

    return( idx );
}
#endif


#if (UTTF_CONFIG_CMAP_FMT12 == ENABLE)
/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_ParseSubtableFmt12( Uttf_Cmap_SubtableParsedFmt12_t* parsed_ptr,
                              Uttf_Cmap_SubtableFmt12_t*       subtable_ptr )
{
    parsed_ptr->numGroups   = UTTF_BE32TOH(subtable_ptr->numGroups);
    parsed_ptr->groups      = subtable_ptr->groups;
    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt12( Uttf_Cmap_SubtableFmt12_t* subtable_ptr,
                                Uttf_CharCode_t            code )
{
    Uttf_Cmap_SubtableParsedFmt12_t parsed_subtable;
    Uttf_GlyphIdx_t idx = 0;
    uint32_t numGroups = UTTF_BE32TOH(subtable_ptr->numGroups);;

    // Parse out the passed in subtable
    uttf_Cmap_ParseSubtableFmt12( &parsed_subtable, subtable_ptr );

    //Binary Search (left,right,middle) the ranges 
    int16_t l = 0;
    int16_t r = (numGroups - 1);
    int16_t m = 0;

    while( l <= r )
    {
        m = l + (r-l)/2;
        uint32_t endCharCode = UTTF_BE32TOH( parsed_subtable.groups[m].endCharCode );
        if( endCharCode >= code )
        {
            uint32_t startCharCode = UTTF_BE32TOH( parsed_subtable.groups[m].startCharCode );
            if( startCharCode <= code )
            {
                uint32_t startGlyphID = UTTF_BE32TOH( parsed_subtable.groups[m].startGlyphID );
                idx = (startGlyphID + (code - startCharCode));
                break;
            }
        }
    }

    return( idx );
}
#endif


#if (UTTF_CONFIG_CMAP_FMT14 == ENABLE)
/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_ParseSubtableFmt14( Uttf_Cmap_SubtableParsedFmt14_t* parsed_ptr,
                              Uttf_Cmap_SubtableFmt14_t*       subtable_ptr )
{
    parsed_ptr->numVarSelectorRecords = UTTF_BE16TOH( subtable_ptr->numVarSelectorRecords );
    parsed_ptr->varSelector           = subtable_ptr->varSelector;

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt14( Uttf_Cmap_SubtableFmt14_t* subtable_ptr,
                                Uttf_CharCode_t            code )
{
    Uttf_Cmap_SubtableParsedFmt14_t parsed_subtable;
    Uttf_GlyphIdx_t idx = 0;

    // Parse out the passed in subtable
    uttf_Cmap_ParseSubtableFmt14( &parsed_subtable, subtable_ptr );

    return( idx );
}
#endif


/*****************************************************************************/
#define UTTF_CMAP_FORMAT_SET( _num, _info_ptr, _ptr )                       \
    if( UTTF_CONFIG_CMAP_FMT##_num == ENABLE )                              \
    {                                                                       \
       _info_ptr->fmt##_num##Ptr = (Uttf_Cmap_SubtableFmt##_num##_t *)_ptr; \
    }                                                                       \

#define UTTF_CMAP_FORMAT_SAVE( _num, _info_ptr, _ptr )     \
    case _num:                                             \
    {                                                      \
        if( (UTTF_CONFIG_CMAP_FMT##_num == ENABLE) &&      \
            (_info_ptr->fmt##_num##Ptr == NULL) )          \
        {                                                  \
            UTTF_CMAP_FORMAT_SET( _num, _info_ptr, _ptr ); \
        }                                                  \
    }                                                      \
    break;

/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_SubtableArraysGet( void*      subtable_ptr,
                             uint16_t*  seg_count_X2_ptr,
                             uint16_t** end_count_array_ptr,
                             uint16_t** start_count_array_ptr,
                             uint16_t** id_delta_array_ptr,
                             uint16_t** id_range_offset_array_ptr,
                             uint16_t** glyph_id_array_ptr )
{
#if (UTTF_CONFIG_CMAP_FMT4 == ENABLE)
    if( subtable_ptr != NULL )
    {
        Uttf_Cmap_SubtableParsedFmt4_t parsed_subtable;
        uttf_Cmap_ParseSubtableFmt4( &parsed_subtable, (Uttf_Cmap_SubtableFmt4_t*)subtable_ptr );
        *seg_count_X2_ptr          = parsed_subtable.segCountX2;
        *end_count_array_ptr       = parsed_subtable.endCountArray;
        *start_count_array_ptr     = parsed_subtable.startCountArray;
        *id_delta_array_ptr        = parsed_subtable.idDeltaArray;
        *id_range_offset_array_ptr = parsed_subtable.idRangeOffsetArray;
        *glyph_id_array_ptr        = parsed_subtable.glyphIdArray;
    }
    else
#endif
    {
        *seg_count_X2_ptr          = 0;
        *end_count_array_ptr       = NULL;
        *start_count_array_ptr     = NULL;
        *id_delta_array_ptr        = NULL;
        *id_range_offset_array_ptr = NULL;
        *glyph_id_array_ptr        = NULL;        
    }

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_Open( Uttf_Cmap_t*      table_ptr,
                uint32_t          table_len,
                Uttf_Cmap_Info_t* info_ptr )
{
    info_ptr->cmapPtr = table_ptr;

    // NULL out the subtable lookup table pointers
    UTTF_CMAP_FORMAT_SET(  0, info_ptr, NULL );
    UTTF_CMAP_FORMAT_SET(  4, info_ptr, NULL );
    UTTF_CMAP_FORMAT_SET(  6, info_ptr, NULL );
    UTTF_CMAP_FORMAT_SET( 12, info_ptr, NULL );
    UTTF_CMAP_FORMAT_SET( 14, info_ptr, NULL );

    Uttf_Cmap_EncodingRec_t* encodingrecArray = table_ptr->encodingRecords;
    uint16_t num_tables = UTTF_BE16TOH( table_ptr->numTables );

    // Find supported tables for quick lookups
    for( int i=0; i<num_tables; i++ )
    {
        Uttf_Cmap_Subtable_t* subtable_ptr = (Uttf_Cmap_Subtable_t*)((uint8_t*)(table_ptr) + UTTF_BE32TOH(encodingrecArray[i].offset));
        uint16_t format = UTTF_BE16TOH( subtable_ptr->format );
        switch( format )
        {
            UTTF_CMAP_FORMAT_SAVE(  0, info_ptr, subtable_ptr );
            UTTF_CMAP_FORMAT_SAVE(  4, info_ptr, subtable_ptr );
            UTTF_CMAP_FORMAT_SAVE(  6, info_ptr, subtable_ptr );
            UTTF_CMAP_FORMAT_SAVE( 12, info_ptr, subtable_ptr );
            UTTF_CMAP_FORMAT_SAVE( 14, info_ptr, subtable_ptr );

            default:
                UTTF_LOG_INFO( "Cmap: Unsupported Format %d\n", format );
        }
    }

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdx( Uttf_Cmap_Info_t* info_ptr,
                   Uttf_CharCode_t   code )
{
    Uttf_GlyphIdx_t idx = 0;

    // If fmt0 is availalbe then do the lookup with that table because it's
    // much faster. Only first 256 unicodes are available in FMT0
#if (UTTF_CONFIG_CMAP_FMT0 == ENABLE)
    if( (code <= UTTF_CMAP_FMT0_MAX_CODE) && (info_ptr->fmt0Ptr != NULL) )
    {
        idx = uttf_Cmap_FindIdxSubtableFmt0( info_ptr->fmt0Ptr, code );
    }
#endif

#if (UTTF_CONFIG_CMAP_FMT6 == ENABLE)
    // Format 6 is also faster than Format 4 and supports direct lookups
    // for unicodes up to 0xFFFF
    if( (idx == 0) && (code <= UTTF_CMAP_FMT4_MAX_CODE) && (info_ptr->fmt6Ptr != NULL) )
    {
        idx = uttf_Cmap_FindIdxSubtableFmt6( info_ptr->fmt6Ptr, code );
    }
#endif

#if (UTTF_CONFIG_CMAP_FMT4 == ENABLE)
    // Format 4 only supports unicodes up to 0xFFFF
    if( (idx == 0) && (code <= UTTF_CMAP_FMT4_MAX_CODE) && (info_ptr->fmt4Ptr != NULL) )
    {
        idx = uttf_Cmap_FindIdxSubtableFmt4( info_ptr->fmt4Ptr, code );
    }
#endif

#if (UTTF_CONFIG_CMAP_FMT12 == ENABLE)
    if( (idx == 0) && (info_ptr->fmt12Ptr != NULL) )
    {
        idx = uttf_Cmap_FindIdxSubtableFmt12( info_ptr->fmt12Ptr, code );
    }
#endif

    // Insert code to search the tables from the font file

    return( idx );
}
