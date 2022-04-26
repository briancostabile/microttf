/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_NAME_H
#define UTTF_NAME_H

#include <stdint.h>
#include "uttf_system.h"

typedef enum Uttf_Name_PlatformId_e {
    UTTF_NAME_PLATFORM_ID_UNICODE   = 0,
    UTTF_NAME_PLATFORM_ID_MACINTOSH = 1,
    UTTF_NAME_PLATFORM_ID_ISO       = 2,
    UTTF_NAME_PLATFORM_ID_WINDOWS   = 3,
    UTTF_NAME_PLATFORM_ID_CUSTOM    = 4
} Uttf_Name_PlatformId_t;

typedef enum Uttf_Name_EncodingId_e {
    // Platform ID 0 (Unicode) Encoding IDs
    UTTF_NAME_ENCODING_ID_UNICODE_1P0       = 0,
    UTTF_NAME_ENCODING_ID_UNICODE_1P1       = 1,
    UTTF_NAME_ENCODING_ID_UNICODE_ISO_10646 = 2,
    UTTF_NAME_ENCODING_ID_UNICODE_2P0_BMP   = 3,
    UTTF_NAME_ENCODING_ID_UNICODE_2P0_FULL  = 4,
    UTTF_NAME_ENCODING_ID_UNICODE_VARIATION = 5,
    UTTF_NAME_ENCODING_ID_UNICODE_FULL      = 6,

    // Platform ID 1 (Macintosh) Encoding IDs
    UTTF_NAME_ENCODING_ID_MACINTOSH_ROMAN          = 0,
    UTTF_NAME_ENCODING_ID_MACINTOSH_JAPANESE       = 1,
    UTTF_NAME_ENCODING_ID_MACINTOSH_TRAD_CHINESE   = 2,
    UTTF_NAME_ENCODING_ID_MACINTOSH_KOREAN         = 3,
    UTTF_NAME_ENCODING_ID_MACINTOSH_ARABIC         = 4,
    UTTF_NAME_ENCODING_ID_MACINTOSH_HEBREW         = 5,
    UTTF_NAME_ENCODING_ID_MACINTOSH_GREEK          = 6,
    UTTF_NAME_ENCODING_ID_MACINTOSH_RUSSIAN        = 7,
    UTTF_NAME_ENCODING_ID_MACINTOSH_RSYMBOL        = 8,
    UTTF_NAME_ENCODING_ID_MACINTOSH_DEVANAGARI     = 9,
    UTTF_NAME_ENCODING_ID_MACINTOSH_GURMUKHI       = 10,
    UTTF_NAME_ENCODING_ID_MACINTOSH_GUJARATI       = 11,
    UTTF_NAME_ENCODING_ID_MACINTOSH_ORIYA          = 12,
    UTTF_NAME_ENCODING_ID_MACINTOSH_BENGALI        = 13,
    UTTF_NAME_ENCODING_ID_MACINTOSH_TAMIL          = 14,
    UTTF_NAME_ENCODING_ID_MACINTOSH_TELUGU         = 15,
    UTTF_NAME_ENCODING_ID_MACINTOSH_KANNADA        = 16,
    UTTF_NAME_ENCODING_ID_MACINTOSH_MALAYALAM      = 17,
    UTTF_NAME_ENCODING_ID_MACINTOSH_SINHALESE      = 18,
    UTTF_NAME_ENCODING_ID_MACINTOSH_BURMESE        = 19,
    UTTF_NAME_ENCODING_ID_MACINTOSH_KHMER          = 20,
    UTTF_NAME_ENCODING_ID_MACINTOSH_THAI           = 21,
    UTTF_NAME_ENCODING_ID_MACINTOSH_LAOTIAN        = 22,
    UTTF_NAME_ENCODING_ID_MACINTOSH_GEORGIAN       = 23,
    UTTF_NAME_ENCODING_ID_MACINTOSH_ARMENIAN       = 24,
    UTTF_NAME_ENCODING_ID_MACINTOSH_SIMP_CHINESE   = 25,
    UTTF_NAME_ENCODING_ID_MACINTOSH_TIBETAN        = 26,
    UTTF_NAME_ENCODING_ID_MACINTOSH_MONGOLIAN      = 27,
    UTTF_NAME_ENCODING_ID_MACINTOSH_GEEZ           = 28,
    UTTF_NAME_ENCODING_ID_MACINTOSH_SLAVIC         = 29,
    UTTF_NAME_ENCODING_ID_MACINTOSH_VIETNAMESE     = 30,
    UTTF_NAME_ENCODING_ID_MACINTOSH_SINDHI         = 31,
    UTTF_NAME_ENCODING_ID_MACINTOSH_UNINTERPRETED  = 32,
    
    // Platform ID 3 (Windows) Encoding IDs
    UTTF_NAME_ENCODING_ID_WINDOWS_SYMBOL    = 0,
    UTTF_NAME_ENCODING_ID_WINDOWS_UCS2      = 1,
    UTTF_NAME_ENCODING_ID_WINDOWS_SHIFT_JIS = 2,
    UTTF_NAME_ENCODING_ID_WINDOWS_PRC       = 3,
    UTTF_NAME_ENCODING_ID_WINDOWS_BIG5      = 4,
    UTTF_NAME_ENCODING_ID_WINDOWS_WANSUNG   = 5,
    UTTF_NAME_ENCODING_ID_WINDOWS_JOHAB     = 6,
    UTTF_NAME_ENCODING_ID_WINDOWS_UCS4      = 10,

} Uttf_Name_EncodingId_t;

typedef enum Uttf_Name_LanguageId_e {
    UTTF_NAME_LANGUAGE_ID_MS_AF_ZA = 0x0436, //Afrikaans, South Africa
    UTTF_NAME_LANGUAGE_ID_MS_SQ_AL = 0x041C, //Albanian, Albania

    UTTF_NAME_LANGUAGE_ID_MAC_ENGLISH = 0,
    UTTF_NAME_LANGUAGE_ID_MAC_FRENCH  = 1,
} Uttf_Name_LanguageId_t;

typedef enum Uttf_Name_NameId_e {
    UTTF_NAME_ID_COPYRIGHT                         = 0,
    UTTF_NAME_ID_FONT_FAMILY                       = 1,
    UTTF_NAME_ID_FONT_SUBFAMILY                    = 2,
    UTTF_NAME_ID_UNIQUE_ID                         = 3,
    UTTF_NAME_ID_FULL_FONT_NAME                    = 4,
    UTTF_NAME_ID_VERSION                           = 5,
    UTTF_NAME_ID_POSTSCRIPT_NAME                   = 6,
    UTTF_NAME_ID_TRADEMAR                          = 7,
    UTTF_NAME_ID_MANUFACTURER                      = 8,
    UTTF_NAME_ID_DESIGNER                          = 9,
    UTTF_NAME_ID_DESCRIPTION                       = 10,
    UTTF_NAME_ID_URL_VENDOR                        = 11,
    UTTF_NAME_ID_URL_DESIGNER                      = 12,
    UTTF_NAME_ID_LICENSE_DESCRIPTION               = 13,
    UTTF_NAME_ID_LICENSE_INFO_URL                  = 14,
    UTTF_NAME_ID_RESERVED                          = 15,
    UTTF_NAME_ID_TYPOGRAPHIC_FAMILY_NAME           = 16,
    UTTF_NAME_ID_TYPOGRAPHIC_SUBFAMILY_NAME        = 17,
    UTTF_NAME_ID_COMPATIBLE_FULL                   = 18,
    UTTF_NAME_ID_SAMPLE_TEXT                       = 19,
    UTTF_NAME_ID_POSTSCRIPT_CID                    = 20,
    UTTF_NAME_ID_WWS_FAMILY_NAME                   = 21,
    UTTF_NAME_ID_WWS_SUBFAMILY_NAME                = 22,
    UTTF_NAME_ID_LIGHT_BACKGROUND_PALETTE          = 23,
    UTTF_NAME_ID_DARK_BACKGROUND_PALETTE           = 24,
    UTTF_NAME_ID_VARIATIONS_POSTSCRIPT_NAME_PREFIX = 25
} Uttf_Name_NameId_t;

typedef PACKED_STRUCT(Uttf_Name_LangTagRec_s) {
    uint16_t length;  // Language-tag string length (in bytes)
    uint16_t offset;  // Language-tag string offset from start of storage area (in bytes).
} Uttf_Name_LangTagRec_t;

typedef PACKED_STRUCT(Uttf_Name_LangTable_s) {
    uint16_t               langTagCount;
    Uttf_Name_LangTagRec_t langTagRecords[];
} Uttf_Name_LangTable_t;

typedef PACKED_STRUCT(Uttf_Name_Rec_s) {
    uint16_t platformID;         // Platform identifier code.
    uint16_t platformSpecificID; // Platform-specific encoding identifier.
    uint16_t languageID;         // Language identifier.
    uint16_t nameID;             // Name identifiers.
    uint16_t length;             // Name string length in bytes.
    uint16_t offset;             // Name string offset in bytes from stringOffset.
} Uttf_Name_Rec_t;

typedef PACKED_STRUCT(Uttf_Name_s) {
    uint16_t        format;
    uint16_t        count;
    uint16_t        stringOffset;
    Uttf_Name_Rec_t nameRecords[];
} Uttf_Name_t;

typedef struct Uttf_Name_Info_s {
    Uttf_Name_t*     namePtr;
    Uttf_Name_Rec_t* fontFamilyRecPtr;
    Uttf_Name_Rec_t* fontSubFamilyRecPtr;
    Uttf_Name_Rec_t* fontNameRecPtr;
    Uttf_Name_Rec_t* psNameRecPtr;
} Uttf_Name_Info_t;

Uttf_Status_t
uttf_Name_Open( Uttf_Name_t*      table_ptr,
                uint32_t          length,
                Uttf_Name_Info_t* info_ptr );

Uttf_Status_t
uttf_Name_StringGet( Uttf_Name_Info_t* info_ptr,
                     uint16_t          name_id,
                     uint16_t*         str_len_ptr,
                     char**            str_ptr_ptr );

#endif
