/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "uttf.h"
#include "uttf_name.h"

#define UTTF_GLYF_FLAGS_IS_ON_POINT( _flag )           (((_flag) & 0x01) != 0)
#define UTTF_GLYF_FLAGS_IS_SHORT_X( _flag )            (((_flag) & 0x02) != 0)
#define UTTF_GLYF_FLAGS_IS_SHORT_Y( _flag )            (((_flag) & 0x04) != 0)
#define UTTF_GLYF_FLAGS_IS_REPEAT( _flag )             (((_flag) & 0x08) != 0)
#define UTTF_GLYF_FLAGS_IS_SAME_OR_POSITIVE_X( _flag ) (((_flag) & 0x10) != 0)
#define UTTF_GLYF_FLAGS_IS_SAME_OR_POSITIVE_Y( _flag ) (((_flag) & 0x20) != 0)

/*****************************************************************************/
int16_t
uttf_Glyf_ParseContourNext8( bool      positive,
                             uint8_t** coordPtr )
{
    int16_t nxt = (uint8_t)((*coordPtr)[0]);

    if( positive == false )
    {
        nxt *= -1;
    }

    *coordPtr += 1;
    return( nxt );
}

/*****************************************************************************/
int16_t
uttf_Glyf_ParseContourNext16( uint8_t** coordPtr )
{
    int16_t nxt = (((*coordPtr)[0] << 8) + (*coordPtr)[1]);
    *coordPtr += 2;
    return( nxt );
}

/*****************************************************************************/
Uttf_Status_t
uttf_Glyf_ParseContour( Uttf_Glyf_ParsedCoord_t* new_coord_ptr,
                        uint8_t** flagsPtr,
                        uint8_t** xCoordPtr,
                        uint8_t** yCoordPtr )
{
    new_coord_ptr->onCurve  = UTTF_GLYF_FLAGS_IS_ON_POINT( **flagsPtr);
    new_coord_ptr->x8       = UTTF_GLYF_FLAGS_IS_SHORT_X( **flagsPtr);
    new_coord_ptr->y8       = UTTF_GLYF_FLAGS_IS_SHORT_Y( **flagsPtr );
    new_coord_ptr->repeat   = UTTF_GLYF_FLAGS_IS_REPEAT( **flagsPtr );
    new_coord_ptr->xPosSame = UTTF_GLYF_FLAGS_IS_SAME_OR_POSITIVE_X( **flagsPtr );
    new_coord_ptr->yPosSame = UTTF_GLYF_FLAGS_IS_SAME_OR_POSITIVE_Y( **flagsPtr );

    // See how many points are described by this flag
    new_coord_ptr->count = 1;
    if( new_coord_ptr->repeat )
    {
        new_coord_ptr->count += (*flagsPtr)[1];
    }

    // X Coordinate parsing
    if( new_coord_ptr->x8 )
    {
        new_coord_ptr->xCoord = uttf_Glyf_ParseContourNext8( new_coord_ptr->xPosSame,
                                                             xCoordPtr );
    }
    else if ( new_coord_ptr->xPosSame )
    {
        new_coord_ptr->xCoord = 0;
    }
    else
    {
        new_coord_ptr->xCoord = uttf_Glyf_ParseContourNext16( xCoordPtr );
    }

    // Y Coordinate parsing
    if( new_coord_ptr->y8 )
    {
        new_coord_ptr->yCoord = uttf_Glyf_ParseContourNext8( new_coord_ptr->yPosSame,
                                                             yCoordPtr );
    }
    else if( new_coord_ptr->yPosSame )
    {
        new_coord_ptr->yCoord = 0;
    }
    else
    {
        new_coord_ptr->yCoord = uttf_Glyf_ParseContourNext16( yCoordPtr );
    }

    // Go past the count in the flags array
    if( new_coord_ptr->count > 1 )
    {
        *flagsPtr += 1;
    }
 
    *flagsPtr += 1;

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Glyf_ParseSimple( Uttf_Glyf_Hdr_t*          glyph_ptr,
                       Uttf_Glyf_ParsedSimple_t* parsed_ptr )
{
    parsed_ptr->hdr.numberOfContours = UTTF_BE16TOH(glyph_ptr->numberOfContours);
    parsed_ptr->hdr.xMin             = UTTF_BE16TOH(glyph_ptr->xMin);
    parsed_ptr->hdr.yMin             = UTTF_BE16TOH(glyph_ptr->yMin);
    parsed_ptr->hdr.xMax             = UTTF_BE16TOH(glyph_ptr->xMax);
    parsed_ptr->hdr.yMax             = UTTF_BE16TOH(glyph_ptr->yMax);
    parsed_ptr->endPtsOfContourArray = (uint16_t*)((uint8_t*)glyph_ptr + sizeof(Uttf_Glyf_Hdr_t));
    parsed_ptr->instructionLength    = UTTF_BE16TOH(parsed_ptr->endPtsOfContourArray[parsed_ptr->hdr.numberOfContours]);

    uint16_t num_points = UTTF_BE16TOH(parsed_ptr->endPtsOfContourArray[(parsed_ptr->hdr.numberOfContours - 1)]);
    
    if( parsed_ptr->instructionLength > 0 )
    {
        parsed_ptr->instructionArray = (uint8_t*)&(parsed_ptr->endPtsOfContourArray[parsed_ptr->hdr.numberOfContours + 1]);
        parsed_ptr->flagsArray = &(parsed_ptr->instructionArray[parsed_ptr->instructionLength]);
    }
    else
    {
        parsed_ptr->instructionArray = NULL;
        parsed_ptr->flagsArray = (uint8_t*)&(parsed_ptr->endPtsOfContourArray[parsed_ptr->hdr.numberOfContours + 1]);
    }

    // Figure out how many flags there are and the length of the xCoordinate array
    parsed_ptr->numCoordinateElements = 0; // Only one set of X,Y coordinates per actual flag
    parsed_ptr->xCoordinatesLength = 0;
    parsed_ptr->yCoordinatesLength = 0;

    uint16_t i; // i tracks the location in the flagsArray
    parsed_ptr->numCoordinates = 0; // Count the total number of flags/coordinates including the repeated flags
    for( i=0; parsed_ptr->numCoordinates <= num_points; i++ )
    {
        uint8_t count = 1; // Number of points described with this flag

        parsed_ptr->numCoordinateElements++;

        // Check for repeats
        if( UTTF_GLYF_FLAGS_IS_REPEAT(parsed_ptr->flagsArray[i]) == true )
        {
            count += parsed_ptr->flagsArray[i+1];
        }
        
        // Count the number of bytes in the xCoordinateArray
        if( UTTF_GLYF_FLAGS_IS_SHORT_X(parsed_ptr->flagsArray[i]) )
        {
            parsed_ptr->xCoordinatesLength += count;
        }
        else if( UTTF_GLYF_FLAGS_IS_SAME_OR_POSITIVE_X(parsed_ptr->flagsArray[i]) == false )
        {
            // If the X_IS_SAME bit is not set then add 2 bytes for 16 bit signed
            // vector; otherwise, the vector is the same as the previous X vector
            parsed_ptr->xCoordinatesLength += (2 * count);
        }

        // Count the number of bytes in the yCoordinateArray
        if( UTTF_GLYF_FLAGS_IS_SHORT_Y(parsed_ptr->flagsArray[i]) == true )
        {
            parsed_ptr->yCoordinatesLength += count;
        }
        else if( UTTF_GLYF_FLAGS_IS_SAME_OR_POSITIVE_Y(parsed_ptr->flagsArray[i]) == false )
        {
            // If the Y_IS_SAME bit is not set then add 2 bytes for 16 bit signed
            // vector; otherwise, the vector is the same as the previous Y vector
            parsed_ptr->yCoordinatesLength += (2 * count);
        }

        // Check for repeat count to skip over the count byte
        if( count > 1 )
        {
            i++;
        }

        // Count the coordinates including the repeats
        parsed_ptr->numCoordinates += count;
    }   

    // i is index to the byte past the end of the flagsArray which is the byte count of the flags
    parsed_ptr->flagsLength       = i;
    parsed_ptr->xCoordinatesArray = (uint8_t*)&(parsed_ptr->flagsArray[parsed_ptr->flagsLength]);
    parsed_ptr->yCoordinatesArray = (uint8_t*)&(parsed_ptr->xCoordinatesArray[parsed_ptr->xCoordinatesLength]);

    return( UTTF_STATUS_NO_ERROR );
}

/*****************************************************************************/
void *
uttf_Glyf_ParseCompositeHdr( Uttf_Glyf_Hdr_t*             glyph_ptr,
                             Uttf_Glyf_ParsedComposite_t* parsed_ptr )
{
    parsed_ptr->hdr.numberOfContours = UTTF_BE16TOH(glyph_ptr->numberOfContours);
    parsed_ptr->hdr.xMin             = UTTF_BE16TOH(glyph_ptr->xMin);
    parsed_ptr->hdr.yMin             = UTTF_BE16TOH(glyph_ptr->yMin);
    parsed_ptr->hdr.xMax             = UTTF_BE16TOH(glyph_ptr->xMax);
    parsed_ptr->hdr.yMax             = UTTF_BE16TOH(glyph_ptr->yMax);
    return( ((uint8_t*)glyph_ptr + sizeof(Uttf_Glyf_Hdr_t)) );
}

/*****************************************************************************/
void *
uttf_Glyf_ParseCompositeComponent( Uttf_Glyf_CompositeComponent_t*       component_ptr,
                                   Uttf_Glyf_ParsedCompositeComponent_t* parsed_ptr )
{
    uint8_t* current_ptr = (uint8_t*)component_ptr;

    parsed_ptr->flags      = component_ptr->flags;
    parsed_ptr->glyphIndex = UTTF_BE16TOH(component_ptr->glyphIndex);
    current_ptr += (sizeof(component_ptr->flags) + sizeof(component_ptr->glyphIndex));

    if (parsed_ptr->flags.argsAreWords == true)
    {
        parsed_ptr->args.args16.arg1 = UTTF_BE16TOH(component_ptr->args.args16.arg1);
        parsed_ptr->args.args16.arg2 = UTTF_BE16TOH(component_ptr->args.args16.arg2);
        current_ptr += (sizeof(component_ptr->args.args16.arg1) + sizeof(component_ptr->args.args16.arg2));
    }
    else
    {
        parsed_ptr->args.args16.arg1 = component_ptr->args.args8.arg1;
        parsed_ptr->args.args16.arg2 = component_ptr->args.args8.arg2;
        current_ptr += (sizeof(component_ptr->args.args8.arg1) + sizeof(component_ptr->args.args8.arg2));
    }

    return( current_ptr );
}

/*****************************************************************************/
void
uttf_Glyf_ParseCompositeInstructions( Uttf_Glyf_CompositeInstructions_t*       instructions_ptr,
                                      Uttf_Glyf_ParsedCompositeInstructions_t* parsed_ptr )
{
    parsed_ptr->numInstructions = UTTF_BE16TOH(instructions_ptr->numInstructions);
    parsed_ptr->instr_ptr       = &instructions_ptr->instruction0;
    return;
}

/*****************************************************************************/
Uttf_Status_t
uttf_Glyf_Open( Uttf_Glyf_t*      table_ptr,
                uint32_t          length,
                Uttf_Glyf_Info_t* info_ptr )
{
    info_ptr->glyfPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}
