/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_GPOS_H
#define UTTF_GPOS_H

#include <stdint.h>
#include "uttf_system.h"
#include "uttf_otf.h"

typedef enum {
    UTTF_GPOS_VALUE_FORMAT_FLAGS_X_PLACEMENT        = 0x0001, // Includes horizontal adjustment for placement
    UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_PLACEMENT        = 0x0002, // Includes vertical adjustment for placement
    UTTF_GPOS_VALUE_FORMAT_FLAGS_X_ADVANCE          = 0x0004, // Includes horizontal adjustment for advance
    UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_ADVANCE          = 0x0008, // Includes vertical adjustment for advance
    UTTF_GPOS_VALUE_FORMAT_FLAGS_X_PLACEMENT_DEVICE = 0x0010, // Includes Device table (non-variable font) / VariationIndex table (variable font) for horizontal placement
    UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_PLACEMENT_DEVICE = 0x0020, // Includes Device table (non-variable font) / VariationIndex table (variable font) for vertical placement
    UTTF_GPOS_VALUE_FORMAT_FLAGS_X_ADVANCE_DEVICE   = 0x0040, // Includes Device table (non-variable font) / VariationIndex table (variable font) for horizontal advance
    UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_ADVANCE_DEVICE   = 0x0080  // Includes Device table (non-variable font) / VariationIndex table (variable font) for vertical advance
} Uttf_Gpos_ValueFormatFlags_t;

/*******************
 * Anchor Table
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_AnchorTableFmt1_s) {
    uint16_t anchorFormat;  // Format identifier, = 1
    int16_t  xCoordinate;   // Horizontal value, in design units
    int16_t  yCoordinate;   // Vertical value, in design units
} Uttf_Gpos_AnchorTableFmt1_t;

typedef PACKED_STRUCT(Uttf_Gpos_AnchorTableFmt2_s) {
    uint16_t anchorFormat;  // Format identifier, = 2
    int16_t  xCoordinate;   // Horizontal value, in design units
    int16_t  yCoordinate;   // Vertical value, in design units
    uint16_t anchorPoint;   // Index to glyph contour point
} Uttf_Gpos_AnchorTableFmt2_t;

typedef PACKED_STRUCT(Uttf_Gpos_AnchorTableFmt3_s) {
    uint16_t anchorFormat;  // Format identifier, = 3
    int16_t  xCoordinate;   // Horizontal value, in design units
    int16_t  yCoordinate;   // Vertical value, in design units
    uint16_t xDeviceOffset; // Offset to Device table (non-variable font) / VariationIndex table (variable font) for X coordinate, from beginning of Anchor table (may be NULL)
    uint16_t yDeviceOffset; // Offset to Device table (non-variable font) / VariationIndex table (variable font) for Y coordinate, from beginning of Anchor table (may be NULL)
} Uttf_Gpos_AnchorTableFmt3_t;

typedef PACKED_UNION(Uttf_Gpos_AnchorTable_s) {
    uint16_t                    anchorFormat;
    Uttf_Gpos_AnchorTableFmt1_t fmt1;
    Uttf_Gpos_AnchorTableFmt2_t fmt2;
    Uttf_Gpos_AnchorTableFmt3_t fmt3;
} Uttf_Gpos_AnchorTable_t;

/*******************
 * Mark Table
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_MarkArrayRecord_s) {
    uint16_t markClass;        // Class defined for the associated mark.
    uint16_t markAnchorOffset; // Offset to Anchor table, from beginning of MarkArray table.
} Uttf_Gpos_MarkArrayRecord_t;

typedef PACKED_STRUCT(Uttf_Gpos_MarkArrayTable_s) {
    uint16_t                    markCount;       // Number of MarkRecords
    Uttf_Gpos_MarkArrayRecord_t markRecords[]; // Array of MarkRecords, ordered by corresponding glyphs in the associated mark Coverage table.
} Uttf_Gpos_MarkArrayTable_t;

/*******************
 * Lookup Type 1
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_SinglePosFmt1_s) {
    uint16_t                posFormat;      // Format identifier: format = 1
    uint16_t                coverageOffset; // Offset to Coverage table, from beginning of SinglePos subtable.
    uint16_t                valueFormat;    // Defines the types of data in the ValueRecord.
} Uttf_Gpos_SinglePosFmt1_t;

typedef PACKED_STRUCT(Uttf_Gpos_SinglePosFmt2_s) {
    uint16_t                posFormat;      // Format identifier: format = 2
    uint16_t                coverageOffset; // Offset to Coverage table, from beginning of SinglePos subtable.
    uint16_t                valueFormat;    // Defines the types of data in the ValueRecord.
    uint16_t                valueCount;     // Number of ValueRecords — must equal glyphCount in the Coverage table.
} Uttf_Gpos_SinglePosFmt2_t;

typedef PACKED_UNION(Uttf_Gpos_SinglePos_u) {
    uint16_t                  posFormat; // Format identifier
    Uttf_Gpos_SinglePosFmt1_t fmt1;
    Uttf_Gpos_SinglePosFmt2_t fmt2;
} Uttf_Gpos_SinglePos_t;

/*******************
 * Lookup Type 4
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_BaseArrayTable_s) {
    uint16_t baseCount;     // Number of BaseRecords
    uint16_t baseRecords[]; // Array of BaseRecords, in order of baseCoverage Index.
} Uttf_Gpos_BaseArrayTable_t;


typedef PACKED_STRUCT(Uttf_Gpos_MarkBasePosFmt1_s) {
    uint16_t posFormat;          // Format identifier: format = 1
    uint16_t markCoverageOffset; // Offset to markCoverage table, from beginning of MarkBasePos subtable.
    uint16_t baseCoverageOffset; // Offset to baseCoverage table, from beginning of MarkBasePos subtable.
    uint16_t markClassCount;     // Number of classes defined for marks
    uint16_t markArrayOffset;    // Offset to MarkArray table, from beginning of MarkBasePos subtable.
    uint16_t baseArrayOffset;    // Offset to BaseArray table, from beginning of MarkBasePos subtable.
} Uttf_Gpos_MarkBasePosFmt1_t;

typedef PACKED_UNION(Uttf_Gpos_MarkBasePos_u) {
    uint16_t                    posFormat; // Format identifier: format = 1
    Uttf_Gpos_MarkBasePosFmt1_t fmt1;
} Uttf_Gpos_MarkBasePos_t;

/*******************
 * Lookup Type 5
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_LigAttachTable_s) {
    uint16_t componentCount;     // Number of LigatureAttach table offsets
    uint16_t componentRecords[]; // rray of offsets to LigatureAttach tables. Offsets are from beginning of LigatureArray table, ordered by ligatureCoverage index.
} Uttf_Gpos_LigAttachTable_t;

typedef PACKED_STRUCT(Uttf_Gpos_LigArrayTable_s) {
    uint16_t ligatureCount;           // Number of LigatureAttach table offsets
    uint16_t ligatureAttachOffsets[]; // Array of offsets to LigatureAttach tables. Offsets are from beginning of LigatureArray table, ordered by ligatureCoverage index.
} Uttf_Gpos_LigArrayTable_t;

typedef PACKED_STRUCT(Uttf_Gpos_MarkLigPosFmt1_s) {
    uint16_t posFormat;              // Format identifier: format = 1
    uint16_t markCoverageOffset;     // Offset to markCoverage table, from beginning of MarkBasePos subtable.
    uint16_t ligatureCoverageOffset; // Offset to ligatureCoverage table, from beginning of MarkLigPos subtable.
    uint16_t markClassCount;         // Number of classes defined for marks
    uint16_t markArrayOffset;        // Offset to MarkArray table, from beginning of MarkBasePos subtable.
    uint16_t ligatureArrayOffset;    // Offset to LigatureArray table, from beginning of MarkLigPos subtable.
} Uttf_Gpos_MarkLigPosFmt1_t;

typedef PACKED_UNION(Uttf_Gpos_MarkLigPos_u) {
    uint16_t                   posFormat; // Format identifier: format = 1
    Uttf_Gpos_MarkLigPosFmt1_t fmt1;
} Uttf_Gpos_MarkLigPos_t;

/*******************
 * Lookup Type 6
 ******************/

typedef PACKED_STRUCT(Uttf_Gpos_Mark2ArrayTable_s) {
    uint16_t mark2Count;     // Number of Mark2 records
    uint16_t mark2Records[]; // Array of Mark2Records, in Coverage order.
} Uttf_Gpos_Mark2ArrayTable_t;


typedef PACKED_STRUCT(Uttf_Gpos_MarkMarkPosFmt1_s) {
    uint16_t posFormat;              // Format identifier: format = 1
    uint16_t mark1CoverageOffset;    // Offset to Combining Mark Coverage table, from beginning of MarkMarkPos subtable.
    uint16_t mark2CoverageOffset;    // Offset to Base Mark Coverage table, from beginning of MarkMarkPos subtable.
    uint16_t markClassCount;         // Number of Combining Mark classes defined
    uint16_t mark1ArrayOffset;       // Offset to MarkArray table for mark1, from beginning of MarkMarkPos subtable.
    uint16_t mark2ArrayOffset;       // Offset to Mark2Array table for mark2, from beginning of MarkMarkPos subtable.
} Uttf_Gpos_MarkMarkPosFmt1_t;

typedef PACKED_UNION(Uttf_Gpos_MarkMarkPos_u) {
    uint16_t                   posFormat; // Format identifier: format = 1
    Uttf_Gpos_MarkMarkPosFmt1_t fmt1;
} Uttf_Gpos_MarkMarkPos_t;

/*******************
 * Lookup Type 7
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_PosLookupRecord_s) {
    uint16_t sequenceIndex;   // Index (zero-based) to input glyph sequence
    uint16_t lookupListIndex; // Index (zero-based) into the LookupList for the Lookup table to apply to that position in the glyph sequence.
} Uttf_Gpos_PosLookupRecord_t;

/*******************
 * Lookup Type 8
 ******************/
typedef struct Uttf_Gpos_ChainPosRuleTable_s {
    uint16_t  backtrackGlyphCount;  // Total number of glyphs in the backtrack sequence.
    uint16_t* backtrackSequence;    // Array of backtrack glyph IDs.
    uint16_t  inputGlyphCount;      // Total number of glyphs in the input sequence — includes the first glyph.
    uint16_t* inputSequencePtr;     // Array of input glyph IDs — start with second glyph.
    uint16_t  lookaheadGlyphCount;  // Total number of glyphs in the lookahead sequence.
    uint16_t* lookAheadSequencePtr;	// Array of lookahead glyph IDs.
    uint16_t  posCount;             // Number of PosLookupRecords
    Uttf_Gpos_PosLookupRecord_t* posLookupRecords; //Array of PosLookupRecords, in design order.
} Uttf_Gpos_ChainPosRuleTable_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainPosRuleTableBacktrack_s) {
    uint16_t backtrackGlyphCount; // Total number of glyphs in the backtrack sequence.
    uint16_t backtrackSequence[]; // Array of backtrack glyph IDs.
} Uttf_Gpos_ChainPosRuleTableBacktrack_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainPosRuleTableInput_s) {
    uint16_t inputGlyphCount; // Total number of glyphs in the input sequence — includes the first glyph.
    uint16_t inputSequence[]; // Array of input glyph IDs — start with second glyph.
} Uttf_Gpos_ChainPosRuleTableInput_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainPosRuleTableLookahead_s) {
    uint16_t lookaheadGlyphCount; // Total number of glyphs in the lookahead sequence.
    uint16_t lookaheadSequence[]; // Array of lookahead glyph IDs.
} Uttf_Gpos_ChainPosRuleTableLookahead_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainPosRuleTablePos_s) {
    uint16_t                    posCount;           // Number of PosLookupRecords
    Uttf_Gpos_PosLookupRecord_t posLookupRecords[]; // Array of PosLookupRecords, in design order.
} Uttf_Gpos_ChainPosRuleTablePos_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainPosRuleSetTable_s) {
    uint16_t chainPosRuleCount;     // Number of ChainPosRule tables
    uint16_t chainPosRuleOffsets[]; //Array of offsets to ChainPosRule tables. Offsets are from beginning of ChainPosRuleSet, ordered by preference.
} Uttf_Gpos_ChainPosRuleSetTable_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainContextPosFmt1_s) {
    uint16_t posFormat;                // Format identifier: format = 1
    uint16_t coverageOffset;           // Offset to Coverage table, from beginning of ChainContextPos subtable.
    uint16_t chainPosRuleSetCount;     // Number of ChainPosRuleSet tables
    uint16_t chainPosRuleSetOffsets[]; // Array of offsets to ChainPosRuleSet tables. Offsets are from beginning of ChainContextPos subtable, ordered by Coverage Index.
} Uttf_Gpos_ChainContextPosFmt1_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainPosClassSet_s) {
    uint16_t chainPosClassRuleCount;     // Number of ChainPosClassRule tables
    uint16_t chainPosClassRuleOffsets[]; // Array of offsets to ChainPosClassRule tables. Offsets are from beginning of ChainPosClassSet, ordered by preference.
} Uttf_Gpos_ChainPosClassSet_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainContextPosFmt2_s) {
    uint16_t posFormat;                 // Format identifier: format = 2
    uint16_t coverageOffset;            // Offset to Coverage table, from beginning of ChainContextPos subtable.
    uint16_t backtrackClassDefOffset;   // Offset to ClassDef table containing backtrack sequence context, from beginning of ChainContextPos subtable.
    uint16_t inputClassDefOffset;       // Offset to ClassDef table containing input sequence context, from beginning of ChainContextPos subtable.
    uint16_t lookaheadClassDefOffset;   // Offset to ClassDef table containing lookahead sequence context, from beginning of ChainContextPos subtable.
    uint16_t chainPosClassSetCount;     // Number of ChainPosClassSet tables
    uint16_t chainPosClassSetOffsets[]; // Array of offsets to ChainPosClassSet tables. Offsets are from beginning of ChainContextPos subtable, ordered by input class (may be NULL).
} Uttf_Gpos_ChainContextPosFmt2_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainContextPosFmt3_s) {
    uint16_t posFormat;                   // Format identifier: format = 3
    uint16_t backtrackGlyphCount;         // Number of glyphs in the backtrack sequence
    uint16_t backtrackCoverageOffsets[];  // Array of offsets to coverage tables for the backtrack sequence, in glyph sequence order.
} Uttf_Gpos_ChainContextPosFmt3_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainContextPosFmt3Input_s) {
    uint16_t inputGlyphCount;  // Number of glyphs in the backtrack sequence
    uint16_t inputSequence[];  // Offset to ClassDef table containing backtrack sequence context, from beginning of ChainContextPos subtable.
} Uttf_Gpos_ChainContextPosFmt3Input_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainContextPosFmt3Lookahead_s) {
    uint16_t lookaheadGlyphCount;         // Number of glyphs in lookahead sequence
    uint16_t lookaheadCoverageOffsets[];  // Offset to ClassDef table containing backtrack sequence context, from beginning of ChainContextPos subtable.
} Uttf_Gpos_ChainContextPosFmt3Lookahead_t;

typedef PACKED_STRUCT(Uttf_Gpos_ChainContextPosFmt3Pos_s) {
    uint16_t                    posCount;             // Number of PosLookupRecords
    Uttf_Gpos_PosLookupRecord_t posLookupRecords[];   // Array of PosLookupRecords, in design order.
} Uttf_Gpos_ChainContextPosFmt3Pos_t;

typedef PACKED_UNION(Uttf_Gpos_ChainContextPos_u) {
    uint16_t                        posformat;
    Uttf_Gpos_ChainContextPosFmt1_t fmt1;
    Uttf_Gpos_ChainContextPosFmt2_t fmt2;
    Uttf_Gpos_ChainContextPosFmt3_t fmt3;
} Uttf_Gpos_ChainContextPos_t;

/*******************
 * GPOS Header
 ******************/
typedef PACKED_STRUCT(Uttf_Gpos_Hdr_Ver_s) {
    uint16_t majorVersion; // Major version of the GPOS table
    uint16_t minorVersion; // Minor version of the GPOS table
} Uttf_Gpos_Hdr_Ver_t;

typedef PACKED_STRUCT(Uttf_Gpos_Hdr_V1P0_s) {
    Uttf_Gpos_Hdr_Ver_t ver;
    uint16_t scriptListOffset;    // Offset to ScriptList table, from beginning of GPOS table
    uint16_t featureListOffset;   // Offset to FeatureList table, from beginning of GPOS table
    uint16_t lookupListOffset;    // Offset to LookupList table, from beginning of GPOS table
} Uttf_Gpos_Hdr_V1P0_t;

typedef PACKED_STRUCT(Uttf_Gpos_Hdr_V1P1_s) {
    Uttf_Gpos_Hdr_Ver_t ver;
    uint16_t scriptListOffset;        // Offset to ScriptList table, from beginning of GPOS table
    uint16_t featureListOffset;       // Offset to FeatureList table, from beginning of GPOS table
    uint16_t lookupListOffset;        // Offset to LookupList table, from beginning of GPOS table
    uint32_t featureVariationsOffset; // Offset to FeatureVariations table, from beginning of GPOS table (may be NULL)
} Uttf_Gpos_Hdr_V1P1_t;

typedef PACKED_UNION(Uttf_Gpos_u) {
    Uttf_Gpos_Hdr_Ver_t  ver;
    Uttf_Gpos_Hdr_V1P0_t v10;
    Uttf_Gpos_Hdr_V1P1_t v11;
} Uttf_Gpos_t;

typedef struct Uttf_Gpos_Info_s {
    Uttf_Gpos_t* gposPtr;
} Uttf_Gpos_Info_t;


/*****************************************************************************/
Uttf_Status_t
uttf_Gpos_Open( Uttf_Gpos_t*      table_ptr,
                uint32_t          length,
                Uttf_Gpos_Info_t* info_ptr );

#endif