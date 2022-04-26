
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"


/*****************************************************************************/
void
otf_dump_OtfClassDefinition( uint8_t                   leading_spaces,
                             Uttf_Otf_ClassDefTable_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->format );

    OTF_DUMP_PRINTF( leading_spaces, OTF_DUMP_TABLE_SEPARATOR );
    OTF_DUMP_PRINTF( leading_spaces, OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "GlyphClassDefinitionTable format: %d"OTF_DUMP_NL, format ); 

    if( format == 1 )
    {
        uint16_t glyph_count = UTTF_BE16TOH( table_ptr->fmt1.glyphCount );
        uint16_t start_glyph_id = UTTF_BE16TOH( table_ptr->fmt1.startGlyphID );
        OTF_DUMP_PRINTF( leading_spaces, "Count:%d startGlyphID: %d"OTF_DUMP_NL, glyph_count, start_glyph_id ); 
        OTF_DUMP_PRINTF( leading_spaces, "[idx]glyphId\tclass"OTF_DUMP_NL ); 
        for( uint16_t i=0; i<glyph_count; i++ )
        {
            OTF_DUMP_PRINTF( leading_spaces, "[%2d]%d\t%d"OTF_DUMP_NL, i, (i + start_glyph_id), UTTF_BE16TOH( table_ptr->fmt1.classValueArray[i] ) ); 
        }
    }
    else if( format == 2 )
    {
        uint16_t range_count = UTTF_BE16TOH( table_ptr->fmt2.classRangeCount );
        OTF_DUMP_PRINTF( leading_spaces, "Count:%d"OTF_DUMP_NL, range_count ); 
        OTF_DUMP_PRINTF( leading_spaces, "[idx]start\tend\tclass"OTF_DUMP_NL ); 
        for( uint16_t i=0; i<range_count; i++ )
        {
            OTF_DUMP_PRINTF( leading_spaces, "[%2d]%d\t%d\t%d"OTF_DUMP_NL, i, 
                             UTTF_BE16TOH( table_ptr->fmt2.classRangeRecords[i].startGlyphID ), 
                             UTTF_BE16TOH( table_ptr->fmt2.classRangeRecords[i].endGlyphID ), 
                             UTTF_BE16TOH( table_ptr->fmt2.classRangeRecords[i].classValue ) ); 
        }
    }
}


/*****************************************************************************/
void
otf_dump_OtfCoverageTable( uint8_t                   leading_spaces,
                           Uttf_Otf_CoverageTable_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->format );

    OTF_DUMP_PRINTF( leading_spaces, OTF_DUMP_TABLE_SEPARATOR );
    OTF_DUMP_PRINTF( leading_spaces, OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "Coverage Table format: %d"OTF_DUMP_NL, format ); 
    if( format == 1 )
    {
        uint16_t glyph_count = UTTF_BE16TOH( table_ptr->fmt1.glyphCount );
        OTF_DUMP_PRINTF( leading_spaces, "Count:%d"OTF_DUMP_NL, glyph_count ); 
        OTF_DUMP_PRINTF( leading_spaces, "[idx]\tglyphId"OTF_DUMP_NL ); 
        for( uint16_t i=0; i<glyph_count; i++ )
        {
            OTF_DUMP_PRINTF( leading_spaces, "[%d]\t%d"OTF_DUMP_NL,
                             i,
                             UTTF_BE16TOH( table_ptr->fmt1.glyphArray[i] ) ); 
        }
    }
    else if( format == 2 )
    {
        uint16_t range_count = UTTF_BE16TOH( table_ptr->fmt2.rangeCount );
        OTF_DUMP_PRINTF( leading_spaces, "Count:%d"OTF_DUMP_NL, range_count ); 
        OTF_DUMP_PRINTF( leading_spaces, "[idx]\tstart\tend\tstartIdx"OTF_DUMP_NL ); 
        for( uint16_t i=0; i<range_count; i++ )
        {
            OTF_DUMP_PRINTF( leading_spaces, "[%2d]\t%d\t%d\t%d"OTF_DUMP_NL, i, 
                             UTTF_BE16TOH( table_ptr->fmt2.rangeRecords[i].startGlyphID ), 
                             UTTF_BE16TOH( table_ptr->fmt2.rangeRecords[i].endGlyphID ), 
                             UTTF_BE16TOH( table_ptr->fmt2.rangeRecords[i].startCoverageIndex ) ); 
        }
    }
}
