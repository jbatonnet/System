/*
    http://www.cs.usfca.edu/~benson/cs326/pintos/pintos/src/lib/arithmetic.c

    On x86, division of one 64-bit integer by another cannot be
    done with a single instruction or a short sequence.  Thus, GCC
    implements 64-bit division and remainder operations through
    function calls.  These functions are normally obtained from
    libgcc, which is automatically included by GCC in any link
    that it does.

    Some x86-64 machines, however, have a compiler and utilities
    that can generate 32-bit x86 code without having any of the
    necessary libraries, including libgcc.  Thus, we can make
    Pintos work on these machines by simply implementing our own
    64-bit division routines, which are the only routines from
    libgcc that Pintos requires.

    Completeness is another reason to include these routines.  If
    Pintos is completely self-contained, then that makes it that
    much less mysterious.
*/

typedef unsigned char      u8;
typedef int                s32;
typedef unsigned           u32;
typedef long long          s64;
typedef unsigned long long u64;

extern "C" __declspec(naked) u32 divl(u32 n1, u32 n0, u32 d)
{
    _asm
    {
        push ebp
        mov ebp, esp
        push ebx

        mov edx, [n1]
        mov eax, [n0]
        mov ebx, [d]

        div ebx

        pop ebx
        mov esp, ebp
        pop ebp

        ret
    }
}
static int nlz(u32 x) 
{
    int n = 0;
    if (x <= 0x0000FFFF)
    {
        n += 16;
        x <<= 16; 
    }
    if (x <= 0x00FFFFFF)
    {
        n += 8;
        x <<= 8; 
    }
    if (x <= 0x0FFFFFFF)
    {
        n += 4;
        x <<= 4;
    }
    if (x <= 0x3FFFFFFF)
    {
        n += 2;
        x <<= 2; 
    }
    if (x <= 0x7FFFFFFF)
        n++;
    return n;
}

// Shifting
extern "C" _declspec(naked) u64 _aullshl(u64 a, u8 b)
{
    _asm
    {
        cmp cl, 64
        jae zero

        cmp cl, 32
        ja above
        jb below

        mov edx, eax
        xor eax, eax
        ret

        above:
            mov edx, eax
            xor eax, eax
            and cl, 31
            shl edx, cl
            ret

        below:
            shld edx, eax, cl
            shl eax, cl
            ret

        zero:
            xor edx, edx
            xor eax, eax
            ret
    }
}
extern "C" _declspec(naked) s64 _allshl(s64 a, u8 b)
{
    _asm
    {
        call _aullshl
        ret
    }
}
extern "C" _declspec(naked) u64 _aullshr(u64 a, u8 b)
{
    _asm
    {
        cmp cl, 64
        jae zero

        cmp cl, 32
        ja above
        jb below

        mov eax, edx
        xor edx, edx
        ret

        above:
            mov eax, edx
            xor edx, edx
            and cl, 31
            shr eax, cl
            ret

        below:
            shrd eax, edx, cl
            shr edx, cl
            ret

        zero:
            xor edx, edx
            xor eax, eax
            ret
    }
}
extern "C" _declspec(naked) s64 _allshr(s64 a, u8 b)
{
    _asm
    {
        call _aullshr
        ret
    }
}

// Multiplications (TODO: Check signed multiplication)
extern "C" _declspec(naked) u64 _aullmul(u64 a, u64 b)
{
    /*
        ah: 20
        al: 16
        bh: 12
        bl: 8
    */

    _asm
    {
        push ebp
        mov ebp, esp
        push ebx

        // ah * bl
        mov eax, [ebp + 20]
        mov edx, [ebp + 8]
        mul edx
        mov ebx, eax

        // al * bh
        mov eax, [ebp + 12]
        mov edx, [ebp + 16]
        mul edx
        add ebx, eax

        // al * bl
        mov eax, [ebp + 8]
        mov edx, [ebp + 16]
        mul edx
        add edx, ebx

        pop ebx
        mov esp, ebp
        pop ebp

        ret 0x10
    }
}
extern "C" _declspec(naked) s64 _allmul(s64 a, s64 b)
{
    /*
        ah: 20
        al: 16
        bh: 12
        bl: 8
    */

    _asm
    {
        push ebp
        mov ebp, esp
        push ebx

        // ah * bl
        mov eax, [ebp + 20]
        mov edx, [ebp + 8]
        mul edx
        mov ebx, eax

        // al * bh
        mov eax, [ebp + 12]
        mov edx, [ebp + 16]
        mul edx
        add ebx, eax

        // al * bl
        mov eax, [ebp + 8]
        mov edx, [ebp + 16]
        mul edx
        add edx, ebx

        pop ebx
        mov esp, ebp
        pop ebp

        ret 0x10
    }
}

// Divisions (FIXME: _aulldiv, _allrem)
extern "C" u64 _aulldiv(u64 a, u64 b)
{
    u64 result;

    if ((b >> 32) == 0) 
    {
        /* Proof of correctness:

        Let n, d, c, n1, and n0 be defined as in this function.
        Let [x] be the "floor" of x.  Let T = b[a1/d].  Assume d
        nonzero.  Then:
        [a/b] = [a/b] - T + T
        = [a/b - T] + T                         by (1) below
        = [(c*a1 + a0)/b - T] + T               by definition of n
        = [(c*a1 + a0)/b - bT/c] + T
        = [(c(a1 - b[a1/b]) + a0)/c] + T
        = [(c[a1 % b] + a0)/b] + T,             by definition of %
        which is the expression calculated below.

        (1) Note that for any real x, integer i: [x] + i = [x + i].

        To prevent divl() from trapping, [(b[n1 % d] + n0)/d] must
        be less than b.  Assume that [n1 % d] and n0 take their
        respective maximum values of d - 1 and b - 1:
        [(b(d - 1) + (b - 1))/d] < b
        <=> [(bd - 1)/d] < b
        <=> [b - 1/d] < b
        which is a tautology.

        Therefore, this code is correct and will not trap. */

        u64 c = 1ULL << 32;
        u32 a1 = a >> 32;
        u32 a0 = a; 
        u32 b0 = b;

        u32 n = a1 % b0;
        u64 d = (u64)(a1 / b0) << 32;

        result = divl(n, a0, b0) + d;
    }
    else 
    {
        // Based on the algorithm and proof available from http://www.hackersdelight.org/revisions.pdf
        if (a < b)
            result = 0;
        else 
        {
            u32 b1 = b >> 32;
            int s = nlz(b1);

            u64 n = a >> 1;
            u32 n1 = n >> 32;
            u32 n0 = n;

            u64 q = divl(n1, n0, (b << s) >> 32) >> (31 - s);
            result = a - (q - 1) * b < b ? q - 1 : q; 
        }
    }

    _asm
    {
        mov	eax, [ebp - 0x30]
	    mov	edx, [ebp - 0x2C]

        mov	esp, ebp
	    pop	ebp
	    ret	0x10
    }

    return result;
}
extern "C" u64 _aullrem(u64 a, u64 b)
{
    u64 result = a - b * (a / b);

    _asm
    {
        mov	eax, [ebp - 8]
	    mov	edx, [ebp - 4]

        mov	esp, ebp
	    pop	ebp
	    ret	0x10
    }

    return result;
}
extern "C" s64 _alldiv(s64 a, s64 b)
{
    u64 _a = a >= 0 ? (u64)a : -(u64)a;
    u64 _b = b >= 0 ? (u64)b : -(u64)b;
    u64 _r = _a / _b;
    s64 result = (a < 0) == (b < 0) ? (s64)_r : -(s64)_r;

    _asm
    {
        mov	eax, [ebp - 0x40]
	    mov	edx, [ebp - 0x3C]

        mov	esp, ebp
	    pop	ebp
	    ret	0x10
    }

    return result;
}
extern "C" s64 _allrem(s64 a, s64 b)
{
    s64 result = a - b * (a / b);

    _asm
    {
        mov	eax, [ebp - 8]
	    mov	edx, [ebp - 4]

        mov	esp, ebp
	    pop	ebp
	    ret	0x10
    }

    return result;
}

// Optimizations



// Other
extern "C" long __declspec(naked) _ftol2_sse()
{
    int a;
    _asm
    {
        fistp [a]
        mov	ebx, a
        ret
    }
}
extern "C" long __declspec(naked) _ftol2()
{
    _asm
    {
        call _ftol2_sse
        ret
    }
}