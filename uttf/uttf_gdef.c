/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "uttf.h"

/*****************************************************************************/
Uttf_Otf_ClassDefTable_t*
uttf_Gdef_GetGlyphClassDef( Uttf_Gdef_Info_t* info_ptr )
{
    Uttf_Otf_ClassDefTable_t* table_ptr = NULL;
    if( info_ptr->gdefPtr->v10.glyphClassDefOffset != 0 )
    {
        table_ptr = (Uttf_Otf_ClassDefTable_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH(info_ptr->gdefPtr->v10.glyphClassDefOffset));
    }
    return( table_ptr );
}

/*****************************************************************************/
Uttf_Gdef_AttachList_t*
uttf_Gdef_GetAttachListPtr( Uttf_Gdef_Info_t* info_ptr )
{
    Uttf_Gdef_AttachList_t* table_ptr = NULL;
    if( info_ptr->gdefPtr->v10.attachListOffset != 0 )
    {
        table_ptr = (Uttf_Gdef_AttachList_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH(info_ptr->gdefPtr->v10.attachListOffset));
    }
    return( table_ptr );
}

/*****************************************************************************/
Uttf_Gdef_LigatureCaretList_t*
uttf_Gdef_GetLigCaretListPtr( Uttf_Gdef_Info_t* info_ptr )
{
    Uttf_Gdef_LigatureCaretList_t* table_ptr = NULL;
    if( info_ptr->gdefPtr->v10.glyphClassDefOffset != 0 )
    {
        table_ptr = (Uttf_Gdef_LigatureCaretList_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH(info_ptr->gdefPtr->v10.ligCaretListOffset));
    }
    return( table_ptr );
}

/*****************************************************************************/
Uttf_Gdef_MarkGlyphSetsTable_t*
uttf_Gdef_GetMarkGlyphSetsTablePtr( Uttf_Gdef_Info_t* info_ptr )
{
    Uttf_Gdef_MarkGlyphSetsTable_t* table_ptr = NULL;
    if( (UTTF_BE16TOH(info_ptr->gdefPtr->ver.minorVersion) >= 2) && (info_ptr->gdefPtr->v13.markGlyphSetsDefOffset != 0) )
    {
        table_ptr = (Uttf_Gdef_MarkGlyphSetsTable_t*)((uint8_t*)(info_ptr->gdefPtr) + UTTF_BE16TOH(info_ptr->gdefPtr->v13.markGlyphSetsDefOffset));
    }
    return( table_ptr );
}

/*****************************************************************************/
Uttf_Status_t
uttf_Gdef_Open( Uttf_Gdef_t*      table_ptr,
                uint32_t          length,
                Uttf_Gdef_Info_t* info_ptr )
{
    info_ptr->gdefPtr = table_ptr;
    return( UTTF_STATUS_NO_ERROR );
}

/*****************************************************************************/
Uttf_Status_t
uttf_Gdef_CoverageIdxGet( Uttf_Otf_CoverageTable_t* table_ptr,
                          Uttf_GlyphIdx_t           glyph_idx,
                          Uttf_Otf_CoverageIdx_t*   coverage_idx_ptr )
{
    if( UTTF_BE16TOH(table_ptr->format) == 1 )
    {
        uint16_t glyph_count = UTTF_BE16TOH(table_ptr->fmt1.glyphCount);

        //Binary Search (left,right,middle) the ranges 
        int16_t l = 0;
        int16_t r = (glyph_count - 1);
        int16_t m = 0;

        while( l <= r )
        {
            m = l + (r-l)/2;
            uint16_t glyph_id = UTTF_BE16TOH( table_ptr->fmt1.glyphArray[m] );
            if( glyph_idx == glyph_id )
            {
                *coverage_idx_ptr = m;
                return( UTTF_STATUS_NO_ERROR );
            }
            else if( glyph_idx < glyph_id )
            {   
                r = m - 1; // too high, look in the lower (left) half
            }
            else
            {
                l = m + 1; // too low, look in the upper (right) half
            }
        }            
    }
    else if( UTTF_BE16TOH(table_ptr->format) == 2 )
    {
        uint16_t range_count = UTTF_BE16TOH(table_ptr->fmt2.rangeCount);

        //Binary Search (left,right,middle) the ranges 
        int16_t l = 0;
        int16_t r = (range_count - 1);
        int16_t m = 0;

        while( l <= r )
        {
            m = l + (r-l)/2;
            uint16_t end_glyph_idx = UTTF_BE16TOH( table_ptr->fmt2.rangeRecords[m].endGlyphID );
            if( end_glyph_idx >= glyph_idx )
            {
                uint16_t start_glyph_idx = UTTF_BE16TOH( table_ptr->fmt2.rangeRecords[m].startGlyphID );
                if( start_glyph_idx <= glyph_idx )
                {
                    *coverage_idx_ptr = (UTTF_BE16TOH( table_ptr->fmt2.rangeRecords[m].startCoverageIndex ) + (glyph_idx - start_glyph_idx));
                    return( UTTF_STATUS_NO_ERROR );
                }
                else
                {   
                    r = m - 1; // Range is too high, look in the lower (left) half
                }
            }
            else
            {
                l = m + 1; // Range is too low, look in the upper (right) half
            }
        }            
    }

    return( UTTF_STATUS_FAILURE );
}


/*****************************************************************************/
Uttf_Otf_Class_t
uttf_Gdef_ClassGet( Uttf_Gdef_Info_t* info_ptr,
                    Uttf_GlyphIdx_t   glyph_idx )
{
    Uttf_Otf_Class_t class_val = 0;

    if( info_ptr->gdefPtr->v10.glyphClassDefOffset != 0 )
    {
        Uttf_Otf_ClassDefTable_t* table_ptr = uttf_Gdef_GetGlyphClassDef( info_ptr );

        if( UTTF_BE16TOH(table_ptr->format) == 1 )
        {
            uint16_t glyph_start_idx = UTTF_BE16TOH(table_ptr->fmt1.startGlyphID);
            uint16_t glyph_count = UTTF_BE16TOH(table_ptr->fmt1.glyphCount);

            // Direct lookup
            if( (glyph_start_idx <= glyph_idx) && (glyph_idx < (glyph_start_idx + glyph_count)) )
            {
                class_val = UTTF_BE16TOH(table_ptr->fmt1.classValueArray[ (glyph_idx - glyph_start_idx) ]);
            }
        }
        else if( UTTF_BE16TOH(table_ptr->format) == 2 )
        {
            uint16_t classRangeCount = UTTF_BE16TOH(table_ptr->fmt2.classRangeCount);

            //Binary Search (left,right,middle) the ranges 
            int16_t l = 0;
            int16_t r = (classRangeCount - 1);
            int16_t m = 0;

            while( l <= r )
            {
                m = l + (r-l)/2;
                uint16_t end_glyph_id = UTTF_BE16TOH( table_ptr->fmt2.classRangeRecords[m].endGlyphID );
                if( end_glyph_id >= glyph_idx )
                {
                    uint16_t start_glyph_id = UTTF_BE16TOH( table_ptr->fmt2.classRangeRecords[m].startGlyphID );
                    if( start_glyph_id <= glyph_idx )
                    {
                        class_val = UTTF_BE16TOH( table_ptr->fmt2.classRangeRecords[m].classValue );
                        break;
                    }
                    else
                    {   
                        r = m - 1; // Range is too high, look in the lower (left) half
                    }
                }
                else
                {
                    l = m + 1; // Range is too low, look in the upper (right) half
                }
            }            
        }
    }

    return( class_val );
}


/*****************************************************************************/
Uttf_Gdef_LigatureGlyphTable_t*
uttf_Gdef_LigatureGlyphTableGet( Uttf_Gdef_Info_t* info_ptr,
                                 Uttf_GlyphIdx_t   glyph_idx )
{
    Uttf_Status_t                   status;
    Uttf_Otf_CoverageIdx_t          coverage_idx;
    Uttf_Gdef_LigatureGlyphTable_t* table_ptr = NULL;
    Uttf_Gdef_LigatureCaretList_t*  list_ptr = uttf_Gdef_GetLigCaretListPtr(info_ptr);

    if( list_ptr != NULL )
    {
        // Assuming there is a valid offset or coverage table
        Uttf_Otf_CoverageTable_t* coverage_table_ptr = (Uttf_Otf_CoverageTable_t*)((uint8_t*)list_ptr + UTTF_BE16TOH(list_ptr->coverageOffset));
        uint16_t count = UTTF_BE16TOH(list_ptr->ligGlyphCount);

        // First find the CoverageIdx
        status = uttf_Gdef_CoverageIdxGet( coverage_table_ptr, glyph_idx, &coverage_idx );
        if( (status == UTTF_STATUS_NO_ERROR) && (coverage_idx < count) )
        {
            // Got the coverage index so now do a direct lookup of the list offset
            table_ptr = (Uttf_Gdef_LigatureGlyphTable_t*)((uint8_t*)list_ptr + UTTF_BE16TOH(list_ptr->ligGlyphOffsets[coverage_idx]));
        }
    }

    return( table_ptr );    
}


/*****************************************************************************/
Uttf_Status_t
uttf_Gdef_MarkSetGlyphCoverageIdx( Uttf_Gdef_Info_t*       info_ptr,
                                   Uttf_GlyphIdx_t         glyph_idx,
                                   Uttf_Otf_CoverageIdx_t* coverage_idx_ptr )
{
    Uttf_Gdef_MarkGlyphSetsTable_t* set_table_ptr = uttf_Gdef_GetMarkGlyphSetsTablePtr(info_ptr);

    if( set_table_ptr != NULL )
    {
        for( uint16_t i=0; i<UTTF_BE16TOH(set_table_ptr->markGlyphSetCount); i++ )
        {
            Uttf_Otf_CoverageTable_t* coverage_table_ptr;
            coverage_table_ptr = (Uttf_Otf_CoverageTable_t*)((uint8_t*)set_table_ptr + UTTF_BE32TOH(set_table_ptr->coverageOffsets[i]));
            if( uttf_Gdef_CoverageIdxGet( coverage_table_ptr, glyph_idx, coverage_idx_ptr ) == UTTF_STATUS_NO_ERROR )
            {
                return( UTTF_STATUS_NO_ERROR );
            }
        }        
    }

    return( UTTF_STATUS_FAILURE );
}
