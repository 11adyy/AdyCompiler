#ifndef APL_SYS_WAIT_H_
#define APL_SYS_WAIT_H_ 0

#include "sys_types_h.apl"

#define WNOHANG    1
#define WUNTRACED  2
#define WCONTINUED 8

extern function wait(ptr i32 status) -> i32;
extern function waitpid(i32 pid, ptr i32 status, i32 options) -> i32;

#endif
