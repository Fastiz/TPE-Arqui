GLOBAL syscall

section .text

syscall:
  enter 0,0
  int 80h
  leave
  ret
