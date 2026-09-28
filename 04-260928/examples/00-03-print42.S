    .intel_syntax noprefix
    .text
    .global main
main:
    mov edi, 42
    call writei32
    call nl
    call finish
