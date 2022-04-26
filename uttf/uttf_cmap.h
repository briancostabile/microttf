/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_CMAP_H
#define UTTF_CMAP_H

#include <stdint.h>
#include "uttf_log.h"
#include "uttf_endian.h"
#include "uttf_system.h"
#include "uttf_config.h"

/**
 * To ensure macros work, subtable types must follow a format
 */
#define UTTF_CMAP_SUBTABLE_NAME( _num, _postfix )        Uttf_Cmap_SubtableFmt##_num##_postfix
#define UTTF_CMAP_SUBTABLE_TYPE( _num )                  UTTF_CMAP_SUBTABLE_NAME( _num, _t )
#define UTTF_CMAP_SUBTABLE_STRUCT( _num )                UTTF_CMAP_SUBTABLE_NAME( _num, _s )
#define UTTF_CMAP_SUBTABLE_PARSED_NAME( _num, _postfix ) Uttf_Cmap_SubtableParsedFmt##_num##_postfix
#define UTTF_CMAP_SUBTABLE_PARSED_TYPE( _num )           UTTF_CMAP_SUBTABLE_PARSED_NAME( _num, _t )
#define UTTF_CMAP_SUBTABLE_PARSED_STRUCT( _num )         UTTF_CMAP_SUBTABLE_PARSED_NAME( _num, _s )
#define UTTF_CMAP_SUBTABLE_FIELD( _num )                 UTTF_CMAP_SUBTABLE_TYPE( _num ) *fmt##_num##Ptr


#if (UTTF_CONFIG_CMAP_FMT0 == ENABLE)
typedef PACKED_STRUCT(UTTF_CMAP_SUBTABLE_STRUCT(0)) {
    uint16_t format;            // Format number is set to 0.
    uint16_t length;            // This is the length in bytes of the subtable.
    uint16_t language;          // Please see “Note on the language field in 'cmap' subtables“ in this document.
    uint8_t  glyphIdArray[256]; // An array that maps character codes to glyph index values.
} UTTF_CMAP_SUBTABLE_TYPE(0);

typedef struct UTTF_CMAP_SUBTABLE_PARSED_STRUCT(0) {
    uint16_t length;       // parsed length is the array length, not the section length
    uint8_t* glyphIdArray; // glyph IDs are 1-byte so no byte-swapping is necessary
} UTTF_CMAP_SUBTABLE_PARSED_TYPE(0);
#endif


#if (UTTF_CONFIG_CMAP_FMT4 == ENABLE)
typedef PACKED_STRUCT(UTTF_CMAP_SUBTABLE_STRUCT(4)) {
    uint16_t format;        // Format number is set to 4.
    uint16_t length;        // This is the length in bytes of the subtable.
    uint16_t language;      // Please see “Note on the language field in 'cmap' subtables“ in this document.
    uint16_t segCountX2;    // 2 x segCount.
    uint16_t searchRange;   // 2 x (2**floor(log2(segCount)))
    uint16_t entrySelector; // log2(searchRange/2)
    uint16_t rangeShift;    // 2 x segCount - searchRange
} UTTF_CMAP_SUBTABLE_TYPE(4);

typedef struct UTTF_CMAP_SUBTABLE_PARSED_STRUCT(4) {
    uint16_t  segCountX2;         // parsed will be byte swapped
    uint16_t* endCountArray;      // array contents will not be byte-swapped
    uint16_t* startCountArray;
    uint16_t* idDeltaArray;
    uint16_t* idRangeOffsetArray;
    uint16_t* glyphIdArray;
} UTTF_CMAP_SUBTABLE_PARSED_TYPE(4);
#endif


#if (UTTF_CONFIG_CMAP_FMT6 == ENABLE)
typedef PACKED_STRUCT(UTTF_CMAP_SUBTABLE_STRUCT(6)) {
    uint16_t format;         // Format number is set to 0.
    uint16_t length;         // This is the length in bytes of the subtable.
    uint16_t language;       // Please see “Note on the language field in 'cmap' subtables“ in this document.
    uint16_t firstCode;      // First character code of subrange.
    uint16_t entryCount;     // Number of character codes in subrange.
    uint16_t glyphIdArray[]; // An array that maps character codes to glyph index values.
} UTTF_CMAP_SUBTABLE_TYPE(6);

typedef struct UTTF_CMAP_SUBTABLE_PARSED_STRUCT(6) {
    uint16_t  firstCode;    // parsed first code. The code for glyphIdArray location 0
    uint16_t  entryCount;   // parsed number of glyphIds
    uint16_t* glyphIdArray; // glyph IDs are 2-byte so byte-swapping is necessary
} UTTF_CMAP_SUBTABLE_PARSED_TYPE(6);
#endif


#if (UTTF_CONFIG_CMAP_FMT12 == ENABLE)
typedef PACKED_STRUCT(Uttf_Cmap_SequentialMapGroup_s) {
    uint32_t  startCharCode; // First character code in this group
    uint32_t  endCharCode;   // Last character code in this group
    uint32_t  startGlyphID;  // Glyph index corresponding to the starting character code
} Uttf_Cmap_SequentialMapGroup_t;

typedef PACKED_STRUCT(UTTF_CMAP_SUBTABLE_STRUCT(12)) {
    uint16_t format;    // Subtable format; set to 12.
    uint16_t reserved;  // Reserved; set to 0
    uint32_t length;    // Byte length of this subtable (including the header)
    uint32_t language;  // Please see “Note on the language field in 'cmap' subtables“ in this document.
    uint32_t numGroups; // Number of groupings which follow
    Uttf_Cmap_SequentialMapGroup_t groups[];  // Array of SequentialMapGroup records.
} UTTF_CMAP_SUBTABLE_TYPE(12);

typedef struct UTTF_CMAP_SUBTABLE_PARSED_STRUCT(12) {
    uint32_t                        numGroups;  // parsed length is the array length, not the section length
    Uttf_Cmap_SequentialMapGroup_t* groups;     // Map elements array
} UTTF_CMAP_SUBTABLE_PARSED_TYPE(12);
#endif


#if (UTTF_CONFIG_CMAP_FMT14 == ENABLE)
typedef PACKED_STRUCT(Uttf_Cmap_SubtableFmt14UvsRangeRec_s) {
    uint8_t startUnicodeValueMswLsb; // First value in this range
    uint8_t startUnicodeValueLswMsb;
    uint8_t startUnicodeValueLswLsb;
    uint8_t additionalCount;         // Number of additional values in this range
} Uttf_Cmap_SubtableFmt14UvsRangeRec_t;

typedef PACKED_STRUCT(Uttf_Cmap_SubtableFmt14DefaultUvsTable_s) {
    uint32_t                             numUnicodeValueRanges; // Number of Unicode character ranges.
    Uttf_Cmap_SubtableFmt14UvsRangeRec_t ranges[];
} Uttf_Cmap_SubtableFmt14DefaultUvsTable_t;

typedef PACKED_STRUCT(Uttf_Cmap_SubtableFmt14UvsMappingRec_s) {
    uint8_t unicodeValueMswLsb; // Base Unicode value of the UVS
    uint8_t unicodeValueLswMsb; 
    uint8_t unicodeValueLswLsb; 
    uint8_t glyphIDMsb;         // Glyph ID of the UVS
    uint8_t glyphIDLsb;
} Uttf_Cmap_SubtableFmt14UvsMappingRec_t;

typedef PACKED_STRUCT(Uttf_Cmap_SubtableFmt14NonDefaultUvsTable_s) {
    uint32_t                               numUVSMappings; // Number of UVS Mappings that follow
    Uttf_Cmap_SubtableFmt14UvsMappingRec_t uvsMappings[];
} Uttf_Cmap_SubtableFmt14NonDefaultUvsTable_t;

typedef PACKED_STRUCT(Uttf_Cmap_SubtableFmt14VarSelRec_s) {
    uint8_t   varSelectorMs8;      // Most significant 8 bits of varSelector 
    uint16_t  varSelectorLs16;     // Least significant 16 bits of varSelector
    uint32_t  defaultUVSOffset;    // Offset from the start of the format 14 subtable to Default UVS Table. May be 0.
    uint32_t  nonDefaultUVSOffset; // Offset from the start of the format 14 subtable to Non-Default UVS Table. May be 0.
} Uttf_Cmap_SubtableFmt14VarSelRec_t;

typedef PACKED_STRUCT(UTTF_CMAP_SUBTABLE_STRUCT(14)) {
    uint16_t                           format;                // Subtable format; set to 12.
    uint32_t                           length;                // Byte length of this subtable (including the header)
    uint32_t                           numVarSelectorRecords; // Number of groupings which follow
    Uttf_Cmap_SubtableFmt14VarSelRec_t varSelector[];         // Array of SequentialMapGroup records.
} UTTF_CMAP_SUBTABLE_TYPE(14);

typedef struct UTTF_CMAP_SUBTABLE_PARSED_STRUCT(14) {
    uint32_t                            numVarSelectorRecords;
    Uttf_Cmap_SubtableFmt14VarSelRec_t* varSelector;
} UTTF_CMAP_SUBTABLE_PARSED_TYPE(14);
#endif


typedef PACKED_STRUCT(Uttf_Cmap_Subtable_s) {
    uint16_t format;
} Uttf_Cmap_Subtable_t;

typedef PACKED_STRUCT(Uttf_Cmap_EncodingRec_s) {
    uint16_t platformID;
    uint16_t encodingID;
    uint32_t offset;
} Uttf_Cmap_EncodingRec_t;

typedef PACKED_STRUCT(Uttf_Cmap_s) {
    uint16_t                version;
    uint16_t                numTables;
    Uttf_Cmap_EncodingRec_t encodingRecords[];
} Uttf_Cmap_t;


typedef struct Uttf_Cmap_Info_s {
    Uttf_Cmap_t* cmapPtr;
#if (UTTF_CONFIG_CMAP_FMT0 == ENABLE)
    UTTF_CMAP_SUBTABLE_FIELD(0);
#endif
#if  (UTTF_CONFIG_CMAP_FMT4 == ENABLE)
    UTTF_CMAP_SUBTABLE_FIELD(4);
#endif
#if  (UTTF_CONFIG_CMAP_FMT6 == ENABLE)
    UTTF_CMAP_SUBTABLE_FIELD(6);
#endif
#if (UTTF_CONFIG_CMAP_FMT12 == ENABLE)
    UTTF_CMAP_SUBTABLE_FIELD(12);
#endif
#if (UTTF_CONFIG_CMAP_FMT14 == ENABLE)
     UTTF_CMAP_SUBTABLE_FIELD(14);
#endif
} Uttf_Cmap_Info_t;

/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_Open( Uttf_Cmap_t*      table_ptr,
                uint32_t          table_len,
                Uttf_Cmap_Info_t* info_ptr );

/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdx( Uttf_Cmap_Info_t* info_ptr,
                   Uttf_CharCode_t   code );

/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt0( Uttf_Cmap_SubtableFmt0_t* subtable_ptr,
                               Uttf_CharCode_t           code );

/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt4( Uttf_Cmap_SubtableFmt4_t* subtable_ptr,
                               Uttf_CharCode_t           code );

/*****************************************************************************/
Uttf_GlyphIdx_t
uttf_Cmap_FindIdxSubtableFmt6( Uttf_Cmap_SubtableFmt6_t* subtable_ptr,
                               Uttf_CharCode_t           code );
                               
/*****************************************************************************/
Uttf_Status_t
uttf_Cmap_SubtableArraysGet( void*      subtable_ptr,
                             uint16_t*  seg_count_X2_ptr,
                             uint16_t** end_count_array_ptr,
                             uint16_t** start_count_array_ptr,
                             uint16_t** id_delta_array_ptr,
                             uint16_t** id_range_offset_array_ptr,
                             uint16_t** glyph_id_array_ptr );
#endif
