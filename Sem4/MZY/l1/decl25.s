global start

section .data
; 25 00 как WORD
w2500   dw    37
; 00 25 как WORD
w0025   dw    9472

; 25 00 как два BYTE
b2500   db    37, 0
; 00 25 как два BYTE
b0025   db    0, 37

; 25 00 00 25 как один DWORD
dboth   dd    620757029

section .text
start:
  ud2

