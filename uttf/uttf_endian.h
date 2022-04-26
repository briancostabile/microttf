/*****************************************************************************/
/**
 * 
 */
#ifndef UTTF_ENDIAN_H
#define UTTF_ENDIAN_H

#include <stdint.h>

#define UTTF_HCHARTOBE32( _h32 ) ((((_h32) & 0xFF000000) >> 24) | \
                                  (((_h32) & 0x00FF0000) >>  8) | \
                                  (((_h32) & 0x0000FF00) <<  8) | \
                                  (((_h32) & 0x000000FF) << 24))

#define UTTF_BE64TOH( _be64 ) uttf_be64toh( (_be64) )
#define UTTF_BE32TOH( _be32 ) uttf_be32toh( (_be32) )
#define UTTF_BE16TOH( _be16 ) uttf_be16toh( (_be16) )
#define UTTF_H64TOBE( _h64 )  uttf_be64toh( (_h64) )
#define UTTF_H32TOBE( _h32 )  uttf_be32toh( (_h32) )
#define UTTF_H16TOBE( _h16 )  uttf_be16toh( (_h16) )

uint16_t uttf_be16toh( uint64_t big_endian_16bits );
uint32_t uttf_be32toh( uint64_t big_endian_32bits );
uint64_t uttf_be64toh( uint64_t big_endian_64bits );

#endif
