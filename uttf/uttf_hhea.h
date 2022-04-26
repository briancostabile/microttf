/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_HHEA_H
#define UTTF_HHEA_H

#include <stdint.h>
#include "uttf_system.h"

#define UTTF_MAXP_TABLE_VERSION_V1 0x00010000

typedef PACKED_STRUCT(Uttf_Hhea_s) {
    uint32_t version;
    int16_t  ascent;               // Distance from baseline of highest ascender
    int16_t  descent;              // Distance from baseline of lowest descender
    int16_t  lineGap;              // typographic line gap
    uint16_t advanceWidthMax;      // must be consistent with horizontal metrics
    int16_t  minLeftSideBearing;   // must be consistent with horizontal metrics
    int16_t  minRightSideBearing;  // must be consistent with horizontal metrics
    int16_t  xMaxExtent;           // max(lsb + (xMax-xMin))
    int16_t  caretSlopeRise;       // used to calculate the slope of the caret (rise/run) set to 1 for vertical caret
    int16_t  caretSlopeRun;        // 0 for vertical
    int16_t	 caretOffset;          // set value to 0 for non-slanted fonts
    int16_t  reserved[4];          // set value to 0
    int16_t  metricDataFormat;     // 0 for current format
    uint16_t numOfLongHorMetrics; // number of advance widths in metrics table
} Uttf_Hhea_t;

typedef struct Uttf_Hhea_Info_s {
    Uttf_Hhea_t* hheaPtr;
} Uttf_Hhea_Info_t;

/*****************************************************************************/
Uttf_Status_t
uttf_Hhea_Open( Uttf_Hhea_t*      table_ptr,
                uint32_t          table_len,
                Uttf_Hhea_Info_t* info_ptr );

#endif
