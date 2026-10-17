; address in asm != address in RAM
; virtual memory / tlb

; 0xbbbb...:
; uintptr_t x = &array;
; x = x & (1 << 48);
; x = x | array->size; // array->size is uint16_t
;  - restricted memory <- java compressed oops
;  - lock-free

; kernel-space vs user-space
; 0x0000000000000000-0x00007fffffffffff: user-space
;  - 0x00007ffffffff000->0x00007fffffde000 v: stack
;  - 0x0000555555554000 ^: heap
;  - elf sections (.data / .rodata / .bss / .text)
; 0xffff800000000000-0xffff800000000000: kernel-space
; 0x0000800000000000-0xffff800000000000: unused

; ca->spb, 100ms
; hdd, Xms
; ssd, Yus
; nvme, Zus
; RAM, 50x
; l3, 20x
; l2, 10x
; l1, 10x
; register, 3x
