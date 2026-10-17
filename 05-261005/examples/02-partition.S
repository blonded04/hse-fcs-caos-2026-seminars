    .intel_syntax noprefix
    .text
    .global partition
partition:
    push rbp
    mov rbp, rsp

    xor edx, edx
    xor ecx, ecx
partition_loop:
    cmp ecx, esi
    jge partition_done
    movsx eax, word ptr [rbx + rcx * 2]
    cmp eax, edi
    jge partition_next

    mov r8w, word ptr [rbx + rdx * 2]
    mov word ptr [rbx + rdx * 2], ax
    mov word ptr [rbx + rcx * 2], r8w
    add edx, 1

partition_next:
    add ecx, 1
    jmp partition_loop
partition_done:
    pop rbp
    ret
