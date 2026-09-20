%define directive

%define NAME 42

%define PROT_EXEC 0x4
%define PROT_READ 0x1
%define MAP_PRIVATE 0x2
%define O_RDONLY 0x0
; Sempre pesquisar no google coisa do tipo:  lxr PROT_READ  (por exemplo)

section .rodata
	file: db 'test.txt',0

section .text
	global _start

print_str:
	push rdi
	call strlen
	pop rsi  ; Ja jogando no rsi
	mov eax,1
	mov edi,1
	syscall
	ret

strlen:
   xor edx,edx
.loop:
	add edx,0x1
	cmp byte [rdi+rdx], 0
	jnz .loop
	ret

_start:

	mov eax,2 ; open()
	mov rdi, file
	mov rsi, O_RDONLY
	mov rdx,0
	syscall


	; mmap
	mov r8, rax  ; rax armazena o fd do arquivo aberto
	mov rax, 9
	xor edi,edi
	mov rsi, 4096  ; Tamanho da pagina (4kb)
	mov rdx, PROT_READ    ; Somente leitura nessa regiao de memoria alocada
	mov r10, MAP_PRIVATE  ; A(s) pagina(s) nao sera(ao) compartilhada(s)

	mov r9, 0  ; Offset em test.txt
	syscall   ; Agora rax apontara para o local mapeado

	mov rdi, rax
	call print_str

	; exit
	mov eax,60
	xor edi,edi
	syscall

