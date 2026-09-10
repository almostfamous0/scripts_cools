section .rodata
msg: db 'Hello', 0xa

section .text
global _start

_start:
    mov eax,1  ; Write syscall
    mov edi,eax ; stdout
    lea rsi, [msg]
    mov edx, 6
    syscall

    xor edi,edi
    mov eax,60  ; Quit Syscall
    syscall
