GLOBAL _syscall

section .text

_syscall:
  enter 0,0
  int 80h
  leave
  ret
