%include 'lib.inc'

SECTION .data
	msg db "Aqui temos uma linha!",0xa,0xa,0
	msglen equ $ - msg
	msg2 db "Outra linha!",0xa,0
	msg2len equ $ - msg2

	arq db 'asmout.txt'

	fd dq 0  ; File Descriptor

SECTION .text
global _start

_start:
    mov rax, 2       ; syscall para open
    mov rdi, arq     ; nome do arquivo
    mov rsi, O_CREAT | O_WRONLY | O_APPEND      ; flags combinadas usando o operador |
    mov rdx, 0o664    ; modo de acesso
    syscall          ; chama o sistema

	mov [fd], eax  ; The File Descriptor ID is returned to eax after syscall

File_write:
    mov rax, 1       ; syscall para write
    mov rdi, [fd]    ; file descriptor
    lea rsi, [msg]     ; mensagem a ser escrita
    mov rdx, msglen  ; tamanho da mensagem
    syscall          ; chama o sistema

Close_file:
    mov rax, 3       ; syscall para close
    mov rdi, [fd]    ; file descriptor
    syscall          ; chama o sistema

fin:
	mov eax, 60
	xor edx,edx
	syscall
