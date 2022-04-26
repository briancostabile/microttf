/*****************************************************************************/
/**
 * 
 */
#include <stddef.h>
#include <stdint.h>

#include "uttf.h"


uint16_t
uttf_be16toh( uint64_t big_endian_16bits )
{
    uint16_t ret = 0;

    ret |= ((big_endian_16bits >> 8) & 0x00FF);
    ret |= ((big_endian_16bits << 8) & 0xFF00);
    
    return( ret );
}

uint32_t
uttf_be32toh( uint64_t big_endian_32bits )
{
    uint32_t ret = 0;

    ret |= ((big_endian_32bits >> 24) & 0x000000FF);
    ret |= ((big_endian_32bits >>  8) & 0x0000FF00);
    ret |= ((big_endian_32bits <<  8) & 0x00FF0000);
    ret |= ((big_endian_32bits << 24) & 0xFF000000);
    
    return( ret );
}

uint64_t
uttf_be64toh( uint64_t big_endian_64bits )
{
    uint64_t ret = 0;

    ret |= ((big_endian_64bits >> 56) & 0x00000000000000FF);
    ret |= ((big_endian_64bits >> 40) & 0x000000000000FF00);
    ret |= ((big_endian_64bits >> 24) & 0x0000000000FF0000);
    ret |= ((big_endian_64bits >>  8) & 0x00000000FF000000);
    ret |= ((big_endian_64bits <<  8) & 0x000000FF00000000);
    ret |= ((big_endian_64bits << 24) & 0x0000FF0000000000);
    ret |= ((big_endian_64bits << 40) & 0x00FF000000000000);
    ret |= ((big_endian_64bits << 56) & 0xFF00000000000000);

    return( ret );
}
