#ifndef APL_POLL_H_
#define APL_POLL_H_ 0

#include "platform_h.apl"

#include "stddef_h.apl"

#define POLLIN   1
#define POLLPRI  2
#define POLLOUT  4
#define POLLERR  8
#define POLLHUP  16
#define POLLNVAL 32

@[like_c]
container c_pollfd {
    i32 fd;
    i16 events;
    i16 revents;
}

#ifdef CAPL_MACHO64
@[vname("_poll")] @[abi] extern function poll(ptr c_pollfd fds, u64 count, i32 timeout) -> i32;
#endif
#ifndef CAPL_MACHO64
@[abi] extern function poll(ptr c_pollfd fds, u64 count, i32 timeout) -> i32;
#endif

#endif
