; void process_words(char* str)
global _process_words

; void print_word_pair(char* w1, int w1len, char* w2, int w2len)
extern _print_words

%ifdef DEBUG
; void debug_wordscan(char* str, int word_count,
;   char** word_starts, int* word_lens)
extern _debug_wordscan
%endif

section .bss
max_strlen equ 256

word_count: resd 1
word_starts: resb max_strlen / 2
word_lens: resb max_strlen / 2

string_start: resd 1

section .text
_process_words:
  ; get string ptr
  mov esi, [esp + 4]
  mov [string_start], esi

  ; push callee-saved registers:
  ; ebx, ebp, esi, edi
  ; 4 regs are pushed, so stack alignment is fine
  push ebx
  push ebp
  push esi
  push edi

  ; - fill word_starts, word_lens, word_count
  ; edi: current word_start
  ; eax: current word_length
  ; ecx: current word_count

  ; zero ecx and eax
  xor ecx, ecx
  xor eax, eax

  ; set edi to string start
  mov edi, esi

  ; since find_non_space loop starts with inc, we have to dec first
  dec edi

.word_scan.find_non_space:
  inc edi
  mov bl, byte [edi]

  ; stop scan on \0
  test bl, bl
  je .word_scan.done

  ; proceed to next step only if [edi] != ' '
  cmp bl, ' '
  je .word_scan.find_non_space

  ; save edi to word_starts[ecx]
  mov [word_starts + ecx*4], edi


  ; now find word end
  ; first, set eax to edi (= word start)
  ; then find first ' ' or \0 and set it's addr to eax
  ; then eax -= edi, and eax would have word length in it
  mov eax, edi

  ; no need to dec and it's ok that loop starts with inc
  ; since first character is already checked (word can't have len 0)
.word_scan.find_space:
  inc eax
  mov bl, byte [eax]

  ; word ends if current char is 0 ...
  test bl, bl
  je .word_scan.find_space.done

  ; or if current char is ' '
  cmp bl, ' '
  jne .word_scan.find_space
.word_scan.find_space.done:

  ; preserve word end in ebp, and set edi to it later
  ; so word isn't scanned again
  mov ebp, eax
  sub eax, edi

  ; save word lens
  mov [word_lens + ecx*4], eax

  ; incrememnt word count
  inc ecx

  ; set edi to word end
  mov edi, ebp
  ; remember that find_non_space starts with inc
  dec edi
  jne .word_scan.find_non_space
.word_scan.done:

  ; save word_count to memory
  mov [word_count], ecx

%ifdef DEBUG
  ; call debug function to print string scanning results
  lea eax, [word_lens]
  push eax
  lea eax, [word_starts]
  push eax
  mov eax, [word_count]
  push eax
  mov eax, [string_start]
  push eax
  call _debug_wordscan
  add esp, 16
%endif

  ; pop callee-saved registers:
  ; ebx, ebp, esi, edi
  pop edi
  pop esi
  pop ebp
  pop ebx

  ret

