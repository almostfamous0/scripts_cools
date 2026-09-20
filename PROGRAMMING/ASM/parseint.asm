section .data 

msg db '28',0

_start:
	mov eax, 0 mov ebx, msg

loop:
	mov dl, [ebx] test dl, dl
	je done
	sub dl, '0'
imul eax, eax, 10 add eax, edx
add ebx, 1
jmp loop
