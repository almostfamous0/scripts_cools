section .rodata
	asterisk_line: db '*  *  *  *  *  *  *',0xa,0
	space_line: db  '  x  x  x  x  x  x ',0xa,0

section .text

global _start

_start:
	mov ebx, 0

loop:
	inc ebx
	cmp ebx, 10
	jz fin

	mov eax, 1
	mov edi, 1
	mov edx, 20

	push rbx
	and ebx, 0x1
	jnz ast  ; IF
	jmp spc ; ELSE

ast:
	pop rbx
	lea rsi, [asterisk_line]
	syscall
	jmp loop

spc:
	pop rbx
	lea rsi, [space_line]
	syscall
	jmp loop

fin:
	mov eax,60
	xor edi,edi
	syscall
