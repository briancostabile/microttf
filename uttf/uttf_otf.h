/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_OTF_H
#define UTTF_OTF_H

#include <stdint.h>
#include "uttf_system.h"

#define OTF_COVERAGE_TABLE_PTR( _ptr, _offset ) (Uttf_Otf_CoverageTable_t*)((uint8_t*)(_ptr) + (_offset))

typedef uint16_t Uttf_Otf_Class_t;
typedef uint16_t Uttf_Otf_CoverageIdx_t;

enum{
    UTTF_OTF_CLASS_ID_0           = 0,
    UTTF_OTF_CLASS_ID_1_BASE      = 1,
    UTTF_OTF_CLASS_ID_2_LIGATURE  = 2,
    UTTF_OTF_CLASS_ID_3_MARK      = 3,
    UTTF_OTF_CLASS_ID_4_COMPONENT = 4
};

typedef PACKED_STRUCT(Uttf_Otf_LookupTable_s) {
    uint16_t lookupType;        // Different enumerations for GSUB and GPOS
    uint16_t lookupFlag;        // Lookup qualifiers
    uint16_t subTableCount;     // Number of subtables for this lookup
    uint16_t subtableOffsets[]; // Array of offsets to lookup subtables, from beginning of Lookup table
} Uttf_Otf_LookupTable_t;

typedef PACKED_STRUCT(Uttf_Otf_LookupListTable_s) {
    uint16_t lookupCount; // Number of lookups in this table
    uint16_t lookups[];   // Array of offsets to Lookup tables, from beginning of LookupList — zero based (first lookup is Lookup index = 0)
} Uttf_Otf_LookupListTable_t;

typedef PACKED_STRUCT(Uttf_Otf_FeatureTable_s) {
    uint16_t featureParams;       // = NULL (reserved for offset to FeatureParams)
    uint16_t lookupIndexCount;    // Number of LookupList indices for this feature
    uint16_t lookupListIndices[]; // Array of indices into the LookupList — zero-based (first lookup is LookupListIndex = 0)
} Uttf_Otf_FeatureTable_t;

typedef PACKED_STRUCT(Uttf_Otf_FeatureRecord_s) {
    uint32_t featureTag;    // 4-byte feature identification tag
    uint16_t featureOffset; // Offset to Feature table, from beginning of FeatureList
} Uttf_Otf_FeatureRecord_t;

typedef PACKED_STRUCT(Uttf_Otf_FeatureListTable_s) {
    uint16_t                 featureCount;     // Number of FeatureRecords in this table
    Uttf_Otf_FeatureRecord_t featureRecords[]; // Array of FeatureRecords — zero-based (first feature has FeatureIndex = 0), listed alphabetically by feature tag
} Uttf_Otf_FeatureListTable_t;

typedef PACKED_STRUCT(Uttf_Otf_LangSysTable_s) {
    uint16_t lookupOrder;           // = NULL (reserved for an offset to a reordering table)
    uint16_t requiredFeatureIndex;  // Index of a feature required for this language system; if no required features = 0xFFFF
    uint16_t featureIndexCount;     // Number of feature index values for this language system — excludes the required feature
    uint16_t featureIndices[];      // Array of indices into the FeatureList, in arbitrary order
} Uttf_Otf_LangSysTable_t;

typedef PACKED_STRUCT(Uttf_Otf_LangSysRecord_s) {
    uint32_t langSysTag;    // 4-byte LangSysTag identifier
    uint16_t langSysOffset; // Offset to LangSys table, from beginning of Script table
} Uttf_Otf_LangSysRecord_t;

typedef PACKED_STRUCT(Uttf_Otf_ScriptTable_s) {
    uint16_t                 defaultLangSys;   // Offset to default LangSys table, from beginning of Script table — may be NULL
    uint16_t                 langSysCount;     // Number of LangSysRecords for this script — excluding the default LangSys
    Uttf_Otf_LangSysRecord_t langSysRecords[]; // Array of LangSysRecords, listed alphabetically by LangSys tag
} Uttf_Otf_ScriptTable_t;

typedef PACKED_STRUCT(Uttf_Otf_ScriptRecord_s) {
    uint32_t scriptTag;    // 4-byte script tag identifier
    uint16_t scriptOffset; // Offset to Script table, from beginning of ScriptList
} Uttf_Otf_ScriptRecord_t;

typedef PACKED_STRUCT(Uttf_Otf_ScriptListTable_s) {
    uint16_t                scriptCount;     // Number of ScriptRecords
    Uttf_Otf_ScriptRecord_t scriptRecords[]; // Array of ScriptRecords, listed alphabetically by script tag
} Uttf_Otf_ScriptListTable_t;

typedef PACKED_STRUCT(Uttf_Otf_ClassDefTableFmt1_s) {
    uint16_t classFormat;       // Format identifier — format = 1
    uint16_t startGlyphID;      // First glyph ID of the classValueArray
    uint16_t glyphCount;        // Size of the classValueArray
    uint16_t classValueArray[]; // Array of Class Values — one per glyph ID
} Uttf_Otf_ClassDefTableFmt1_t;


typedef PACKED_STRUCT(Uttf_Otf_ClassRangeRecord_s) {
    uint16_t startGlyphID; // First glyph ID in the range
    uint16_t endGlyphID;   // Last glyph ID in the range
    uint16_t classValue;   // Applied to all glyphs in the range
} Uttf_Otf_ClassRangeRecord_t;

typedef PACKED_STRUCT(Uttf_Otf_ClassDefTableFmt2_s) {
    uint16_t                    classFormat;         // Format identifier — format = 1
    uint16_t                    classRangeCount;     // Number of ClassRangeRecords
    Uttf_Otf_ClassRangeRecord_t classRangeRecords[]; // Array of ClassRangeRecords — ordered by startGlyphID
}  Uttf_Otf_ClassDefTableFmt2_t;

typedef PACKED_UNION(Uttf_Otf_ClassDefTable_u) {
    uint16_t                     format;
    Uttf_Otf_ClassDefTableFmt1_t fmt1;
    Uttf_Otf_ClassDefTableFmt2_t fmt2;
}Uttf_Otf_ClassDefTable_t;


typedef PACKED_STRUCT(Uttf_Otf_CoverageTableFmt1_s) {
    uint16_t coverageFormat;  // Format identifier — format = 1
    uint16_t glyphCount;      // Number of glyphs in the glyph array
    uint16_t glyphArray[];    // Array of glyph IDs — in numerical order
}  Uttf_Otf_CoverageTableFmt1_t;

typedef PACKED_STRUCT(Uttf_Otf_CoverageRecord_s) {
    uint16_t startGlyphID;       // First glyph ID in the range
    uint16_t endGlyphID;         // Last glyph ID in the range
    uint16_t startCoverageIndex; // Coverage Index of first glyph ID in range
} Uttf_Otf_CoverageRecord_t;

typedef PACKED_STRUCT(Uttf_Otf_CoverageTableFmt2_s) {
    uint16_t                  coverageFormat; // Format identifier — format = 1
    uint16_t                  rangeCount;     // Number of ClassRangeRecords
    Uttf_Otf_CoverageRecord_t rangeRecords[]; // Array of ClassRangeRecords — ordered by startGlyphID
}  Uttf_Otf_CoverageTableFmt2_t;

typedef PACKED_UNION(Uttf_Otf_CoverageTable_u) {
    uint16_t                     format;
    Uttf_Otf_CoverageTableFmt1_t fmt1;
    Uttf_Otf_CoverageTableFmt2_t fmt2;
}Uttf_Otf_CoverageTable_t;


typedef PACKED_STRUCT(Uttf_Otf_DeviceTable_s) {
    uint16_t startSize;    // Smallest size to correct, in ppem
    uint16_t endSize;      // Largest size to correct, in ppem
    uint16_t deltaFormat;  // Format of deltaValue array data: 0x0001, 0x0002, or 0x0003
    uint16_t deltaValue[]; // Array of compressed data
} Uttf_Otf_DeviceTable_t;


#endif