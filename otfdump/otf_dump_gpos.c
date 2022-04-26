
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>

#include "otf_dump.h"

void otf_dump_GdefCoverageTable( Uttf_Otf_CoverageTable_t* table_ptr );

/*****************************************************************************/
void
otf_dump_GposLangSysTable( char*                    prefix_str,
                           Uttf_Otf_LangSysTable_t* table_ptr )
{
    printf( "%s----------------------"OTF_DUMP_NL, prefix_str );
    printf( "%slookupOrder:%d"OTF_DUMP_NL, prefix_str, UTTF_BE16TOH(table_ptr->lookupOrder));  
    printf( "%srequiredFeatureIndex:%d"OTF_DUMP_NL, prefix_str, UTTF_BE16TOH(table_ptr->requiredFeatureIndex));
    printf( "%sfeatureIndexCount:%d"OTF_DUMP_NL, prefix_str, UTTF_BE16TOH(table_ptr->featureIndexCount));
    for( uint16_t i=0; i<UTTF_BE16TOH(table_ptr->featureIndexCount); i++ )
    {
        printf("%s[%d]:%d"OTF_DUMP_NL, prefix_str, i, UTTF_BE16TOH(table_ptr->featureIndices[i]));
    }
}

/*****************************************************************************/
void
otf_dump_GposScriptTable( Uttf_Otf_ScriptTable_t* table_ptr )
{
    printf( "\t----------------------"OTF_DUMP_NL );
    printf( "\tdefaultSysLangOffset:%d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->defaultLangSys));  
    otf_dump_GposLangSysTable("\t\t", (Uttf_Otf_LangSysTable_t*)( (char*)table_ptr + UTTF_BE16TOH(table_ptr->defaultLangSys)));
    printf( OTF_DUMP_NL );
    printf( "\tlangSysCount:%d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->langSysCount));
    for( uint16_t i=0; i<UTTF_BE16TOH(table_ptr->langSysCount); i++ )
    {
        char* tag_ptr = (char*)&(table_ptr->langSysRecords[i].langSysTag);
        uint32_t offset = UTTF_BE16TOH(table_ptr->langSysRecords[i].langSysOffset);
        printf("\t%c%c%c%c: %d"OTF_DUMP_NL, tag_ptr[0], tag_ptr[1], tag_ptr[2], tag_ptr[3], offset);        
        otf_dump_GposLangSysTable("\t\t", (Uttf_Otf_LangSysTable_t*)(tag_ptr + offset));
    }
}


/*****************************************************************************/
void
otf_dump_GposScriptListTable( Uttf_Gpos_Info_t* info_ptr )
{
    if(info_ptr->gposPtr->v10.scriptListOffset != 0)
    {
        Uttf_Otf_ScriptListTable_t* list_ptr = (Uttf_Otf_ScriptListTable_t*)((uint8_t*)(info_ptr->gposPtr) + UTTF_BE16TOH(info_ptr->gposPtr->v10.scriptListOffset));
        printf( "----------------------"OTF_DUMP_NL );
        printf( "ScriptList Length:%d"OTF_DUMP_NL, UTTF_BE16TOH(list_ptr->scriptCount));
        for( uint16_t i=0; i<UTTF_BE16TOH(list_ptr->scriptCount); i++ )
        {
            char* tag_ptr = (char*)&(list_ptr->scriptRecords[i].scriptTag);
            uint32_t offset = UTTF_BE16TOH(list_ptr->scriptRecords[i].scriptOffset);
            printf("%c%c%c%c: %d"OTF_DUMP_NL, tag_ptr[0], tag_ptr[1], tag_ptr[2], tag_ptr[3], offset);
            otf_dump_GposScriptTable( (Uttf_Otf_ScriptTable_t*)((uint8_t*)list_ptr + offset) );
        }
    }    
}


/*****************************************************************************/
void
otf_dump_GposFeatureTable( char*                    prefix_str,
                           Uttf_Otf_FeatureTable_t* table_ptr )
{
    printf( "%s----------------------"OTF_DUMP_NL, prefix_str );
    printf( "%sfeatureParams:%d"OTF_DUMP_NL, prefix_str, UTTF_BE16TOH(table_ptr->featureParams));  
    printf( "%slookupIndexCount:%d"OTF_DUMP_NL, prefix_str, UTTF_BE16TOH(table_ptr->lookupIndexCount));
    for( uint16_t i=0; i<UTTF_BE16TOH(table_ptr->lookupIndexCount); i++ )
    {
        printf("%s[%d]:%d"OTF_DUMP_NL, prefix_str, i, UTTF_BE16TOH(table_ptr->lookupListIndices[i]));
    }
}


/*****************************************************************************/
void
otf_dump_GposFeatureListTable( Uttf_Gpos_Info_t* info_ptr )
{
    if(info_ptr->gposPtr->v10.scriptListOffset != 0)
    {
        Uttf_Otf_FeatureListTable_t* list_ptr = (Uttf_Otf_FeatureListTable_t*)((uint8_t*)(info_ptr->gposPtr) + UTTF_BE16TOH(info_ptr->gposPtr->v10.featureListOffset));
        printf( "----------------------"OTF_DUMP_NL );
        printf( "FeatureList Length:%d"OTF_DUMP_NL, UTTF_BE16TOH(list_ptr->featureCount));
        for( uint16_t i=0; i<UTTF_BE16TOH(list_ptr->featureCount); i++ )
        {
            char* tag_ptr = (char*)&(list_ptr->featureRecords[i].featureTag);
            uint32_t offset = UTTF_BE16TOH(list_ptr->featureRecords[i].featureOffset);
            printf("%c%c%c%c: %d"OTF_DUMP_NL, tag_ptr[0], tag_ptr[1], tag_ptr[2], tag_ptr[3], offset);
            otf_dump_GposFeatureTable( "\t", (Uttf_Otf_FeatureTable_t*)((uint8_t*)list_ptr + offset) );
        }
    }    
}


/*****************************************************************************/
void
otf_dump_GposDeviceTable( uint8_t                 leading_spaces,
                          Uttf_Otf_DeviceTable_t* table_ptr )
{
    OTF_DUMP_PRINTF( leading_spaces, "DeviceTable"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "start/end/format: %d/%d/0x%04X"OTF_DUMP_NL,
                     UTTF_BE16TOH( table_ptr->startSize ),
                     UTTF_BE16TOH( table_ptr->endSize ),
                     UTTF_BE16TOH( table_ptr->deltaFormat ) );
}


/*****************************************************************************/
void
otf_dump_GposValueRecord( uint8_t  leading_spaces,
                          void*    pos_table_ptr,
                          uint16_t format_flags,
                          uint8_t* table_ptr )
{
    uint16_t offset;

    OTF_DUMP_PRINTF( leading_spaces, "valueFormat:0x%04X"OTF_DUMP_NL, format_flags );
    OTF_DUMP_PRINTF( leading_spaces, "ValueRecord"OTF_DUMP_NL );
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_X_PLACEMENT )
    {
        int16_t x_placement = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "Placement x:%d"OTF_DUMP_NL, x_placement );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_PLACEMENT )
    {
        int16_t y_placement = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "Placement y:%d"OTF_DUMP_NL, y_placement );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_X_ADVANCE )
    {
        int16_t x_advance = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "Advance x:%d"OTF_DUMP_NL, x_advance );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_ADVANCE )
    {
        int16_t y_advance = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "Advance y:%d"OTF_DUMP_NL, y_advance );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_X_PLACEMENT_DEVICE )
    {
        uint16_t offset = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "x Placement Device Table Offset:%d"OTF_DUMP_NL, offset );
        otf_dump_GposDeviceTable( (leading_spaces + 4), (Uttf_Otf_DeviceTable_t*)((uint8_t*)pos_table_ptr + offset) );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_PLACEMENT_DEVICE )
    {
        int16_t offset = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "y Placement Device Table Offset:%d"OTF_DUMP_NL, offset );
        otf_dump_GposDeviceTable( (leading_spaces + 4), (Uttf_Otf_DeviceTable_t*)((uint8_t*)pos_table_ptr + offset) );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_X_ADVANCE_DEVICE )
    {
        uint16_t offset = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "x Advance Device Table Offset:%d"OTF_DUMP_NL, offset );
        otf_dump_GposDeviceTable( (leading_spaces + 4), (Uttf_Otf_DeviceTable_t*)((uint8_t*)pos_table_ptr + offset) );
        table_ptr += 2;
    }
    if( format_flags & UTTF_GPOS_VALUE_FORMAT_FLAGS_Y_ADVANCE_DEVICE )
    {
        int16_t offset = ((table_ptr[0] << 8) + table_ptr[1]);
        OTF_DUMP_PRINTF( leading_spaces, "y Advance Device Table Offset:%d"OTF_DUMP_NL, offset );
        otf_dump_GposDeviceTable( (leading_spaces + 4), (Uttf_Otf_DeviceTable_t*)((uint8_t*)pos_table_ptr + offset) );
        table_ptr += 2;
    }
}

/***************
 * Type 1
 **************/
/*****************************************************************************/
void
otf_dump_GposLookupTableType1Fmt1( uint8_t                    leading_spaces,
                                   Uttf_Gpos_SinglePosFmt1_t* table_ptr )
{
    uint16_t coverage_offset = UTTF_BE16TOH( table_ptr->coverageOffset );
    Uttf_Otf_CoverageTable_t* coverage_table_ptr = (Uttf_Otf_CoverageTable_t*)((uint8_t*)table_ptr + coverage_offset);
    OTF_DUMP_PRINTF( leading_spaces, "coverageOffset:%d"OTF_DUMP_NL, coverage_offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );
    otf_dump_GposValueRecord( leading_spaces, table_ptr, UTTF_BE16TOH( table_ptr->valueFormat ), (uint8_t*)table_ptr + sizeof(Uttf_Gpos_SinglePosFmt1_t) );
}

/*****************************************************************************/
void
otf_dump_GposLookupTableType1( uint8_t                leading_spaces,
                               Uttf_Gpos_SinglePos_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->posFormat );

    OTF_DUMP_PRINTF( leading_spaces, "-----"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "format:%d"OTF_DUMP_NL, format );
    
    switch( format )
    {
        case 1:
        {
            otf_dump_GposLookupTableType1Fmt1( (leading_spaces + 4), (Uttf_Gpos_SinglePosFmt1_t*)table_ptr );
        }
        break;
        case 2:
        {
            //otf_dump_GposLookupTableType1Fmt2( (leading_spaces + 4), (Uttf_Gpos_SinglePosFmt2_t*)table_ptr );
        }
        break;
        default:
            break;
    }

}

/***************
 * Type 4
 **************/
/*****************************************************************************/
void
otf_dump_GposLookupTableAnchorTable( uint8_t                  leading_spaces,
                                     Uttf_Gpos_AnchorTable_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->anchorFormat ); 
    OTF_DUMP_PRINTF( leading_spaces, "Format: %d"OTF_DUMP_NL, format );
    OTF_DUMP_PRINTF( leading_spaces, "x/y: %d/%d"OTF_DUMP_NL, (int16_t)UTTF_BE16TOH( table_ptr->fmt1.xCoordinate ), (int16_t)UTTF_BE16TOH( table_ptr->fmt1.yCoordinate ) );
    if( format == 2 )
    {
        OTF_DUMP_PRINTF( leading_spaces, "anchorPoint: %d"OTF_DUMP_NL, UTTF_BE16TOH( table_ptr->fmt2.anchorPoint ) );
    }
    else if( format == 3 )
    {
        OTF_DUMP_PRINTF( leading_spaces, "Device Table Offset x/y: %d/%d"OTF_DUMP_NL, UTTF_BE16TOH( table_ptr->fmt3.xDeviceOffset ), UTTF_BE16TOH( table_ptr->fmt3.yDeviceOffset ) );
    }
}


/*****************************************************************************/
void
otf_dump_GposLookupTableBaseArrayTable( uint8_t                     leading_spaces,
                                        uint16_t                    mark_class_count,
                                        Uttf_Gpos_BaseArrayTable_t* table_ptr )
{
    uint16_t count = UTTF_BE16TOH( table_ptr->baseCount ); 
    OTF_DUMP_PRINTF( leading_spaces, "baseCount: %d"OTF_DUMP_NL, count );
    OTF_DUMP_PRINTF( leading_spaces, "[idx.mark]\tvalue"OTF_DUMP_NL );
    for( int i=0; i<count; i++ )
    {
        for( int m=0; m<mark_class_count; m++ )
        {
            uint16_t offset = UTTF_BE16TOH( table_ptr->baseRecords[(mark_class_count * i) + m] );
            OTF_DUMP_PRINTF( leading_spaces, "[%d.%d]\t\t%d"OTF_DUMP_NL, i, m, offset );
            otf_dump_GposLookupTableAnchorTable( (leading_spaces + 2), (Uttf_Gpos_AnchorTable_t*)((uint8_t*)table_ptr + offset) );
        }
    }
}


/*****************************************************************************/
void
otf_dump_GposLookupTableMarkArrayTable( uint8_t                     leading_spaces,
                                        Uttf_Gpos_MarkArrayTable_t* table_ptr )
{
    uint16_t count = UTTF_BE16TOH( table_ptr->markCount ); 
    OTF_DUMP_PRINTF( leading_spaces, "MarkCount: %d"OTF_DUMP_NL, count );
    OTF_DUMP_PRINTF( leading_spaces, "class\tanchorOffset"OTF_DUMP_NL );
    for( int i=0; i<count; i++ )
    {
        uint16_t class = UTTF_BE16TOH( table_ptr->markRecords[i].markClass ); 
        uint16_t offset = UTTF_BE16TOH( table_ptr->markRecords[i].markAnchorOffset );
        OTF_DUMP_PRINTF( leading_spaces, "  %d\t%d"OTF_DUMP_NL, class, offset );
        otf_dump_GposLookupTableAnchorTable( (leading_spaces + 10), (Uttf_Gpos_AnchorTable_t*)((uint8_t*)table_ptr + offset) );
    }
}


/*****************************************************************************/
void
otf_dump_GposLookupTableType4Fmt1( uint8_t                      leading_spaces,
                                   Uttf_Gpos_MarkBasePosFmt1_t* table_ptr )
{
    uint16_t offset;
    Uttf_Otf_CoverageTable_t* coverage_table_ptr;
    Uttf_Gpos_MarkArrayTable_t* mark_array_table_ptr;
    Uttf_Gpos_BaseArrayTable_t* base_array_table_ptr;

    offset = UTTF_BE16TOH( table_ptr->markCoverageOffset );
    coverage_table_ptr = OTF_COVERAGE_TABLE_PTR( table_ptr, offset );
    OTF_DUMP_PRINTF( leading_spaces, "markCoverageOffset: %d"OTF_DUMP_NL, offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );

    offset = UTTF_BE16TOH( table_ptr->baseCoverageOffset );
    coverage_table_ptr = OTF_COVERAGE_TABLE_PTR( table_ptr, offset );
    OTF_DUMP_PRINTF( leading_spaces, "baseCoverageOffset: %d"OTF_DUMP_NL, offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );

    uint16_t mark_class_count = UTTF_BE16TOH( table_ptr->markClassCount );
    OTF_DUMP_PRINTF( leading_spaces, "markClassCount:     %d"OTF_DUMP_NL, mark_class_count );

    offset = UTTF_BE16TOH( table_ptr->markArrayOffset );
    mark_array_table_ptr =  ((Uttf_Gpos_MarkArrayTable_t*)((uint8_t*)table_ptr + offset));
    OTF_DUMP_PRINTF( leading_spaces, "markArrayOffset:    %d"OTF_DUMP_NL, offset );
    otf_dump_GposLookupTableMarkArrayTable( (leading_spaces + 4), mark_array_table_ptr );

    offset = UTTF_BE16TOH( table_ptr->baseArrayOffset );
    base_array_table_ptr =  ((Uttf_Gpos_BaseArrayTable_t*)((uint8_t*)table_ptr + offset));
    OTF_DUMP_PRINTF( leading_spaces, "baseArrayOffset:    %d"OTF_DUMP_NL, offset );
    otf_dump_GposLookupTableBaseArrayTable( (leading_spaces + 4), mark_class_count, base_array_table_ptr );
}

/*****************************************************************************/
void
otf_dump_GposLookupTableType4( uint8_t                  leading_spaces,
                               Uttf_Gpos_MarkBasePos_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->posFormat );

    OTF_DUMP_PRINTF( leading_spaces, "-----"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "format:%d"OTF_DUMP_NL, format );
    
    switch( format )
    {
        case 1:
        {
            otf_dump_GposLookupTableType4Fmt1( (leading_spaces + 4), (Uttf_Gpos_MarkBasePosFmt1_t*)table_ptr );
        }
        break;
        default:
            OTF_DUMP_PRINTF( leading_spaces, "Error: Unsupported Format"OTF_DUMP_NL );
            break;
    }

}


/***************
 * Type 5
 **************/

/*****************************************************************************/
void
otf_dump_GposLookupTableLigAttachTable( uint8_t                     leading_spaces,
                                       uint16_t                    mark_class_count,
                                       Uttf_Gpos_LigAttachTable_t* table_ptr )
{
    uint16_t count = UTTF_BE16TOH( table_ptr->componentCount ); 
    OTF_DUMP_PRINTF( leading_spaces, "componentCount: %d"OTF_DUMP_NL, count );
    OTF_DUMP_PRINTF( leading_spaces, "[idx.lig]\tvalue"OTF_DUMP_NL );
    for( int i=0; i<count; i++ )
    {
        for( int m=0; m<mark_class_count; m++ )
        {
            uint16_t offset = UTTF_BE16TOH( table_ptr->componentRecords[(mark_class_count * i) + m] );
            OTF_DUMP_PRINTF( leading_spaces, "[%d.%d]\t\t%d"OTF_DUMP_NL, i, m, offset );
            otf_dump_GposLookupTableAnchorTable( (leading_spaces + 2), (Uttf_Gpos_AnchorTable_t*)((uint8_t*)table_ptr + offset) );
        }
    }
}


/*****************************************************************************/
void
otf_dump_GposLookupTableLigArrayTable( uint8_t                    leading_spaces,
                                       uint16_t                   mark_class_count,
                                       Uttf_Gpos_LigArrayTable_t* table_ptr )
{
    uint16_t count = UTTF_BE16TOH( table_ptr->ligatureCount ); 
    OTF_DUMP_PRINTF( leading_spaces, "ligCount: %d"OTF_DUMP_NL, count );
    OTF_DUMP_PRINTF( leading_spaces, "[idx.offset]\tvalue"OTF_DUMP_NL );
    for( int i=0; i<count; i++ )
    {
        uint16_t offset = UTTF_BE16TOH( table_ptr->ligatureAttachOffsets[count] );
        OTF_DUMP_PRINTF( leading_spaces, "[%d]\t\t%d"OTF_DUMP_NL, i, offset );
        otf_dump_GposLookupTableLigAttachTable( (leading_spaces + 2),
                                                mark_class_count,
                                                (Uttf_Gpos_LigAttachTable_t*)((uint8_t*)table_ptr + offset) );
    }
}


/*****************************************************************************/
void
otf_dump_GposLookupTableType5Fmt1( uint8_t                     leading_spaces,
                                   Uttf_Gpos_MarkLigPosFmt1_t* table_ptr )
{
    uint16_t offset;
    Uttf_Otf_CoverageTable_t* coverage_table_ptr;
    Uttf_Gpos_MarkArrayTable_t* mark_array_table_ptr;
    Uttf_Gpos_LigArrayTable_t*  lig_array_table_ptr;

    offset = UTTF_BE16TOH( table_ptr->markCoverageOffset );
    coverage_table_ptr = OTF_COVERAGE_TABLE_PTR( table_ptr, offset );
    OTF_DUMP_PRINTF( leading_spaces, "markCoverageOffset: %d"OTF_DUMP_NL, offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );

    offset = UTTF_BE16TOH( table_ptr->ligatureCoverageOffset );
    coverage_table_ptr = OTF_COVERAGE_TABLE_PTR( table_ptr, offset );
    OTF_DUMP_PRINTF( leading_spaces, "ligatureCoverageOffset: %d"OTF_DUMP_NL, offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );

    uint16_t mark_class_count = UTTF_BE16TOH( table_ptr->markClassCount );
    OTF_DUMP_PRINTF( leading_spaces, "markClassCount:     %d"OTF_DUMP_NL, mark_class_count );

    offset = UTTF_BE16TOH( table_ptr->markArrayOffset );
    mark_array_table_ptr =  ((Uttf_Gpos_MarkArrayTable_t*)((uint8_t*)table_ptr + offset));
    OTF_DUMP_PRINTF( leading_spaces, "markArrayOffset:    %d"OTF_DUMP_NL, offset );
    otf_dump_GposLookupTableMarkArrayTable( (leading_spaces + 4), mark_array_table_ptr );

    offset = UTTF_BE16TOH( table_ptr->ligatureArrayOffset );
    lig_array_table_ptr =  ((Uttf_Gpos_LigArrayTable_t*)((uint8_t*)table_ptr + offset));
    OTF_DUMP_PRINTF( leading_spaces, "ligatureArrayOffset:    %d"OTF_DUMP_NL, offset );
    otf_dump_GposLookupTableLigArrayTable( (leading_spaces + 4), mark_class_count, lig_array_table_ptr );
}


/*****************************************************************************/
void
otf_dump_GposLookupTableType5( uint8_t                 leading_spaces,
                               Uttf_Gpos_MarkLigPos_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->posFormat );

    OTF_DUMP_PRINTF( leading_spaces, "-----"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "format:%d"OTF_DUMP_NL, format );
    
    switch( format )
    {
        case 1:
        {
            otf_dump_GposLookupTableType4Fmt1( (leading_spaces + 4), (Uttf_Gpos_MarkBasePosFmt1_t*)table_ptr );
        }
        break;
        default:
            OTF_DUMP_PRINTF( leading_spaces, "Error: Unsupported Format"OTF_DUMP_NL );
            break;
    }
}


/***************
 * Type 6
 **************/

/*****************************************************************************/
void
otf_dump_GposLookupTableType6Fmt1( uint8_t                      leading_spaces,
                                   Uttf_Gpos_MarkMarkPosFmt1_t* table_ptr )
{
    uint16_t offset;
    Uttf_Otf_CoverageTable_t* coverage_table_ptr;
    Uttf_Gpos_MarkArrayTable_t* mark_array_table_ptr;
    Uttf_Gpos_LigArrayTable_t*  lig_array_table_ptr;

    offset = UTTF_BE16TOH( table_ptr->mark1CoverageOffset );
    coverage_table_ptr = OTF_COVERAGE_TABLE_PTR( table_ptr, offset );
    OTF_DUMP_PRINTF( leading_spaces, "mark1CoverageOffset: %d"OTF_DUMP_NL, offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );

    offset = UTTF_BE16TOH( table_ptr->mark2CoverageOffset );
    coverage_table_ptr = OTF_COVERAGE_TABLE_PTR( table_ptr, offset );
    OTF_DUMP_PRINTF( leading_spaces, "mark2CoverageOffset: %d"OTF_DUMP_NL, offset );
    otf_dump_OtfCoverageTable( (leading_spaces + 4), coverage_table_ptr );

    uint16_t mark_class_count = UTTF_BE16TOH( table_ptr->markClassCount );
    OTF_DUMP_PRINTF( leading_spaces, "markClassCount:     %d"OTF_DUMP_NL, mark_class_count );

    offset = UTTF_BE16TOH( table_ptr->mark1ArrayOffset );
    mark_array_table_ptr =  ((Uttf_Gpos_MarkArrayTable_t*)((uint8_t*)table_ptr + offset));
    OTF_DUMP_PRINTF( leading_spaces, "mark1ArrayOffset:    %d"OTF_DUMP_NL, offset );
    otf_dump_GposLookupTableMarkArrayTable( (leading_spaces + 4), mark_array_table_ptr );

    offset = UTTF_BE16TOH( table_ptr->mark1ArrayOffset );
    mark_array_table_ptr =  ((Uttf_Gpos_MarkArrayTable_t*)((uint8_t*)table_ptr + offset));
    OTF_DUMP_PRINTF( leading_spaces, "mark2ArrayOffset:    %d"OTF_DUMP_NL, offset );
    otf_dump_GposLookupTableMarkArrayTable( (leading_spaces + 4), mark_array_table_ptr );
}


/*****************************************************************************/
void
otf_dump_GposLookupTableType6( uint8_t                  leading_spaces,
                               Uttf_Gpos_MarkMarkPos_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH( table_ptr->posFormat );

    OTF_DUMP_PRINTF( leading_spaces, "-----"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "format:%d"OTF_DUMP_NL, format );
    
    switch( format )
    {
        case 1:
        {
            otf_dump_GposLookupTableType6Fmt1( (leading_spaces + 4), (Uttf_Gpos_MarkMarkPosFmt1_t*)table_ptr );
        }
        break;
        default:
            OTF_DUMP_PRINTF( leading_spaces, "Error: Unsupported Format"OTF_DUMP_NL );
            break;
    }
}


/***************
 * Type 8
 **************/
/*****************************************************************************/
void
otf_dump_GposLookupTableType8Fmt1ChainPosRuleTable( uint8_t                           leading_spaces,
                                                    Uttf_Gpos_ChainPosRuleSetTable_t* table_ptr )
{

}


/*****************************************************************************/
void
otf_dump_GposLookupTableType8Fmt1( uint8_t                          leading_spaces,
                                   Uttf_Gpos_ChainContextPosFmt1_t* table_ptr )
{
    uint16_t coverage_offset = UTTF_BE16TOH( table_ptr->coverageOffset );
    Uttf_Otf_CoverageTable_t* coverage_table_ptr = (Uttf_Otf_CoverageTable_t*)((uint8_t*)table_ptr + coverage_offset);
    uint16_t chain_Pos_rule_set_count = UTTF_BE16TOH( table_ptr->chainPosRuleSetCount );

    OTF_DUMP_PRINTF( leading_spaces, "CoverageOffset:%d"OTF_DUMP_NL, coverage_offset );
    
    OTF_DUMP_PRINTF( leading_spaces, "chainPosRuleSetCount:%d"OTF_DUMP_NL, chain_Pos_rule_set_count );
    for( int i=0; i<chain_Pos_rule_set_count; i++ )
    {
        uint16_t offset = UTTF_BE16TOH( table_ptr->chainPosRuleSetOffsets[i] );
        Uttf_Gpos_ChainPosRuleSetTable_t* chain_pos_rule_set_table_ptr = (Uttf_Gpos_ChainPosRuleSetTable_t*)((uint8_t*)table_ptr + offset);
        otf_dump_GposLookupTableType8Fmt1ChainPosRuleTable( leading_spaces, chain_pos_rule_set_table_ptr );
    }
    OTF_DUMP_PRINTF( 0, OTF_DUMP_NL );
}

/*****************************************************************************/
void
otf_dump_GposLookupTableType8Fmt3( uint8_t                          leading_spaces,
                                   Uttf_Gpos_ChainContextPosFmt3_t* table_ptr )
{
    Uttf_Gpos_ChainContextPosFmt3Input_t*     input_ptr;
    Uttf_Gpos_ChainContextPosFmt3Lookahead_t* lookahead_ptr;
    Uttf_Gpos_ChainContextPosFmt3Pos_t*       pos_ptr;

    uint16_t backtrace_glyph_count = UTTF_BE16TOH(table_ptr->backtrackGlyphCount);
    input_ptr = (Uttf_Gpos_ChainContextPosFmt3Input_t*)(((uint8_t*)table_ptr) + offsetof(Uttf_Gpos_ChainContextPosFmt3_t, backtrackCoverageOffsets) + (backtrace_glyph_count * sizeof(table_ptr->backtrackCoverageOffsets[0])));
    uint16_t input_glyph_count = UTTF_BE16TOH(input_ptr->inputGlyphCount);
    lookahead_ptr = (Uttf_Gpos_ChainContextPosFmt3Lookahead_t*)(((uint8_t*)input_ptr) + offsetof(Uttf_Gpos_ChainContextPosFmt3Input_t, inputSequence) + (input_glyph_count * sizeof(input_ptr->inputSequence[0])));
    uint16_t lookahead_glyph_count = UTTF_BE16TOH(lookahead_ptr->lookaheadGlyphCount);
    pos_ptr = (Uttf_Gpos_ChainContextPosFmt3Pos_t*)(((uint8_t*)lookahead_ptr) + offsetof(Uttf_Gpos_ChainContextPosFmt3Lookahead_t, lookaheadCoverageOffsets) + (lookahead_glyph_count * sizeof(lookahead_ptr->lookaheadCoverageOffsets[0])));
    uint16_t pos_count = UTTF_BE16TOH(pos_ptr->posCount);

    OTF_DUMP_PRINTF( leading_spaces, "Bactrace Glyph Count:%d"OTF_DUMP_NL, backtrace_glyph_count );
    for( int i=0; i < backtrace_glyph_count; i++ )
    {
        uint16_t offset = UTTF_BE16TOH(table_ptr->backtrackCoverageOffsets[i]);
        OTF_DUMP_PRINTF( leading_spaces, "offset:%d"OTF_DUMP_NL, offset );
        otf_dump_OtfCoverageTable( (leading_spaces + 4), (Uttf_Otf_CoverageTable_t*)(((uint8_t*)table_ptr) + offset));
    }
    
    OTF_DUMP_PRINTF( leading_spaces, "Input Glyph Count:%d"OTF_DUMP_NL, input_glyph_count );
    for( int i=0; i < input_glyph_count; i++ )
    {
        uint16_t offset = UTTF_BE16TOH(input_ptr->inputSequence[i]);
        OTF_DUMP_PRINTF( leading_spaces, "offset:%d"OTF_DUMP_NL, offset );
        otf_dump_OtfCoverageTable( (leading_spaces + 4), (Uttf_Otf_CoverageTable_t*)(((uint8_t*)table_ptr) + offset));
    }
    
    OTF_DUMP_PRINTF( leading_spaces, "Lookahead Glyph Count:%d"OTF_DUMP_NL, lookahead_glyph_count );
    for( int i=0; i < lookahead_glyph_count; i++ )
    {
        uint16_t offset = UTTF_BE16TOH(lookahead_ptr->lookaheadCoverageOffsets[i]);
        OTF_DUMP_PRINTF( leading_spaces, "offset:%d"OTF_DUMP_NL, offset );
        otf_dump_OtfCoverageTable( (leading_spaces + 4), (Uttf_Otf_CoverageTable_t*)(((uint8_t*)table_ptr) + offset));
    }
    
    OTF_DUMP_PRINTF( leading_spaces, "Pos Count:%d"OTF_DUMP_NL, pos_count );
    OTF_DUMP_PRINTF( leading_spaces, "SeqIdx,lookupIdx"OTF_DUMP_NL );
    for( int i=0; i < pos_count; i++ )
    {
         OTF_DUMP_PRINTF( leading_spaces, "%d,%d"OTF_DUMP_NL, UTTF_BE16TOH(pos_ptr->posLookupRecords[i].sequenceIndex), UTTF_BE16TOH(pos_ptr->posLookupRecords[i].lookupListIndex) );
    }
    printf( OTF_DUMP_NL);
}


/*****************************************************************************/
void
otf_dump_GposLookupTableType8( uint8_t                      leading_spaces,
                               Uttf_Gpos_ChainContextPos_t* table_ptr )
{
    uint16_t format = UTTF_BE16TOH(table_ptr->posformat);

    OTF_DUMP_PRINTF( leading_spaces, "-----"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "format:%d"OTF_DUMP_NL, format );
    
    switch( format )
    {
        case 1:
        {
            otf_dump_GposLookupTableType8Fmt1( (leading_spaces + 4), (Uttf_Gpos_ChainContextPosFmt1_t*)table_ptr );
        }
        break;
        case 2:
        break;
        case 3:
        {
            otf_dump_GposLookupTableType8Fmt3( (leading_spaces + 4), (Uttf_Gpos_ChainContextPosFmt3_t*)table_ptr );
        }
        break;
        default:
            break;
    }

}

/*****************************************************************************/
void
otf_dump_GposLookupTable( uint8_t                 leading_spaces,
                          Uttf_Otf_LookupTable_t* table_ptr )
{
    uint16_t type = UTTF_BE16TOH(table_ptr->lookupType);
    OTF_DUMP_PRINTF( leading_spaces, "----------------------"OTF_DUMP_NL );
    OTF_DUMP_PRINTF( leading_spaces, "lookupType:%d"OTF_DUMP_NL, type );  
    OTF_DUMP_PRINTF( leading_spaces, "lookupFlag:0x%04X"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->lookupFlag));  
    OTF_DUMP_PRINTF( leading_spaces, "subTableCount:%d"OTF_DUMP_NL, UTTF_BE16TOH(table_ptr->subTableCount));
    for( uint16_t i=0; i<UTTF_BE16TOH(table_ptr->subTableCount); i++ )
    {
        uint16_t offset = UTTF_BE16TOH(table_ptr->subtableOffsets[i]);
        OTF_DUMP_PRINTF( leading_spaces, "[%d]:%d"OTF_DUMP_NL, i, offset);
        switch( type )
        {
            case 1:
                otf_dump_GposLookupTableType1( (leading_spaces + 4), (Uttf_Gpos_SinglePos_t*)((uint8_t*)table_ptr + offset) );
                break;
            case 4:
                otf_dump_GposLookupTableType4( (leading_spaces + 4), (Uttf_Gpos_MarkBasePos_t*)((uint8_t*)table_ptr + offset) );
                break;
            case 5:
                otf_dump_GposLookupTableType5( (leading_spaces + 4), (Uttf_Gpos_MarkLigPos_t*)((uint8_t*)table_ptr + offset) );
                break;
            case 6:
                otf_dump_GposLookupTableType6( (leading_spaces + 4), (Uttf_Gpos_MarkMarkPos_t*)((uint8_t*)table_ptr + offset) );
                break;
            case 8:
                otf_dump_GposLookupTableType8( (leading_spaces + 4), (Uttf_Gpos_ChainContextPos_t*)((uint8_t*)table_ptr + offset) );
                break;
            default:
                break;
        }
    }
}


/*****************************************************************************/
void
otf_dump_GposLookupListTable( Uttf_Gpos_Info_t* info_ptr )
{
    if(info_ptr->gposPtr->v10.lookupListOffset != 0)
    {
        Uttf_Otf_LookupListTable_t* list_ptr = (Uttf_Otf_LookupListTable_t*)((uint8_t*)(info_ptr->gposPtr) + UTTF_BE16TOH(info_ptr->gposPtr->v10.lookupListOffset));
        OTF_DUMP_PRINTF( 0, "----------------------"OTF_DUMP_NL );
        OTF_DUMP_PRINTF( 0, "LookupList Length:%d"OTF_DUMP_NL, UTTF_BE16TOH(list_ptr->lookupCount));
        for( uint16_t i=0; i<UTTF_BE16TOH(list_ptr->lookupCount); i++ )
        {
            uint32_t offset = UTTF_BE16TOH(list_ptr->lookups[i]);
            OTF_DUMP_PRINTF( 0, "[%d]: %d"OTF_DUMP_NL, i, offset );
            otf_dump_GposLookupTable( 4, (Uttf_Otf_LookupTable_t*)((uint8_t*)list_ptr + offset) );
        }
    }    
}


/*****************************************************************************/
void
otf_dump_Gpos( Uttf_Gpos_Info_t* info_ptr )
{
    OTF_DUMP_PRINTF( 0, OTF_DUMP_SECTION_START("gpos") );
    if( info_ptr->gposPtr != NULL )
    {
        uint16_t majorVersion = UTTF_BE16TOH( info_ptr->gposPtr->ver.majorVersion );
        uint16_t minorVersion = UTTF_BE16TOH( info_ptr->gposPtr->ver.minorVersion );

        OTF_DUMP_PRINTF( 0, "majorVersion:            %d"OTF_DUMP_NL, majorVersion );
        OTF_DUMP_PRINTF( 0, "minorVersion:            %d"OTF_DUMP_NL, minorVersion );
        OTF_DUMP_PRINTF( 0, "scriptListOffset:        %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gposPtr->v10.scriptListOffset ) );
        OTF_DUMP_PRINTF( 0, "featureListOffset:       %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gposPtr->v10.featureListOffset ) );
        OTF_DUMP_PRINTF( 0, "lookupListOffset:        %d"OTF_DUMP_NL, UTTF_BE16TOH( info_ptr->gposPtr->v10.lookupListOffset ) );
        if( minorVersion >= 1 )
        {
            OTF_DUMP_PRINTF( 0, "featureVariationsOffset: %d"OTF_DUMP_NL, UTTF_BE32TOH( info_ptr->gposPtr->v11.featureVariationsOffset ) ); 
        }

        //otf_dump_GposScriptListTable(info_ptr);
        //otf_dump_GposFeatureListTable(info_ptr);
        otf_dump_GposLookupListTable(info_ptr);
    }
    else
    {
        OTF_DUMP_PRINTF( 0, "Not Present"OTF_DUMP_NL );
    }
}

