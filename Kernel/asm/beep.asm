GLOBAL beep

section .text

beep:
  mov al, 1
  out 0x61, al
  ret
