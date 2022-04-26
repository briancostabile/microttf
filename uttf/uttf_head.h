/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_HEAD_H
#define UTTF_HEAD_H

#include <stdint.h>
#include "uttf_system.h"

#define UTTF_MAXP_TABLE_VERSION_V1 0x00010000

typedef PACKED_STRUCT(Uttf_Head_s) {
    uint32_t version;
    uint32_t fontRevision;
    uint32_t checkSumAdjustment; // To compute: set it to 0, calculate the checksum for the 'head' table and put it in the table directory, sum the entire font as a uint32_t, then store 0xB1B0AFBA - sum. (The checksum for the 'head' table will be wrong as a result. That is OK; do not reset it.)
    uint32_t magicNumber;        // set to 0x5F0F3CF5
    uint16_t flags;              // bit 0 - y value of 0 specifies baseline
                                 // bit 1 - x position of left most black bit is LSB
                                 // bit 2 - scaled point size and actual point size will differ (i.e. 24 point glyph differs from 12 point glyph scaled by factor of 2)
                                 // bit 3 - use integer scaling instead of fractional
                                 // bit 4 - (used by the Microsoft implementation of the TrueType scaler)
                                 // bit 5 - This bit should be set in fonts that are intended to e laid out vertically, and in which the glyphs have been drawn such that an x-coordinate of 0 corresponds to the desired vertical baseline.
                                 // bit 6 - This bit must be set to zero.
                                 // bit 7 - This bit should be set if the font requires layout for correct linguistic rendering (e.g. Arabic fonts).
                                 // bit 8 - This bit should be set for an AAT font which has one or more metamorphosis effects designated as happening by default.
                                 // bit 9 - This bit should be set if the font contains any strong right-to-left glyphs.
                                 // bit 10 - This bit should be set if the font contains Indic-style rearrangement effects.
                                 // bits 11-13 - Defined by Adobe.
                                 // bit 14 - This bit should be set if the glyphs in the font are simply generic symbols for code point ranges, such as for a last resort font.
    uint16_t unitsPerEm;         // range from 64 to 16384
    uint64_t created;            // international date
    uint64_t modified;           // international date
    int16_t  xMin;               // for all glyph bounding boxes
    int16_t  yMin;               // for all glyph bounding boxes
    int16_t  xMax;               // for all glyph bounding boxes
    int16_t  yMax;               // for all glyph bounding boxes
    uint16_t macStyle;           // bit 0 bold
                                 // bit 1 italic
                                 // bit 2 underline
                                 // bit 3 outline
                                 // bit 4 shadow
                                 // bit 5 condensed (narrow)
                                 // bit 6 extended
    uint16_t lowestRecPPEM;      // smallest readable size in pixels
    int16_t  fontDirectionHint;  // 0 Mixed directional glyphs
                                 // 1 Only strongly left to right glyphs
                                 // 2 Like 1 but also contains neutrals
                                 // -1 Only strongly right to left glyphs
                                 // -2 Like -1 but also contains neutrals
    int16_t indexToLocFormat;    // 0 for short offsets, 1 for long
    int16_t glyphDataFormat;     // 0 for current format
} Uttf_Head_t;

typedef struct Uttf_Head_Info_s {
    Uttf_Head_t* headPtr;
} Uttf_Head_Info_t;

Uttf_Status_t
uttf_Head_Open( Uttf_Head_t*      table_ptr,
                uint32_t          table_len,
                Uttf_Head_Info_t* info_ptr );

#endif
