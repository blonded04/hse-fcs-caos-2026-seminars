    .intel_syntax noprefix
    .text
    .global calculate
calculate:
    push rbp
    mov rbp, rsp

    mov rax, rdi
    add rax, rsi
    add rax, rdx
    add rax, rcx
    add rax, r8
    add rax, r9

    # После пролога x лежит в [rbp + 16], y — в [rbp + 24].
    mov r10, qword ptr [rbp + 24]
    add r10, 1
    imul r10, qword ptr [rbp + 16]
    add rax, r10

    pop rbp
    ret
