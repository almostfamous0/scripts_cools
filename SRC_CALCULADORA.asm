comment * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

			Criado por Ryokusei para fins didáticos

						Compile com

                     >> Console Assemble & Link <<

; ««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««« *

   .486
   .model flat, stdcall
   option casemap :none   ; case sensitive

; «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

   include \masm32\include\windows.inc
   include \masm32\include\kernel32.inc
   include \masm32\include\msvcrt.inc

includelib \masm32\lib\msvcrt.lib
   includelib \masm32\lib\kernel32.lib

; «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

.data
	Operator1	dd	0
	Operator2	dd	0
	Result		dd	0
	Operation	db	0
	Str1		db	"Digite o primeiro operador: ",0
	Str2		db	"Pressione a tecla correspondente a operacao (+, -, *, /): ",0
	Str3		db	13,10,"Digite o segundo operador: ",0
	Str4		db	"Resultado: %i %c %i = %i",0
	Str5		db	"%i",0
	Str6		db	13,10,"Pressione qualquer tecla para continuar...",0
	Str7		db	"%c",0
	Str8		db	"cls",0
	Char1		db	"+"
	Char2		db	"-"
	Char3		db	"*"
	Char4		db	"/"
	
; «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

   .code

ClearCIn proc

PUSH STD_INPUT_HANDLE
CALL GetStdHandle
PUSH EAX
CALL FlushConsoleInputBuffer
RET

ClearCIn Endp	

main:

; «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

;Exibir primeira string	
PUSH OFFSET Str1
CALL crt_printf		;Função printf. Está declarada com os nomes "crt_printf" e "_imp__printf" em msvcrt.inc. Outras funções da mesma biblioteca seguem este padrão. Para mais informações visualize o arquivo \masm32\include\msvcrt.inc.
ADD ESP,4			;Faz-se o stack cleanup porque a função é cdecl.	

;Pegar valor inputado pelo usuário
PUSH OFFSET Operator1
PUSH OFFSET Str5
CALL crt_scanf
ADD ESP,8	

;Exibir segunda string
PUSH OFFSET Str2
CALL crt_printf
ADD ESP,4

;Limpar o input do console. Isso é necessário porque quando se pressiona ENTER dois bytes são enviados ao input, o que pode ocasionar problemas com outras funções que estejam adiante (getche, scanf, por exemplo). Veja a função ClearCIn.
CALL ClearCIn

GetOperation:
;Pegar valor inputado de somente 1 caractere, e só continua a execução se for uma das operações
CALL crt__getch
MOV Operation,AL	;O retorno é DWORD (EAX), mas a variável "Operation" só suporta 1 byte (db). Portanto opera-se com AL.	
CMP AL,Char1
JZ Continue
CMP AL,Char2
JZ Continue
CMP AL,Char3
JZ Continue
CMP AL,Char4
JZ Continue
JMP GetOperation	

Continue:
;Exibe o tipo de operação escolhida
MOVZX EAX,Operation
PUSH EAX
PUSH OFFSET Str7
CALL crt_printf
ADD ESP,8

;Exibir terceira string
PUSH OFFSET Str3
CALL crt_printf
ADD ESP,4

CALL ClearCIn

;Pegar valor inputado pelo usuário
PUSH OFFSET Operator2
PUSH OFFSET Str5
CALL crt_scanf
ADD ESP,8	

Calculate:	;Realizar cáculo
MOV CL,Operation
MOV EAX,Operator1
CMP CL,Char1
JZ Sum
CMP CL,Char2
JZ Subt
CMP CL,Char3
JZ Mult
JMP Divi

Sum:		;Somar	
ADD EAX,Operator2
JMP Continue2

Subt:
SUB EAX,Operator2
JMP Continue2

Mult:
XOR EDX,EDX	;Deve-se zerar EDX para que a operação não seja considerada como QWORD. Para mais informações pesquise sobre MUL, IMUL, DIV e IDIV.
IMUL EAX,Operator2
JMP Continue2

Divi:
XOR EDX,EDX
IDIV Operator2

Continue2:	

MOV Result,EAX

;Exibir resultado
PUSH Result	
PUSH Operator2
MOVZX EAX,Operation
PUSH EAX
PUSH Operator1
PUSH OFFSET Str4
CALL crt_printf
ADD ESP,0Ch

;Pausar
PUSH OFFSET Str6
CALL crt_printf
ADD ESP,4		
CALL ClearCIn	
CALL crt__getch

;Limpar a tela
PUSH OFFSET Str8
CALL crt_system
ADD ESP,4

;Voltar ao início
JMP main

;Encerrar processo. Na verdade isso nunca será executado, porque não coloquei opção de fechar aplicativo.
PUSH 0
CALL ExitProcess

; «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

end main
