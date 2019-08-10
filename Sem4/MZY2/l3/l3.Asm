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

ExprStr DB "Calc:", 10, 13
  db '    +--', 10, 13
  db '    | a * c^2 - b (if a > b)', 10, 13
  db 'x = +', 10
  db '    | a/c + a/b   (else)', 10, 13
  db '    +--', 10, 13
  db 10, 13, 0

ResultStr DB "m = ", 0
NewLine DB 0ah,0dh,0

FirstExprCond DB "a >  b, calc a * c^2 - b", 10, 13, 0
SecondExprCond DB "a <= b, calc a/c + a/b", 10, 13, 0
ZeroError DB "Error: b and c should not be 0",10,13,0


         .DATA
InputStr DB "Enter "
InputStrVarname DB "*"
DB ': ',0
  

         .DATA?
Buf    DB    100 DUP (?)

vA SDWORD ?
vB SDWORD ?
vC SDWORD ?

vM SDWORD ?


readVar MACRO vname:REQ, saveat:REQ
    mov byte ptr [InputStrVarname], vname
    Invoke StdOut, ADDR InputStr
    Invoke StdIn, ADDR Buf, LengthOf Buf
    Invoke StripLF, ADDR Buf
    Invoke atol, ADDR Buf
    mov saveat, eax
endm 

         .CODE
Start:
         Invoke StdOut, ADDR ExprStr
         readVar 'a', dword ptr [vA]
         readVar 'b', dword ptr [vB]
         readVar 'c', dword ptr [vC]

         ; cmp a, b
         mov eax, dword ptr [vA]
         cmp eax, dword ptr [vB]
         jle second_expr
         
   first_expr:
         Invoke StdOut, ADDR FirstExprCond
         
         ; edx:eax = a * c * c
         mov eax, dword ptr [vA]
         imul dword ptr [vC]
         imul dword ptr [vC]
         
         ; m = eax -= b
         sub eax, dword ptr [vB]
         
         mov dword ptr [vM], eax
     
         jmp output
 
   second_expr:
         Invoke StdOut, ADDR SecondExprCond
         
         mov eax, dword ptr [vB]
         test eax, eax
         je second_expr_zeroerr
         
         mov eax, dword ptr [vC]
         test eax, eax
         je second_expr_zeroerr
         
         ; m = eax = a/c
         mov eax, dword ptr [vA]
         cdq
         mov ebx, dword ptr [vC]
         idiv ebx
         mov dword ptr [vM], eax
         
         ; m += eax = a/b
         mov eax, dword ptr [vA]
         cdq
         mov ebx, dword ptr [vB]
         idiv ebx
         add dword ptr [vM], eax
         jmp output
         
   second_expr_zeroerr:
         Invoke StdOut, ADDR ZeroError
         jmp exit
   
   output:
         
         Invoke StdOut, ADDR ResultStr
         
         Invoke dwtoa, vM,ADDR Buf
         Invoke StdOut, ADDR Buf
         Invoke StdOut, ADDR NewLine

    exit:
         XOR    EAX, EAX
         Invoke StdOut,ADDR MsgExit
         Invoke StdIn,ADDR Buf,LengthOf Buf		
	
         Invoke ExitProcess,0
         End    Start

