// nvmasm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

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

int main(int argc, char *argv[]) {
	FILE* fp = NULL;
	fopen_s(&fp, argv[1], "w+");
	while (!feof(fp)) {

	}
	return 0;
}

