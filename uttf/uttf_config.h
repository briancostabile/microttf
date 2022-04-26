/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_CONFIG_H
#define UTTF_CONFIG_H


/*****************************************************************************/
/**
 * All the flags defined in this file are "ENABLE" flags. They can be overridden on
 * the build command line by defining the equivalent "DISABLE" flag. Only the
 * "ENABLE" flag is checked in the code. You can modify this file and comment
 * out the "ENABLE" flag or define the "DISABLE" flag on the command line.
 */
#define ENABLE  1
#define DISABLE 0
/*****************************************************************************/
/**
 * One of the CMAP formats must be enabled.
 * 
 * FMT0 is the fastest lookup, but only supports unicodes up to 0x000000FF. If
 * enabled along with another format, microttf will use the fmt0 table first
 * before doing a lookup with another table included in the font. That assumes
 * the font file contains a fmt0 table.
 * 
 * FMT4 is the most common and should be included. If possible a font should be
 * stripped to only include 1 FMT0 and 1 FMT4 table. The FMT4 table includes
 * everything needed to lookup a glyph, even the glyphs included in the FMT0 table
 * if code-size is an issue, then only enable FMT4 and strip the font of the FMT0
 * table.
 * 
 * FMT12 is required for Emoji fonts because those unicodes go beyond unicode 0xFFFF
 * FMT14 is used in conjunciton with FMT12 to support things like skin-tones on
 * faces, hands, and people. FMT14 cannot standalone, it requires FMT12.
 */
#if !defined( UTTF_CONFIG_CMAP_FMT0 )
#define UTTF_CONFIG_CMAP_FMT0 ENABLE
#endif

#if !defined( UTTF_CONFIG_CMAP_FMT4 )
#define UTTF_CONFIG_CMAP_FMT4 ENABLE
#endif

#if !defined( UTTF_CONFIG_CMAP_FMT6 )
#define UTTF_CONFIG_CMAP_FMT6 ENABLE
#endif

#if !defined( UTTF_CONFIG_CMAP_FMT12 )
#define UTTF_CONFIG_CMAP_FMT12 ENABLE
#endif

#if !defined( UTTF_CONFIG_CMAP_FMT14 )
#define UTTF_CONFIG_CMAP_FMT14 ENABLE
#endif


/*****************************************************************************/
/**
 * POST is not strictly required for embedded device font rendering onto an LCD.
 * It's meant for postscript printers. There are some metrics defined in the
 * post table that may be useful. If you're not using this on a postscript printer
 * then strip the fonts of the names and use format 3
 */
#if !defined( UTTF_CONFIG_POST_FMT1_DISABLE ) && !defined( UTTF_CONFIG_POST_FMT1_ENABLE )
#define UTTF_CONFIG_POST_FMT1_ENABLE 1
#endif

#if !defined( UTTF_CONFIG_POST_FMT2_DISABLE ) && !defined( UTTF_CONFIG_POST_FMT2_ENABLE )
#define UTTF_CONFIG_POST_FMT2_ENABLE 1
#endif

#if !defined( UTTF_CONFIG_POST_FMT3_DISABLE ) && !defined( UTTF_CONFIG_POST_FMT3_ENABLE )
#define UTTF_CONFIG_POST_FMT3_ENABLE 1
#endif


/*****************************************************************************/
/**
 * NAME table has 2 formats. FMT0 is simpler/smaller and contains all that's really
 * needed for basic font rendering. FMT1 includes language strings instead of
 * codes.
 */
#if !defined( UTTF_CONFIG_NAME_FMT0_DISABLE ) && !defined( UTTF_CONFIG_NAME_FMT0_ENABLE )
#define UTTF_CONFIG_NAME_FMT0_ENABLE 1
#endif

#if !defined( UTTF_CONFIG_NAME_FMT1_DISABLE ) && !defined( UTTF_CONFIG_NAME_FMT1_ENABLE )
#define UTTF_CONFIG_NAME_FMT1_ENABLE 1
#endif

#endif