{
    from "test.apl" import foo;
    from "test_1.apl" import bar;
    
    start(i64 argc, ptr u64 argv) {
        exit bar();
    }
}

: Expected
{
    from "test_1.apl" import bar;
    
    start(i64 argc, ptr u64 argv) {
        exit 0;
    }
}
: