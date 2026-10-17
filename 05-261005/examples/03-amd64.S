; calling conventions x86-64
; * stack alignment before call: 16 byte <- SSE
; * function arguments:
;   - rdi
;   - rsi
;   - rdx
;   - rcx
;   - r8
;   - r9
;   - ...stack
; * function return value:
;   - rax
; * preserved registers:
;   - rbx
;   - rsp
;   - rbp 
;   - r12
;   - r13
;   - r14
;   - r15
; * "dirty" registers:
;   - rcx
;   - rdx
;   - rsi
;   - r8-r11

