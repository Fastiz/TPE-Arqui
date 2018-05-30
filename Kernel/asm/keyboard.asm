
GLOBAL getKey

getKey:
	push rbp
	mov rbp,rsp
	mov rax, 0
	checkKey:
		in al, 64h
		test al, 01h
		jz checkKey
	in al,60h
	pop rbp
	ret

