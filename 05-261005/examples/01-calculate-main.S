    .intel_syntax noprefix
    .text
    .global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    call readi64
    mov qword ptr [rbp - 64], rax
    call readi64
    mov qword ptr [rbp - 56], rax
    call readi64
    mov qword ptr [rbp - 48], rax
    call readi64
    mov qword ptr [rbp - 40], rax
    call readi64
    mov qword ptr [rbp - 32], rax
    call readi64
    mov qword ptr [rbp - 24], rax
    call readi64
    mov qword ptr [rbp - 16], rax
    call readi64
    mov qword ptr [rbp - 8], rax

    mov rdi, qword ptr [rbp - 64]
    mov rsi, qword ptr [rbp - 56]
    mov rdx, qword ptr [rbp - 48]
    mov rcx, qword ptr [rbp - 40]
    mov r8, qword ptr [rbp - 32]
    mov r9, qword ptr [rbp - 24]

    push qword ptr [rbp - 8]
    push qword ptr [rbp - 16]
    call calculate
    add rsp, 16

    mov rdi, rax
    call writei64
    call nl

    xor eax, eax
    mov rsp, rbp
    pop rbp
    ret
