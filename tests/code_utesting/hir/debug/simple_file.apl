#include "header_h.apl"

start() {
    if 1; exit 0;
    exit 1;
}

:/ OUTPUT
setpos, line=2, column=86, file=<unknown>
{
setpos, line=1, column=10, file=code_utesting/hir/debug/header_h.apl
setpos, line=3, column=7, file=/private/var/folders/74/d7gcqwxd1x9__83fh6m_lb6c0000gn/T/tmplboqcskl.apl
    fn _main()
    {
setpos, line=4, column=8, file=/private/var/folders/74/d7gcqwxd1x9__83fh6m_lb6c0000gn/T/tmplboqcskl.apl
        {
            if i8n 1, goto lb8, else goto lb10;
            lb8:
            {
                u8t %0 = i8n 0 as u8;
                exit u8t %0;
            }
            goto lb10;
            lb10:
setpos, line=5, column=10, file=/private/var/folders/74/d7gcqwxd1x9__83fh6m_lb6c0000gn/T/tmplboqcskl.apl
            u8t %1 = i8n 1 as u8;
            exit u8t %1;
        }
    }
}
/: