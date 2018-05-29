; void process_words(char* str)
global _process_words

; void print_word_pair(char* w1, int w1len, char* w2, int w2len)
extern _print_word_pair

%ifdef DEBUG
; void debug_wordscan(char* str, int word_count,
;   char** word_starts, int* word_lens)
extern _debug_wordscan
%endif


section .data
global _max_diff_count

# max allowed unmatching chars + 1
_max_diff_count: dd 2

section .bss
max_strlen equ 256

word_count: resd 1
word_starts: resb max_strlen / 2
word_lens: resb max_strlen / 2

string_start: resd 1

section .text
_process_words:
  ; push callee-saved registers:
  ; ebx, ebp, esi, edi
  ; 4 regs are pushed, so stack alignment is fine
  push ebx
  push ebp
  push esi
  push edi

  ; get string ptr
  mov esi, [esp + 16 + 4]
  mov [string_start], esi

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

  ; iterate over all words "combinations"
  mov ebp, [word_count]
.word_combinations.outer_loop:
  cmp ebp, 1
  jbe .word_combinations.outer_loop.done
  dec ebp
  mov ebx, ebp

.word_combinations.inner_loop:
  test ebx, ebx
  je .word_combinations.inner_loop.done
  dec ebx

  ; check if words have same lengths
  mov eax, [word_lens + ebp*4]
  mov ecx, [word_lens + ebx*4]

  cmp eax, ecx
  jne .word_combinations.inner_loop

  ; if they do, compare two words
  ; flags are caller-saved => df can be changed
  cld

  mov esi, [word_starts + ebp*4]
  mov edi, [word_starts + ebx*4]

  ; Compare words:
  ; a: if they are same: print them
  ; b: else:
  ;  1. decrement edx (used for number of differences encountered)
  ;  2. if edx is 0, there were more than _max_diff_count differences,
  ;     and word pair is skipped
  ;  3. try comparing again

  mov edx, [_max_diff_count]
.word_combinations.cmps_loop:
  jecxz .word_combinations.cmps_loop.done
  repe cmpsb
  jne .word_combinations.cmps_loop.unequal
  ; a
  jecxz .word_combinations.cmps_loop.done

.word_combinations.cmps_loop.unequal
  ; 1
  dec edx
  ; 2
  test edx, edx
  jne .word_combinations.cmps_loop
  ; 3
  jmp .word_combinations.inner_loop
.word_combinations.cmps_loop.done:

  ; If we reached this point, words should be printed
  push eax
  push dword [word_starts + ebp*4]
  push eax
  push dword [word_starts + ebx*4]
  call dword _print_word_pair
  add esp, 16

  jmp .word_combinations.inner_loop

.word_combinations.inner_loop.done:
  jmp .word_combinations.outer_loop

.word_combinations.outer_loop.done:

  ; pop callee-saved registers:
  ; ebx, ebp, esi, edi
  pop edi
  pop esi
  pop ebp
  pop ebx

  ret

