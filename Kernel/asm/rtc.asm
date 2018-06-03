GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHour

%macro accessRTC 1
	push rbp
	mov rbp,rsp
	mov rax, 0h
	mov al, %1h
	out 70h, al
	in al, 71h
	pop cx
	mov cx, 10
	div cx
	push cx
	leave
	ret
%endmacro

getSeconds:
	accessRTC 0

getMinutes:
	accessRTC 2

getHour:
	accessRTC 4
