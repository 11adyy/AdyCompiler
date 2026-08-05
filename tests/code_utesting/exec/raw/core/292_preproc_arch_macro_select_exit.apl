: BLOCK_TEST :
: RUN_ASM :

#define ARCH_VALUE 0

#ifdef CAPL_MACHO64
    #undef ARCH_VALUE
    #define ARCH_VALUE 42
#endif

#ifdef CAPL_GNU64
    #undef ARCH_VALUE
    #define ARCH_VALUE 42
#endif

#ifdef CAPL_GNUI386
    #undef ARCH_VALUE
    #define ARCH_VALUE 42
#endif

start() {
    exit ARCH_VALUE;
}

:/ OUTPUT
@exit_code=42
/:
