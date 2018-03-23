%include "util.inc"

section .data
expr_str: db 'Calc x = a * y * (b - a)/4 + a^2 - 2', 10, 0

section .bss
buf: resb 100
buf_size equ $ - buf

a: resd 1
b: resd 1
x: resd 1
y: resd 1


section .data
inputstr: db 'Enter '
inputstr_varname: db '*'
  db ': ', 0

%macro ReadVar 2
  mov byte [inputstr_varname], %1
  Puts inputstr
  Gets buf, buf_size
  AtoDW buf
  mov %2, eax
%endmacro

section .text
Start:
  ; Print expression to be calculated
  Puts expr_str

  ; Read input variables
  ReadVar 'a', dword [a]
  ReadVar 'b', dword [b]
  ReadVar 'y', dword [y]

  ; Put last part of expression
  ; x = -2
  mov dword [x], -2

  ; Add a^2
  ; x += a*a
  mov eax, dword [a]
  imul eax
  add dword [x], eax

  ; Find b - a
  ; eax = b - a
  mov eax, dword [b]
  sub eax, dword [a]

  ; Divide (b - a) by 4
  ; eax = eax / 4
  cdq
  mov ebx, 4
  idiv ebx

  ; Multiply by a and y
  ; eax *= a; eax *= y
  imul dword [a]
  imul dword [y]

  ; Add last component to x
  ; x += eax
  add dword [x], eax

  ; Convert x to string and print it
  DWtoA [x], buf, buf_size
  Puts buf

  ; Exit program
  Exit 0

