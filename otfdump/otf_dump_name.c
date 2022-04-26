
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"


void
otf_dump_Name( Uttf_Name_Info_t* info_ptr )
{
    printf( OTF_DUMP_SECTION_START("name") );
    if( info_ptr != NULL )
    {
        printf( "format:             %04X"OTF_DUMP_NL, UTTF_BE16TOH(info_ptr->namePtr->format) );
        printf( "count:              %d"OTF_DUMP_NL,   UTTF_BE16TOH(info_ptr->namePtr->count) );
        printf( "stringOffset:       %d"OTF_DUMP_NL,   UTTF_BE16TOH(info_ptr->namePtr->stringOffset) );

        for( Uttf_Name_NameId_t name_id = UTTF_NAME_ID_COPYRIGHT;
             (name_id <= UTTF_NAME_ID_VARIATIONS_POSTSCRIPT_NAME_PREFIX);
             name_id++ )
        {
            uint16_t str_len;
            char*   str_ptr;

            uttf_Name_StringGet( info_ptr, name_id, &str_len, &str_ptr );

            printf( "id:%2d len:%4d str:", name_id, str_len );
            while( str_len-- != 0 )
            {
                printf("%c", *str_ptr++);
            }
            printf( OTF_DUMP_NL );
        }
        printf( OTF_DUMP_NL );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
