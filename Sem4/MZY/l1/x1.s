extern _exit
extern _read
extern _write

global _main

section .data

section .bss
inbuf resb 100
buflen equ $ - inbuf

section .text
_main:
  ; make sure stack is aligned
  push ebp
  mov ebp, esp
  add esp, 16
  and esp, 0xfffffff0

  sub esp, 4        ; align
  push dword buflen ; arg3: nbyte   : size of inbuf
  push inbuf        ; arg2: buf     : inbuf
  push dword 0      ; arg1: flides  : stdin
  call _read
  add esp, 16

  sub esp, 4        ; align
  push eax          ; arg3: nbyte   : retval of read
  push inbuf        ; arg2: buf     : inbuf
  push dword 1      ; arg1: flides  : stdout
  call _write
  add esp, 16

;  ; align for call
;  sub esp, 12
;  ; exit code
;  push dword 0
;  call _exit

  mov eax, 0        ; return value

  mov esp, ebp
  pop ebp
  ret
