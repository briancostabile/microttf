/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_OS2_H
#define UTTF_OS2_H

#include <stdint.h>
#include "uttf_system.h"

typedef PACKED_STRUCT(Uttf_Os2_Panose_s) {
    uint8_t bFamilyType;
    uint8_t bSerifStyle;
    uint8_t bWeight;
    uint8_t bProportion;
    uint8_t bContrast;
    uint8_t bStrokeVariation;
    uint8_t bArmStyle;
    uint8_t bLetterform;
    uint8_t bMidline;
    uint8_t bXHeight;
} Uttf_Os2_Panose_t;

// 100 Bytes
typedef PACKED_STRUCT(Uttf_Os2_s) {
    uint16_t version;
    int16_t  xAvgCharWidth;
    uint16_t usWeightClass;
    uint16_t usWidthClass;
    uint16_t fsType;
    int16_t  ySubscriptXSize;
    int16_t  ySubscriptYSize;
    int16_t  ySubscriptXOffset;
    int16_t  ySubscriptYOffset;
    int16_t  ySuperscriptXSize;
    int16_t  ySuperscriptYSize;
    int16_t  ySuperscriptXOffset;
    int16_t  ySuperscriptYOffset;
    int16_t  yStrikeoutSize;
    int16_t  yStrikeoutPosition;
    int16_t  sFamilyClass;
    Uttf_Os2_Panose_t  panose;
    uint32_t ulUnicodeRange1;
    uint32_t ulUnicodeRange2;
    uint32_t ulUnicodeRange3;
    uint32_t ulUnicodeRange4;
    uint32_t achVendID;
    uint16_t fsSelection;
    uint16_t usFirstCharIndex;
    uint16_t usLastCharIndex;
    int16_t  sTypoAscender;
    int16_t  sTypoDescender;
    int16_t  sTypoLineGap;
    uint16_t usWinAscent;
    uint16_t usWinDescent;
    uint32_t ulCodePageRange1;
    uint32_t ulCodePageRange2;
    int16_t  sxHeight;
    int16_t  sCapHeight;
    uint16_t usDefaultChar;
    uint16_t usBreakChar;
    uint16_t usMaxContext;
    uint16_t usLowerOpticalPointSize;
    uint16_t usUpperOpticalPointSize;
} Uttf_Os2_t;

typedef struct Uttf_Os2_Info_s {
    Uttf_Os2_t* os2Ptr;
} Uttf_Os2_Info_t;


/*****************************************************************************/
Uttf_Status_t
uttf_Os2_Open( Uttf_Os2_t*      table_ptr,
               uint32_t         length,
               Uttf_Os2_Info_t* info_ptr );

#endif