.586
.MODEL  flat, stdcall
OPTION CASEMAP:NONE

Include kernel32.inc
Include masm32.inc

IncludeLib kernel32.lib
IncludeLib masm32.lib

.CONST
MsgExit  DB    "Press Enter to Exit"
NewLine  DB    0AH,0DH,0

.DATA

.DATA?
MaxLen     equ 256
MaxWordCnt equ 16

InBuf    DB    MaxLen DUP (?)
OutBuf   DB    MaxLen DUP (?)

.CODE

tokenize PROC s:DWORD, l:DWORD, words:DWORD, words_size:DWORD
    ; preserve ebx and esi
    push ebx
    push esi
    push edi

    ; cx is index of current char in str
    xor ecx, ecx
    ; edx is index of current word start
    xor edx, edx
    ; esi is ptr to word_tok array
    mov esi, words
    ; bl is flag: 1 if in word, 0 if not
    xor bl, bl
    ; edi is index of shortest word so far
    xor edi, edi
str_loop:
    ; load current char
    mov eax, s
    mov al, [eax + ecx]

    ; check the flag
    test bl, bl
    jz not_in_word

    ; we're in word, check if we've reached space
    cmp al, ' '
    jne inw_not_space

    ; calculate word len
    mov eax, ecx
    mov bl, byte ptr [esi+edx*2]
    sub al, bl
    ; and save it
    mov byte ptr [esi+edx*2+1], al

    ; load shortst word so far
    mov bl, [esi+edi*2+1]
    ; if current word is shorter, change edi
    cmp bl, al
    jle inw_skip_edi_assign
    mov edi, edx
inw_skip_edi_assign:
    ; we're not in word anymore
    xor bl, bl

    ; increment word count
    inc edx

    ; not enough space for words?
    cmp edx, words_size
    jge out_not_in_word
inw_not_space:
    jmp loopend
not_in_word:
    cmp al, ' '
    je loopend

    ; we're in word now
    mov bl, 1
    ; save word start
    mov byte ptr [esi+edx*2], cl
loopend:
    inc ecx
    cmp ecx, l
    jl str_loop

    test bl, bl
    jz out_not_in_word

    ; calculate word len
    mov eax, ecx
    mov bl, byte ptr [esi+edx*2]
    sub al, bl
    ; and save it
    mov byte ptr [esi+edx*2+1], al

    ; load shortst word so far
    mov bl, [esi+edi*2+1]
    ; if current word is shorter, change edi
    cmp bl, al
    jle out_skip_edi_assign
    mov edi, edx
out_skip_edi_assign:
    inc edx

out_not_in_word:

    ; return shortest word index
    mov eax, edi
    shl eax, 16
    ; and the word count
    or ax, dx

    pop edi
    pop esi
    pop ebx
    ret
tokenize ENDP

detokenize PROC sin:DWORD, sout:DWORD, words:DWORD, words_len:DWORD
    push edi
    push esi
    push ebx

    xor ebx, ebx
    mov edi, sout
wcl:
    mov ecx, words
    ; eax = s
    mov eax, sin
    ; eax += words[i].start
    add al, byte ptr [ecx+ebx*2]

    ; esi = eax (s + words[i].start)
    mov esi, eax
    
    ; eax = words[i].len
    xor eax, eax
    mov al, byte ptr [ecx+ebx*2+1]
    ; ecx = eax (words[i].len)
    mov ecx, eax

    rep movsb

    mov byte ptr [edi], ' '
    inc edi

    inc ebx
    cmp ebx, words_len
    jl wcl

    mov byte ptr [edi], 0
    
    pop ebx
    pop esi
    pop edi

    ret
detokenize ENDP

strlen PROC s:PTR
    push edi

    mov edi, s
	xor ecx, ecx
	xor al, al
	not ecx
	cld
    repne scasb
	not ecx
	dec ecx
    mov eax, ecx

    pop edi
    ret
strlen ENDP

sortarr PROC Arr:DWORD, Cnt:DWORD, Context:DWORD, CmpF:DWORD
    push esi
    push edi
    push ebx

    ; size of array
    mov     esi, Cnt

    ; for (j = n-1; j > 0; --j)
    dec     esi
outer_for:
    ; for (i = 0; i != j-1; ++i)
    xor     ebx, ebx
inner_for:
    mov     ecx, Arr
    xor     eax, eax
    mov     ax, word ptr [ebx*2+ecx]
    mov     edi, eax
    mov     ax, word ptr [ebx*2+ecx+2]

    ; if a[i] > a[i+1]
    push eax

    push eax
    push edi
    push Context
    call CmpF

    pop ecx
    cmp eax, 0
    jle     skip_swap
    ; swap && write back
    mov     eax, ecx
    mov     ecx, Arr
    mov     word ptr [ebx*2+ecx], ax
    mov     eax, edi
    mov     word ptr [ebx*2+ecx+2], ax
skip_swap:
    inc     ebx

    cmp     ebx, esi
    jb      inner_for
    dec     esi
    test    esi, esi
    jne     outer_for

    pop ebx
    pop edi
    pop esi

    ret
sortarr endp

WordCmp PROC StrP:DWORD, WordInfL:DWORD, WordInfR:DWORD
    push esi
    push edi

    mov esi, StrP
    mov edi, esi

    mov eax, WordInfL
    and eax, 0ffh
    add edi, eax
    
    mov eax, WordInfR
    and eax, 0ffh
    add esi, eax

    mov ecx, WordInfL
    shr ecx, 8

    mov eax, WordInfR
    shr eax, 8

    cmp ecx, eax
    jle cmpcycl

    mov ecx, eax

cmpcycl:
    repe cmpsb
    jl lgreater
    jg rgreater

    mov ecx, WordInfL
    shr ecx, 8
    cmp ecx, eax
    je lrequal
    ; jg lgreater
    jl rgreater


lgreater:
    mov eax, 1
    jmp exitf

rgreater:
lrequal:
    mov eax, 0

exitf:
    pop edi
    pop esi
    ret
WordCmp ENDP

main PROC
LOCAL SL:DWORD, WC:DWORD
    Invoke StdIn, ADDR InBuf, LengthOf InBuf
    Invoke StripLF, ADDR InBuf

    Invoke strlen, ADDR InBuf
    mov SL, eax

    mov eax, MaxWordCnt
    shl eax, 1
    sub esp, eax

    mov eax, esp
    mov ecx, MaxWordCnt
    Invoke tokenize, ADDR InBuf, SL, eax, ecx

    ; esi is ptr to word_tok array
    mov esi, esp
    
    ; extract WordCnt ( eax & 0xffff )
    movzx ebx, ax
    mov WC, ebx

    mov ecx, WordCmp
    Invoke sortarr, esi, WC, ADDR InBuf, ecx

    Invoke StdOut, ADDR InBuf
    Invoke StdOut, ADDR NewLine

    mov eax, esp
    Invoke detokenize, ADDR InBuf, ADDR OutBuf, eax, WC

    Invoke StdOut, ADDR OutBuf
    Invoke StdOut, ADDR NewLine

    ret
main ENDP

Start:
    Invoke main
    Invoke StdOut, ADDR MsgExit
    Invoke StdIn, ADDR InBuf, LengthOf InBuf		

    Invoke ExitProcess, 0

END Start