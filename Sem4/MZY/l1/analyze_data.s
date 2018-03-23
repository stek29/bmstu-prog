global start

section .data
val1    db     255
chart   dw     256
ue3     dw    -128
alu     resb    1
v5      db     10h
        db     100101B
beta    db     23,23h,0ch
sdk     db     'Hello',0
min     dw    -32767
ar      dd     12345678h
valar   db     1, 2, 8
        times 5-$+valar resb 1

section .text
start:
  ud2

