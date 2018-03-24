; Exit: exit program
; args:
;   1 -- r32/imm32/m32 -- exit code
extern _exit
%macro Exit 1
  sub esp, 12
  push dword %1
  call _exit
%endmacro

; Gets: Read string from stdin into buffer (see fgets(3))
; args:
;   1 -- r32/imm32/m32 -- address of buffer
;   2 -- r32/imm32/m32 -- size of buffer
extern _GetStr
%macro Gets 2
  sub esp, 8
  push dword %2
  push dword %1
  call _GetStr
  add esp, 16
%endmacro

; Puts: Write (c-style) string from buffer to stdout
; args:
;   1 -- r32/imm32/m32 -- address of string to print
extern _PutStr
%macro Puts 1
  sub esp, 12
  push dword %1
  call _PutStr
  add esp, 16
%endmacro

; DWtoA: Convert 32bit signed value to (c-style) string (in base 10)
; args:
;   1 -- r32/imm32/m32 -- value
;   2 -- r32/imm32/m32 -- buffer (output string)
;   3 -- r32/imm32/m32 -- size of buffer
extern _IntToStr
%macro DWtoA 3
  sub esp, 4
  push dword %3
  push dword %2
  push dword %1
  call _IntToStr
  add esp, 16
%endmacro

; AtoDW: Convert (c-style) string to 32bit signed value (in base 10)
; args:
;   1 -- r32/imm32/m32 -- address of string
; ret:
;   eax -- converted value
;   edx -- new string ptr (NULL on conversion failure)
extern _StrToInt
%macro AtoDW 1
  sub esp, 24
  lea edx, [esp + 8]
  push dword edx
  push dword %1
  call _StrToInt
  mov edx, [esp + 16]
  add esp, 32
%endmacro

; MASM-style "Start" shim
global _main
section .text
_main:
  ; when main gets called stack is 4 byte aligned
  ; However, macOS IA-32 calling convention
  ; requires 16 byte aligned stack
  ; so we "fix" esp here
  sub esp, 12
  jmp Start

