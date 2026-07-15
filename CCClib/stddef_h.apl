#ifndef APL_STDDEF_H_
#define APL_STDDEF_H_ 0

#include "platform_h.apl"
#include "types_h.apl"

#ifdef CAPL_GNUI386
    #define size_t    u32
    #define ssize_t   i32
    #define ptrdiff_t i32
    #define wchar_t   i32
#endif
#ifndef CAPL_GNUI386
#ifdef CAPL_WINDOWS64
    #define size_t    u64
    #define ssize_t   i64
    #define ptrdiff_t i64
    #define wchar_t   u16
#endif
#ifndef CAPL_WINDOWS64
    #define size_t    u64
    #define ssize_t   i64
    #define ptrdiff_t i64
    #define wchar_t   i32
#endif

#endif
