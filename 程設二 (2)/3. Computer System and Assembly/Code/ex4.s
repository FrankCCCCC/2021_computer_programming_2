	.file	"ex4.c"
	.intel_syntax noprefix
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	push	ebp
	mov	ebp, esp
	and	esp, -16
	sub	esp, 16
	call	___main
	mov	edx, DWORD PTR [esp+12]
	mov	eax, DWORD PTR [esp+8]
	add	eax, edx
	mov	DWORD PTR [esp+4], eax
	leave
	ret
	.ident	"GCC: (tdm-1) 4.9.2"
