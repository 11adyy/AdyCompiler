#ifndef RAW_CORE_SYSCALL_INC_
#define RAW_CORE_SYSCALL_INC_ 0

#ifdef CAPL_MACHO64
    #define RAW_SYS_WRITE 0x2000004
#endif

#ifdef CAPL_GNU64
    #define RAW_SYS_WRITE 1
#endif

#ifdef CAPL_GNUI386
    #define RAW_SYS_WRITE 4
#endif

#endif
