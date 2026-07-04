#ifndef APL_INTTYPES_H_
#define APL_INTTYPES_H_ 0

#include "platform_h.apl"

#include "stdint_h.apl"

#define intmax_t  i64
#define uintmax_t u64

#ifdef CAPL_MACHO64
@[vname("_imaxabs")] extern function imaxabs(i64 value) -> i64;
#endif
#ifndef CAPL_MACHO64
extern function imaxabs(i64 value) -> i64;
#endif
#ifdef CAPL_MACHO64
@[vname("_strtoimax")] extern function strtoimax(ptr i8 s, ptr ptr i8 endptr, i32 base) -> i64;
#endif
#ifndef CAPL_MACHO64
extern function strtoimax(ptr i8 s, ptr ptr i8 endptr, i32 base) -> i64;
#endif
#ifdef CAPL_MACHO64
@[vname("_strtoumax")] extern function strtoumax(ptr i8 s, ptr ptr i8 endptr, i32 base) -> u64;
#endif
#ifndef CAPL_MACHO64
extern function strtoumax(ptr i8 s, ptr ptr i8 endptr, i32 base) -> u64;
#endif

#endif
