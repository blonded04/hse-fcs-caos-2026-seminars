; stack: [data + labels]

    .intel_syntax noprefix
    .text
    .global main
main:
    call readi32
    mov ebx, eax
    call readi32
    add eax, ebx
    mov edi, eax
    call writei32
    call nl
    call finish

caller:
    call callee
    ...

callee:
    ret

; rbp (base-pointer / frame-pointer), rsp (stack-pointer)
; [10, 20, 40]
;  ^ rbp     ^ rsp
; call function
; function....
; [10, 20, 40, 50, 70, 80]
;          ^ rbp         ^rsp
; ret
; [10, 20, 40]
;  ^ rbp     ^ rsp

; call, ret:
;    call func <-  prologue
                 ; [...]
    push rbp     ; [..., old-rbp]
    mov rbp rsp  ; rbp := rsp
    push 41-INSTRUCITON  ; [..., old-rbp, 41-INSTRUCITON]
    jmp func
    ...

; ret <- epilogue
             ; [..., old-rbp, 40-INSTRUCITON]
    pop rdx  ; [..., old-rbp], rdx := 40-INSTRUCITON
    pop rbp  ; [...], rbp := old-rbp
    jmp rdx  ; [...], rbp := old-rbp

; -fno-omit-frame-pointer
; gcc, clang, rustc.
; rbp as frame-pointer:
;  + predictability: profilers
;  - security 
;  - performance 2-3%
