
#include "uttf.h"

#define OTF_DUMP_NL "\r\n"
#define OTF_DUMP_SECTION_START( _name )  "****************************************************"OTF_DUMP_NL"<"_name">"OTF_DUMP_NL
#define OTF_DUMP_TABLE_SEPARATOR "------------------" 
#define OTF_DUMP_CMAP_TABLE_SEPARATOR(_entry) "--cmap:%d------------"OTF_DUMP_NL, _entry
#define OTF_DUMP_CMAP_TABLE_START(_platform, _encoding) "-------------- p:%d e:%d -------------"OTF_DUMP_NL, _platform, _encoding

#define OTF_DUMP_PRINTF( _spaces, ... ) { otf_dump_leading_spaces((_spaces)); printf( __VA_ARGS__ ); }

void
otf_dump_leading_spaces( uint8_t count );

void
otf_dump_Os2( Uttf_Os2_t* table_ptr );

void
otf_dump_Maxp( Uttf_Maxp_t* table_ptr );

void
otf_dump_Cmap( Uttf_Cmap_Info_t* info_ptr );

void
otf_dump_Head( Uttf_Head_t* table_ptr );

void
otf_dump_Loca( Uttf_Loca_Info_t* info_ptr,
               uint32_t          num_glyphs,
               int16_t           format );

void
otf_dump_Hhea( Uttf_Hhea_Info_t* info_ptr );

void
otf_dump_Hmtx( Uttf_Hmtx_Info_t* info_ptr );

void
otf_dump_Post( Uttf_Post_Info_t* info_ptr );

void
otf_dump_Name( Uttf_Name_Info_t* info_ptr );

void
otf_dump_Glyf( Uttf_Glyf_Info_t* info_ptr,
               Uttf_Loca_Info_t* loca_info_ptr,
               uint16_t          numGlyphs );
void
otf_dump_Gdef( Uttf_Gdef_Info_t* info_ptr );

void
otf_dump_Gpos( Uttf_Gpos_Info_t* info_ptr );

void
otf_dump_OtfCoverageTable( uint8_t                   leading_spaces,
                           Uttf_Otf_CoverageTable_t* table_ptr );

void
otf_dump_OtfClassDefinition( uint8_t                   leading_spaces,
                             Uttf_Otf_ClassDefTable_t* table_ptr );
