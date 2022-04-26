/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"
#include "uttf_hmtx.h"




/*****************************************************************************/
Uttf_Status_t
uttf_Hmtx_Open( void*             table_ptr,
                uint32_t          table_len,
                Uttf_Hmtx_Info_t* info_ptr,
                uint16_t          num_metrics,
                uint16_t          num_glyphs )
{
    info_ptr->hmtxPtr              = table_ptr;
    info_ptr->numMetrics           = num_metrics;
    info_ptr->longHorMetricArray   = NULL;
    info_ptr->numSideBearing       = ((int32_t)num_glyphs - num_metrics);
    info_ptr->leftSideBearingArray = NULL;

    if( num_metrics > 0 )
    {
        info_ptr->longHorMetricArray = (Uttf_Hmtx_LongHorMetric_t*)table_ptr;
    }

    if( info_ptr->numSideBearing > 0 )
    {
        info_ptr->leftSideBearingArray = (Uttf_Hmtx_LeftSideBearing_t*)&(((Uttf_Hmtx_LongHorMetric_t*)table_ptr)[num_metrics]);
    }

    return( UTTF_STATUS_NO_ERROR );
}


/*****************************************************************************/
Uttf_Status_t
uttf_Hmtx_MetricsGet( Uttf_Hmtx_Info_t* info_ptr,
                      Uttf_GlyphIdx_t   idx,
                      uint16_t*         advance_width_ptr,
                      int16_t*          left_side_bearing_ptr )
{
    if( idx < info_ptr->numMetrics )
    {
        *advance_width_ptr     = info_ptr->longHorMetricArray[idx].advanceWidth;
        *left_side_bearing_ptr = info_ptr->longHorMetricArray[idx].leftSideBearing;
    }
    else
    {
        *advance_width_ptr     = info_ptr->longHorMetricArray[(idx-info_ptr->numMetrics - 1)].advanceWidth;
        *left_side_bearing_ptr = info_ptr->leftSideBearingArray[ (idx-info_ptr->numMetrics) ];
    }

    return( UTTF_STATUS_NO_ERROR );
}
