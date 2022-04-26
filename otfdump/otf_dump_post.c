
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"


static void
otf_dump_PostFmt1Fmt2( Uttf_Post_Info_t* info_ptr )
{
    uint16_t num_glyphs;

    uttf_Post_NameCountGet( info_ptr, &num_glyphs );
    printf( "numGlyphs:     %d"OTF_DUMP_NL, num_glyphs );
    for( int i=0; i<num_glyphs; i++ )
    {
        char* name_ptr;
        uint8_t len;

        uttf_Post_NameFind( info_ptr, i, &len, &name_ptr );

        printf("%d : ", i);
        for( int c=0; c<len; c++ )
        {
            printf("%c", name_ptr[c]);
        }
        printf( OTF_DUMP_NL );
    }
}

void
otf_dump_Post( Uttf_Post_Info_t* info_ptr )
{
    printf( OTF_DUMP_SECTION_START("post") );
    if( info_ptr != NULL )
    {
        uint32_t format = UTTF_BE32TOH(info_ptr->postPtr->format);

        printf( "format:             %08X"OTF_DUMP_NL, format );
        printf( "italicAngle:        %08X"OTF_DUMP_NL, UTTF_BE32TOH(info_ptr->postPtr->italicAngle) );
        printf( "underlinePosition:  %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->postPtr->underlinePosition) );
        printf( "underlineThickness: %d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH(info_ptr->postPtr->underlineThickness) );
        printf( "isFixedPitch:       %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->postPtr->isFixedPitch) );
        printf( "minMemType42:       %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->postPtr->minMemType42) );
        printf( "maxMemType42:       %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->postPtr->maxMemType42) );
        printf( "minMemType1:        %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->postPtr->minMemType1) );
        printf( "maxMemType1:        %d"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->postPtr->maxMemType1) );

        printf( OTF_DUMP_NL );

        switch( format )
        {
            case UTTF_POST_TABLE_FORMAT_1:
            case UTTF_POST_TABLE_FORMAT_2:
            {
                otf_dump_PostFmt1Fmt2( info_ptr );
            }
            break;
            case UTTF_POST_TABLE_FORMAT_3:
            {
                // Nothing to do, no names in the table
            }
            break;
            default:
                printf( "post: Unsupported Format" );
        }

    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
