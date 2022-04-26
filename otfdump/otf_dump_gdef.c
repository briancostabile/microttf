
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

/*****************************************************************************/
void
otf_dump_GdefLigGlyphCaretValue( uint8_t                              leading_spaces,
                                 uint16_t                             idx,
                                 Uttf_Gdef_LigatureGlyphCaretValue_t* value_ptr )
{
    if( value_ptr )
    {
        uint16_t fmt = UTTF_BE16TOH( value_ptr->caretValueFormat );
        if( fmt == 1 )
        {
            OTF_DUMP_PRINTF( leading_spaces, "coordinate: %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( value_ptr->fmt1.coordinate ) );
        }
        else if ( fmt == 2 )
        {
            OTF_DUMP_PRINTF( leading_spaces, "caretValuePointIndex: %d"OTF_DUMP_NL, UTTF_BE16TOH( value_ptr->fmt2.caretValuePointIndex ) );
        }
        else if ( fmt == 3 )
        {
            OTF_DUMP_PRINTF( leading_spaces, "coordinate: %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( value_ptr->fmt3.coordinate ) );
            OTF_DUMP_PRINTF( leading_spaces, "deviceOffset: %d"OTF_DUMP_NL, UTTF_BE16TOH( value_ptr->fmt3.deviceOffset ) );
        }
        else
        {
            OTF_DUMP_PRINTF( leading_spaces, "LigGlyphCaret: Unknown Format %d"OTF_DUMP_NL, fmt );
        }
    }
}


/*****************************************************************************/
void
otf_dump_GdefLigGlyphTable( Uttf_Gdef_LigatureGlyphTable_t* table_ptr,
                            uint16_t                        glyph_id )
{
    if( table_ptr )
    {
        OTF_DUMP_PRINTF( 0, OTF_DUMP_TABLE_SEPARATOR );
        OTF_DUMP_PRINTF( 0, OTF_DUMP_NL );

        uint16_t caret_count = UTTF_BE16TOH( table_ptr->caretCount );
        OTF_DUMP_PRINTF( 0, "LigatureGlyphTable glyph_id: %d caret_count:%d"OTF_DUMP_NL, glyph_id, caret_count );

        for( uint16_t i; i<caret_count; i++ )
        {
            uint16_t offset = UTTF_BE16TOH( table_ptr->caretValueOffsets[i] );
            Uttf_Gdef_LigatureGlyphCaretValue_t* value_ptr = (Uttf_Gdef_LigatureGlyphCaretValue_t*)((uint8_t*)table_ptr + offset);
            OTF_DUMP_PRINTF( 4, "[%d] offset: %d"OTF_DUMP_NL, i, offset );
            otf_dump_GdefLigGlyphCaretValue( 4, i, value_ptr );
        }
    }
}


/*****************************************************************************/
void
otf_dump_GdefMarkGlyphSets( Uttf_Gdef_MarkGlyphSetsTable_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->format );

    OTF_DUMP_PRINTF( 0, OTF_DUMP_TABLE_SEPARATOR );
    OTF_DUMP_PRINTF( 0, OTF_DUMP_NL );
    OTF_DUMP_PRINTF( 0, "MarkGlyphsSetsTable"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( 0, "format: %d"OTF_DUMP_NL, format ); 

    if( format == 1 )
    {
        uint16_t glyph_count = UTTF_BE16TOH( table_ptr->markGlyphSetCount );
        OTF_DUMP_PRINTF( 0, "Count:%d"OTF_DUMP_NL, glyph_count ); 
        OTF_DUMP_PRINTF( 0, "[idx]\toffset"OTF_DUMP_NL ); 
        for( uint16_t i=0; i<glyph_count; i++ )
        {
            uint32_t offset = UTTF_BE32TOH( table_ptr->coverageOffsets[i] );
            OTF_DUMP_PRINTF( 0, "[%2d]\t%d"OTF_DUMP_NL, i, offset ); 
            Uttf_Otf_CoverageTable_t* coverage_table_ptr = (Uttf_Otf_CoverageTable_t*)((uint8_t*)table_ptr + offset);
            OTF_DUMP_PRINTF( 4, "***** MarkGlyphSet ****"OTF_DUMP_NL ); 
            otf_dump_OtfCoverageTable( 4, coverage_table_ptr );
        }
    }
    else 
    {
        printf( "Unsupported Format"OTF_DUMP_NL ); 
    }
#if 0    
    uint16_t coverage_idx = 0;
    printf( "Mark Set Coverage Indexes:"OTF_DUMP_NL );
    for( uint16_t i=0; i<0xFFFF; i++ )
    {
        if( uttf_Gdef_MarkSetGlyphCoverageIdx( info_ptr, i, &coverage_idx ) == UTTF_STATUS_NO_ERROR )
        {
            printf( "\t%d:\t%d"OTF_DUMP_NL, i, coverage_idx );
        }
    }
#endif
    printf( OTF_DUMP_NL );
}

/*****************************************************************************/
void
otf_dump_Gdef( Uttf_Gdef_Info_t* info_ptr )
{
    printf( OTF_DUMP_SECTION_START("gdef") );
    if( info_ptr->gdefPtr != NULL )
    {
        uint16_t majorVersion = UTTF_BE16TOH( info_ptr->gdefPtr->ver.majorVersion );
        uint16_t minorVersion = UTTF_BE16TOH( info_ptr->gdefPtr->ver.minorVersion );

        printf( "majorVersion:             %d"OTF_DUMP_NL, majorVersion );
        printf( "minorVersion:             %d"OTF_DUMP_NL, minorVersion );
        printf( "glyphClassDefOffset:      %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gdefPtr->v10.glyphClassDefOffset ) );
        printf( "attachListOffset:         %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gdefPtr->v10.attachListOffset ) );
        printf( "ligCaretListOffset:       %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gdefPtr->v10.ligCaretListOffset ) );
        printf( "markAttachClassDefOffset: %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gdefPtr->v10.markAttachClassDefOffset ) );
        if( minorVersion >= 2 )
        {
            printf( "markGlyphSetsDefOffset:   %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gdefPtr->v12.markGlyphSetsDefOffset ) ); 
        }
        if( minorVersion >= 3 )
        {
            printf( "itemVarStoreOffset:       %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gdefPtr->v13.itemVarStoreOffset ) ); 
        }

        if( info_ptr->gdefPtr->v10.glyphClassDefOffset != 0 )
        {
            Uttf_Otf_ClassDefTable_t* subtable_ptr = (Uttf_Otf_ClassDefTable_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH( info_ptr->gdefPtr->v10.glyphClassDefOffset ));
            OTF_DUMP_PRINTF( 0, "***** GlyphClassDef ****"OTF_DUMP_NL ); 
            otf_dump_OtfClassDefinition( 4, subtable_ptr );
        }

        if( info_ptr->gdefPtr->v10.ligCaretListOffset != 0 )
        {
            Uttf_Gdef_LigatureCaretList_t* subtable_ptr = (Uttf_Gdef_LigatureCaretList_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH( info_ptr->gdefPtr->v10.ligCaretListOffset ));
            Uttf_Otf_CoverageTable_t* coverage_table_ptr = (Uttf_Otf_CoverageTable_t*)((uint8_t*)subtable_ptr + UTTF_BE16TOH(subtable_ptr->coverageOffset));
            OTF_DUMP_PRINTF( 0, "***** LigatureCaretList ****"OTF_DUMP_NL ); 
            otf_dump_OtfCoverageTable( 4, coverage_table_ptr );
#if 0    
            for( uint32_t i=0; i<=0xFFFF; i++ )
            {
                Uttf_Gdef_LigatureGlyphTable_t* lig_glyph_table = uttf_Gdef_LigatureGlyphTableGet( info_ptr, i );
                otf_dump_GdefLigGlyphTable( lig_glyph_table, i );
            }
#endif
        }

        if( info_ptr->gdefPtr->v10.markAttachClassDefOffset != 0 )
        {
            Uttf_Otf_ClassDefTable_t* subtable_ptr = (Uttf_Otf_ClassDefTable_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH( info_ptr->gdefPtr->v10.glyphClassDefOffset ));
            OTF_DUMP_PRINTF( 0, "***** MarkAttachClassDef ****"OTF_DUMP_NL ); 
            otf_dump_OtfClassDefinition( 4, subtable_ptr );
        }

        if( (minorVersion >= 2) && (info_ptr->gdefPtr->v12.markGlyphSetsDefOffset != 0) )
        {
            Uttf_Gdef_MarkGlyphSetsTable_t* subtable_ptr = (Uttf_Gdef_MarkGlyphSetsTable_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH( info_ptr->gdefPtr->v12.markGlyphSetsDefOffset ));
            OTF_DUMP_PRINTF( 0, "***** MarkGlyphSetDef ****"OTF_DUMP_NL ); 
            otf_dump_GdefMarkGlyphSets( subtable_ptr );
        }

        if( (minorVersion >= 2) && (info_ptr->gdefPtr->v13.ligCaretListOffset != 0) )
        {
            
        }
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}

