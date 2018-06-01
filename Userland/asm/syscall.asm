GLOBAL system

section .text

system:
  enter 0,0
  mov rax, [ebp+16]
  mov rbx, [ebp+24]
  mov rcx, [ebp+32]
  mov rdx, [ebp+40]

  int 80h
  leave
  ret
