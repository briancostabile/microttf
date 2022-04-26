/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_MAXP_H
#define UTTF_MAXP_H

#include <stdint.h>
#include "uttf_system.h"

#define UTTF_MAXP_TABLE_VERSION_V1 0x00010000
#define UTTF_MAXP_TABLE_VERSION_V5 0x00005000

typedef PACKED_STRUCT(Uttf_Maxp_V1_s) {
    uint32_t version;
    uint16_t numGlyphs;             // the number of glyphs in the font
    uint16_t maxPoints;             // points in non-compound glyph
    uint16_t maxContours;           // contours in non-compound glyph
    uint16_t maxComponentPoints;    // points in compound glyph
    uint16_t maxComponentContours;  // contours in compound glyph
    uint16_t maxZones;              // set to 2
    uint16_t maxTwilightPoints;     // points used in Twilight Zone (Z0)
    uint16_t maxStorage;            // number of Storage Area locations
    uint16_t maxFunctionDefs;       // number of FDEFs
    uint16_t maxInstructionDefs;    // number of IDEFs
    uint16_t maxStackElements;      // maximum stack depth
    uint16_t maxSizeOfInstructions; // byte count for glyph instructions
    uint16_t maxComponentElements;  // number of glyphs referenced at top level
    uint16_t maxComponentDepth;     // levels of recursion, set to 0 if font has only simple glyphs
} Uttf_Maxp_V1_t;

typedef PACKED_STRUCT(Uttf_Maxp_V5_s) {
    uint32_t version;
    uint16_t numGlyphs; // the number of glyphs in the font
} Uttf_Maxp_V5_t;

typedef PACKED_UNION(Uttf_Maxp_Table_u) {
    uint32_t       version;
    Uttf_Maxp_V1_t v1;
    Uttf_Maxp_V5_t v5;
} Uttf_Maxp_t;

typedef struct Uttf_Maxp_Info_s {
    Uttf_Maxp_t* maxpPtr;
} Uttf_Maxp_Info_t;


Uttf_Status_t
uttf_Maxp_Open( Uttf_Maxp_t*      table_ptr,
                uint32_t          length,
                Uttf_Maxp_Info_t* info_ptr );

#endif
