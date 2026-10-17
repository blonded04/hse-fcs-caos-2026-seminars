    .intel_syntax noprefix
    .text
    .global main
main:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    sub rsp, 8

    call readi32
    mov r12d, eax
    xor ebx, ebx
    xor r13d, r13d
read_loop:
    call readi32
    jc read_done
    mov dword ptr [rbp - 32], eax

    mov rdi, rbx
    mov esi, r13d
    add rsi, 1
    imul rsi, rsi, 2
    call realloc
    test rax, rax
    je incorrect
    mov rbx, rax
    mov eax, dword ptr [rbp - 32]
    mov word ptr [rbx + r13 * 2], ax
    add r13d, 1
    jmp read_loop

read_done:
    mov esi, r13d
    mov edi, r12d
    call partition
    cmp edx, r13d
    jae incorrect

    xor ecx, ecx
check_loop:
    cmp ecx, r13d
    jge correct
    movsx eax, word ptr [rbx + rcx * 2]
    cmp ecx, edx
    jge check_right
    cmp eax, r12d
    jg incorrect
    jmp check_next
check_right:
    cmp eax, r12d
    jl incorrect
check_next:
    add ecx, 1
    jmp check_loop

correct:
    mov edi, 1
    jmp print_result
incorrect:
    xor edi, edi
print_result:
    call writei32
    call nl
    mov rdi, rbx
    call free

    xor eax, eax
    add rsp, 8
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret
