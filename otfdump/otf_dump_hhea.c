
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void
otf_dump_Hhea( Uttf_Hhea_Info_t* info_ptr )
{
    printf( OTF_DUMP_SECTION_START("hhea") );
    if( info_ptr != NULL )
    {
        uint32_t version = UTTF_BE32TOH( info_ptr->hheaPtr->version );

        printf( "version:            0x%08X"OTF_DUMP_NL, version );
        printf( "ascent:                 %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->ascent) );
        printf( "descent:                %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->descent) );
        printf( "lineGap:                %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->lineGap) );
        printf( "advanceWidthMax:        %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->hheaPtr->advanceWidthMax) );
        printf( "minLeftSideBearing:     %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->minLeftSideBearing) );
        printf( "minRightSideBearing:    %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->minRightSideBearing) );
        printf( "xMaxExtent:             %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->xMaxExtent) );
        printf( "caretSlopeRise:         %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->caretSlopeRise) );
        printf( "caretSlopeRun:          %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->caretSlopeRun) );
        printf( "caretOffset:            %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->hheaPtr->caretOffset) );
        printf( "metricDataFormat:       %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->hheaPtr->metricDataFormat) );
        printf( "numOfLongHorMetrics:    %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->hheaPtr->numOfLongHorMetrics) );
        printf( OTF_DUMP_NL );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
