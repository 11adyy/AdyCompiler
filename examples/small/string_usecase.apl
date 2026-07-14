#include "io_h.apl"

start() {
    ptr string msg = string::new(ref "Hello world!\n");
    std::print(msg);
    msg.print();
    msg.destroy();
    exit 0;
}