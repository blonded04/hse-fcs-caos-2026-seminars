	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.intel_syntax noprefix
	.globl	_sum                            ## -- Begin function sum
	.p2align	4, 0x90
_sum:                                   ## @sum
	.cfi_startproc
## %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	test	rsi, rsi
	je	LBB0_1
## %bb.2:
	cmp	rsi, 7
	ja	LBB0_4
## %bb.3:
	xor	ecx, ecx
	xor	eax, eax
	jmp	LBB0_7
LBB0_1:
	xor	eax, eax
	pop	rbp
	ret
LBB0_4:
	mov	rcx, rsi
	and	rcx, -8
	pxor	xmm0, xmm0
	xor	eax, eax
	pxor	xmm1, xmm1
	.p2align	4, 0x90
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	movdqu	xmm2, xmmword ptr [rdi + 4*rax]
	paddd	xmm0, xmm2
	movdqu	xmm2, xmmword ptr [rdi + 4*rax + 16]
	paddd	xmm1, xmm2
	add	rax, 8
	cmp	rcx, rax
	jne	LBB0_5
## %bb.6:
	paddd	xmm1, xmm0
	pshufd	xmm0, xmm1, 238                 ## xmm0 = xmm1[2,3,2,3]
	paddd	xmm0, xmm1
	pshufd	xmm1, xmm0, 85                  ## xmm1 = xmm0[1,1,1,1]
	paddd	xmm1, xmm0
	movd	eax, xmm1
	cmp	rcx, rsi
	je	LBB0_8
	.p2align	4, 0x90
LBB0_7:                                 ## =>This Inner Loop Header: Depth=1
	add	eax, dword ptr [rdi + 4*rcx]
	inc	rcx
	cmp	rsi, rcx
	jne	LBB0_7
LBB0_8:
	pop	rbp
	ret
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
