; Объявим start экспортированным глобальным символом
; Понадобится позже
global start

; "Код" должен находиться в секции .text
section .text
; Объявим метку start, понадобится позже
start:
; Используем инструкцию ud2 чтобы создать невалидную
; инструкцию и вызвать экстренное завершение программы
  ud2

