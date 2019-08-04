#pragma once
#include <vector>
#include <map>

typedef enum InstrucionSet {
	TYPE_SPEC_REG,
	TYPE_INT_IMM,
	TYPE_INT_REG,
	TYPE_FLOAT_REG,
	TYPE_DOUBLE_REG,
	TYPE_BYTE_REG,
	OP_NOP,
	OP_SAVE,
	OP_RET,
	OP_LOOP,
	OP_JMP,
	OP_IMOV,
	OP_IPRINT,
	OP_IADD,
	OP_ISUB,
	OP_IMUL,
	OP_IDIV,
	OP_IMOD,
	OP_IJE,
	OP_IJNE,
	OP_IJL,
	OP_IJLE,
	OP_IJG,
	OP_IJGE,
	OP_FMOV,
	OP_FPRINT,
	OP_FADD,
	OP_FSUB,
	OP_FMUL,
	OP_FDIV,
	OP_FSQRT,
	OP_FJE,
	OP_FJNE,
	OP_FJL,
	OP_FJLE,
	OP_FJG,
	OP_FJGE,
	OP_DMOV,
	OP_DPRINT,
	OP_DADD,
	OP_DSUB,
	OP_DMUL,
	OP_DDIV,
	OP_DSQRT,
	OP_DJE,
	OP_DJNE,
	OP_DJL,
	OP_DJLE,
	OP_DJG,
	OP_DJGE,
	OP_BMOV,
	OP_BPUT,
	OP_BADD,
	OP_BSUB,
	OP_BMUL,
	OP_BDIV,
	OP_BMOD,
	OP_BJE,
	OP_BJNE,
	OP_BJL,
	OP_BJLE,
	OP_BJG,
	OP_BJGE,
	OP_I2F,
	OP_I2D,
	OP_I2B,
	OP_F2I,
	OP_F2D,
	OP_F2B,
	OP_D2I,
	OP_D2F,
	OP_D2B,
	OP_B2I,
	OP_B2F,
	OP_B2D
}InstrucionSet;

extern bool debug;

extern int LastIP;
extern int IP;

extern int Instructions[65535];

extern int SpecialReg[65535];
extern int IntReg[65535];
extern float FloatReg[65535];
extern double DoubleReg[65535];
extern unsigned char ByteReg[65535];

extern bool IPJumped;

void Exec(int iCount);

void Op_iprint(int type1, int var1);
void Op_imov(int type1, int var1, int type2, int var2);
void Op_iadd(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_isub(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_imul(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_idiv(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_imod(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ije(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ijne(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ijl(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ijle(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ijg(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ijge(int type1, int var1, int type2, int var2, int type3, int var3);

void Op_fprint(int type1, int var1);
void Op_fmov(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_fadd(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_fsub(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_fmul(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_fdiv(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_fsqrt(int type1, int var1, int type2, int var2);

void Op_dprint(int type1, int var1);
void Op_dmov(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_dadd(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_dsub(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_dmul(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_ddiv(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_dsqrt(int type1, int var1, int type2, int var2);

void Op_bput(int type1, int var1);
void Op_bmov(int type1, int var1, int type2, int var2);
void Op_badd(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_bsub(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_bmul(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_bdiv(int type1, int var1, int type2, int var2, int type3, int var3);
void Op_bmod(int type1, int var1, int type2, int var2, int type3, int var3);

void Op_i2f(int type1, int var1, int type2, int var2);
void Op_i2d(int type1, int var1, int type2, int var2);
void Op_i2b(int type1, int var1, int type2, int var2);
void Op_f2i(int type1, int var1, int type2, int var2);
void Op_f2d(int type1, int var1, int type2, int var2);
void Op_f2b(int type1, int var1, int type2, int var2);
void Op_b2i(int type1, int var1, int type2, int var2);
void Op_b2f(int type1, int var1, int type2, int var2);
void Op_b2d(int type1, int var1, int type2, int var2);
void Op_d2f(int type1, int var1, int type2, int var2);
void Op_d2i(int type1, int var1, int type2, int var2);
void Op_d2b(int type1, int var1, int type2, int var2);

void Op_save();
void Op_jmp(int type1, int var1);
void Op_ret();
void Op_loop(int type1, int var1, int type2, int var2);
void Op_nop();