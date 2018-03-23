global start

section .data
F1 dw 65535
F2 dd 65535

section .text
start:
  add  word [F1], 1
  add dword [F2], 1

