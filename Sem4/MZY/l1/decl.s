global start

section .data
; целое число 25 размером 2 байта
dat25     dw  25
; двойное слово, содержащее -35
datdblw   dd -35
; символьную строку, содержащую ваше имя
nameeng   db 'Soltan',0   ; на английском
namerus   db 'Солтан',0   ; на русском

section .text
start:
  ud2

