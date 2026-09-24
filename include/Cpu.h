#ifndef _CPU_H_
#define _CPU_H_

// Addresses modes
typedef enum {
  NOAD = 0, // No address mode or invalid one
  ACC,      // Accumulator
  ABS,      // Absolute
  ABSX,     // Absolute X-indexed
  ABSY,     // Absolute Y-indexed
  IMM,      // Immediate
  IMPL,     // Implied
  IND,      // Indirect
  INDX,     // X-indexed, Indirect
  INDY,     // Indirect,  Y-indexed
  REL,      // Relative
  ZPG,      // Zeropage
  ZPGX,     // Zeropage, X-indexed
  ZPGY,     // Zeropage, Y-indexed
} AddressMode;

typedef enum {
  NOIN = 0, // Invalid instruction
  ADC,      // add with carry
  ALR,      // Illegal instruction
  ANC,      // Illegal instruction
  AND,      // and (with accumulator)
  ANE,      // Illegal instruction
  ARR,      // Illegal instruction
  ASL,      // arithmetic shift left
  BCC,      // branch on carry clear
  BCS,      // branch on carry set
  BEQ,      // branch on equal (zero set)
  BIT,      // bit test
  BMI,      // branch on minus (negative set)
  BNE,      // branch on not equal (zero clear)
  BPL,      // branch on plus (negative clear)
  BRK,      // break / interrupt
  BVC,      // branch on overflow clear
  BVS,      // branch on overflow set
  CLC,      // clear carry
  CLD,      // clear decimal
  CLI,      // clear interrupt disable
  CLV,      // clear overflow
  CMP,      // compare (with accumulator)
  CPX,      // compare with X
  CPY,      // compare with Y
  DCP,      // Illegal instruction
  DEC,      // decrement
  DEX,      // decrement X
  DEY,      // decrement Y
  EOR,      // exclusive or (with accumulator)
  INC,      // increment
  INX,      // increment X
  INY,      // increment Y
  ISC,      // Illegal instruction
  JAM,      // Illegal instruction
  JMP,      // jump
  JSR,      // jump subroutine
  LAS,      // Illegal instruction
  LAX,      // Illegal instruction
  LDA,      // load accumulator
  LDX,      // load X
  LDY,      // load Y
  LSR,      // logical shift right
  LXA,      // Illegal instruction
  NOP,      // no operation
  NOPS,     // Illegal instruction
  ORA,      // or with accumulator
  PHA,      // push accumulator
  PHP,      // push processor status (SR)
  PLA,      // pull accumulator
  PLP,      // pull processor status (SR)
  RLA,      // Illegal instruction
  ROL,      // rotate left
  ROR,      // rotate right
  RRA,      // Illegal instruction
  RTI,      // return from interrupt
  RTS,      // return from subroutine
  SAX,      // Illegal instruction
  SBC,      // subtract with carry
  SBX,      // Illegal instruction
  SEC,      // set carry
  SED,      // set decimal
  SEI,      // set interrupt disable
  SHA,      // Illegal instruction
  SHX,      // Illegal instruction
  SHY,      // Illegal instruction
  SLO,      // Illegal instruction
  SRE,      // Illegal instruction
  STA,      // store accumulator
  STX,      // store X
  STY,      // store Y
  TAS,      // Illegal instruction
  TAX,      // transfer accumulator to X
  TAY,      // transfer accumulator to Y
  TSX,      // transfer stack pointer to X
  TXA,      // transfer X to accumulator
  TXS,      // transfer X to stack pointer
  TYA,      // transfer Y to accumulator
  USBC,     // Illegal instruction 
} OpCode;

typedef struct {
  OpCode opCode;
  AddressMode mode;
} Instruction;

// Implement 256 instructions FF (Counting illegal ones)
static Instruction instructions[256] = {
//       |     0x0     |     0x1     |     0x2     |     0x3     |     0x4     |     0x5     |     0x6     |     0x7     |     0x8     |     0x9     |     0xa     |     0xb     |     0xc     |     0xd     |     0xe     |     0xf    |
/* 0x0 */  {BRK, IMPL},  {ORA, NOAD},   {ORA, ZPG},   {ASL, ZPG},  {PHP, IMPL},   {ORA, IMM},   {ASL, ACC},   {ORA, ABS},   {ASL, ABS},   {BPL, REL},  {ORA, INDY},  {ORA, ZPGX},  {ASL, ZPGX},  {CLC, IMPL},  {ORA, ABSY},  {ORA, ABSX},
/* 0x1 */  {ASL, ABSX},   {JSR, ABS},  {AND, NOAD},   {BIT, ZPG},   {AND, ZPG},   {ROL, ZPG},  {PLP, IMPL},   {AND, IMM},   {ROL, ACC},   {BIT, ABS},   {AND, ABS},   {ROL, ABS},   {BMI, REL},  {AND, INDY},  {AND, ZPGX},  {ROL, ZPGX},
/* 0x2 */  {SEC, IMPL},  {AND, ABSY},  {AND, ABSX},  {ROL, ABSX},  {RTI, IMPL},  {EOR, NOAD},   {EOR, ZPG},   {LSR, ZPG},  {PHA, IMPL},   {EOR, IMM},   {LSR, ACC},   {JMP, ABS},   {EOR, ABS},   {LSR, ABS},   {BVC, REL},  {EOR, INDY},
/* 0x3 */  {EOR, ZPGX},  {LSR, ZPGX},  {CLI, IMPL},  {EOR, ABSY},  {EOR, ABSX},  {LSR, ABSX},  {RTS, IMPL},  {ADC, NOAD},   {ADC, ZPG},   {ROR, ZPG},  {PLA, IMPL},   {ADC, IMM},   {ROR, ACC},   {JMP, IND},   {ADC, ABS},   {ROR, ABS},
/* 0x4 */   {BVS, REL},  {ADC, INDY},  {ADC, ZPGX},  {ROR, ZPGX},  {SEI, IMPL},  {ADC, ABSY},  {ADC, ABSX},  {ROR, ABSX},  {STA, NOAD},   {STY, ZPG},   {STA, ZPG},   {STX, ZPG},  {DEY, IMPL},  {TXA, IMPL},   {STY, ABS},   {STA, ABS},
/* 0x5 */   {STX, ABS},   {BCC, REL},  {STA, INDY},  {STY, ZPGX},  {STA, ZPGX},  {STX, ZPGY},  {TYA, IMPL},  {STA, ABSY},  {TXS, IMPL},  {STA, ABSX},   {LDY, IMM},  {LDA, NOAD},   {LDX, IMM},   {LDY, ZPG},   {LDA, ZPG},   {LDX, ZPG},
/* 0x6 */  {TAY, IMPL},   {LDA, IMM},  {TAX, IMPL},   {LDY, ABS},   {LDA, ABS},   {LDX, ABS},   {BCS, REL},  {LDA, INDY},  {LDY, ZPGX},  {LDA, ZPGX},  {LDX, ZPGY},  {CLV, IMPL},  {LDA, ABSY},  {TSX, IMPL},  {LDY, ABSX},  {LDA, ABSX},
/* 0x7 */  {LDX, ABSY},   {CPY, IMM},  {CMP, NOAD},   {CPY, ZPG},   {CMP, ZPG},   {DEC, ZPG},  {INY, IMPL},   {CMP, IMM},  {DEX, IMPL},   {CPY, ABS},   {CMP, ABS},   {DEC, ABS},   {BNE, REL},  {CMP, INDY},  {CMP, ZPGX},  {DEC, ZPGX},
/* 0x8 */  {CLD, IMPL},  {CMP, ABSY},  {CMP, ABSX},  {DEC, ABSX},   {CPX, IMM},  {SBC, NOAD},   {CPX, ZPG},   {SBC, ZPG},   {INC, ZPG},  {INX, IMPL},   {SBC, IMM},  {NOP, IMPL},   {CPX, ABS},   {SBC, ABS},   {INC, ABS},   {BEQ, REL},
/* 0x9 */  {SBC, INDY},  {SBC, ZPGX},  {INC, ZPGX},  {SED, IMPL},  {SBC, ABSY},  {SBC, ABSX},  {INC, ABSX},  {JAM, NOAD},  {SLO, NOAD},  {NOPS, ZPG},   {SLO, ZPG},   {ANC, IMM},  {NOPS, ABS},   {SLO, ABS},  {JAM, NOAD},  {SLO, INDY},
/* 0xa */ {NOPS, ZPGX},  {SLO, ZPGX}, {NOPS, IMPL},  {SLO, ABSY}, {NOPS, ABSX},  {SLO, ABSX},  {JAM, NOAD},  {RLA, NOAD},   {RLA, ZPG},   {ANC, IMM},   {RLA, ABS},  {JAM, NOAD},  {RLA, INDY}, {NOPS, ZPGX},  {RLA, ZPGX}, {NOPS, IMPL},
/* 0xb */  {RLA, ABSY}, {NOPS, ABSX},  {RLA, ABSX},  {JAM, NOAD},  {SRE, NOAD},  {NOPS, ZPG},   {SRE, ZPG},   {ALR, IMM},   {SRE, ABS},  {JAM, NOAD},  {SRE, INDY}, {NOPS, ZPGX},  {SRE, ZPGX}, {NOPS, IMPL},  {SRE, ABSY}, {NOPS, ABSX},
/* 0xc */  {SRE, ABSX},  {JAM, NOAD},  {RRA, NOAD},  {NOPS, ZPG},   {RRA, ZPG},   {ARR, IMM},   {RRA, ABS},  {JAM, NOAD},  {RRA, INDY}, {NOPS, ZPGX},  {RRA, ZPGX}, {NOPS, IMPL},  {RRA, ABSY}, {NOPS, ABSX},  {RRA, ABSX},  {NOPS, IMM},
/* 0xd */  {NOPS, IMM},  {SAX, NOAD},   {SAX, ZPG},  {NOPS, IMM},   {ANE, IMM},   {SAX, ABS},  {JAM, NOAD},  {SHA, INDY},  {SAX, ZPGY},  {TAS, ABSY},  {SHY, ABSX},  {SHX, ABSY},  {SHA, ABSY},  {LAX, NOAD},   {LAX, ZPG},   {LXA, IMM},
/* 0xe */   {LAX, ABS},  {JAM, NOAD},  {LAX, INDY},  {LAX, ZPGY},  {LAS, ABSY},  {LAX, ABSY},  {NOPS, IMM},  {DCP, NOAD},   {DCP, ZPG},   {SBX, IMM},   {DCP, ABS},  {JAM, NOAD},  {DCP, INDY}, {NOPS, ZPGX},  {DCP, ZPGX}, {NOPS, IMPL},
/* 0xf */  {DCP, ABSY}, {NOPS, ABSX},  {DCP, ABSX},  {NOPS, IMM},  {ISC, NOAD},   {ISC, ZPG},  {USBC, IMM},   {ISC, ABS},  {JAM, NOAD},  {ISC, INDY}, {NOPS, ZPGX},  {ISC, ZPGX}, {NOPS, IMPL},  {ISC, ABSY}, {NOPS, ABSX},  {ISC, ABSX}
};

#endif
