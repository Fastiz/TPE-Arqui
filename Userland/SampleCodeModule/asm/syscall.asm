GLOBAL _syscall

section .text

_syscall:
	push rbp
	mov rbp, rsp
	
	push rbx
	mov rax, rdi

	mov rbx, rsi
	mov [aux], rcx 
	mov rcx, rdx
	mov rdx, [aux]
	int 80h
	
	pop rbx
	leave
	ret


section .bss
	aux resq 1