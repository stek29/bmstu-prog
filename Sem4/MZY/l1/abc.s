global start

section .data
A db   13
B db   37
section .bss
C resb 1

section .text
start:
  mov al, byte [A]
  add al, byte [B]
  mov byte [C], al

