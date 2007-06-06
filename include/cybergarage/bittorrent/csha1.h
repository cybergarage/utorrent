/*
 *  sha1.h
 *
 *  Description:
 *      This is the header file for code which implements the Secure
 *      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *      April 17, 1995.
 *
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
 *
 *      Please read the file sha1.c for more information.
 *
 */

#ifndef _SHA1_H_
#define _SHA1_H_

#ifdef  __cplusplus
extern "C" {
#endif

#if !defined(WIN32)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef short int int_least16_t;
typedef unsigned char uint8_t;
#endif

/*
 * If you do not have the ISO standard stdint.h header file, then you
 * must typdef the following:
 *    name              meaning
 *  uint32_t         unsigned 32 bit integer
 *  uint8_t          unsigned 8 bit integer (i.e., unsigned char)

 *  int_least16_t    integer of >= 16 bits
 *
 */

#ifndef _CgSHAEnum_
#define _CgSHAEnum_
enum
{
    shaSuccess = 0,
    shaNull,            /* Null pointer parameter */
    shaInputTooLong,    /* input data too long */
    shaStateError       /* called Input after Result */
};
#endif
#define CG_SHA1_HASH_SIZE 20

/*
 *  This structure will hold context information for the SHA-1
 *  hashing operation
 */
typedef struct _CgSHA1Context
{
    uint32_t Intermediate_Hash[CG_SHA1_HASH_SIZE/4]; /* Message Digest  */

    uint32_t Length_Low;            /* Message length in bits      */
    uint32_t Length_High;           /* Message length in bits      */

                               /* Index into message block array   */
    int_least16_t Message_Block_Index;
    uint8_t Message_Block[64];      /* 512-bit message blocks      */

    int Computed;               /* Is the digest computed?         */
    int Corrupted;             /* Is the message digest corrupted? */
} CgSHA1Context;

/*
 *  Function Prototypes
 */

int cg_sha1_reset(  CgSHA1Context *);
int cg_sha1_input(  CgSHA1Context *,
                const uint8_t *,
                unsigned int);
int cg_sha1_result( CgSHA1Context *,
                uint8_t Message_Digest[CG_SHA1_HASH_SIZE]);

#ifdef  __cplusplus
}
#endif

#endif

