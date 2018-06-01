GLOBAL system

section .text

system:
  enter 0,0

  int 80h
  leave
  ret
