/*
 * This file is part of the VanitySearch distribution (https://github.com/JeanLucPons/VanitySearch).
 * Copyright (c) 2019 Jean Luc PONS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// ---------------------------------------------------------------------------------
// SHA256
// ---------------------------------------------------------------------------------

__device__ __constant__ uint32_t K[] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
	0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
	0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
	0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
	0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
	0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
	0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
	0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
	0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
	0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
};

__device__ __constant__ uint32_t I[] = {
	0x6a09e667ul,
	0xbb67ae85ul,
	0x3c6ef372ul,
	0xa54ff53aul,
	0x510e527ful,
	0x9b05688cul,
	0x1f83d9abul,
	0x5be0cd19ul,
};

//#define ASSEMBLY_SIGMA
#ifdef ASSEMBLY_SIGMA

__device__ __forceinline__ uint32_t S0(uint32_t x)
{

	uint32_t y;
	asm("{\n\t"
		" .reg .u64 r1,r2,r3;\n\t"
		" cvt.u64.u32 r1, %1;\n\t"
		" mov.u64 r2, r1;\n\t"
		" shl.b64 r2, r2,32;\n\t"
		" or.b64  r1, r1,r2;\n\t"
		" shr.b64 r3, r1, 2;\n\t"
		" mov.u64 r2, r3;\n\t"
		" shr.b64 r3, r1, 13;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" shr.b64 r3, r1, 22;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" cvt.u32.u64 %0,r2;\n\t"
		"}\n\t"
		: "=r"(y) : "r"(x));
	return y;

}

__device__ __forceinline__ uint32_t S1(uint32_t x)
{

	uint32_t y;
	asm("{\n\t"
		" .reg .u64 r1,r2,r3;\n\t"
		" cvt.u64.u32 r1, %1;\n\t"
		" mov.u64 r2, r1;\n\t"
		" shl.b64 r2, r2,32;\n\t"
		" or.b64  r1, r1,r2;\n\t"
		" shr.b64 r3, r1, 6;\n\t"
		" mov.u64 r2, r3;\n\t"
		" shr.b64 r3, r1, 11;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" shr.b64 r3, r1, 25;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" cvt.u32.u64 %0,r2;\n\t"
		"}\n\t"
		: "=r"(y) : "r"(x));
	return y;

}

__device__ __forceinline__ uint32_t s0(uint32_t x)
{

	uint32_t y;
	asm("{\n\t"
		" .reg .u64 r1,r2,r3;\n\t"
		" cvt.u64.u32 r1, %1;\n\t"
		" mov.u64 r2, r1;\n\t"
		" shl.b64 r2, r2,32;\n\t"
		" or.b64  r1, r1,r2;\n\t"
		" shr.b64 r2, r2, 35;\n\t"
		" shr.b64 r3, r1, 18;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" shr.b64 r3, r1, 7;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" cvt.u32.u64 %0,r2;\n\t"
		"}\n\t"
		: "=r"(y) : "r"(x));
	return y;

}

__device__ __forceinline__ uint32_t s1(uint32_t x)
{

	uint32_t y;
	asm("{\n\t"
		" .reg .u64 r1,r2,r3;\n\t"
		" cvt.u64.u32 r1, %1;\n\t"
		" mov.u64 r2, r1;\n\t"
		" shl.b64 r2, r2,32;\n\t"
		" or.b64  r1, r1,r2;\n\t"
		" shr.b64 r2, r2, 42;\n\t"
		" shr.b64 r3, r1, 19;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" shr.b64 r3, r1, 17;\n\t"
		" xor.b64 r2, r2, r3;\n\t"
		" cvt.u32.u64 %0,r2;\n\t"
		"}\n\t"
		: "=r"(y) : "r"(x));
	return y;

}

#else

#define ROR(x,n) ((x>>n)|(x<<(32-n)))
#define S0(x) (ROR(x,2) ^ ROR(x,13) ^ ROR(x,22))
#define S1(x) (ROR(x,6) ^ ROR(x,11) ^ ROR(x,25))
#define s0(x) (ROR(x,7) ^ ROR(x,18) ^ (x >> 3))
#define s1(x) (ROR(x,17) ^ ROR(x,19) ^ (x >> 10))

#endif

//#define Maj(x,y,z) ((x&y)^(x&z)^(y&z))
//#define Ch(x,y,z)  ((x&y)^(~x&z))

// The following functions are equivalent to the above
#define Maj(x,y,z) ((x & y) | (z & (x | y)))
#define Ch(x,y,z) (z ^ (x & (y ^ z)))

// SHA-256 inner round
#define S2Round(a, b, c, d, e, f, g, h, k, w) \
    t1 = h + S1(e) + Ch(e,f,g) + k + (w); \
    t2 = S0(a) + Maj(a,b,c); \
    d += t1; \
    h = t1 + t2;

// WMIX
#define WMIX() { \
w[0] += s1(w[14]) + w[9] + s0(w[1]);\
w[1] += s1(w[15]) + w[10] + s0(w[2]);\
w[2] += s1(w[0]) + w[11] + s0(w[3]);\
w[3] += s1(w[1]) + w[12] + s0(w[4]);\
w[4] += s1(w[2]) + w[13] + s0(w[5]);\
w[5] += s1(w[3]) + w[14] + s0(w[6]);\
w[6] += s1(w[4]) + w[15] + s0(w[7]);\
w[7] += s1(w[5]) + w[0] + s0(w[8]);\
w[8] += s1(w[6]) + w[1] + s0(w[9]);\
w[9] += s1(w[7]) + w[2] + s0(w[10]);\
w[10] += s1(w[8]) + w[3] + s0(w[11]);\
w[11] += s1(w[9]) + w[4] + s0(w[12]);\
w[12] += s1(w[10]) + w[5] + s0(w[13]);\
w[13] += s1(w[11]) + w[6] + s0(w[14]);\
w[14] += s1(w[12]) + w[7] + s0(w[15]);\
w[15] += s1(w[13]) + w[8] + s0(w[0]);\
}

// ROUND
#define SHA256_RND(k) {\
S2Round(a, b, c, d, e, f, g, h, K[k], w[0]);\
S2Round(h, a, b, c, d, e, f, g, K[k + 1], w[1]);\
S2Round(g, h, a, b, c, d, e, f, K[k + 2], w[2]);\
S2Round(f, g, h, a, b, c, d, e, K[k + 3], w[3]);\
S2Round(e, f, g, h, a, b, c, d, K[k + 4], w[4]);\
S2Round(d, e, f, g, h, a, b, c, K[k + 5], w[5]);\
S2Round(c, d, e, f, g, h, a, b, K[k + 6], w[6]);\
S2Round(b, c, d, e, f, g, h, a, K[k + 7], w[7]);\
S2Round(a, b, c, d, e, f, g, h, K[k + 8], w[8]);\
S2Round(h, a, b, c, d, e, f, g, K[k + 9], w[9]);\
S2Round(g, h, a, b, c, d, e, f, K[k + 10], w[10]);\
S2Round(f, g, h, a, b, c, d, e, K[k + 11], w[11]);\
S2Round(e, f, g, h, a, b, c, d, K[k + 12], w[12]);\
S2Round(d, e, f, g, h, a, b, c, K[k + 13], w[13]);\
S2Round(c, d, e, f, g, h, a, b, K[k + 14], w[14]);\
S2Round(b, c, d, e, f, g, h, a, K[k + 15], w[15]);\
}

#define bswap32(v) __byte_perm(v, 0, 0x0123)

// Initialise state
__device__ void SHA256Initialize(uint32_t s[8])
{
#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = I[i];
}

#define DEF(x,y) uint32_t x = s[y]

// Perform SHA-256 transformations, process 64-byte chunks
__device__ void SHA256Transform(uint32_t s[8], uint32_t* w)
{

	uint32_t t1;
	uint32_t t2;

	DEF(a, 0);
	DEF(b, 1);
	DEF(c, 2);
	DEF(d, 3);
	DEF(e, 4);
	DEF(f, 5);
	DEF(g, 6);
	DEF(h, 7);

	SHA256_RND(0);
	WMIX();
	SHA256_RND(16);
	WMIX();
	SHA256_RND(32);
	WMIX();
	SHA256_RND(48);

	s[0] += a;
	s[1] += b;
	s[2] += c;
	s[3] += d;
	s[4] += e;
	s[5] += f;
	s[6] += g;
	s[7] += h;

}


// ---------------------------------------------------------------------------------
// RIPEMD160
// ---------------------------------------------------------------------------------
__device__ __constant__ uint64_t ripemd160_sizedesc_32 = 32 << 3;

__device__ void RIPEMD160Initialize(uint32_t s[5])
{

	s[0] = 0x67452301ul;
	s[1] = 0xEFCDAB89ul;
	s[2] = 0x98BADCFEul;
	s[3] = 0x10325476ul;
	s[4] = 0xC3D2E1F0ul;

}

#define ROL(x,n) ((x>>(32-n))|(x<<n))
#define f1(x, y, z) (x ^ y ^ z)
#define f2(x, y, z) ((x & y) | (~x & z))
#define f3(x, y, z) ((x | ~y) ^ z)
#define f4(x, y, z) ((x & z) | (~z & y))
#define f5(x, y, z) (x ^ (y | ~z))

#define RPRound(a,b,c,d,e,f,x,k,r) \
  u = a + f + x + k; \
  a = ROL(u, r) + e; \
  c = ROL(c, 10);

#define R11(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f1(b, c, d), x, 0, r)
#define R21(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f2(b, c, d), x, 0x5A827999ul, r)
#define R31(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f3(b, c, d), x, 0x6ED9EBA1ul, r)
#define R41(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f4(b, c, d), x, 0x8F1BBCDCul, r)
#define R51(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f5(b, c, d), x, 0xA953FD4Eul, r)
#define R12(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f5(b, c, d), x, 0x50A28BE6ul, r)
#define R22(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f4(b, c, d), x, 0x5C4DD124ul, r)
#define R32(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f3(b, c, d), x, 0x6D703EF3ul, r)
#define R42(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f2(b, c, d), x, 0x7A6D76E9ul, r)
#define R52(a,b,c,d,e,x,r) RPRound(a, b, c, d, e, f1(b, c, d), x, 0, r)

/** Perform a RIPEMD-160 transformation, processing a 64-byte chunk. */
__device__ void RIPEMD160Transform(uint32_t s[5], uint32_t* w)
{

	uint32_t u;
	uint32_t a1 = s[0], b1 = s[1], c1 = s[2], d1 = s[3], e1 = s[4];
	uint32_t a2 = a1, b2 = b1, c2 = c1, d2 = d1, e2 = e1;

	R11(a1, b1, c1, d1, e1, w[0], 11);
	R12(a2, b2, c2, d2, e2, w[5], 8);
	R11(e1, a1, b1, c1, d1, w[1], 14);
	R12(e2, a2, b2, c2, d2, w[14], 9);
	R11(d1, e1, a1, b1, c1, w[2], 15);
	R12(d2, e2, a2, b2, c2, w[7], 9);
	R11(c1, d1, e1, a1, b1, w[3], 12);
	R12(c2, d2, e2, a2, b2, w[0], 11);
	R11(b1, c1, d1, e1, a1, w[4], 5);
	R12(b2, c2, d2, e2, a2, w[9], 13);
	R11(a1, b1, c1, d1, e1, w[5], 8);
	R12(a2, b2, c2, d2, e2, w[2], 15);
	R11(e1, a1, b1, c1, d1, w[6], 7);
	R12(e2, a2, b2, c2, d2, w[11], 15);
	R11(d1, e1, a1, b1, c1, w[7], 9);
	R12(d2, e2, a2, b2, c2, w[4], 5);
	R11(c1, d1, e1, a1, b1, w[8], 11);
	R12(c2, d2, e2, a2, b2, w[13], 7);
	R11(b1, c1, d1, e1, a1, w[9], 13);
	R12(b2, c2, d2, e2, a2, w[6], 7);
	R11(a1, b1, c1, d1, e1, w[10], 14);
	R12(a2, b2, c2, d2, e2, w[15], 8);
	R11(e1, a1, b1, c1, d1, w[11], 15);
	R12(e2, a2, b2, c2, d2, w[8], 11);
	R11(d1, e1, a1, b1, c1, w[12], 6);
	R12(d2, e2, a2, b2, c2, w[1], 14);
	R11(c1, d1, e1, a1, b1, w[13], 7);
	R12(c2, d2, e2, a2, b2, w[10], 14);
	R11(b1, c1, d1, e1, a1, w[14], 9);
	R12(b2, c2, d2, e2, a2, w[3], 12);
	R11(a1, b1, c1, d1, e1, w[15], 8);
	R12(a2, b2, c2, d2, e2, w[12], 6);

	R21(e1, a1, b1, c1, d1, w[7], 7);
	R22(e2, a2, b2, c2, d2, w[6], 9);
	R21(d1, e1, a1, b1, c1, w[4], 6);
	R22(d2, e2, a2, b2, c2, w[11], 13);
	R21(c1, d1, e1, a1, b1, w[13], 8);
	R22(c2, d2, e2, a2, b2, w[3], 15);
	R21(b1, c1, d1, e1, a1, w[1], 13);
	R22(b2, c2, d2, e2, a2, w[7], 7);
	R21(a1, b1, c1, d1, e1, w[10], 11);
	R22(a2, b2, c2, d2, e2, w[0], 12);
	R21(e1, a1, b1, c1, d1, w[6], 9);
	R22(e2, a2, b2, c2, d2, w[13], 8);
	R21(d1, e1, a1, b1, c1, w[15], 7);
	R22(d2, e2, a2, b2, c2, w[5], 9);
	R21(c1, d1, e1, a1, b1, w[3], 15);
	R22(c2, d2, e2, a2, b2, w[10], 11);
	R21(b1, c1, d1, e1, a1, w[12], 7);
	R22(b2, c2, d2, e2, a2, w[14], 7);
	R21(a1, b1, c1, d1, e1, w[0], 12);
	R22(a2, b2, c2, d2, e2, w[15], 7);
	R21(e1, a1, b1, c1, d1, w[9], 15);
	R22(e2, a2, b2, c2, d2, w[8], 12);
	R21(d1, e1, a1, b1, c1, w[5], 9);
	R22(d2, e2, a2, b2, c2, w[12], 7);
	R21(c1, d1, e1, a1, b1, w[2], 11);
	R22(c2, d2, e2, a2, b2, w[4], 6);
	R21(b1, c1, d1, e1, a1, w[14], 7);
	R22(b2, c2, d2, e2, a2, w[9], 15);
	R21(a1, b1, c1, d1, e1, w[11], 13);
	R22(a2, b2, c2, d2, e2, w[1], 13);
	R21(e1, a1, b1, c1, d1, w[8], 12);
	R22(e2, a2, b2, c2, d2, w[2], 11);

	R31(d1, e1, a1, b1, c1, w[3], 11);
	R32(d2, e2, a2, b2, c2, w[15], 9);
	R31(c1, d1, e1, a1, b1, w[10], 13);
	R32(c2, d2, e2, a2, b2, w[5], 7);
	R31(b1, c1, d1, e1, a1, w[14], 6);
	R32(b2, c2, d2, e2, a2, w[1], 15);
	R31(a1, b1, c1, d1, e1, w[4], 7);
	R32(a2, b2, c2, d2, e2, w[3], 11);
	R31(e1, a1, b1, c1, d1, w[9], 14);
	R32(e2, a2, b2, c2, d2, w[7], 8);
	R31(d1, e1, a1, b1, c1, w[15], 9);
	R32(d2, e2, a2, b2, c2, w[14], 6);
	R31(c1, d1, e1, a1, b1, w[8], 13);
	R32(c2, d2, e2, a2, b2, w[6], 6);
	R31(b1, c1, d1, e1, a1, w[1], 15);
	R32(b2, c2, d2, e2, a2, w[9], 14);
	R31(a1, b1, c1, d1, e1, w[2], 14);
	R32(a2, b2, c2, d2, e2, w[11], 12);
	R31(e1, a1, b1, c1, d1, w[7], 8);
	R32(e2, a2, b2, c2, d2, w[8], 13);
	R31(d1, e1, a1, b1, c1, w[0], 13);
	R32(d2, e2, a2, b2, c2, w[12], 5);
	R31(c1, d1, e1, a1, b1, w[6], 6);
	R32(c2, d2, e2, a2, b2, w[2], 14);
	R31(b1, c1, d1, e1, a1, w[13], 5);
	R32(b2, c2, d2, e2, a2, w[10], 13);
	R31(a1, b1, c1, d1, e1, w[11], 12);
	R32(a2, b2, c2, d2, e2, w[0], 13);
	R31(e1, a1, b1, c1, d1, w[5], 7);
	R32(e2, a2, b2, c2, d2, w[4], 7);
	R31(d1, e1, a1, b1, c1, w[12], 5);
	R32(d2, e2, a2, b2, c2, w[13], 5);

	R41(c1, d1, e1, a1, b1, w[1], 11);
	R42(c2, d2, e2, a2, b2, w[8], 15);
	R41(b1, c1, d1, e1, a1, w[9], 12);
	R42(b2, c2, d2, e2, a2, w[6], 5);
	R41(a1, b1, c1, d1, e1, w[11], 14);
	R42(a2, b2, c2, d2, e2, w[4], 8);
	R41(e1, a1, b1, c1, d1, w[10], 15);
	R42(e2, a2, b2, c2, d2, w[1], 11);
	R41(d1, e1, a1, b1, c1, w[0], 14);
	R42(d2, e2, a2, b2, c2, w[3], 14);
	R41(c1, d1, e1, a1, b1, w[8], 15);
	R42(c2, d2, e2, a2, b2, w[11], 14);
	R41(b1, c1, d1, e1, a1, w[12], 9);
	R42(b2, c2, d2, e2, a2, w[15], 6);
	R41(a1, b1, c1, d1, e1, w[4], 8);
	R42(a2, b2, c2, d2, e2, w[0], 14);
	R41(e1, a1, b1, c1, d1, w[13], 9);
	R42(e2, a2, b2, c2, d2, w[5], 6);
	R41(d1, e1, a1, b1, c1, w[3], 14);
	R42(d2, e2, a2, b2, c2, w[12], 9);
	R41(c1, d1, e1, a1, b1, w[7], 5);
	R42(c2, d2, e2, a2, b2, w[2], 12);
	R41(b1, c1, d1, e1, a1, w[15], 6);
	R42(b2, c2, d2, e2, a2, w[13], 9);
	R41(a1, b1, c1, d1, e1, w[14], 8);
	R42(a2, b2, c2, d2, e2, w[9], 12);
	R41(e1, a1, b1, c1, d1, w[5], 6);
	R42(e2, a2, b2, c2, d2, w[7], 5);
	R41(d1, e1, a1, b1, c1, w[6], 5);
	R42(d2, e2, a2, b2, c2, w[10], 15);
	R41(c1, d1, e1, a1, b1, w[2], 12);
	R42(c2, d2, e2, a2, b2, w[14], 8);

	R51(b1, c1, d1, e1, a1, w[4], 9);
	R52(b2, c2, d2, e2, a2, w[12], 8);
	R51(a1, b1, c1, d1, e1, w[0], 15);
	R52(a2, b2, c2, d2, e2, w[15], 5);
	R51(e1, a1, b1, c1, d1, w[5], 5);
	R52(e2, a2, b2, c2, d2, w[10], 12);
	R51(d1, e1, a1, b1, c1, w[9], 11);
	R52(d2, e2, a2, b2, c2, w[4], 9);
	R51(c1, d1, e1, a1, b1, w[7], 6);
	R52(c2, d2, e2, a2, b2, w[1], 12);
	R51(b1, c1, d1, e1, a1, w[12], 8);
	R52(b2, c2, d2, e2, a2, w[5], 5);
	R51(a1, b1, c1, d1, e1, w[2], 13);
	R52(a2, b2, c2, d2, e2, w[8], 14);
	R51(e1, a1, b1, c1, d1, w[10], 12);
	R52(e2, a2, b2, c2, d2, w[7], 6);
	R51(d1, e1, a1, b1, c1, w[14], 5);
	R52(d2, e2, a2, b2, c2, w[6], 8);
	R51(c1, d1, e1, a1, b1, w[1], 12);
	R52(c2, d2, e2, a2, b2, w[2], 13);
	R51(b1, c1, d1, e1, a1, w[3], 13);
	R52(b2, c2, d2, e2, a2, w[13], 6);
	R51(a1, b1, c1, d1, e1, w[8], 14);
	R52(a2, b2, c2, d2, e2, w[14], 5);
	R51(e1, a1, b1, c1, d1, w[11], 11);
	R52(e2, a2, b2, c2, d2, w[0], 15);
	R51(d1, e1, a1, b1, c1, w[6], 8);
	R52(d2, e2, a2, b2, c2, w[3], 13);
	R51(c1, d1, e1, a1, b1, w[15], 5);
	R52(c2, d2, e2, a2, b2, w[9], 11);
	R51(b1, c1, d1, e1, a1, w[13], 6);
	R52(b2, c2, d2, e2, a2, w[11], 11);

	uint32_t t = s[0];
	s[0] = s[1] + c1 + d2;
	s[1] = s[2] + d1 + e2;
	s[2] = s[3] + e1 + a2;
	s[3] = s[4] + a1 + b2;
	s[4] = t + b1 + c2;
}

// ---------------------------------------------------------------------------------
// Key encoding
// ---------------------------------------------------------------------------------

__device__ __noinline__ void _GetHash160Comp(uint64_t* x, uint8_t isOdd, uint8_t* hash)
{

	uint32_t* x32 = (uint32_t*)(x);
	uint32_t publicKeyBytes[16];
	uint32_t s[16];

	// Compressed public key
	publicKeyBytes[0] = __byte_perm(x32[7], 0x2 + isOdd, 0x4321);
	publicKeyBytes[1] = __byte_perm(x32[7], x32[6], 0x0765);
	publicKeyBytes[2] = __byte_perm(x32[6], x32[5], 0x0765);
	publicKeyBytes[3] = __byte_perm(x32[5], x32[4], 0x0765);
	publicKeyBytes[4] = __byte_perm(x32[4], x32[3], 0x0765);
	publicKeyBytes[5] = __byte_perm(x32[3], x32[2], 0x0765);
	publicKeyBytes[6] = __byte_perm(x32[2], x32[1], 0x0765);
	publicKeyBytes[7] = __byte_perm(x32[1], x32[0], 0x0765);
	publicKeyBytes[8] = __byte_perm(x32[0], 0x80, 0x0456);
	publicKeyBytes[9] = 0;
	publicKeyBytes[10] = 0;
	publicKeyBytes[11] = 0;
	publicKeyBytes[12] = 0;
	publicKeyBytes[13] = 0;
	publicKeyBytes[14] = 0;
	publicKeyBytes[15] = 0x108;

	SHA256Initialize(s);
	SHA256Transform(s, publicKeyBytes);

#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = bswap32(s[i]);

	*(uint64_t*)(s + 8) = 0x80ULL;
	*(uint64_t*)(s + 10) = 0ULL;
	*(uint64_t*)(s + 12) = 0ULL;
	*(uint64_t*)(s + 14) = ripemd160_sizedesc_32;

	RIPEMD160Initialize((uint32_t*)hash);
	RIPEMD160Transform((uint32_t*)hash, s);

}

__device__ __noinline__ void _GetHash160CompSym(uint64_t* x, uint8_t* h1, uint8_t* h2)
{

	uint32_t* x32 = (uint32_t*)(x);
	uint32_t publicKeyBytes[16];
	uint32_t publicKeyBytes2[16];
	uint32_t s[16];

	// Compressed public key

	// Even
	publicKeyBytes[0] = __byte_perm(x32[7], 0x2, 0x4321);
	publicKeyBytes[1] = __byte_perm(x32[7], x32[6], 0x0765);
	publicKeyBytes[2] = __byte_perm(x32[6], x32[5], 0x0765);
	publicKeyBytes[3] = __byte_perm(x32[5], x32[4], 0x0765);
	publicKeyBytes[4] = __byte_perm(x32[4], x32[3], 0x0765);
	publicKeyBytes[5] = __byte_perm(x32[3], x32[2], 0x0765);
	publicKeyBytes[6] = __byte_perm(x32[2], x32[1], 0x0765);
	publicKeyBytes[7] = __byte_perm(x32[1], x32[0], 0x0765);
	publicKeyBytes[8] = __byte_perm(x32[0], 0x80, 0x0456);
	publicKeyBytes[9] = 0;
	publicKeyBytes[10] = 0;
	publicKeyBytes[11] = 0;
	publicKeyBytes[12] = 0;
	publicKeyBytes[13] = 0;
	publicKeyBytes[14] = 0;
	publicKeyBytes[15] = 0x108;

	// Odd
	publicKeyBytes2[0] = __byte_perm(x32[7], 0x3, 0x4321);
	publicKeyBytes2[1] = publicKeyBytes[1];
	*(uint64_t*)(&publicKeyBytes2[2]) = *(uint64_t*)(&publicKeyBytes[2]);
	*(uint64_t*)(&publicKeyBytes2[4]) = *(uint64_t*)(&publicKeyBytes[4]);
	*(uint64_t*)(&publicKeyBytes2[6]) = *(uint64_t*)(&publicKeyBytes[6]);
	*(uint64_t*)(&publicKeyBytes2[8]) = *(uint64_t*)(&publicKeyBytes[8]);
	*(uint64_t*)(&publicKeyBytes2[10]) = *(uint64_t*)(&publicKeyBytes[10]);
	*(uint64_t*)(&publicKeyBytes2[12]) = *(uint64_t*)(&publicKeyBytes[12]);
	*(uint64_t*)(&publicKeyBytes2[14]) = *(uint64_t*)(&publicKeyBytes[14]);

	SHA256Initialize(s);
	SHA256Transform(s, publicKeyBytes);

#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = bswap32(s[i]);

	*(uint64_t*)(s + 8) = 0x80ULL;
	*(uint64_t*)(s + 10) = 0ULL;
	*(uint64_t*)(s + 12) = 0ULL;
	*(uint64_t*)(s + 14) = ripemd160_sizedesc_32;

	RIPEMD160Initialize((uint32_t*)h1);
	RIPEMD160Transform((uint32_t*)h1, s);

	SHA256Initialize(s);
	SHA256Transform(s, publicKeyBytes2);

#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = bswap32(s[i]);

	RIPEMD160Initialize((uint32_t*)h2);
	RIPEMD160Transform((uint32_t*)h2, s);

}

__device__ __noinline__ void _GetHash160(uint64_t* x, uint64_t* y, uint8_t* hash)
{

	uint32_t* x32 = (uint32_t*)(x);
	uint32_t* y32 = (uint32_t*)(y);
	uint32_t publicKeyBytes[32];
	uint32_t s[16];

	// Uncompressed public key
	publicKeyBytes[0] = __byte_perm(x32[7], 0x04, 0x4321);
	publicKeyBytes[1] = __byte_perm(x32[7], x32[6], 0x0765);
	publicKeyBytes[2] = __byte_perm(x32[6], x32[5], 0x0765);
	publicKeyBytes[3] = __byte_perm(x32[5], x32[4], 0x0765);
	publicKeyBytes[4] = __byte_perm(x32[4], x32[3], 0x0765);
	publicKeyBytes[5] = __byte_perm(x32[3], x32[2], 0x0765);
	publicKeyBytes[6] = __byte_perm(x32[2], x32[1], 0x0765);
	publicKeyBytes[7] = __byte_perm(x32[1], x32[0], 0x0765);
	publicKeyBytes[8] = __byte_perm(x32[0], y32[7], 0x0765);
	publicKeyBytes[9] = __byte_perm(y32[7], y32[6], 0x0765);
	publicKeyBytes[10] = __byte_perm(y32[6], y32[5], 0x0765);
	publicKeyBytes[11] = __byte_perm(y32[5], y32[4], 0x0765);
	publicKeyBytes[12] = __byte_perm(y32[4], y32[3], 0x0765);
	publicKeyBytes[13] = __byte_perm(y32[3], y32[2], 0x0765);
	publicKeyBytes[14] = __byte_perm(y32[2], y32[1], 0x0765);
	publicKeyBytes[15] = __byte_perm(y32[1], y32[0], 0x0765);
	publicKeyBytes[16] = __byte_perm(y32[0], 0x80, 0x0456);
	publicKeyBytes[17] = 0;
	publicKeyBytes[18] = 0;
	publicKeyBytes[19] = 0;
	publicKeyBytes[20] = 0;
	publicKeyBytes[21] = 0;
	publicKeyBytes[22] = 0;
	publicKeyBytes[23] = 0;
	publicKeyBytes[24] = 0;
	publicKeyBytes[25] = 0;
	publicKeyBytes[26] = 0;
	publicKeyBytes[27] = 0;
	publicKeyBytes[28] = 0;
	publicKeyBytes[29] = 0;
	publicKeyBytes[30] = 0;
	publicKeyBytes[31] = 0x208;

	SHA256Initialize(s);
	SHA256Transform(s, publicKeyBytes);
	SHA256Transform(s, publicKeyBytes + 16);

#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = bswap32(s[i]);

	*(uint64_t*)(s + 8) = 0x80ULL;
	*(uint64_t*)(s + 10) = 0ULL;
	*(uint64_t*)(s + 12) = 0ULL;
	*(uint64_t*)(s + 14) = ripemd160_sizedesc_32;

	RIPEMD160Initialize((uint32_t*)hash);
	RIPEMD160Transform((uint32_t*)hash, s);

}

__device__ __noinline__ void _GetHash160P2SHComp(uint64_t* x, uint8_t isOdd, uint8_t* hash)
{

	uint32_t h[5];
	uint32_t scriptBytes[16];
	uint32_t s[16];
	_GetHash160Comp(x, isOdd, (uint8_t*)h);

	// P2SH script script
	scriptBytes[0] = __byte_perm(h[0], 0x14, 0x5401);
	scriptBytes[1] = __byte_perm(h[0], h[1], 0x2345);
	scriptBytes[2] = __byte_perm(h[1], h[2], 0x2345);
	scriptBytes[3] = __byte_perm(h[2], h[3], 0x2345);
	scriptBytes[4] = __byte_perm(h[3], h[4], 0x2345);
	scriptBytes[5] = __byte_perm(h[4], 0x80, 0x2345);
	scriptBytes[6] = 0;
	scriptBytes[7] = 0;
	scriptBytes[8] = 0;
	scriptBytes[9] = 0;
	scriptBytes[10] = 0;
	scriptBytes[11] = 0;
	scriptBytes[12] = 0;
	scriptBytes[13] = 0;
	scriptBytes[14] = 0;
	scriptBytes[15] = 0xB0;

	SHA256Initialize(s);
	SHA256Transform(s, scriptBytes);

#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = bswap32(s[i]);

	*(uint64_t*)(s + 8) = 0x80ULL;
	*(uint64_t*)(s + 10) = 0ULL;
	*(uint64_t*)(s + 12) = 0ULL;
	*(uint64_t*)(s + 14) = ripemd160_sizedesc_32;

	RIPEMD160Initialize((uint32_t*)hash);
	RIPEMD160Transform((uint32_t*)hash, s);

}

__device__ __noinline__ void _GetHash160P2SHUncomp(uint64_t* x, uint64_t* y, uint8_t* hash)
{

	uint32_t h[5];
	uint32_t scriptBytes[16];
	uint32_t s[16];
	_GetHash160(x, y, (uint8_t*)h);

	// P2SH script script
	scriptBytes[0] = __byte_perm(h[0], 0x14, 0x5401);
	scriptBytes[1] = __byte_perm(h[0], h[1], 0x2345);
	scriptBytes[2] = __byte_perm(h[1], h[2], 0x2345);
	scriptBytes[3] = __byte_perm(h[2], h[3], 0x2345);
	scriptBytes[4] = __byte_perm(h[3], h[4], 0x2345);
	scriptBytes[5] = __byte_perm(h[4], 0x80, 0x2345);
	scriptBytes[6] = 0;
	scriptBytes[7] = 0;
	scriptBytes[8] = 0;
	scriptBytes[9] = 0;
	scriptBytes[10] = 0;
	scriptBytes[11] = 0;
	scriptBytes[12] = 0;
	scriptBytes[13] = 0;
	scriptBytes[14] = 0;
	scriptBytes[15] = 0xB0;

	SHA256Initialize(s);
	SHA256Transform(s, scriptBytes);

#pragma unroll 8
	for (int i = 0; i < 8; i++)
		s[i] = bswap32(s[i]);

	*(uint64_t*)(s + 8) = 0x80ULL;
	*(uint64_t*)(s + 10) = 0ULL;
	*(uint64_t*)(s + 12) = 0ULL;
	*(uint64_t*)(s + 14) = ripemd160_sizedesc_32;

	RIPEMD160Initialize((uint32_t*)hash);
	RIPEMD160Transform((uint32_t*)hash, s);

}




// ---------------------------------------------------------------------------------
// KECCAK/SHA3
// ---------------------------------------------------------------------------------


typedef union {
	uint8_t b[200];
	uint64_t q[25];
	uint32_t d[50];
} _KECCAK_STATE;

__device__ __constant__ uint64_t _KECCAKF_RNDC[24] = {
	0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL,
	0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL,
	0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL,
	0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
	0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL,
	0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
	0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL,
	0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

#define ROTL64(a,b) (((a) << (b)) | ((a) >> (64 - b)))

__device__ __noinline__ void _GetHashKeccak160(const uint64_t* __restrict__ x, const uint64_t* __restrict__ y, uint32_t* __restrict__ hash)
{
	_KECCAK_STATE e = { 0 };
	const uint2* X = (const uint2*)x;
	const uint2* Y = (const uint2*)y;

	// Оптимизированная загрузка с байт-свопом
	e.d[0] = __byte_perm(X[3].y, 0, 0x0123);
	e.d[1] = __byte_perm(X[3].x, 0, 0x0123);
	e.d[2] = __byte_perm(X[2].y, 0, 0x0123);
	e.d[3] = __byte_perm(X[2].x, 0, 0x0123);
	e.d[4] = __byte_perm(X[1].y, 0, 0x0123);
	e.d[5] = __byte_perm(X[1].x, 0, 0x0123);
	e.d[6] = __byte_perm(X[0].y, 0, 0x0123);
	e.d[7] = __byte_perm(X[0].x, 0, 0x0123);
	e.d[8] = __byte_perm(Y[3].y, 0, 0x0123);
	e.d[9] = __byte_perm(Y[3].x, 0, 0x0123);
	e.d[10] = __byte_perm(Y[2].y, 0, 0x0123);
	e.d[11] = __byte_perm(Y[2].x, 0, 0x0123);
	e.d[12] = __byte_perm(Y[1].y, 0, 0x0123);
	e.d[13] = __byte_perm(Y[1].x, 0, 0x0123);
	e.d[14] = __byte_perm(Y[0].y, 0, 0x0123);
	e.d[15] = __byte_perm(Y[0].x, 0, 0x0123);

	uint64_t* s = e.q;
	e.d[16] ^= 0x01;
	e.d[33] ^= 0x80000000;

	// Инициализация локальных переменных
	uint64_t s0 = s[0], s1 = s[1], s2 = s[2], s3 = s[3], s4 = s[4];
	uint64_t s5 = s[5], s6 = s[6], s7 = s[7], s8 = s[8], s9 = s[9];
	uint64_t s10 = s[10], s11 = s[11], s12 = s[12], s13 = s[13], s14 = s[14];
	uint64_t s15 = s[15], s16 = s[16], s17 = s[17], s18 = s[18], s19 = s[19];
	uint64_t s20 = s[20], s21 = s[21], s22 = s[22], s23 = s[23], s24 = s[24];

#pragma unroll
	for (int i = 0; i < 24; i++) {
		// theta
		uint64_t t0 = s0 ^ s5 ^ s10 ^ s15 ^ s20;
		uint64_t t1 = s1 ^ s6 ^ s11 ^ s16 ^ s21;
		uint64_t t2 = s2 ^ s7 ^ s12 ^ s17 ^ s22;
		uint64_t t3 = s3 ^ s8 ^ s13 ^ s18 ^ s23;
		uint64_t t4 = s4 ^ s9 ^ s14 ^ s19 ^ s24;

		uint64_t u0 = t4 ^ ROTL64(t1, 1);
		uint64_t u1 = t0 ^ ROTL64(t2, 1);
		uint64_t u2 = t1 ^ ROTL64(t3, 1);
		uint64_t u3 = t2 ^ ROTL64(t4, 1);
		uint64_t u4 = t3 ^ ROTL64(t0, 1);

		s0 ^= u0; s5 ^= u0; s10 ^= u0; s15 ^= u0; s20 ^= u0;
		s1 ^= u1; s6 ^= u1; s11 ^= u1; s16 ^= u1; s21 ^= u1;
		s2 ^= u2; s7 ^= u2; s12 ^= u2; s17 ^= u2; s22 ^= u2;
		s3 ^= u3; s8 ^= u3; s13 ^= u3; s18 ^= u3; s23 ^= u3;
		s4 ^= u4; s9 ^= u4; s14 ^= u4; s19 ^= u4; s24 ^= u4;

		// rho pi
		uint64_t v = s1;
		uint64_t w;
		s1 = ROTL64(s6, 44);
		s6 = ROTL64(s9, 20);
		s9 = ROTL64(s22, 61);
		s22 = ROTL64(s14, 39);
		s14 = ROTL64(s20, 18);
		s20 = ROTL64(s2, 62);
		s2 = ROTL64(s12, 43);
		s12 = ROTL64(s13, 25);
		s13 = ROTL64(s19, 8);
		s19 = ROTL64(s23, 56);
		s23 = ROTL64(s15, 41);
		s15 = ROTL64(s4, 27);
		s4 = ROTL64(s24, 14);
		s24 = ROTL64(s21, 2);
		s21 = ROTL64(s8, 55);
		s8 = ROTL64(s16, 45);
		s16 = ROTL64(s5, 36);
		s5 = ROTL64(s3, 28);
		s3 = ROTL64(s18, 21);
		s18 = ROTL64(s17, 15);
		s17 = ROTL64(s11, 10);
		s11 = ROTL64(s7, 6);
		s7 = ROTL64(s10, 3);
		s10 = ROTL64(v, 1);

		// chi
		v = s0; w = s1; s0 ^= (~w) & s2; s1 ^= (~s2) & s3; s2 ^= (~s3) & s4; s3 ^= (~s4) & v; s4 ^= (~v) & w;
		v = s5; w = s6; s5 ^= (~w) & s7; s6 ^= (~s7) & s8; s7 ^= (~s8) & s9; s8 ^= (~s9) & v; s9 ^= (~v) & w;
		v = s10; w = s11; s10 ^= (~w) & s12; s11 ^= (~s12) & s13; s12 ^= (~s13) & s14; s13 ^= (~s14) & v; s14 ^= (~v) & w;
		v = s15; w = s16; s15 ^= (~w) & s17; s16 ^= (~s17) & s18; s17 ^= (~s18) & s19; s18 ^= (~s19) & v; s19 ^= (~v) & w;
		v = s20; w = s21; s20 ^= (~w) & s22; s21 ^= (~s22) & s23; s22 ^= (~s23) & s24; s23 ^= (~s24) & v; s24 ^= (~v) & w;

		// iota
		s0 ^= _KECCAKF_RNDC[i];
	}

	// Сохраняем результаты
	s[0] = s0; s[1] = s1; s[2] = s2; s[3] = s3; s[4] = s4;
	s[5] = s5; s[6] = s6; s[7] = s7; s[8] = s8; s[9] = s9;
	s[10] = s10; s[11] = s11; s[12] = s12; s[13] = s13; s[14] = s14;
	s[15] = s15; s[16] = s16; s[17] = s17; s[18] = s18; s[19] = s19;
	s[20] = s20; s[21] = s21; s[22] = s22; s[23] = s23; s[24] = s24;

	hash[0] = e.d[3];
	hash[1] = e.d[4];
	hash[2] = e.d[5];
	hash[3] = e.d[6];
	hash[4] = e.d[7];
}