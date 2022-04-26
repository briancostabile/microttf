/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_GDEF_H
#define UTTF_GDEF_H

#include <stdint.h>
#include "uttf_system.h"
#include "uttf_otf.h"

typedef PACKED_STRUCT(Uttf_Gdef_MarkGlyphSetsTable_s) {
uint16_t format;                  // Format identifier == 1
uint16_t markGlyphSetCount;       // Number of mark glyph sets defined
uint32_t coverageOffsets[];       //Array of offsets to mark glyph set coverage tables.
} Uttf_Gdef_MarkGlyphSetsTable_t;

typedef PACKED_STRUCT(Uttf_Gdef_LigatureGlyphCaretValue_Fmt1_s) {
    uint16_t caretValueFormat; // Format identifier: format = 1
    int16_t  coordinate;       // X or Y value, in design units
} Uttf_Gdef_LigatureGlyphCaretValue_Fmt1_t;

typedef PACKED_STRUCT(Uttf_Gdef_LigatureGlyphCaretValue_Fmt2_s) {
    uint16_t caretValueFormat;     // Format identifier: format = 2
    uint16_t caretValuePointIndex; // Contour point index on glyph
} Uttf_Gdef_LigatureGlyphCaretValue_Fmt2_t;

typedef PACKED_STRUCT(Uttf_Gdef_LigatureGlyphCaretValue_Fmt3_s) {
    uint16_t caretValueFormat; // Format identifier-format = 3
    int16_t  coordinate;       // X or Y value, in design units
    uint16_t deviceOffset;     // Offset to Device table (non-variable font) / Variation Index table (variable font) for X or Y value-from beginning of CaretValue table
} Uttf_Gdef_LigatureGlyphCaretValue_Fmt3_t;

typedef PACKED_UNION(Uttf_Gdef_LigatureGlyphCaretValue_u) {
    uint16_t                                 caretValueFormat;
    Uttf_Gdef_LigatureGlyphCaretValue_Fmt1_t fmt1;
    Uttf_Gdef_LigatureGlyphCaretValue_Fmt2_t fmt2;
    Uttf_Gdef_LigatureGlyphCaretValue_Fmt3_t fmt3;
} Uttf_Gdef_LigatureGlyphCaretValue_t;

typedef PACKED_STRUCT(Uttf_Gdef_LigatureGlyphTable_s) {
    uint16_t caretCount;          // Number of CaretValue tables for this ligature (components - 1)
    uint16_t caretValueOffsets[]; // Array of offsets to CaretValue tables, from beginning of LigGlyph table — in increasing coordinate order
} Uttf_Gdef_LigatureGlyphTable_t;

typedef PACKED_STRUCT(Uttf_Gdef_LigatureCaretList_s) {
    uint16_t coverageOffset;    // Offset to Coverage table - from beginning of LigCaretList table
    uint16_t ligGlyphCount;     // Number of ligature glyphs
    uint16_t ligGlyphOffsets[]; // Array of offsets to LigGlyph tables, from beginning of LigCaretList table —in Coverage Index order
} Uttf_Gdef_LigatureCaretList_t;

typedef PACKED_STRUCT(Uttf_Gdef_AttachPointTable_s) {
    uint16_t pointCount;     // Number of attachment points on this glyph
    uint16_t pointIndices[]; // Array of contour point indices -in increasing numerical order
} Uttf_Gdef_AttachPointTable_t;

typedef PACKED_STRUCT(Uttf_Gdef_AttachList_s) {
    uint16_t coverageOffset;       // Offset to Coverage table - from beginning of AttachList table
    uint16_t glyphCount;           // Number of glyphs with attachment points
    uint16_t attachPointOffsets[]; // Array of offsets to AttachPoint tables-from beginning of AttachList table-in Coverage Index order
} Uttf_Gdef_AttachList_t;

typedef PACKED_STRUCT(Uttf_Gdef_Hdr_Ver_s) {
    uint16_t majorVersion; // Major version of the GDEF table
    uint16_t minorVersion; // Minor version of the GDEF table
}  Uttf_Gdef_Hdr_Ver_t;

typedef PACKED_STRUCT(Uttf_Gdef_Hdr_V1P0_s) {
    Uttf_Gdef_Hdr_Ver_t ver;
    uint16_t glyphClassDefOffset;      // Offset to class definition table for glyph type, from beginning of GDEF header (may be NULL)
    uint16_t attachListOffset;         // Offset to attachment point list table, from beginning of GDEF header (may be NULL)
    uint16_t ligCaretListOffset;       // Offset to ligature caret list table, from beginning of GDEF header (may be NULL)
    uint16_t markAttachClassDefOffset; // Offset to class definition table for mark attachment type, from beginning of GDEF header (may be NULL)
} Uttf_Gdef_Hdr_V1P0_t;

typedef PACKED_STRUCT(Uttf_Gdef_Hdr_V1P2_s) {
    Uttf_Gdef_Hdr_Ver_t ver;
    uint16_t glyphClassDefOffset;      // Offset to class definition table for glyph type, from beginning of GDEF header (may be NULL)
    uint16_t attachListOffset;         // Offset to attachment point list table, from beginning of GDEF header (may be NULL)
    uint16_t ligCaretListOffset;       // Offset to ligature caret list table, from beginning of GDEF header (may be NULL)
    uint16_t markAttachClassDefOffset; // Offset to class definition table for mark attachment type, from beginning of GDEF header (may be NULL)
    uint16_t markGlyphSetsDefOffset;   // Offset to the table of mark glyph set definitions, from beginning of GDEF header (may be NULL)
} Uttf_Gdef_Hdr_V1P2_t;

typedef PACKED_STRUCT(Uttf_Gdef_Hdr_V1P3_s) {
    Uttf_Gdef_Hdr_Ver_t ver;
    uint16_t glyphClassDefOffset;      // Offset to class definition table for glyph type, from beginning of GDEF header (may be NULL)
    uint16_t attachListOffset;         // Offset to attachment point list table, from beginning of GDEF header (may be NULL)
    uint16_t ligCaretListOffset;       // Offset to ligature caret list table, from beginning of GDEF header (may be NULL)
    uint16_t markAttachClassDefOffset; // Offset to class definition table for mark attachment type, from beginning of GDEF header (may be NULL)
    uint16_t markGlyphSetsDefOffset;   // Offset to the table of mark glyph set definitions, from beginning of GDEF header (may be NULL)
    uint32_t itemVarStoreOffset;       // Offset to the Item Variation Store table, from beginning of GDEF header (may be NULL)
} Uttf_Gdef_Hdr_V1P3_t;

typedef PACKED_UNION(Uttf_Gdef_u) {
    Uttf_Gdef_Hdr_Ver_t  ver;
    Uttf_Gdef_Hdr_V1P0_t v10;
    Uttf_Gdef_Hdr_V1P2_t v12;
    Uttf_Gdef_Hdr_V1P3_t v13;
} Uttf_Gdef_t;

typedef struct Uttf_Gdef_Info_s {
    Uttf_Gdef_t* gdefPtr;
} Uttf_Gdef_Info_t;


/*****************************************************************************/
Uttf_Otf_Class_t
uttf_Gdef_ClassGet( Uttf_Gdef_Info_t* info_ptr,
                    Uttf_GlyphIdx_t   glyph_idx );

/*****************************************************************************/
Uttf_Status_t
uttf_Gdef_MarkSetGlyphCoverageIdx( Uttf_Gdef_Info_t*       info_ptr,
                                   Uttf_GlyphIdx_t         glyph_idx,
                                   Uttf_Otf_CoverageIdx_t* coverage_idx_ptr );

/*****************************************************************************/
Uttf_Status_t
uttf_Gdef_Open( Uttf_Gdef_t*      table_ptr,
                uint32_t          length,
                Uttf_Gdef_Info_t* info_ptr );

/*****************************************************************************/
Uttf_Gdef_LigatureGlyphTable_t*
uttf_Gdef_LigatureGlyphTableGet( Uttf_Gdef_Info_t* info_ptr,
                                 Uttf_GlyphIdx_t   glyph_idx );

#endif