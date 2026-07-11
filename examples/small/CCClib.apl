#include <io_h.apl>

start() {
    std::print(ref "I print ");
    std::print(10 as i32);
    std::putc('\n');
    exit 0;
}
