#include "header_h.apl"

start() {
    if 1; exit 0;
    exit 1;
}

:/ OUTPUT
setpos, line=2, column=86, file={X}
{
setpos, line=1, column=10, file={X}apl
setpos, line=3, column=7, file={X}apl
    start {
        {
setpos, line=4, column=8, file={X}apl
            {
                if i8n 1, goto lb8, else goto lb10;
                lb8:
                {
                    exit i8n 0;
                }
                goto lb10;
                lb10:
setpos, line=5, column=10, file={X}apl
                exit i8n 1;
            }
        }
    }
}
/: