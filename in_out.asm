GLOBAL _in
GLOBAL _out

section .text

_in:
  pop rbp
  mov rbp, rsp
  mov rax, 0
  mov rbx, [rbp+16]
  mov rcx, [rbp+24]
  cmp rcx, 1
  jz .oneByte
  cmp rcx, 2
  jz .twoBytes
  cmp rcx, 4
  jz .fourBytes
  cmp rcx, 8
  jz .eightBytes
  jmp .endWithError
.oneByte:
  in rax, BYTE[rbx]
  jmp .end
.twoBytes:
  in rax, WORD[rbx]
  jmp .end
.fourBytes:
  in rax, DWORD[rbx]
  jmp .end
.eightBytes:
  in rax, QWORD[rbx]
  jmp .end
.endWithError:

.end:
  leave



_out:
  pop rbp
  mov rbp, rsp
  mov rbx, [rbp+16]
  mov rcx, [rbp+24]
  out rcx, rbx  ;DESTINO, VALOR
  leave
