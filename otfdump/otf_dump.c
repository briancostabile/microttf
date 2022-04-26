
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void
otf_dump_leading_spaces( uint8_t count )
{
    while( count-- ){ printf( " " ); }
}

int main( int32_t argc, char** argv )
{
    if( argc != 2 )
    {
        printf( "Usage %s <filename>\n"OTF_DUMP_NL, argv[0] );
        return( -1 );
    }
    
    char* fname = argv[1];
    FILE* fp = fopen( fname, "rb+" );
    if( fp < 0 )
    {
        printf( "%s Failed to Open!\n"OTF_DUMP_NL, fname );
        return( -1 );
    }

    fseek( fp, 0L, SEEK_END );
    int sz = ftell( fp );
    fseek( fp, 0L, SEEK_SET );

    printf( "%s is %d bytes long\n"OTF_DUMP_NL, fname, sz );

    // Read entire file into contiguous memory buffer
    uint8_t* fb = (uint8_t*)malloc( sz );

    if( fb == NULL )
    {
        fclose( fp );
        printf( "Could not allocate %d byte buffer\n"OTF_DUMP_NL, sz );
        return( -1 );
    }

    int rsz = fread( fb, 1, sz, fp );
    fclose( fp );
    if( rsz != sz )
    {
        free( fb );
        printf( "Read Size mismatch %d:%d\n"OTF_DUMP_NL, rsz, sz );
        return( -1 );
    }

    Uttf_FileInfo_t file_info;
    uttf_Open( &file_info, fb, sz );

    printf( OTF_DUMP_SECTION_START( "FileHdr" ) );
    printf( "sfntVersion:   0x%08X"OTF_DUMP_NL, UTTF_BE32TOH(file_info.offsetTablePtr->sfntVersion) );
    printf( "numTables:     %d"OTF_DUMP_NL,     UTTF_BE16TOH(file_info.offsetTablePtr->numTables) );
    printf( "searchRange:   %d"OTF_DUMP_NL,     UTTF_BE16TOH(file_info.offsetTablePtr->searchRange) );
    printf( "entrySelector: %d"OTF_DUMP_NL,     UTTF_BE16TOH(file_info.offsetTablePtr->entrySelector) );
    printf( "rangeShift:    %d"OTF_DUMP_NL,     UTTF_BE16TOH(file_info.offsetTablePtr->rangeShift) );
    printf( OTF_DUMP_NL );

    printf( OTF_DUMP_SECTION_START( "OffsetTables" ) );
    size_t num_tables = UTTF_BE16TOH( file_info.offsetTablePtr->numTables );
    for( int i=0; i < num_tables; i++ )
    {
        Uttf_OffsetTableRec_t* offset_table_rec_ptr = &(file_info.offsetTablePtr->tableArray[i]);
        uint32_t tag = UTTF_BE32TOH( offset_table_rec_ptr->tag );
        printf( OTF_DUMP_TABLE_SEPARATOR OTF_DUMP_NL );
        printf( "Table:    %c%c%c%c"OTF_DUMP_NL, (char)(tag >> 24), (char)(tag >> 16), (char)(tag >> 8), (char)(tag >> 0) );
        printf( "Checksum: 0x%08X"OTF_DUMP_NL,   UTTF_BE32TOH(offset_table_rec_ptr->checksum) );
        printf( "Offset:   %d"OTF_DUMP_NL,       UTTF_BE32TOH(offset_table_rec_ptr->offset) );
        printf( "Length:   %d"OTF_DUMP_NL,       UTTF_BE32TOH(offset_table_rec_ptr->length) );
    }
    printf( OTF_DUMP_TABLE_SEPARATOR OTF_DUMP_NL );
    printf( OTF_DUMP_NL );

    otf_dump_Os2( file_info.os2Info.os2Ptr );
    otf_dump_Cmap( &(file_info.cmapInfo) );
    otf_dump_Maxp( file_info.maxpInfo.maxpPtr );
    otf_dump_Head( file_info.headInfo.headPtr );
    otf_dump_Loca( &(file_info.locaInfo),
                  UTTF_BE16TOH(file_info.maxpInfo.maxpPtr->v1.numGlyphs),
                  UTTF_BE16TOH(file_info.headInfo.headPtr->indexToLocFormat) );
    otf_dump_Hhea( &(file_info.hheaInfo) );
    otf_dump_Hmtx( &(file_info.hmtxInfo) );
    otf_dump_Post( &(file_info.postInfo) );
    otf_dump_Name( &(file_info.nameInfo) );
    otf_dump_Glyf( &(file_info.glyfInfo),
                   &(file_info.locaInfo),
                   UTTF_BE16TOH(file_info.maxpInfo.maxpPtr->v1.numGlyphs) );

    otf_dump_Gdef( &(file_info.gdefInfo) );
    otf_dump_Gpos( &(file_info.gposInfo) );

    free( fb );
    
    return( 0 );
}