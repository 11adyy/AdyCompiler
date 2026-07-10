#ifndef APL_SYS_WAIT_H_
#define APL_SYS_WAIT_H_ 0

#include "platform_h.apl"
#include "sys_types_h.apl"

#define WNOHANG    1
#define WUNTRACED  2
#ifdef CAPL_MACHO64
#define WCONTINUED 16
#endif
#ifndef CAPL_MACHO64
#define WCONTINUED 8
#endif

#ifdef CAPL_MACHO64
@[vname("_wait")] @[abi] extern function wait(ptr i32 status) -> i32;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function wait(ptr i32 status) -> i32;
#endif
#ifdef CAPL_MACHO64
@[vname("_waitpid")] @[abi] extern function waitpid(i32 pid, ptr i32 status, i32 options) -> i32;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function waitpid(i32 pid, ptr i32 status, i32 options) -> i32;
#endif

#endif
