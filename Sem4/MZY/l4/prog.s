%include "util.inc"

; Symmetrically swap elements on main diagonal:
; 1 2 3    9 2 3
; 4 5 6 => 4 5 6
; 7 8 9    7 8 1
; (Look at 1 and 9)

section .data

; Assuming that matrix_dim is less than 10
; (otherwise prompt would be broken)
matrix_dim equ 3
width equ matrix_dim
height equ matrix_dim

request_str: db 'Введите матрицу размером '
  db '0'+width, 'x', '0'+height
  db 10, 0

original_mat_str: db 'Исходная матрица:', 10, 0
output_mat_str: db 'Преобразованная матрица:', 10, 0

section .bss
; Buffer for Gets/AtoDW/Puts/DWtoA
buf: resb 100
buf_size equ $ - buf

; Main Matrix
matrix: resd (width * height)


section .data
; For "pretty" formatting
; "\t\0"
_tab: db 9, 0
; "\n\0"
_newline: db 10, 0

; 1 - matrix addr
; 2 - width
; 3 - height
%macro PrintMatrix 3
  %%elem_size equ 4 ; sizeof dword
  %%mat_end equ %1 + %2*%3*%%elem_size

; Load address of matrix into esi
; esi is address of current row
  lea esi, [%1]

; Print in two loops, like this:
; for (i = 0; i != h; ++i) {
;   for (j = 0; j != w; ++j) {
;     print("\t", a[i][j])
;   }
;   print("\n")
; }
%%.print.outer_loop:
; edi -- index of current element (in column)
  xor edi, edi
%%.print.inner_loop:
; print "\t"
  Puts _tab
; Print current element
  DWtoA dword[esi + edi*%%elem_size], buf, buf_size
  Puts buf
; increment index and if it's not equal to width,
; go to inner_loop
  inc edi
  cmp edi, %2
  jne %%.print.inner_loop

; print "\n"
  Puts _newline

; adjust esi so it stores address of next row
; and if it's not equal to end of matrix
; (last non-existent row), go to outer_loop
  add esi, %2*%%elem_size
  cmp esi, %%mat_end
  jne %%.print.outer_loop
%endmacro


; 1 - matrix addr
; 2 - width
; 3 - height
%macro ReadMatrix 3
; (matrix is read top-to-bottom, left-to-right)
; AtoDW sets edx to new string address on successful conversion
; Or to 0 on failure
; We only need to read new string when edx is 0
; Otherwise we should try to perform DWtoA on new value

; edi stores current string address
; esi stores current index

  %%elem_size equ 4 ; sizeof dword

  ; set esi to 0
  xor esi, esi
%%.read_loop.read_new_str:
  ; "reset" edi to buf and read string
  lea edi, [buf]
  Gets edi, buf_size

  ; keep converting until conversion fails
%%.read_loop:
  AtoDW edi

  ; edx==0 => conversion failed and new string should be read
  test edx, edx
  je %%.read_loop.read_new_str

  ; otherwise conversion succeeded, and:
  ;   - edi should be set to new string address
  ;   - converted value should be saved
  ;   - esi should be incremented
  mov edi, edx
  mov [%1 + esi*%%elem_size], eax
  inc esi

  ; if esi is equal to height*width, matrix is fully read
  cmp esi, %2*%3
  jne %%.read_loop
%endmacro

section .text
Start:
  ; Print expression to be calculated
  Puts request_str
  ReadMatrix matrix, width, height

  Puts original_mat_str
  PrintMatrix matrix, width, height

  lea ebx, [matrix + (width*height - 1)*4]
  lea esi, [matrix]

.swap_loop:
  mov eax, dword [esi]
  mov ecx, dword [ebx]

  mov dword [esi], ecx
  mov dword [ebx], eax

  add esi, (width+1)*4
  sub ebx, (width+1)*4

  cmp ebx, esi
  jg .swap_loop

  Puts output_mat_str
  PrintMatrix matrix, width, height

  ; Exit program
  Exit 0

