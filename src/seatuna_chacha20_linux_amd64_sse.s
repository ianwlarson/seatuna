

.file "seatuna_chacha20_linux_amd64_sse.s"

/*
void seatuna_chacha20_bytes(uint8_t *key, uint32_t *counter, uint8_t *nonce, size_t req_len, uint8_t *out)
	rdi -> key
	rsi -> counter
	rdx -> nonce
	rcx -> req_len
	r8 -> out
*/
	.section .text
	.p2align 4,,15
	.globl seatuna_chacha20_bytes
	.type seatuna_chacha20_bytes, @function
seatuna_chacha20_bytes:
	push	%rbx
	subq	$16, %rsp

	leaq counter_add(%rip), %rbx
	movdqa (%rbx), %xmm8
	
	/* Load the state into xmm0-xmm3 */
	movl	(%rsi), %eax
	movl	%eax, (%rsp)	# store counter at front.
	mov		(%rsi), %r10	/* Store counter in r10 */
	movl	(%rdx), %eax
	movl	%eax, 4(%rsp)
	movl	4(%rdx), %eax
	movl	%eax, 8(%rsp)
	movl	8(%rdx), %eax
	movl	%eax, 12(%rsp)
	leaq	seatuna_chacha20_state(%rip), %rbx
	movdqa (%rbx), %xmm0
	movdqu (%rdi), %xmm1
	movdqu 16(%rdi), %xmm2
	movdqu (%rsp), %xmm3
	
lagain:
	/* Copy the state */
	movdqa %xmm0, %xmm4
	movdqa %xmm1, %xmm5
	movdqa %xmm2, %xmm6
	movdqa %xmm3, %xmm7
	
	mov $10, %rax

ltop:
	/* Start of round */
	paddd	%xmm1, %xmm0 # a += b
	pxor	%xmm0, %xmm3 # d ^= a
	movdqa	%xmm3, %xmm9 # d = roll32(d, 16)
	psrld	$16, %xmm3
	pslld	$16, %xmm9
	por	%xmm9, %xmm3
	
	paddd	%xmm3, %xmm2 # c += d
	pxor	%xmm2, %xmm1 # b ^= c
	movdqa	%xmm1, %xmm9 # b = roll32(b, 12);
	psrld	$20, %xmm1
	pslld	$12, %xmm9
	por	%xmm9, %xmm1
	
	paddd	%xmm1, %xmm0 # a += b
	pxor	%xmm0, %xmm3 # d ^= a
	movdqa	%xmm3, %xmm9 # d = roll32(d, 8)
	psrld	$24, %xmm3
	pslld	$8, %xmm9
	por	%xmm9, %xmm3
	
	paddd	%xmm3, %xmm2 # c += d
	pxor	%xmm2, %xmm1 # b ^= c
	movdqa	%xmm1, %xmm9 # b = roll32(b, 7)
	psrld	$25, %xmm1
	pslld	$7, %xmm9
	por	%xmm9, %xmm1
	/* End of round */
	
	movdqa	%xmm1, %xmm9 # rotate entire xmm1 right by 4 bytes
	pslldq	$12, %xmm1 
	psrldq	$4, %xmm9
	por	%xmm9, %xmm1
	
	movdqa	%xmm2, %xmm9 # rotate entire xmm2 right by 8 bytes
	pslldq	$8, %xmm2
	psrldq	$8, %xmm9
	por	%xmm9, %xmm2
	
	movdqa	%xmm3, %xmm9 # rotate entire xmm3 right by 12 bytes
	pslldq	$4, %xmm3
	psrldq	$12, %xmm9
	por	%xmm9, %xmm3
	
	/* Start of round */
	paddd	%xmm1, %xmm0 # a += b
	pxor	%xmm0, %xmm3 # d ^= a
	movdqa	%xmm3, %xmm9 # d = roll32(d, 16)
	psrld	$16, %xmm3
	pslld	$16, %xmm9
	por	%xmm9, %xmm3
	
	paddd	%xmm3, %xmm2 # c += d
	pxor	%xmm2, %xmm1 # b ^= c
	movdqa	%xmm1, %xmm9 # b = roll32(b, 12);
	psrld	$20, %xmm1
	pslld	$12, %xmm9
	por	%xmm9, %xmm1
	
	paddd	%xmm1, %xmm0 # a += b
	pxor	%xmm0, %xmm3 # d ^= a
	movdqa	%xmm3, %xmm9 # d = roll32(d, 8)
	psrld	$24, %xmm3
	pslld	$8, %xmm9
	por	%xmm9, %xmm3
	
	paddd	%xmm3, %xmm2 # c += d
	pxor	%xmm2, %xmm1 # b ^= c
	movdqa	%xmm1, %xmm9 # b = roll32(b, 7)
	psrld	$25, %xmm1
	pslld	$7, %xmm9
	por	%xmm9, %xmm1
	/* End of round */

	movdqa	%xmm1, %xmm9 # rotate entire xmm1 left by 4 bytes
	pslldq	$4, %xmm1
	psrldq	$12, %xmm9
	por	%xmm9, %xmm1
	
	movdqa	%xmm2, %xmm9 # rotate entire xmm2 left by 8 bytes
	pslldq	$8, %xmm2
	psrldq	$8, %xmm9
	por	%xmm9, %xmm2
	
	movdqa	%xmm3, %xmm9 # rotate entire xmm3 left by 12 bytes
	pslldq	$12, %xmm3
	psrldq	$4, %xmm9
	por	%xmm9, %xmm3
	
	dec		%rax
	jnz		ltop
	
	paddd	%xmm4, %xmm0
	paddd	%xmm5, %xmm1
	paddd	%xmm6, %xmm2
	paddd	%xmm7, %xmm3
	
	inc		%r10
	
	cmp		$64, %rcx
	jl lastblock
	movdqu %xmm0, (%r8)
	add		$16, %r8
	movdqu %xmm1, (%r8)
	add		$16, %r8
	movdqu %xmm2, (%r8)
	add		$16, %r8
	movdqu %xmm3, (%r8)
	add		$16, %r8
	
	movdqa	%xmm4, %xmm0
	movdqa	%xmm5, %xmm1
	movdqa	%xmm6, %xmm2
	movdqa	%xmm7, %xmm3
	
	sub		$64, %rcx
	jz		donefinal
	paddd	%xmm8, %xmm3
	jmp		lagain;
	
lastblock:

	movdqu %xmm0, %xmm4
	cmp		$16, %rcx
	jl		lessthansixteen
	movdqu %xmm4, (%r8)
	add		$16, %r8
	sub		$16, %rcx
	
	movdqu %xmm1, %xmm4
	cmp		$16, %rcx
	jl		lessthansixteen
	movdqu %xmm4, (%r8)
	add		$16, %r8
	sub		$16, %rcx
	
	movdqu %xmm2, %xmm4
	cmp		$16, %rcx
	jl		lessthansixteen
	movdqu %xmm4, (%r8)
	add		$16, %r8
	sub		$16, %rcx
	
	movdqu %xmm3, %xmm4
	cmp		$16, %rcx
	jl		lessthansixteen
	movdqu %xmm4, (%r8)
	add		$16, %r8
	sub		$16, %rcx
	
	jmp donefinal;
	
lessthansixteen:
	cmp		$8, %rcx
	jl		lessthaneight
	movq	%xmm4, %rax
	psrldq	$8, %xmm4
	movq	%rax, (%r8)
	sub		$8, %rcx
	
	cmp		$8, %rcx
	jl		lessthaneight
	movq	%xmm4, %rax
	psrldq	$8, %xmm4
	movq	%rax, (%r8)
	sub		$8, %rcx
	
	jmp donefinal
	
lessthaneight:
	movq	(%r8), %rdi
	shl		$3, %rcx
	shr		%cl, %rdi
	shl		%cl, %rdi
	mov		$64, %rdx
	sub		%rcx, %rdx
	mov		%rdx, %rcx
	shl		%cl, %rax
	shr		%cl, %rax
	or		%rdi, %rax
	movq	%rax, (%r8)
donefinal:
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	pxor	%xmm2, %xmm2
	pxor	%xmm3, %xmm3
	pxor	%xmm4, %xmm4
	pxor	%xmm5, %xmm5
	pxor	%xmm6, %xmm6
	pxor	%xmm7, %xmm7
	pxor	%xmm8, %xmm8
	mov		%r10, %rax
	movl	%eax, (%rsi)
	addq	$16, %rsp
	pop		%rbx
	ret
	.section .rodata
	.balign 16
	.type	seatuna_chacha20_state, @object
seatuna_chacha20_state:
	.long 0x61707865, 0x3320646e, 0x79622d32, 0x6b206574
	.balign 16
	.type counter_add, @object
counter_add:
	.long 0x1, 0x0, 0x0, 0x0

