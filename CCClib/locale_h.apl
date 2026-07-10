#ifndef APL_LOCALE_H_
#define APL_LOCALE_H_ 0

#include "platform_h.apl"
#include "types_h.apl"

#ifdef CAPL_MACHO64
#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5
#define LC_MESSAGES 6
#endif
#ifndef CAPL_MACHO64
#define LC_CTYPE    0
#define LC_NUMERIC  1
#define LC_TIME     2
#define LC_COLLATE  3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_ALL      6
#endif

#ifdef CAPL_MACHO64
@[vname("_setlocale")] @[abi] extern function setlocale(i32 category, ptr i8 locale) -> ptr i8;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function setlocale(i32 category, ptr i8 locale) -> ptr i8;
#endif
#ifdef CAPL_MACHO64
@[vname("_localeconv")] @[abi] extern function localeconv() -> ptr c_lconv;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function localeconv() -> ptr c_lconv;
#endif

#endif
