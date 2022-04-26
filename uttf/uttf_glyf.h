/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_GLYF_H
#define UTTF_GLYF_H

#include <stdint.h>
#include <stdbool.h>
#include "uttf_system.h"

typedef PACKED_STRUCT(Uttf_Glyf_Hdr_s) {
    int16_t numberOfContours; // If the number of contours is greater than or equal to zero, this is a single glyph. If negative, this is a composite glyph — the value -1 should be used for composite glyphs.
    int16_t xMin;             // Minimum x for coordinate data.
    int16_t yMin;             // Minimum y for coordinate data.
    int16_t xMax;             // Maximum x for coordinate data.
    int16_t yMax;             // Maximum y for coordinate data.
} Uttf_Glyf_Hdr_t;

typedef Uttf_Glyf_Hdr_t Uttf_Glyf_t;

typedef struct Uttf_Glyf_Info_s {
    Uttf_Glyf_t* glyfPtr;
} Uttf_Glyf_Info_t;


typedef struct Uttf_Glyf_ParsedSimple_s {
    Uttf_Glyf_Hdr_t hdr;
    uint16_t* endPtsOfContourArray;
    uint8_t*  instructionArray;
    uint8_t*  flagsArray;
    uint8_t*  xCoordinatesArray;
    uint8_t*  yCoordinatesArray;
    uint16_t  instructionLength;
    uint16_t  flagsLength;
    uint16_t  xCoordinatesLength;
    uint16_t  yCoordinatesLength;
    uint16_t  numCoordinateElements;
    uint16_t  numCoordinates;
} Uttf_Glyf_ParsedSimple_t;

typedef struct Uttf_Glyf_ParsedCoord_s {
    uint8_t onCurve  : 1;
    uint8_t x8       : 1;
    uint8_t y8       : 1;
    uint8_t repeat   : 1;
    uint8_t xPosSame : 1;
    uint8_t yPosSame : 1;
    uint8_t count;
    int16_t xCoord;
    int16_t yCoord;
} Uttf_Glyf_ParsedCoord_t;

/*
Composite Glyph Flags
Mask	Name	Description
0x0001	ARG_1_AND_2_ARE_WORDS	Bit 0: If this is set, the arguments are 16-bit (uint16 or int16); otherwise, they are bytes (uint8 or int8).
0x0002	ARGS_ARE_XY_VALUES	Bit 1: If this is set, the arguments are signed xy values; otherwise, they are unsigned point numbers.
0x0004	ROUND_XY_TO_GRID	Bit 2: For the xy values if the preceding is true.
0x0008	WE_HAVE_A_SCALE	Bit 3: This indicates that there is a simple scale for the component. Otherwise, scale = 1.0.
0x0020	MORE_COMPONENTS	Bit 5: Indicates at least one more glyph after this one.
0x0040	WE_HAVE_AN_X_AND_Y_SCALE	Bit 6: The x direction will use a different scale from the y direction.
0x0080	WE_HAVE_A_TWO_BY_TWO	Bit 7: There is a 2 by 2 transformation that will be used to scale the component.
0x0100	WE_HAVE_INSTRUCTIONS	Bit 8: Following the last component are instructions for the composite character.
0x0200	USE_MY_METRICS	Bit 9: If set, this forces the aw and lsb (and rsb) for the composite to be equal to those from this original glyph. This works for hinted and unhinted characters.
0x0400	OVERLAP_COMPOUND	Bit 10: If set, the components of the compound glyph overlap. Use of this flag is not required in OpenType — that is, it is valid to have components overlap without having this flag set. It may affect behaviors in some platforms, however. (See Apple’s specification for details regarding behavior in Apple platforms.)
0x0800	SCALED_COMPONENT_OFFSET	Bit 11: The composite is designed to have the component offset scaled.
0x1000	UNSCALED_COMPONENT_OFFSET	Bit 12: The composite is designed not to have the component offset scaled.
0xE010	Reserved	Bits 4, 13, 14 and 15 are reserved: set to 0.
*/
typedef PACKED_STRUCT(Uttf_Glyf_CompositeFlags_s) {
    uint16_t instructions    : 1;
    uint16_t useMetrics      : 1;
    uint16_t overlap         : 1;
    uint16_t scaledOffset    : 1;
    uint16_t unscaledOffset  : 1;
    uint16_t rsvd13          : 1;
    uint16_t rsvd14          : 1;
    uint16_t rsvd15          : 1;
    uint16_t argsAreWords    : 1;
    uint16_t argsAreValuesXY : 1;
    uint16_t roundToGridXY   : 1;
    uint16_t scale           : 1;
    uint16_t rsvd4           : 1;
    uint16_t more            : 1;
    uint16_t scaleXandY      : 1;
    uint16_t twoByTwo        : 1;
} Uttf_Glyf_CompositeFlags_t;

typedef PACKED_STRUCT(Uttf_Glyf_CompositeArgs8_s) {
    uint8_t arg1;
    uint8_t arg2;
} Uttf_Glyf_CompositeArgs8_t;

typedef PACKED_STRUCT(Uttf_Glyf_CompositeArgs16_s) {
    uint16_t arg1;
    uint16_t arg2;
} Uttf_Glyf_CompositeArgs16_t;

typedef PACKED_STRUCT(Uttf_Glyf_CompositeComponent_s) {
    Uttf_Glyf_CompositeFlags_t  flags;
    uint16_t                    glyphIndex;
    union
    {
        Uttf_Glyf_CompositeArgs8_t  args8;
        Uttf_Glyf_CompositeArgs16_t args16;
    } args;
} Uttf_Glyf_CompositeComponent_t;

typedef struct Uttf_Glyf_ParsedComposite_s {
    Uttf_Glyf_Hdr_t hdr;
} Uttf_Glyf_ParsedComposite_t;

typedef PACKED_STRUCT(Uttf_Glyf_CompositeInstructions_s) {
    uint16_t numInstructions;
    uint8_t  instruction0;
} Uttf_Glyf_CompositeInstructions_t;

typedef struct Uttf_Glyf_ParsedCompositeInstructions_s {
    uint16_t numInstructions;
    uint8_t* instr_ptr;
} Uttf_Glyf_ParsedCompositeInstructions_t;

typedef Uttf_Glyf_CompositeComponent_t Uttf_Glyf_ParsedCompositeComponent_t;


Uttf_Status_t
uttf_Glyf_Open( Uttf_Glyf_t*      table_ptr,
                uint32_t          length,
                Uttf_Glyf_Info_t* info_ptr );


/*****************************************************************************/
Uttf_Status_t
uttf_Glyf_ParseSimple( Uttf_Glyf_Hdr_t*          glyph_ptr,
                       Uttf_Glyf_ParsedSimple_t* parsed_ptr );


/*****************************************************************************/
Uttf_Status_t
uttf_Glyf_ParseContour( Uttf_Glyf_ParsedCoord_t* new_coord_ptr,
                        uint8_t** flagsPtr,
                        uint8_t** xCoordPtr,
                        uint8_t** yCoordPtr );

/*****************************************************************************/
int16_t
uttf_Glyf_ParseContourNext8( bool      positive,
                             uint8_t** coordPtr );

/*****************************************************************************/
int16_t
uttf_Glyf_ParseContourNext16( uint8_t** coordPtr );

/*****************************************************************************/
void *
uttf_Glyf_ParseCompositeHdr( Uttf_Glyf_Hdr_t*             glyph_ptr,
                             Uttf_Glyf_ParsedComposite_t* parsed_ptr );

/*****************************************************************************/
void *
uttf_Glyf_ParseCompositeComponent( Uttf_Glyf_CompositeComponent_t*       component_ptr,
                                   Uttf_Glyf_ParsedCompositeComponent_t* parsed_ptr );

/*****************************************************************************/
void
uttf_Glyf_ParseCompositeInstructions( Uttf_Glyf_CompositeInstructions_t*       instructions_ptr,
                                      Uttf_Glyf_ParsedCompositeInstructions_t* parsed_ptr );

#endif
