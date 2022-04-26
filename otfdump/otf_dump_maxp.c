
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void
otf_dump_Maxp( Uttf_Maxp_t* table_ptr )
{
    printf( OTF_DUMP_SECTION_START("maxp") );
    if( table_ptr != NULL )
    {
        uint32_t version = UTTF_BE32TOH( table_ptr->version );

        printf( "version:               0x%08X"OTF_DUMP_NL, version );
        if( version == UTTF_MAXP_TABLE_VERSION_V1 )
        {
            printf( "numGlyphs:             %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.numGlyphs) );
            printf( "maxPoints:             %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxPoints) );
            printf( "maxContours:           %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxContours) );
            printf( "maxComponentPoints:    %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxComponentPoints) );
            printf( "maxComponentContours:  %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxComponentContours) );
            printf( "maxZones:              %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxZones) );
            printf( "maxTwilightPoints:     %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxTwilightPoints) );
            printf( "maxStorage:            %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxStorage) );
            printf( "maxFunctionDefs:       %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxFunctionDefs) );
            printf( "maxInstructionDefs:    %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxInstructionDefs) );
            printf( "maxStackElements:      %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxStackElements) );
            printf( "maxSizeOfInstructions: %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxSizeOfInstructions) );
            printf( "maxComponentElements:  %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxComponentElements) );
            printf( "maxComponentDepth:     %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v1.maxComponentDepth) );
        }
        else if( version == UTTF_MAXP_TABLE_VERSION_V5 )
        {
            printf( "numGlyphs: %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->v5.numGlyphs) );
        }
        printf( OTF_DUMP_NL );

    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
