/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_HMTX_H
#define UTTF_HMTX_H

#include <stdint.h>
#include "uttf_system.h"

typedef PACKED_STRUCT(Uttf_Hmtx_LongHorMetric_s) {
    uint16_t advanceWidth;
    int16_t  leftSideBearing;
} Uttf_Hmtx_LongHorMetric_t;

typedef uint16_t Uttf_Hmtx_LeftSideBearing_t;

typedef struct Uttf_Hmtx_Info_s {
    void*                        hmtxPtr;
    uint16_t                     numMetrics;
    Uttf_Hmtx_LongHorMetric_t*   longHorMetricArray;
    uint16_t                     numSideBearing;
    Uttf_Hmtx_LeftSideBearing_t* leftSideBearingArray;
} Uttf_Hmtx_Info_t;

Uttf_Status_t
uttf_Hmtx_Open( void*             table_ptr,
                uint32_t          table_len,
                Uttf_Hmtx_Info_t* info_ptr,
                uint16_t          num_metrics,  //hhea
                uint16_t          num_glyphs ); //maxp

Uttf_Status_t
uttf_Hmtx_MetricsGet( Uttf_Hmtx_Info_t* hmtx_info_ptr,
                      Uttf_GlyphIdx_t   idx,
                      uint16_t*         advance_width_ptr,
                      int16_t*          left_side_bearing_ptr );


#endif
