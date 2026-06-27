#ifndef APL_STDIO_H_
#define APL_STDIO_H_ 0

#include "stddef_h.apl"
#include "types_h.apl"

#define EOF          -1
#define SEEK_SET     0
#define SEEK_CUR     1
#define SEEK_END     2
#define BUFSIZ       8192
#define FILENAME_MAX 4096
#define FOPEN_MAX    16
#define TMP_MAX      238328
#define L_tmpnam     20

extern function remove(ptr i8 path) -> i32;
extern function rename(ptr i8 old_path, ptr i8 new_path) -> i32;
extern function tmpfile() -> ptr apl_file;
extern function tmpnam(ptr i8 s) -> ptr i8;

extern function fclose(ptr apl_file stream) -> i32;
extern function fflush(ptr apl_file stream) -> i32;
extern function fopen(ptr i8 path, ptr i8 mode) -> ptr i8;
extern function freopen(ptr i8 path, ptr i8 mode, ptr apl_file stream) -> ptr i8;
extern function setbuf(ptr apl_file stream, ptr i8 buf) -> i0;
extern function setvbuf(ptr apl_file stream, ptr i8 buf, i32 mode, u64 size) -> i32;

@[abi] extern function fprintf(ptr apl_file stream, ptr i8 fmt, ...) -> i32;
@[abi] extern function fscanf(ptr apl_file stream, ptr i8 fmt, ...) -> i32;
@[abi] extern function printf(ptr i8 fmt, ...) -> i32;
@[abi] extern function scanf(ptr i8 fmt, ...) -> i32;
@[abi] extern function snprintf(ptr i8 s, u64 n, ptr i8 fmt, ...) -> i32;
@[abi] extern function sprintf(ptr i8 s, ptr i8 fmt, ...) -> i32;
@[abi] extern function sscanf(ptr i8 s, ptr i8 fmt, ...) -> i32;

extern function fgetc(ptr apl_file stream) -> i32;
extern function fgets(ptr i8 s, i32 n, ptr apl_file stream) -> ptr i8;
extern function fputc(i32 c, ptr apl_file stream) -> i32;
extern function fputs(ptr i8 s, ptr apl_file stream) -> i32;
extern function getc(ptr apl_file stream) -> i32;
extern function getchar() -> i32;
extern function gets(ptr i8 s) -> ptr i8;
extern function putc(i32 c, ptr apl_file stream) -> i32;
extern function putchar(i32 c) -> i32;
extern function puts(ptr i8 s) -> i32;
extern function ungetc(i32 c, ptr apl_file stream) -> i32;

extern function fread(ptr i0 pointer, u64 size, u64 count, ptr apl_file stream) -> u64;
extern function fwrite(ptr i0 pointer, u64 size, u64 count, ptr apl_file stream) -> u64;
extern function fgetpos(ptr apl_file stream, ptr i0 pos) -> i32;
extern function fseek(ptr apl_file stream, i64 offset, i32 whence) -> i32;
extern function fsetpos(ptr apl_file stream, ptr i0 pos) -> i32;
extern function ftell(ptr apl_file stream) -> i64;
extern function rewind(ptr apl_file stream) -> i0;

extern function clearerr(ptr apl_file stream) -> i0;
extern function feof(ptr apl_file stream) -> i32;
extern function ferror(ptr apl_file stream) -> i32;
extern function perror(ptr i8 s) -> i0;

#endif
