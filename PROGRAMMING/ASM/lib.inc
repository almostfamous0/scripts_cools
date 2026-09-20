segment .rodata
    SYS_READ  equ 0x0    ; operaçao de leitura
    SYS_WRITE equ 0x1    ; Output System Call code func
    STD_OUT   equ 0x1    ; valor de saida padrao
    STD_IN    equ 0x0    ; entrada padrao
    SYS_EXIT  equ 0x1    ; codigo de chamada para finalizar o programa
	NL	db 0xa,0

	SYS_OPEN equ 0x2    ; SYSCALL
	SYS_CLOSE equ 0x3   ; SYSCALL
    LSEEK equ 0x8    ; SYSCALL LSEEK

  	OPEN_APPEND equ 0x8 ; Arquivo para adição de informação

  	OPEN_APPEND equ 0x8 ; Arquivo para adição de informação

	SEEK_SET  equ 0x0    ; Inicio do Arquivo
  	SEEK_CUR  equ 0x1    ; Posição do Cursor
  	SEEK_END  equ 0x2    ; Final do Arquivo


	PROT_EXEC equ 0x4
	PROT_READ equ 0x1
	MAP_PRIVATE equ 0x2

    O_RDONLY equ 0x0	
	O_CREAT equ 0100
    O_WRONLY equ 0001
    O_APPEND equ 02000

	RET_EXIT equ 0

SEGMENT .text

input:
    mov eax, SYS_READ
    mov ebx, STD_IN
    syscall
    ret

print:
	mov eax, SYS_WRITE
	mov ebx, STD_OUT
    ;pusha
    ;int SYS_CALL
    ;popa
    ret

pstr:
	call strlen
	mov rsi, rcx
	mov eax, SYS_WRITE
	mov ebx, STD_OUT
	syscall
	;call print
	ret

nw:
    mov rsi, NL
	mov edx,0x1
	call print
	ret

; ----------------------------------------------------------------------------------------------------------------------------------------
  
  ; [ + ] PARA O PROGRAMA ABAIXO FUNCIONAR, EH PRECISO ADICIONAR
  ; O SEGUINTE TRECHO DE CODIGO NO PROGRAMA PRINCIPAL

  ;section .bss
  ;	digitSpace resb 100   ; Isso que vai de fato salvar a string
  ;	digitSpacePos resb 8  ; Isso vai salvar os enderecos de memoria da string atuais

; -------------------------------------------------------------------------------->
	
exit:
    mov eax,60
	xor edi,edi
	syscall

strlen:
	xor edx,edx
    mov rbx, rsi
loop:
  inc edx
  inc rbx
  cmp byte [rbx],0
  jnz loop
  ret
