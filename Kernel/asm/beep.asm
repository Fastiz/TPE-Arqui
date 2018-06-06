;GLOBAL beep

;section .text

;beep:
;  mov al, 1
;  out 0x61, al
;  ret

  GLOBAL beepasm
GLOBAL unbeepasm
section .text

beepasm:
    push rbp
    mov rbp, rsp

    mov al, 0xb6
    out 0x43, al
    mov rax, 0
    mov al, 11931
    out 0x42, al
    mov al, ah
    out 0x42, al
    in al, 0x61
    or al, 0x03
    out 61h, al

    mov rsp, rbp
    pop rbp
    ret

unbeepasm:
    in al, 0x61
    and al, 0xFC
    out 0x61, al
    ret
