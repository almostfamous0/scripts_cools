.text

.global _start

_start:
  mov r0, #1
  mov r1, =string
  mov r2, =len
  mov r7, #4
  swi #0

  sub r7, #3
  swi #0

.data
string: .asciz "hello world!\n"
len = .-message
