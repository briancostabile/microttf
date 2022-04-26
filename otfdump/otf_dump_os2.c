
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void
otf_dump_Os2Panose( Uttf_Os2_Panose_t* panose_ptr )
{
    printf( "panose:"OTF_DUMP_NL );
    printf( "    bFamilyType:      %d"OTF_DUMP_NL, panose_ptr->bFamilyType );
    printf( "    bSerifStyle:      %d"OTF_DUMP_NL, panose_ptr->bSerifStyle );
    printf( "    bWeight:          %d"OTF_DUMP_NL, panose_ptr->bWeight );
    printf( "    bProportion:      %d"OTF_DUMP_NL, panose_ptr->bProportion );
    printf( "    bContrast:        %d"OTF_DUMP_NL, panose_ptr->bFamilyType );
    printf( "    bStrokeVariation: %d"OTF_DUMP_NL, panose_ptr->bStrokeVariation );
    printf( "    bArmStyle:        %d"OTF_DUMP_NL, panose_ptr->bArmStyle );
    printf( "    bLetterform:      %d"OTF_DUMP_NL, panose_ptr->bLetterform );
    printf( "    bMidline:         %d"OTF_DUMP_NL, panose_ptr->bMidline );
    printf( "    bXHeight:         %d"OTF_DUMP_NL, panose_ptr->bXHeight );
}

void
otf_dump_Os2( Uttf_Os2_t* table_ptr )
{
    printf( OTF_DUMP_SECTION_START("OS/2") );
    if( table_ptr != NULL )
    {
        printf( "version:                 %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->version) );
        printf( "xAvgCharWidth:           %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->xAvgCharWidth) );
        printf( "usWeightClass:           %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usWeightClass) );
        printf( "usWidthClass:            %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usWidthClass) );
        printf( "fsType:                  %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->fsType) );
        printf( "ySubscriptXSize:         %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySubscriptXSize) );
        printf( "ySubscriptYSize:         %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySubscriptYSize) );
        printf( "ySubscriptXOffset:       %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySubscriptXOffset) );
        printf( "ySubscriptYOffset:       %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySubscriptYOffset) );
        printf( "ySuperscriptXSize:       %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySuperscriptXSize) );
        printf( "ySuperscriptYSize:       %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySuperscriptYSize) );
        printf( "ySuperscriptXOffset:     %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySuperscriptXOffset) );
        printf( "ySuperscriptYOffset:     %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ySuperscriptYOffset) );
        printf( "yStrikeoutSize:          %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->yStrikeoutSize) );
        printf( "yStrikeoutPosition:      %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->yStrikeoutPosition) );
        printf( "sFamilyClass:            %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->sFamilyClass) );
        otf_dump_Os2Panose( &table_ptr->panose );
        printf( "ulUnicodeRange1:         0x%08X"OTF_DUMP_NL, UTTF_BE32TOH(table_ptr->ulUnicodeRange1) );
        printf( "ulUnicodeRange2:         0x%08X"OTF_DUMP_NL, UTTF_BE32TOH(table_ptr->ulUnicodeRange2) );
        printf( "ulUnicodeRange3:         0x%08X"OTF_DUMP_NL, UTTF_BE32TOH(table_ptr->ulUnicodeRange3) );
        printf( "ulUnicodeRange4:         0x%08X"OTF_DUMP_NL, UTTF_BE32TOH(table_ptr->ulUnicodeRange4) );
        printf( "achVendID:               %c%c%c%c"OTF_DUMP_NL, (table_ptr->achVendID & 0xFF000000) >> 24,
                                                                (table_ptr->achVendID & 0x00FF0000) >> 16,
                                                                (table_ptr->achVendID & 0x0000FF00) >> 8,
                                                                (table_ptr->achVendID & 0x000000FF) >> 0 );
        printf( "fsSelection:             %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->fsSelection) );
        printf( "usFirstCharIndex:        %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usFirstCharIndex) );
        printf( "usLastCharIndex:         %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usLastCharIndex) );
        printf( "sTypoAscender:           %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->sTypoAscender) );
        printf( "sTypoDescender:          %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->sTypoDescender) );
        printf( "sTypoLineGap:            %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->sTypoLineGap) );
        printf( "usWinAscent:             %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usWinAscent) );
        printf( "usWinDescent:            %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usWinDescent) );
        printf( "ulCodePageRange1:        0x%08X"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ulCodePageRange1) );
        printf( "ulCodePageRange2:        0x%08X"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->ulCodePageRange2) );
        printf( "sxHeight:                %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->sxHeight) );
        printf( "sCapHeight:              %i"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->sCapHeight) );
        printf( "usDefaultChar:           %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usDefaultChar) );
        printf( "usBreakChar:             %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usBreakChar) );
        printf( "usMaxContext:            %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usMaxContext) );
        printf( "usLowerOpticalPointSize: %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usLowerOpticalPointSize) );
        printf( "usUpperOpticalPointSize: %d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->usUpperOpticalPointSize) );
    }
    else
    {
        printf( "Not Present"OTF_DUMP_NL );
    }
    printf( OTF_DUMP_NL );
}
