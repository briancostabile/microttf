
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "otf_dump.h"


static void
otf_dump_GlyfCompositeComponent( size_t idx, Uttf_Glyf_ParsedCompositeComponent_t* component_ptr )
{
    uint16_t arg1, arg2;

    printf( "[%zu]\t0x%04X glyphIdx:%d:0x%04X", idx, component_ptr->flags, component_ptr->glyphIndex, component_ptr->glyphIndex );

    if (component_ptr->flags.argsAreWords == true)
    {
        arg1 = component_ptr->args.args16.arg1;
        arg2 = component_ptr->args.args16.arg2;
    }
    else
    {
        arg1 = component_ptr->args.args8.arg1;
        arg2 = component_ptr->args.args8.arg2;
    }

    if (component_ptr->flags.argsAreValuesXY)
    {
        printf (" x=%d y=%d\n", arg1, arg2);
    }
    else
    {
        printf (" %d %d\n", arg1, arg2);
    }

    printf( "\t%s %s %s %s %s %s %s %s %s %s %s %s\n", 
            component_ptr->flags.argsAreWords ? "(Words)" : "" , 
            component_ptr->flags.argsAreValuesXY ? "(X/Y)" : "", 
            component_ptr->flags.roundToGridXY ? "(Round X/Y)" : "", 
            component_ptr->flags.scale ? "(Scale)" : "", 
            component_ptr->flags.more ? "(More)" : "", 
            component_ptr->flags.scaleXandY ? "(Scale X and Y)" : "", 
            component_ptr->flags.twoByTwo ? "(Two by Two)" : "", 
            component_ptr->flags.instructions ? "(Instructions)" : "", 
            component_ptr->flags.useMetrics ? "(My Metrics)" : "", 
            component_ptr->flags.overlap ? "(Overlap)" : "", 
            component_ptr->flags.scaledOffset ? "(Scaled Offset)" : "", 
            component_ptr->flags.unscaledOffset ? "(Unscaled Offset)" : "" );
    return;
}

void
otf_dump_Glyf( Uttf_Glyf_Info_t* info_ptr,
               Uttf_Loca_Info_t* loca_info_ptr,
               uint16_t          numGlyphs )
{
    printf( OTF_DUMP_SECTION_START("glyf") );
    if( info_ptr != NULL )
    {
        uint32_t offset;
        Uttf_Glyf_t* glyf_ptr;
        int32_t maxNumberOfContours = 0;
        uint32_t maxNocGlyphId = 0;
        for( int i=0; i<numGlyphs; i++ )
        {
            uttf_Loca_GlyphOffsetGet( loca_info_ptr, i, &offset );

            glyf_ptr = (Uttf_Glyf_t*)((uint8_t*)(info_ptr->glyfPtr) + offset);

            //MEM_DUMP( glyf_ptr, 256 );

            if( (int16_t)UTTF_BE16TOH(glyf_ptr->numberOfContours) >= 0 )
            { 
                Uttf_Glyf_ParsedSimple_t parsed_glyph;
                uttf_Glyf_ParseSimple( glyf_ptr ,&parsed_glyph );

                printf( "id:%04d offset:%6d numContours:%4d xMin:%4d yMin:%4d xMax:%4d yMax:%4d"OTF_DUMP_NL,
                        i, offset,
                        parsed_glyph.hdr.numberOfContours,
                        parsed_glyph.hdr.xMin,
                        parsed_glyph.hdr.yMin,
                        parsed_glyph.hdr.xMax,
                        parsed_glyph.hdr.yMax );
                        
                if( parsed_glyph.hdr.numberOfContours > maxNumberOfContours )
                { 
                    maxNumberOfContours = parsed_glyph.hdr.numberOfContours;
                    maxNocGlyphId = i;
                }

                uint8_t* flagsPtr    = parsed_glyph.flagsArray;
                uint8_t* x_coord_ptr = parsed_glyph.xCoordinatesArray;
                uint8_t* y_coord_ptr = parsed_glyph.yCoordinatesArray;
                uint16_t* end_idx_ptr = parsed_glyph.endPtsOfContourArray;
                uint16_t idx = 0;
                Uttf_Glyf_ParsedCoord_t coord;

                memset( &coord, 0, sizeof(Uttf_Glyf_ParsedCoord_t) );

                printf( "Index\tflags\tx\ty\tonCurve\tcount"OTF_DUMP_NL );
                uint16_t rpt_cnt = 0;
                for( uint16_t i=0; flagsPtr<parsed_glyph.xCoordinatesArray; i++ )
                {
                    printf( "[%d]\t0x%02X", i, *flagsPtr );

                    uttf_Glyf_ParseContour( &coord, &flagsPtr, &x_coord_ptr, &y_coord_ptr );

                    printf( "\t%d\t%d\t%d\t%d", coord.xCoord, coord.yCoord, coord.onCurve, coord.count);
                    if( UTTF_BE16TOH(*end_idx_ptr) == idx )
                    {
                        printf(" *E");
                        end_idx_ptr++;
                    }
                    printf(OTF_DUMP_NL);
                    
                    for( uint8_t j=1; j < coord.count; j++ )
                    {
                        idx++;
                        
                        if( coord.x8 )
                        {
                            coord.xCoord = uttf_Glyf_ParseContourNext8( coord.xPosSame, &x_coord_ptr );
                        }
                        else if( coord.xPosSame == false )
                        {
                            coord.xCoord = uttf_Glyf_ParseContourNext16( &x_coord_ptr );
                        }

                        if( coord.y8 )
                        {
                            coord.yCoord = uttf_Glyf_ParseContourNext8( coord.yPosSame, &y_coord_ptr );
                        }
                        else if( coord.yPosSame == false )
                        {
                            coord.yCoord = uttf_Glyf_ParseContourNext16( &y_coord_ptr );
                        }

                        printf( "\t\t%d\t%d\t%d\t%d", coord.xCoord, coord.yCoord, coord.onCurve, (coord.count - j) );
                        if( UTTF_BE16TOH(*end_idx_ptr) == idx )
                        {
                            printf(" *E");
                            end_idx_ptr++;
                        }
                        printf(OTF_DUMP_NL);
                    }

                    idx++;
                }
            }
            else
            {
                printf("**COMPOSITE**\n");

                Uttf_Glyf_CompositeComponent_t* component_ptr;
                Uttf_Glyf_ParsedComposite_t parsed_glyph;
                component_ptr = uttf_Glyf_ParseCompositeHdr( glyf_ptr ,&parsed_glyph );

                printf( "id:%04d offset:%6d numContours:%4d xMin:%4d yMin:%4d xMax:%4d yMax:%4d"OTF_DUMP_NL,
                        i, offset,
                        parsed_glyph.hdr.numberOfContours,
                        parsed_glyph.hdr.xMin,
                        parsed_glyph.hdr.yMin,
                        parsed_glyph.hdr.xMax,
                        parsed_glyph.hdr.yMax );

                size_t idx = 0;
                Uttf_Glyf_ParsedCompositeComponent_t parsed_component;
                component_ptr = uttf_Glyf_ParseCompositeComponent( component_ptr, &parsed_component );
                otf_dump_GlyfCompositeComponent(idx, &parsed_component);

                while ((component_ptr != NULL) && (parsed_component.flags.more == true))
                {
                    component_ptr = uttf_Glyf_ParseCompositeComponent( component_ptr, &parsed_component );
                    otf_dump_GlyfCompositeComponent(++idx, &parsed_component);
                }

                if (parsed_component.flags.instructions == true)
                {
                    Uttf_Glyf_ParsedCompositeInstructions_t parsed_instructions;
                    uttf_Glyf_ParseCompositeInstructions((Uttf_Glyf_CompositeInstructions_t*)component_ptr,
                                                            &parsed_instructions);
                    printf( "\tnumInstructions: %d\n", parsed_instructions.numInstructions );
                    MEM_DUMP( parsed_instructions.instr_ptr, parsed_instructions.numInstructions );
                    printf( "\n" );
                }
            }

        }


        printf( "maxNumContours:%4d GlyphId:%d"OTF_DUMP_NL, maxNumberOfContours, maxNocGlyphId );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
}
