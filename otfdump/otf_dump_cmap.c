
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"
#include "uttf_cmap.h"

void
otf_dump_tableCmapSubtableFmt14DefaltUvsTable( Uttf_Cmap_SubtableFmt14DefaultUvsTable_t* subtable_ptr )
{
    uint32_t numUnicodeValueRanges = UTTF_BE32TOH(subtable_ptr->numUnicodeValueRanges);
    printf( "numUnicodeValueRanges:  %d"OTF_DUMP_NL, numUnicodeValueRanges );

    printf( "startUnicodeValue\tadditionalCount"OTF_DUMP_NL );
    for( uint32_t i=0; i<numUnicodeValueRanges; i++ )
    {
        uint8_t* range_rec_ptr = (uint8_t*)&subtable_ptr->ranges[i];
        uint32_t startUnicodeValue = (subtable_ptr->ranges[i].startUnicodeValueMswLsb << 16) | (subtable_ptr->ranges[i].startUnicodeValueLswMsb << 8) | subtable_ptr->ranges[i].startUnicodeValueLswLsb;
        printf( "0x%08X\t\t%d"OTF_DUMP_NL, startUnicodeValue, subtable_ptr->ranges[i].additionalCount );
    }
    
    return;
}

void
otf_dump_tableCmapSubtableFmt14NonDefaltUvsTable( Uttf_Cmap_SubtableFmt14NonDefaultUvsTable_t* subtable_ptr )
{
    uint32_t numUVSMappings = UTTF_BE32TOH(subtable_ptr->numUVSMappings);
    printf( "numUVSMappings:  %d"OTF_DUMP_NL, numUVSMappings );
    
    return;
}

void
otf_dump_tableCmapSubtableFmt14( Uttf_Cmap_SubtableFmt14_t* subtable_ptr )
{
    printf( "format:                %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->format) );
    printf( "length:                %d"OTF_DUMP_NL, UTTF_BE32TOH(subtable_ptr->length) );
    printf( "numVarSelectorRecords: %d"OTF_DUMP_NL, UTTF_BE32TOH(subtable_ptr->numVarSelectorRecords) );
    printf( OTF_DUMP_NL );

    printf( "varSelector\tdefaultUVSOffset\tnonDefaultUVSOffset"OTF_DUMP_NL );
    for( uint32_t i=0; i<UTTF_BE32TOH(subtable_ptr->numVarSelectorRecords); i++ )
    {
        uint32_t varSelector = (subtable_ptr->varSelector[i].varSelectorMs8) | UTTF_BE16TOH(subtable_ptr->varSelector[i].varSelectorLs16);
        uint32_t defaultUVSOffset = UTTF_BE32TOH(subtable_ptr->varSelector[i].defaultUVSOffset);
        uint32_t nonDefaultUVSOffset = UTTF_BE32TOH(subtable_ptr->varSelector[i].nonDefaultUVSOffset);
        printf( "0x%08X\t0x%08X\t\t%d"OTF_DUMP_NL, varSelector, defaultUVSOffset, nonDefaultUVSOffset );

        if( defaultUVSOffset != 0 )
        {
            otf_dump_tableCmapSubtableFmt14DefaltUvsTable( (Uttf_Cmap_SubtableFmt14DefaultUvsTable_t*) ((uint8_t*)subtable_ptr + defaultUVSOffset));
        }

        if( subtable_ptr->varSelector[i].nonDefaultUVSOffset != 0 )
        {
            otf_dump_tableCmapSubtableFmt14NonDefaltUvsTable( (Uttf_Cmap_SubtableFmt14NonDefaultUvsTable_t*) ((uint8_t*)subtable_ptr + nonDefaultUVSOffset) );
        }
    }
    return;
}

void
otf_dump_tableCmapSubtableFmt12( Uttf_Cmap_SubtableFmt12_t* subtable_ptr )
{
    printf( "format:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->format) );
    printf( "length:        %d"OTF_DUMP_NL, UTTF_BE32TOH(subtable_ptr->length) );
    printf( "language:      %d"OTF_DUMP_NL, UTTF_BE32TOH(subtable_ptr->language) );
    printf( "numGroups:     %d"OTF_DUMP_NL, UTTF_BE32TOH(subtable_ptr->numGroups) );
    printf( OTF_DUMP_NL );

    printf( "start\t\tend\t\tstartGlyphId"OTF_DUMP_NL );
    for( uint32_t i=0; i<UTTF_BE32TOH(subtable_ptr->numGroups); i++ )
    {
        printf( "0x%08X\t0x%08X\t%d"OTF_DUMP_NL,
                UTTF_BE32TOH(subtable_ptr->groups[i].startCharCode),
                UTTF_BE32TOH(subtable_ptr->groups[i].endCharCode),
                UTTF_BE32TOH(subtable_ptr->groups[i].startGlyphID) );
    }
    return;
}

void
otf_dump_tableCmapSubtableFmt4( Uttf_Cmap_SubtableFmt4_t* subtable_ptr )
{    
    printf( "format:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->format) );
    printf( "length:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->length) );
    printf( "language:      %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->language) );
    printf( "segCountX2:    %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->segCountX2) );
    printf( "searchRange:   %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->searchRange) );
    printf( "entrySelector: %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->entrySelector) );
    printf( "rangeShift:    %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->rangeShift) );

    uint16_t  seg_count_X2;
    uint16_t* end_count_array;
    uint16_t* start_count_array;
    uint16_t* id_delta_array;
    uint16_t* id_range_offset_array;
    uint16_t* glyph_id_array;

    uttf_Cmap_SubtableArraysGet( subtable_ptr,
                                 &seg_count_X2,
                                 &end_count_array,
                                 &start_count_array,
                                 &id_delta_array,
                                 &id_range_offset_array,
                                 &glyph_id_array );

    printf( "end\t\tstart\t\tidDelta\t\t\tidRangeOffset"OTF_DUMP_NL );
    uint16_t seg_count = (seg_count_X2 / 2);
    for( int i=0; i<seg_count; i++ )
    {
        printf( "%04X:%6d\t%04X:%6d\t%08X:%6i\t\t%04X:%6d"OTF_DUMP_NL, 
                UTTF_BE16TOH(end_count_array[i]), 
                UTTF_BE16TOH(end_count_array[i]), 
                UTTF_BE16TOH(start_count_array[i]), 
                UTTF_BE16TOH(start_count_array[i]), 
                (int16_t)UTTF_BE16TOH(id_delta_array[i]), 
                (int16_t)UTTF_BE16TOH(id_delta_array[i]), 
                UTTF_BE16TOH(id_range_offset_array[i]), 
                UTTF_BE16TOH(id_range_offset_array[i]) );
    }

    printf( OTF_DUMP_NL );
    uint16_t num=0;
    for( uint32_t i=0; i<0xFFFF; i++ )
    {
        Uttf_GlyphIdx_t idx = uttf_Cmap_FindIdxSubtableFmt4( subtable_ptr, i );
        if( idx != 0 )
        {
            printf( "%08X:%d\n", i, idx );
            num++;
        }
    }
    printf( "NumGlyphs:%d\n", num );
    return;
}

void
otf_dump_tableCmapSubtableFmt0( Uttf_Cmap_SubtableFmt0_t* subtable_ptr )
{
    printf( "format:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->format) );
    printf( "length:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->length) );
    printf( "language:      %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->language) );
    printf( OTF_DUMP_NL );

    uint16_t num=0;
    for( uint32_t i=0; i<255; i++ )
    {
        Uttf_GlyphIdx_t idx = uttf_Cmap_FindIdxSubtableFmt0( subtable_ptr, i );
        printf( "%08X:%d\n", i, idx );
        num++;
    }
    printf( "NumGlyphs:%d\n", num );
    return;
}

void
otf_dump_tableCmapSubtableFmt6( Uttf_Cmap_SubtableFmt6_t* subtable_ptr )
{
    printf( "format:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->format) );
    printf( "length:        %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->length) );
    printf( "language:      %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->language) );
    printf( "firstCode:     %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->firstCode) );
    printf( "entryCount:    %d"OTF_DUMP_NL, UTTF_BE16TOH(subtable_ptr->entryCount) );
    printf( OTF_DUMP_NL );

    uint16_t num=0;
    for( uint32_t i=UTTF_BE16TOH(subtable_ptr->firstCode); 
         (i < UTTF_BE16TOH(subtable_ptr->firstCode) + UTTF_BE16TOH(subtable_ptr->entryCount));
         i++ )
    {
        Uttf_GlyphIdx_t idx = uttf_Cmap_FindIdxSubtableFmt6( subtable_ptr, i );
        printf( "%08X:%d\n", i, idx );
        num++;
    }
    printf( "NumGlyphs:%d\n", num );
    return;
}

void
otf_dump_tableCmapSubtable( Uttf_Cmap_Info_t*     info_ptr, 
                            Uttf_Cmap_Subtable_t* subtable_ptr )
{
    uint16_t format = UTTF_BE16TOH(subtable_ptr->format);

    switch( format )
    {
        case 0: { otf_dump_tableCmapSubtableFmt0(info_ptr->fmt0Ptr); }; break;
        case 4: { otf_dump_tableCmapSubtableFmt4(info_ptr->fmt4Ptr); }; break;
        case 6: { otf_dump_tableCmapSubtableFmt6(info_ptr->fmt6Ptr); }; break;
        case 12: { otf_dump_tableCmapSubtableFmt12(info_ptr->fmt12Ptr); }; break;
        case 14: { otf_dump_tableCmapSubtableFmt14(info_ptr->fmt14Ptr); }; break;
        default: { printf( "Unsupported Format :%d"OTF_DUMP_NL, format ); }
    }
    
    return;
}

void
otf_dump_Cmap( Uttf_Cmap_Info_t* info_ptr )
{
    printf( OTF_DUMP_SECTION_START("cmap") );
    if( info_ptr != NULL )
    {
        printf( "version:   %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->cmapPtr->version) );        
        printf( "numTables: %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->cmapPtr->numTables) );
        printf( OTF_DUMP_NL );

        Uttf_Cmap_EncodingRec_t* encodingrecArray = info_ptr->cmapPtr->encodingRecords;
        uint16_t num_tables = UTTF_BE16TOH(info_ptr->cmapPtr->numTables);

        // Dump the table first
        for( int i=0; i<num_tables; i++ )
        {
            printf( OTF_DUMP_TABLE_SEPARATOR OTF_DUMP_NL );
            printf( "platformID: %d"OTF_DUMP_NL, UTTF_BE16TOH(encodingrecArray[i].platformID) );        
            printf( "encodingID: %d"OTF_DUMP_NL, UTTF_BE16TOH(encodingrecArray[i].encodingID) );        
            printf( "offset:     %d"OTF_DUMP_NL, UTTF_BE32TOH(encodingrecArray[i].offset) );        
        }
        printf( OTF_DUMP_TABLE_SEPARATOR OTF_DUMP_NL );
        printf( OTF_DUMP_NL );

        //Dump contents of each cmap
        for( int i=0; i<num_tables; i++ )
        {
            uint8_t* subtable_ptr = ((uint8_t*)(info_ptr->cmapPtr) + UTTF_BE32TOH(encodingrecArray[i].offset));
            uint16_t platform_id = UTTF_BE16TOH(encodingrecArray[i].platformID);
            uint16_t encoding_id = UTTF_BE16TOH(encodingrecArray[i].encodingID);

            printf( OTF_DUMP_CMAP_TABLE_START(platform_id, encoding_id) );
            otf_dump_tableCmapSubtable( info_ptr, (Uttf_Cmap_Subtable_t*)subtable_ptr );

        }        
        printf( OTF_DUMP_TABLE_SEPARATOR OTF_DUMP_TABLE_SEPARATOR OTF_DUMP_NL );
        printf( OTF_DUMP_NL );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
