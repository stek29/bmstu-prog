global start

; Инициализированная память находятся в
; секции __data
section .data
; dd - dword
A dd -30
B dd 21

; Неиницализированная - в bss
; res : reserve - выделить память
; d   : dword
; 1   : количество
section .bss
X resd 1

section .text
start:
  ; dword [A] - адрес A как double word
  mov eax, dword [A]
  add eax, 5
  sub eax, dword [B]
  mov dword [X], eax

