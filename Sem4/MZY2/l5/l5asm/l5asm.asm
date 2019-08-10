.686
.MODEL  flat, stdcall
OPTION CASEMAP:NONE

contains PROTO _str:PTR, strl:DWORD, _sub:PTR, subl:DWORD
test_tokenize PROTO _str:PTR, strl:DWORD, _sub:PTR, subl:DWORD

EXTERNDEF C MAX_WORD_CNT:DWORD

.CODE

tokenize PROC s:PTR, l:DWORD, words:PTR, words_size:DWORD
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
tokenize endp

lcsubstr PROC s:PTR, l:DWORD, lclenptr:PTR
LOCAL WordCnt:DWORD, ShortWordPtr:DWORD, ShortWordLen:DWORD
    ; preserve esi, edi, ebx
    push esi
    push edi
    push ebx

    ; zero lclen
    mov eax, lclenptr
    mov dword ptr [eax], 0

    ; Allocate space for word starts
    mov eax, MAX_WORD_CNT
    shl eax, 1
    sub esp, eax
    
    mov eax, esp
    Invoke tokenize, s, l, eax, MAX_WORD_CNT

    ; esi is ptr to word_tok array
    mov esi, esp
    
    ; extract WordCnt ( eax & 0xffff )
    movzx ebx, ax
    mov WordCnt, ebx

    ; ebx = min_idx ( = eax>>16 )
    mov ebx, eax
    shr ebx, 16
    
    mov ecx, esp
    Invoke test_tokenize, s, l, ecx, eax

    ; eax = words[min_idx].len
    xor eax, eax
    mov al, byte ptr [esi+ebx*2+1]
    ; save ShortWordLen = eax
    mov ShortWordLen, eax
    ; eax = words[min_idx].start
    mov al, [esi+ebx*2]
    ; eax += s
    add eax, s
    ; save ShortWordPtr = eax
    mov ShortWordPtr, eax

    ; for (int ws = short_word_len; ws != 0; --ws) {
    ;     int steps = short_word_len - ws + 1;
    ;     for (int step = steps - 1; step >= 0; --step) {
    ;         for (int i = 0; i != word_cnt; ++i) {
    ;             if (!contains(s+words[i].start, words[i].len, short_word+step, ws)) {
    ;                 goto zaloop;
    ;             }
    ;         }

    ;         return {short_word + step, ws};

    ;         zaloop:
    ;     }
    ; }
    
    ; ws%ebx = short_word_len
    mov ebx, ShortWordLen
wsloop:
    ; steps%esi = short_word_len - ws + 1
    mov esi, ShortWordLen
    sub esi, ebx
    inc esi
    
steploop:
    dec esi
    
    ; i%edi = 0
    xor edi, edi
wordloop:
    mov eax, ShortWordPtr
    add eax, esi
    
    xor edx, edx
    ; edx = words[i].start
    mov dl, [esp+edi*2]
    ; edx += s
    add edx, s
    
    ; ecx = words[i].len
    xor ecx, ecx
    mov cl, byte ptr [esp+edi*2+1]
    
    Invoke contains, edx, ecx, eax, ebx
    
    test eax, eax
    je byeword
    
    inc edi
    cmp edi, WordCnt
    jl wordloop
    
    jmp found

byeword:
    test esi, esi
    jne steploop

    dec ebx
    test ebx, ebx
    jne wsloop

    xor eax, eax
    jmp retu

found:
    mov eax, lclenptr
    mov [eax], ebx
    mov eax, ShortWordPtr
    add eax, esi

retu:
    pop ebx
    pop edi
    pop esi
    ret
lcsubstr endp

END