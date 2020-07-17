BITS 64

SECTION .text
global main

main:
  ;save registers so we can restore them
  push rax
  push rcx
  push rdx
  push rsi
  push rdi
  push r11

  ;syswrite
  mov rax, 1
  ;to stdout
  mov rdi, 1
  ;load effective address of hello
  lea rsi, [rel $+hello-$]
  ;length of hello
  mov rdx, [rel $+len-$]
  syscall

  pop r11
  pop rdi
  pop rsi
  pop rdx
  pop rcx
  pop rax

  ;push entry point of host
  push 0x400430

  ;return to host
  ret

 hello: db "!!! Infected !!!", 10
 len:   dd 17
