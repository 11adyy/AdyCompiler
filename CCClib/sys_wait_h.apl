#ifndef APL_SYS_WAIT_H_
#define APL_SYS_WAIT_H_ 0

#include "platform_h.apl"
#include "sys_types_h.apl"

#define WNOHANG         1
#define WUNTRACED       2
#ifdef CAPL_MACHO64
    #define WCONTINUED  16
#endif
#ifndef CAPL_MACHO64
    #define WCONTINUED  8
#endif

:/ Waits for any child process to change state.
- `status`:[ptr i32] - Optional output pointer receiving encoded child status information.

Returns the changed child process identifier on success, otherwise -1:[i32]
/:
#ifdef CAPL_MACHO64
@[vname("_wait")] @[abi] extern function wait(ptr i32 status) -> i32;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function wait(ptr i32 status) -> i32;
#endif

:/ Waits for a selected child process to change state.
- `pid`:[i32] - Child-process selector.
- `status`:[ptr i32] - Optional output pointer receiving encoded child status information.
- `options`:[i32] - Bit mask controlling wait behavior.

Returns the selected child process identifier, zero for a non-blocking no-change result, or -1 on failure:[i32]
/:
#ifdef CAPL_MACHO64
@[vname("_waitpid")] @[abi] extern function waitpid(i32 pid, ptr i32 status, i32 options) -> i32;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function waitpid(i32 pid, ptr i32 status, i32 options) -> i32;
#endif

#endif
