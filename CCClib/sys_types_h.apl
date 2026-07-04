#ifndef APL_SYS_TYPES_H_
#define APL_SYS_TYPES_H_ 0

#include "platform_h.apl"
#include "stddef_h.apl"

#define clock_t   i64

#ifdef CAPL_MACHO64
#define dev_t     i32
#define gid_t     u32
#define ino_t     u64
#define mode_t    u16
#define nlink_t   u16
#define off_t     i64
#define pid_t     i32
#define time_t    i64
#define uid_t     u32
#endif
#ifndef CAPL_MACHO64
#ifdef CAPL_GNUI386
#define dev_t     u64
#define gid_t     u32
#define ino_t     u32
#define mode_t    u32
#define nlink_t   u32
#define off_t     i32
#define pid_t     i32
#define time_t    i32
#define uid_t     u32
#endif
#ifndef CAPL_GNUI386
#define dev_t     u64
#define gid_t     u32
#define ino_t     u64
#define mode_t    u32
#define nlink_t   u64
#define off_t     i64
#define pid_t     i32
#define time_t    i64
#define uid_t     u32
#endif
#endif

#endif
