#include "io_h.apl"

start() {
    ptr string msg = string::new(ref "Hello world!");
    std::print(msg);
    msg.destroy();
    exit 0;
}