.LC0:
        .string "a): %u\n"
a:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC0
        sal     esi, 5
        jmp     printf
.LC1:
        .string "as): %u\n"
a_solution:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC1
        sal     esi, 5
        jmp     printf
.LC2:
        .string "b): %u\n"
b:
        mov     esi, edi
        xor     eax, eax
        sal     esi, 4
        sub     esi, edi
        mov     edi, OFFSET FLAT:.LC2
        jmp     printf
.LC3:
        .string "bs): %u\n"
b_solution:
        mov     esi, edi
        xor     eax, eax
        sal     esi, 4
        sub     esi, edi
        mov     edi, OFFSET FLAT:.LC3
        jmp     printf
.LC4:
        .string "c): %u\n"
c:
        lea     esi, [rdi+rdi*2]
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC4
        sal     esi, 5
        jmp     printf
.LC5:
        .string "cs): %u\n"
c_solution:
        lea     esi, [rdi+rdi*2]
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC5
        sal     esi, 5
        jmp     printf
.LC7:
        .string "d): %u\n"
d:
        mov     edi, edi
        pxor    xmm0, xmm0
        xor     eax, eax
        cvtsi2sdq       xmm0, rdi
        mulsd   xmm0, QWORD PTR .LC6[rip]
        mov     edi, OFFSET FLAT:.LC7
        cvttsd2si       rsi, xmm0
        jmp     printf
.LC8:
        .string "ds): %u\n"
d_solution:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC8
        shr     esi, 3
        jmp     printf
.LC9:
        .string "e): %u\n"
e:
        lea     rax, [rdi+4000]
        xor     esi, esi
.L13:
        add     esi, DWORD PTR [rdi]
        add     rdi, 20
        cmp     rax, rdi
        jne     .L13
        mov     edi, OFFSET FLAT:.LC9
        xor     eax, eax
        jmp     printf
.LC10:
        .string "es): %u\n"
e_solution:
        lea     rax, [rdi+4000]
        xor     esi, esi
.L16:
        add     esi, DWORD PTR [rdi]
        add     rdi, 20
        cmp     rax, rdi
        jne     .L16
        mov     edi, OFFSET FLAT:.LC10
        xor     eax, eax
        jmp     printf
.LC14:
        .string "f):"
.LC15:
        .string "%lf, "
f:
        push    rbp
        mov     rax, rdi
        lea     rbp, [rdi+8000]
        push    rbx
        mov     rbx, rdi
        sub     rsp, 8
        movdqa  xmm2, XMMWORD PTR .LC11[rip]
        movdqa  xmm4, XMMWORD PTR .LC12[rip]
        movapd  xmm3, XMMWORD PTR .LC13[rip]
.L19:
        pshufd  xmm0, xmm2, 238
        cvtdq2pd        xmm1, xmm2
        movupd  xmm6, XMMWORD PTR [rax]
        add     rax, 32
        cvtdq2pd        xmm0, xmm0
        divpd   xmm1, xmm3
        movupd  xmm5, XMMWORD PTR [rax-16]
        paddd   xmm2, xmm4
        divpd   xmm0, xmm3
        addpd   xmm1, xmm6
        movups  XMMWORD PTR [rax-32], xmm1
        addpd   xmm0, xmm5
        movups  XMMWORD PTR [rax-16], xmm0
        cmp     rax, rbp
        jne     .L19
        mov     edi, OFFSET FLAT:.LC14
        xor     eax, eax
        call    printf
.L20:
        movsd   xmm0, QWORD PTR [rbx]
        mov     edi, OFFSET FLAT:.LC15
        mov     eax, 1
        add     rbx, 8
        call    printf
        cmp     rbx, rbp
        jne     .L20
        add     rsp, 8
        mov     edi, 10
        pop     rbx
        pop     rbp
        jmp     putchar
.LC17:
        .string "fs):"
f_solution:
        push    rbp
        mov     rax, rdi
        lea     rbp, [rdi+8000]
        push    rbx
        mov     rbx, rdi
        sub     rsp, 8
        movdqa  xmm2, XMMWORD PTR .LC11[rip]
        movdqa  xmm4, XMMWORD PTR .LC12[rip]
        movapd  xmm3, XMMWORD PTR .LC16[rip]
.L25:
        pshufd  xmm0, xmm2, 238
        cvtdq2pd        xmm1, xmm2
        movupd  xmm6, XMMWORD PTR [rax]
        add     rax, 32
        cvtdq2pd        xmm0, xmm0
        mulpd   xmm1, xmm3
        movupd  xmm5, XMMWORD PTR [rax-16]
        paddd   xmm2, xmm4
        mulpd   xmm0, xmm3
        addpd   xmm1, xmm6
        addpd   xmm0, xmm5
        movups  XMMWORD PTR [rax-32], xmm1
        movups  XMMWORD PTR [rax-16], xmm0
        cmp     rax, rbp
        jne     .L25
        mov     edi, OFFSET FLAT:.LC17
        xor     eax, eax
        call    printf
.L26:
        movsd   xmm0, QWORD PTR [rbx]
        mov     edi, OFFSET FLAT:.LC15
        mov     eax, 1
        add     rbx, 8
        call    printf
        cmp     rbx, rbp
        jne     .L26
        add     rsp, 8
        mov     edi, 10
        pop     rbx
        pop     rbp
        jmp     putchar
.LC19:
        .string "g): %f\n"
g:
        xorps   xmm0, XMMWORD PTR .LC18[rip]
        mov     edi, OFFSET FLAT:.LC19
        mov     eax, 1
        cvtss2sd        xmm0, xmm0
        jmp     printf
.LC20:
        .string "gs): %f\n"
g_solution:
        xorps   xmm0, XMMWORD PTR .LC18[rip]
        mov     edi, OFFSET FLAT:.LC20
        mov     eax, 1
        cvtss2sd        xmm0, xmm0
        jmp     printf
main:
        xor     eax, eax
        ret
.LC6:
        .long   0
        .long   1069547520
.LC11:
        .long   0
        .long   1
        .long   2
        .long   3
.LC12:
        .long   4
        .long   4
        .long   4
        .long   4
.LC13:
        .long   858993459
        .long   1075131187
        .long   858993459
        .long   1075131187
.LC16:
        .long   972445426
        .long   1070081700
        .long   972445426
        .long   1070081700
.LC18:
        .long   2147483648
        .long   0
        .long   0
        .long   0