
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void
otf_dump_Hmtx( Uttf_Hmtx_Info_t* info_ptr )
{
    printf( OTF_DUMP_SECTION_START("hmtx") );

    printf( "idx\tadvanceWidth\tleftSideBearing"OTF_DUMP_NL );
    if( info_ptr != NULL )
    {
        for( uint16_t i=0; i < info_ptr->numMetrics; i++ )
        {
            printf( "%5d\t%d\t\t%d"OTF_DUMP_NL, i, UTTF_BE16TOH(info_ptr->longHorMetricArray[i].advanceWidth), (int16_t)UTTF_BE16TOH(info_ptr->longHorMetricArray[i].leftSideBearing) );
        }
        for( uint16_t i=0; i < info_ptr->numSideBearing; i++ )
        {
            printf( "%5d\t\t\t%d"OTF_DUMP_NL, (info_ptr->numMetrics + i), (int16_t)UTTF_BE16TOH(info_ptr->leftSideBearingArray[i]) );
        }
        printf( OTF_DUMP_NL );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}

