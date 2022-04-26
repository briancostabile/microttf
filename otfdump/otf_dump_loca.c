
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"


void
otf_dump_Loca( Uttf_Loca_Info_t* info_ptr,
               uint32_t          num_glyphs,
               int16_t           format )
{
    printf( OTF_DUMP_SECTION_START("loca") );
    if( info_ptr != NULL )
    {
        uint8_t* offsetPtr = (format == UTTF_LOCA_FORMAT_SHORT) ? (uint8_t*)(info_ptr->locaShortPtr) : (uint8_t*)(info_ptr->locaLongPtr);

        printf( "idx\toffset"OTF_DUMP_NL );
        for( uint32_t i=0; i<num_glyphs; i++ )
        {
            uint32_t offset;
            uttf_Loca_GlyphOffsetGet( info_ptr, i, &offset );
            printf( "%5d\t%6d"OTF_DUMP_NL, i, offset );
        }
        printf( OTF_DUMP_NL );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
