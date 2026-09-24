#ifndef _CPU_H_
#define _CPU_H_

// Addresses modes
typedef enum {
  none = 0, // No address mode or invalid one
  acc,      // Accumulator
  abs,      // Absolute
  absx,     // Absolute X-indexed
  absy,     // Absolute Y-indexed
  imm,      // Immediate
  impl,     // Implied
  ind,      // Indirect
  indx,     // X-indexed, Indirect
  indy,     // Indirect,  Y-indexed
  rel,      // Relative
  zpg,      // Zeropage
  zpgx,     // Zeropage, X-indexed
  zpgy,     // Zeropage, Y-indexed
} AddressMode;

// Implement 256 instructions FF (Counting illegal ones)
static AddressMode instructions[256] = {
  //      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  | 
  /* 0 */  impl, none,  zpg,  zpg, impl,  imm,  acc,  abs,  abs,  rel, indy, zpgx, zpgx, impl, absy, absx,
  /* 1 */  absx,  abs, none,  zpg,  zpg,  zpg, impl,  imm,  acc,  abs,  abs,  abs,  rel, indy, zpgx, zpgx,
  /* 2 */  impl, absy, absx, absx, impl, none,  zpg,  zpg, impl,  imm,  acc,  abs,  abs,  abs,  rel, indy,
  /* 3 */  zpgx, zpgx, impl, absy, absx, absx, impl, none,  zpg,  zpg, impl,  imm,  acc,  ind,  abs,  abs,
  /* 4 */   rel, indy, zpgx, zpgx, impl, absy, absx, absx, none,  zpg,  zpg,  zpg, impl, impl,  abs,  abs,
  /* 5 */   abs,  rel, indy, zpgx, zpgx, zpgy, impl, absy, impl, absx,  imm, none,  imm,  zpg,  zpg,  zpg,
  /* 6 */  impl,  imm, impl,  abs,  abs,  abs,  rel, indy, zpgx, zpgx, zpgy, impl, absy, impl, absx, absx,
  /* 7 */  absy,  imm, none,  zpg,  zpg,  zpg, impl,  imm, impl,  abs,  abs,  abs,  rel, indy, zpgx, zpgx,
  /* 8 */  impl, absy, absx, absx,  imm, none,  zpg,  zpg,  zpg, impl,  imm, impl,  abs,  abs,  abs,  rel,
  /* 9 */  indy, zpgx, zpgx, impl, absy, absx, absx, none, none,  zpg,  zpg,  imm,  abs,  abs, none, indy,
  /* A */  zpgx, zpgx, impl, absy, absx, absx, none, none,  zpg,  imm,  abs, none, indy, zpgx, zpgx, impl,
  /* B */  absy, absx, absx, none, none,  zpg,  zpg,  imm,  abs, none, indy, zpgx, zpgx, impl, absy, absx,
  /* C */  absx, none, none,  zpg,  zpg,  imm,  abs, none, indy, zpgx, zpgx, impl, absy, absx, absx,  imm,
  /* D */   imm, none,  zpg,  imm,  imm,  abs, none, indy, zpgy, absy, absx, absy, absy, none,  zpg,  imm,
  /* E */   abs, none, indy, zpgy, absy, absy,  imm, none,  zpg,  imm,  abs, none, indy, zpgx, zpgx, impl,
  /* F */  absy, absx, absx,  imm, none,  zpg,  imm,  abs, none, indy, zpgx, zpgx, impl, absy, absx, absx
};

#endif
