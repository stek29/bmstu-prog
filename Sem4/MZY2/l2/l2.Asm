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

ExprStr DB "Calculate m = a*c^2 - b * a/c + a/b",0ah, 0dh,0
ResultStr DB "m = ", 0
NewLine DB 0ah,0dh,0

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
         
         ; m = edx:eax = a * c * c
         mov eax, dword ptr [vA]
         imul dword ptr [vC]
         imul dword ptr [vC]
         mov dword ptr [vM], eax

         ; m -= eax = b * a / (ebx=c)
         mov eax, dword ptr [vB]
         imul dword ptr [vA]
         ; no need for cdq, imul extends to edx
         mov ebx, dword ptr [vC]
         idiv ebx
         sub dword ptr [vM], eax

         ; m += eax = a/b
         mov eax, dword ptr [vA]
         cdq
         mov ebx, dword ptr [vB]
         idiv ebx
         add dword ptr [vM], eax

         Invoke StdOut, ADDR ResultStr
         
         Invoke dwtoa, vM,ADDR Buf
         Invoke StdOut, ADDR Buf
         Invoke StdOut, ADDR NewLine

         XOR    EAX,EAX
         Invoke StdOut,ADDR MsgExit
         Invoke StdIn, ADDR Buf, LengthOf Buf		
         Invoke ExitProcess,0
         End    Start

