
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void
otf_dump_Head( Uttf_Head_t* table_ptr )
{
    printf( OTF_DUMP_SECTION_START("head") );
    if( table_ptr != NULL )
    {
        uint32_t version = UTTF_BE32TOH( table_ptr->version );

        printf( "version:            0x%08X"OTF_DUMP_NL, version );
        printf( "fontRevision:       0x%08X"OTF_DUMP_NL, UTTF_BE32TOH( table_ptr->fontRevision ) );
        printf( "checkSumAdjustment: 0x%08X"OTF_DUMP_NL, UTTF_BE32TOH( table_ptr->checkSumAdjustment ) );
        printf( "magicNumber:        0x%08X"OTF_DUMP_NL, UTTF_BE32TOH( table_ptr->magicNumber ) );
        printf( "flags:              0x%04X"OTF_DUMP_NL, UTTF_BE16TOH( table_ptr->flags ) );
        printf( "unitsPerEm:         %d"OTF_DUMP_NL, UTTF_BE16TOH( table_ptr->unitsPerEm ) );
        printf( "created:            0x%016llX"OTF_DUMP_NL, UTTF_BE64TOH( table_ptr->created ) );
        printf( "modified:           0x%016llX"OTF_DUMP_NL, UTTF_BE64TOH( table_ptr->modified ) );
        printf( "xMin:               %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->xMin ) );
        printf( "yMin:               %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->yMin ) );
        printf( "xMax:               %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->xMax ) );
        printf( "yMax:               %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->yMax ) );
        printf( "macStyle:           0x%04X"OTF_DUMP_NL, UTTF_BE16TOH( table_ptr->macStyle ) );
        printf( "lowestRecPPEM:      %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->lowestRecPPEM ) );
        printf( "fontDirectionHint:  %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->fontDirectionHint ) );
        printf( "indexToLocFormat:   %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->indexToLocFormat ) );
        printf( "glyphDataFormat:    %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->glyphDataFormat ) );
        printf( OTF_DUMP_NL );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}

