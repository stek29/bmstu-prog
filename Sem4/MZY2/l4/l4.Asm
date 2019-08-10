; Template for console application
.586
.MODEL  flat, stdcall
OPTION CASEMAP:NONE

Include kernel32.inc
Include masm32.inc

IncludeLib kernel32.lib
IncludeLib masm32.lib

.CONST
MsgExit  DB    "Press Enter to Exit",0AH,0DH,0

MatW equ 6
MatH equ 5
EnterMatrix db "Enter matrix (6x5)",10,13,0

EnterRowIndex db "Enter Row Index (first is 0): ", 0
InvalidRowIndex DB "Invalid Row Index (should be 0<=idx<mW)",10,13,0

RowBeforeSort db "Selected Row before sort",10,13,0
RowAfterSort db "Selected Row after sort",10,13,0

MatrixBeforeSort db "Matrix before sort",10,13,0
MatrixAfterSort db "Matrix after sort",10,13,0


TabSym DB 9, 0
NewLine DB 10, 13, 0

.DATA?
Buf    DB    100 DUP (?)

Matrix SDWORD MatW*MatH DUP(?)

PrintRow macro rowBase:REQ, rowW:REQ
  LOCAL print_inner_loop
; edi -- index of current element (in column)
   xor edi, edi
print_inner_loop:
; print "\t"

  Invoke StdOut, ADDR TabSym
; Print current element
  Invoke dwtoa, dword ptr [rowBase + edi*4], Addr Buf
  Invoke StdOut, ADDR Buf
; increment index and if it's not equal to width,
; go to inner_loop
  
  inc edi
  cmp edi, rowW
  jne print_inner_loop
  
; print "\n"
  Invoke StdOut, ADDR NewLine
endm

SortRow macro rowBase:REQ, rowW:REQ
  LOCAL outer_for
  LOCAL inner_for
  LOCAL skip_swap

  ; size of array
  mov ecx, rowW
  mov esi, rowBase
  
  ; for (j = n-1; j > 0; --j)
  dec     ecx
outer_for:
  ; for (i = 0; i != j-1; ++i)
  xor     ebx, ebx
inner_for:
  mov     eax, [ebx*4+esi]
  mov     edx, [ebx*4+esi+4]

  ; if a[i] > a[i+1]
  cmp     eax, edx
  jle     skip_swap
  ; swap && write back
  mov    [ebx*4+esi], edx
  mov    [ebx*4+esi+4], eax
skip_swap:
  inc     ebx
  
  cmp     ebx, ecx
  jb      inner_for
  loop    outer_for
endm

PrintMatrix macro mAddr:REQ, mW:REQ, mH:REQ
  LOCAL print_outer_loop 
; Load address of matrix into esi
; esi is address of current row
  lea esi, [mAddr]

; Print in two loops, like this:
; for (i = 0; i != h; ++i) {
;   for (j = 0; j != w; ++j) {
;     print("\t", a[i][j])
;   }
;   print("\n")
; }
print_outer_loop:
  PrintRow esi, mW

; adjust esi so it stores address of next row
; and if it's not equal to end of matrix
; (last non-existent row), go to outer_loop
  
  add esi, 4*mW
  
  lea edi, [mAddr]
  add edi, mW*mH*4
  
  cmp esi, edi
  jl print_outer_loop
endm

ReadMatrix macro mAddr:REQ, mW:REQ, mH:REQ
  LOCAL read_loop
; esi stores current index

  ; set esi to 0
  xor esi, esi
  lea edi, mAddr

read_loop:
  Invoke StdIn, ADDR Buf, LengthOf Buf
  Invoke StripLF, ADDR Buf
  Invoke atol, ADDR Buf
  
  mov dword ptr [edi + esi*4], eax
  inc esi

  ; if esi is equal to height*width, matrix is fully read
  cmp esi, mW*mH
  jne read_loop
endm
         .CODE

Start:
  mov esi, MatW*MatH

  Invoke StdOut, ADDR EnterMatrix
  ReadMatrix Matrix, MatW, MatH

  Invoke StdOut, ADDR MatrixBeforeSort
  PrintMatrix Matrix, MatW, MatH

  Invoke StdOut, ADDR EnterRowIndex
  Invoke StdIn, ADDR Buf, LengthOf Buf
  Invoke StripLF, ADDR Buf
  Invoke atol, ADDR Buf
  mov ebx, eax

  js invalid_row
  cmp ebx, MatW
  jge invalid_row

  mov ebx, MatW
  mul ebx

  lea ebx, [Matrix]
  lea esi, [ebx + eax*4]

  Invoke StdOut, ADDR RowBeforeSort
  PrintRow esi, MatW

  SortRow esi, MatW

  Invoke StdOut, ADDR RowAfterSort
  PrintRow esi, MatW

  Invoke StdOut, ADDR MatrixAfterSort
  PrintMatrix Matrix, MatW, MatH
  jmp exit

  invalid_row:
  Invoke StdOut, ADDR InvalidRowIndex

  exit:
  XOR    EAX,EAX
  Invoke StdOut,ADDR MsgExit
  Invoke StdIn,ADDR Buf,LengthOf Buf	

  Invoke ExitProcess,0
  End    Start

