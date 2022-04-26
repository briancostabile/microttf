/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_POST_H
#define UTTF_POST_H

#include <stdint.h>
#include "uttf_system.h"

#define UTTF_POST_TABLE_FORMAT_1    0x00010000
#define UTTF_POST_TABLE_FORMAT_2    0x00020000
#define UTTF_POST_TABLE_FORMAT_V2P5 0x00025000
#define UTTF_POST_TABLE_FORMAT_3    0x00030000
#define UTTF_POST_TABLE_FORMAT_4    0x00040000


typedef PACKED_STRUCT(Uttf_Post_SubtableFmt2_s) {
    uint16_t numGlyphs;        // Number of glyphs (this should be the same as numGlyphs in 'maxp' table).
    uint16_t glyphNameIndex[]; // This is not an offset, but is the ordinal number of the glyph in 'post' string tables.
} Uttf_Post_SubtableFmt2_t;

typedef PACKED_STRUCT(Uttf_Post_Table_u) {
    uint32_t       format;
    uint32_t       italicAngle;
    int16_t        underlinePosition;
    int16_t        underlineThickness;
    uint32_t       isFixedPitch;
    uint32_t       minMemType42;
    uint32_t       maxMemType42;
    uint32_t       minMemType1;
    uint32_t       maxMemType1;
} Uttf_Post_t;

typedef struct Uttf_Post_Info_s {
    Uttf_Post_t* postPtr;
} Uttf_Post_Info_t;


Uttf_Status_t
uttf_Post_Open( Uttf_Post_t*      table_ptr,
                uint32_t          length,
                Uttf_Post_Info_t* info_ptr );

Uttf_Status_t
uttf_Post_NameFind( Uttf_Post_Info_t* info_ptr,
                    Uttf_GlyphIdx_t   glyph_idx,
                    uint8_t*          name_len_ptr,
                    char**            name_ptr ); // not null terminated

Uttf_Status_t
uttf_Post_NameCountGet( Uttf_Post_Info_t* info_ptr,
                        uint16_t*         num_names_ptr );

#endif
