section .rodata
    ; Pilha de livros
    liv1        db '1. Moby Dick',0xa,0
    liv2        db '2. Tom Swayer',0xa,0
    liv3        db '3. Duna',0xa,0

section .text

global _start

_start:
	push liv3
	push liv2
	push liv1
	mov r12d, 0x0

	; Pegar o ultimo livro colocado
	pop rsi
	jmp imprimir
;	call imprimir

imp2:
	pop rsi
	jmp imprimir
;	call imprimir

imp3:
	pop rsi
	jmp imprimir
;	call imprimir
	

imprimir:
	xor edx,edx
	mov rcx,rsi
	call len
	mov eax,0x1
	mov edi,eax

	inc r12d	
	push r12

	syscall

	pop r12
	cmp r12d,0x1
	jz imp2
	cmp r12d,0x2
	jz imp3

exit:
	mov eax, 60
	xor edi,edi
	syscall

	
len:
	inc edx
	inc rcx
	cmp byte [rcx], 0x0
	jnz len
	ret
