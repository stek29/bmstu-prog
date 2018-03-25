; int process_text(char str[strlen+1], int strlen, struct charinfo info['Z' - 'A' + 1])
global _process_text

; struct charinfo {
;   int freq;
;   char ch;
;   // 3 byte padding
; }

section .bss
str_ptr: resd 1
str_len: resd 1
info_ptr: resd 1

%ifdef DEBUG
global _char_info_buf
%endif

_char_info_buf: resd ('Z' - 'A' + 1)

section .text
_process_text:
  ; push callee-saved registers:
  ; ebx, ebp, esi, edi
  ; 4 regs are pushed, so stack alignment is fine
  push ebx
  push ebp
  push esi
  push edi

  ; get string ptr
  mov eax, [esp + 16 +  4]
  mov [str_ptr], eax
  ; get strlen
  mov eax, [esp + 16 +  8]
  mov [str_len], eax
  ; get info ptr
  mov eax, [esp + 16 + 12]
  mov [info_ptr], eax

  xor eax, eax
  mov ecx, [str_len]
  mov esi, [str_ptr]
  dec esi
.char_loop.start:
  mov al, [esi + ecx]

  sub al, 'A'
  js .char_loop.loop

  cmp al, ('Z' - 'A')
  jbe .char_loop.inc

  sub al, ('a' - 'A')
  js .char_loop.loop

  cmp al, ('z' - 'a')
  jnbe .char_loop.loop

.char_loop.inc:
  inc dword [_char_info_buf + eax*4]

.char_loop.loop:
  loop .char_loop.start

  lea esi, [_char_info_buf]
  mov edi, [info_ptr]

  xor ebx, ebx
  xor ecx, ecx

.fmt_loop.start:
  cmp ebx, ('Z' - 'A' + 1)
  je .fmt_loop.done

  mov eax, [esi + ebx*4]
  inc ebx

  test eax, eax
  je .fmt_loop.start

  mov [edi + ecx*8], eax
  mov eax, ebx
  add eax, ('A' - 1)
  mov [edi + ecx*8 + 4], eax
  inc ecx

  jmp .fmt_loop.start
.fmt_loop.done:

  mov eax, ecx

  ; pop callee-saved registers:
  ; ebx, ebp, esi, edi
  pop edi
  pop esi
  pop ebp
  pop ebx

  ret

