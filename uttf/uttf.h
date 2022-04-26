/*****************************************************************************/
/**
 * Micro-ttf project is meant to provide a very small TrueType/OpenType file parser
 * for embedded systems. While this project can compile for other systems
 * it's development is targeted for ARM Cortex M microcontrollers. Several ARM
 * specific speed and size optimizations are made that may not translate
 * properly when using other compilers or hardware architectures. 
 * 
 * It's expected that users are also carefully stripping and formatting the
 * OpenType font files so only the necessary tables and glyphs are present. This
 * project takes advantage of the fact that random OpenType font files will not
 * be used so many optional fields and features of OpenType are not necessarsy. 
 * 
 * Goal: The goal is to provide the most optimized (size-first, speed-second)
 *       functions to lookup a glyph within a stripped down (size-reduced)
 *       true type font.
 * 
 * Note: Currently, this project does not contain a rendering function. It
 *       relies on stb-truetype written by Sean Barrett. STB truetype is 
 *       a fine standalone rendering system and this project duplicates
 *       much of the functionality of the ttf parsing from stb-truetype.
 *       the point of this wrapper is to improve on the speed by adding to
 *       the code size and complexity.
 */
#ifndef UTTF_H
#define UTTF_H

#include <stdint.h>
#include "uttf_log.h"
#include "uttf_endian.h"
#include "uttf_system.h"
#include "uttf_cmap.h"
#include "uttf_os2.h"
#include "uttf_maxp.h"
#include "uttf_loca.h"
#include "uttf_head.h"
#include "uttf_hhea.h"
#include "uttf_hmtx.h"
#include "uttf_post.h"
#include "uttf_name.h"
#include "uttf_glyf.h"
#include "uttf_gdef.h"
#include "uttf_gpos.h"

#define UTTF_OFFSET_TABLE_REC_TAG_CMAP 'cmap'
#define UTTF_OFFSET_TABLE_REC_TAG_HEAD 'head'
#define UTTF_OFFSET_TABLE_REC_TAG_HHEA 'hhea'
#define UTTF_OFFSET_TABLE_REC_TAG_HMTX 'hmtx'
#define UTTF_OFFSET_TABLE_REC_TAG_MAXP 'maxp'
#define UTTF_OFFSET_TABLE_REC_TAG_NAME 'name'
#define UTTF_OFFSET_TABLE_REC_TAG_OS2  'OS/2'
#define UTTF_OFFSET_TABLE_REC_TAG_POST 'post'

#define UTTF_OFFSET_TABLE_REC_TAG_GLYF 'glyf'
#define UTTF_OFFSET_TABLE_REC_TAG_LOCA 'loca'

#define UTTF_OFFSET_TABLE_REC_TAG_GDEF 'GDEF'
#define UTTF_OFFSET_TABLE_REC_TAG_GPOS 'GPOS'
#define UTTF_OFFSET_TABLE_REC_TAG_GSUB 'GSUB'


typedef PACKED_STRUCT(Uttf_OffsetTableRec_s) {
    uint32_t tag;
    uint32_t checksum;
    uint32_t offset;
    uint32_t length;
} Uttf_OffsetTableRec_t;

typedef PACKED_STRUCT(Uttf_OffsetTable_s) {
    uint32_t              sfntVersion;
    uint16_t              numTables;
    uint16_t              searchRange;
    uint16_t              entrySelector;
    uint16_t              rangeShift;
    Uttf_OffsetTableRec_t tableArray[];
} Uttf_OffsetTable_t;

typedef struct Uttf_FileInfo_s {
    uint8_t*            filePtr;
    uint8_t*            eofPtr;
    Uttf_OffsetTable_t* offsetTablePtr;
    Uttf_Os2_Info_t     os2Info;
    Uttf_Cmap_Info_t    cmapInfo;
    Uttf_Maxp_Info_t    maxpInfo;
    Uttf_Head_Info_t    headInfo;
    Uttf_Loca_Info_t    locaInfo;
    Uttf_Hhea_Info_t    hheaInfo;
    Uttf_Hmtx_Info_t    hmtxInfo;
    Uttf_Post_Info_t    postInfo;
    Uttf_Name_Info_t    nameInfo;
    Uttf_Glyf_Info_t    glyfInfo;
    Uttf_Gdef_Info_t    gdefInfo;
    Uttf_Gpos_Info_t    gposInfo;
} Uttf_FileInfo_t;

Uttf_Status_t
uttf_Open( Uttf_FileInfo_t* file_info_ptr,
           uint8_t*         file_ptr,
           size_t           file_size );


#define MEM_DUMP(_ptr, _len)                      \
{                                                 \
    for( int i=0; i<(_len); i++ )                 \
    {                                             \
        printf( "%02X", ((uint8_t*)(_ptr))[i] );  \
        if( ((i + 1) % 16) == 0 )                 \
            printf("\n");                         \
        else                                      \
            printf(" ");                          \
    }                                             \
}

#define MEM_DUMP_OFFSET(_ptr, _offset, _len)                \
{                                                           \
    for( int i=0; i<(_len); i++ )                           \
    {                                                       \
        printf( "%02X", ((uint8_t*)(_ptr))[(_offset)+i] );  \
        if( ((i + 1) % 16) == 0 )                           \
            printf("\n");                                   \
        else                                                \
            printf(" ");                                    \
    }                                                       \
}
#endif
