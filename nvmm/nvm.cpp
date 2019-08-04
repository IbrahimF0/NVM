#include "stdafx.h"
#include "nvm.h"

bool debug = false;

int LastIP = 0;
int IP = 0;

int Instructions[65535];

int SpecialReg[65535];
int IntReg[65535];
float FloatReg[65535];
double DoubleReg[65535];
unsigned char ByteReg[65535];

bool IPJumped = false;

void Exec(int iCount) {
	if (debug) {
		printf("Instruction Count : %d\n", iCount);
	}
	while (IP < iCount - 1) {
		switch (Instructions[IP]) {
		case OP_IMOV:
			Op_imov(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_IADD:
			Op_iadd(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_ISUB:
			Op_isub(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IMUL:
			Op_imul(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IDIV:
			Op_idiv(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IMOD:
			Op_imod(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IPRINT:
			Op_iprint(Instructions[IP + 1], Instructions[IP + 2]);
			break;
		case OP_JMP:
			Op_jmp(Instructions[IP + 1], Instructions[IP + 2]);
			break;
		case OP_RET:
			Op_ret();
			break;
		case OP_NOP:
			Op_nop();
			break;
		case OP_SAVE:
			Op_save();
			break;
		case OP_IJE:
			Op_ije(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IJNE:
			Op_ijne(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IJL:
			Op_ijl(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IJLE:
			Op_ijle(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IJG:
			Op_ijg(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_IJGE:
			Op_ijge(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_LOOP:
			Op_loop(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_FADD:
			Op_fadd(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_FSUB:
			Op_fsub(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_FMUL:
			Op_fmul(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_FDIV:
			Op_fdiv(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_FMOV:
			Op_fmov(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_FPRINT:
			Op_fprint(Instructions[IP + 1], Instructions[IP + 2]);
			break;
		case OP_DADD:
			Op_dadd(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_DSUB:
			Op_dsub(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_DMUL:
			Op_dmul(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_DDIV:
			Op_ddiv(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_DMOV:
			Op_dmov(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4], Instructions[IP + 5], Instructions[IP + 6]);
			break;
		case OP_DPRINT:
			Op_dprint(Instructions[IP + 1], Instructions[IP + 2]);
			break;
		case OP_BPUT:
			Op_bput(Instructions[IP + 1], Instructions[IP + 2]);
			break;
		case OP_I2F:
			Op_i2f(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_I2D:
			Op_i2d(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_I2B:
			Op_i2b(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_F2I:
			Op_f2i(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_F2D:
			Op_f2d(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_F2B:
			Op_f2b(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_B2I:
			Op_b2i(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_B2D:
			Op_b2d(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_B2F:
			Op_b2f(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_D2I:
			Op_d2i(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_D2B:
			Op_d2b(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		case OP_D2F:
			Op_d2f(Instructions[IP + 1], Instructions[IP + 2], Instructions[IP + 3], Instructions[IP + 4]);
			break;
		default:
			MessageBeep(MB_ICONHAND);
			MessageBox(NULL, L"NVM Error :\nUnknown instruction.", L"NVM Error", MB_ICONHAND);
			exit(0);
			break;
		}
	}
}

void Op_nop() {
	IP += 1;
	if (debug) {
		printf("IP= %d nop\n", IP - 1);
	}
}

void Op_ret() {
	IP += 1;
	if (debug) {
		printf("IP= %d ret\n", IP - 1);
	}
	if (IPJumped) {
		IP = LastIP;
		IPJumped = false;
	}
}

void Op_loop(int type1, int var1, int type2, int var2) {
	IP += 5;
	LastIP = IP - 5;
	if (type1 == TYPE_SPEC_REG && type2 == TYPE_INT_REG) {
		if (debug) {
			printf("IP = %d loop sr%d,ir%d\n", IP - 5, var1, var2);
		}
		if (SpecialReg[var1] != 0) {
			SpecialReg[var1] -= 1;
			IP = IntReg[var2];
		}
		else {
			LastIP += 5;
		}
	}
	else if (type1 == TYPE_SPEC_REG && type2 == TYPE_SPEC_REG) {
		if (debug) {
			printf("IP = %d loop sr%d,sr%d\n", IP - 5, var1, var2);
		}
		if (SpecialReg[var1] != 0) {
			SpecialReg[var1] -= 1;
			IP = SpecialReg[var2];
		}
		else {
			LastIP += 5;
		}
	}
	else if (type1 == TYPE_SPEC_REG && type2 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d loop sr%d,%d\n", IP - 5, var1, var2);
		}
		if (SpecialReg[var1] != 0) {
			SpecialReg[var1] -= 1;
			IP = var2;
		}
		else {
			LastIP += 5;
		}
	}
	IPJumped = true;
}

void Op_jmp(int type1, int var1) {
	IP += 3;
	LastIP = IP;
	if (type1 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d jmp %d\n", IP - 3, var1);
		}
		IP = var1;
	}
	else if (type1 == TYPE_INT_REG) {
		if (debug) {
			printf("IP = %d jmp ir%d\n", IP - 3, var1);
		}
		IP = IntReg[var1];
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (debug) {
			printf("IP = %d jmp sr%d\n", IP - 3, var1);
		}
		IP = SpecialReg[var1];
	}
	IPJumped = true;
}

void Op_imov(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (type1 == TYPE_INT_REG && type2 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d imov ir%d,%d\n", IP - 5, var1, var2);
		}
		IntReg[var1] = var2;
	}
	else if (type1 == TYPE_SPEC_REG && type2 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d imov sr%d,%d\n", IP - 5, var1, var2);
		}
		SpecialReg[var1] = var2;
	}
	else if (type1 == TYPE_INT_REG && type2 == TYPE_INT_REG) {
		if (debug) {
			printf("IP = %d imov ir%d,ir%d\n", IP - 5, var1, var2);
		}
		IntReg[var1] = IntReg[var2];
	}
	else if (type1 == TYPE_SPEC_REG && type2 == TYPE_INT_REG) {
		if (debug) {
			printf("IP = %d imov sr%d,ir%d\n", IP - 5, var1, var2);
		}
		SpecialReg[var1] = IntReg[var2];
	}
	else if (type1 == TYPE_INT_REG && type2 == TYPE_SPEC_REG) {
		if (debug) {
			printf("IP = %d imov ir%d,sr%d\n", IP - 5, var1, var2);
		}
		IntReg[var1] = SpecialReg[var2];
	}
	else if (type1 == TYPE_SPEC_REG && type2 == TYPE_SPEC_REG) {
		if (debug) {
			printf("IP = %d imov sr%d,sr%d\n", IP - 5, var1, var2);
		}
		SpecialReg[var1] = SpecialReg[var2];
	}
}

void Op_iprint(int type1, int var1) {
	IP += 3;
	if (type1 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d iprint %d\n", IP - 3, var1);
		}
		printf("%d\n", var1);
	}
	else if (type1 == TYPE_INT_REG) {
		if (debug) {
			printf("IP = %d iprint ir%d\n", IP - 3, var1);
		}
		printf("%d\n", IntReg[var1]);
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (debug) {
			printf("IP = %d iprint sr%d\n", IP - 3, var1);
		}
		printf("%d\n", SpecialReg[var1]);
	}
}

void Op_fprint(int type1, int var1) {
	IP += 3;
	if (type1 == TYPE_FLOAT_REG) {
		if (debug) {
			printf("IP = %d fprint fr%d\n", IP - 3, var1);
		}
		printf("%f\n", FloatReg[var1]);
	}
}

void Op_fmov(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_FLOAT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d fmov fr%d,ir%d,ir%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)IntReg[var2] * powf(10, IntReg[var3]);
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d fmov fr%d,ir%d,%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)IntReg[var2] * powf(10, var3);
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d fmov fr%d,ir%d,sr%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)IntReg[var2] * powf(10, SpecialReg[var3]);
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d fmov fr%d,sr%d,%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)SpecialReg[var2] * powf(10, var3);
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d fmov fr%d,sr%d,ir%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)SpecialReg[var2] * powf(10, IntReg[var3]);
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d fmov fr%d,sr%d,sr%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)SpecialReg[var2] * powf(10, SpecialReg[var3]);
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d fmov fr%d,%d,%d\n", IP - 6, var1, var2, var3);
			}
			FloatReg[var1] = (float)var2 * powf(10, var3);
		}
	}
}

void Op_dprint(int type1, int var1) {
	IP += 3;
	if (type1 == TYPE_DOUBLE_REG) {
		if (debug) {
			printf("IP = %d dprint dr%d\n", IP - 3, var1);
		}
		printf("%lf\n", DoubleReg[var1]);
	}
}

void Op_dmov(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_DOUBLE_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d dmov dr%d,ir%d,ir%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)IntReg[var2] * pow(10, IntReg[var3]);
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d dmov dr%d,ir%d,%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)IntReg[var2] * pow(10, var3);
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d dmov dr%d,ir%d,sr%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)IntReg[var2] * pow(10, SpecialReg[var3]);
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d dmov dr%d,sr%d,%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)SpecialReg[var2] * pow(10, var3);
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d dmov dr%d,sr%d,ir%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)SpecialReg[var2] * pow(10, IntReg[var3]);
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d dmov dr%d,sr%d,sr%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)SpecialReg[var2] * pow(10, SpecialReg[var3]);
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d dmov dr%d,%d,%d\n", IP - 6, var1, var2, var3);
			}
			DoubleReg[var1] = (double)var2 * pow(10, var3);
		}
	}
}

void Op_bput(int type1, int var1) {
	IP += 3;
	if (type1 == TYPE_BYTE_REG) {
		if (debug) {
			printf("IP = %d bput br%d\n", IP - 3, var1);
		}
		printf("%c", ByteReg[var1]);
	}
	else if (type1 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d bput '%c'\n", IP - 3, (char)var1);
		}
		printf("%c", (char)var1);
	}
}

void Op_bmov(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (type1 == TYPE_BYTE_REG && type2 == TYPE_INT_IMM) {
		if (debug) {
			printf("IP = %d bmov br%d,%d\n", IP - 5, var1, var2);
		}
		ByteReg[var1] = var2;
	}
	else if (type1 == TYPE_BYTE_REG && type2 == TYPE_BYTE_REG) {
		if (debug) {
			printf("IP = %d bmov br%d,br%d\n", IP - 5, var1, var2);
		}
		ByteReg[var1] = ByteReg[var2];
	}
}

void Op_iadd(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d iadd ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] + IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d iadd ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] + IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d iadd ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] + SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d iadd ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] + var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d iadd ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] + var3;
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d iadd sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] + IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d iadd sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] + IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d iadd sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] + SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d iadd sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] + var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d iadd sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] + var3;
		}
	}
}

void Op_ije(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_IMM) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije %d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] == IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije %d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ije %d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == SpecialReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ije %d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] == var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ije %d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije %d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 == IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ije %d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 == IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
	}
	else if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] == IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ije ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == SpecialReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ije ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] == var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ije ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije ir%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 == IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ije ir%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 == IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] == IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ije sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == SpecialReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ije sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] == var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ije sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] == var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ije sr%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 == IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ije sr%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 == IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
	}
}

void Op_ijne(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_IMM) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne %d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] != IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne %d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijne %d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != SpecialReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijne %d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] != var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijne %d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne %d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 != IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijne %d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 != IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
	}
	else if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] != IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijne ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != SpecialReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijne ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] != var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijne ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne ir%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 != IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijne ir%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 != IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] != IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijne sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != SpecialReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijne sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] != var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijne sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] != var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijne sr%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 != IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijne sr%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 != IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
	}
}

void Op_ijl(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_IMM) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl %d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] < IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl %d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijl %d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < SpecialReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijl %d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] < var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijl %d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl %d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 < IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijl %d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 < IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
	}
	else if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] < IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijl ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < SpecialReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijl ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] < var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijl ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl ir%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 < IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijl ir%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 < IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] < IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijl sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < SpecialReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijl sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] < var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijl sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] < var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijl sr%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 < IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijl sr%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 < IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
	}
}

void Op_ijle(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_IMM) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle %d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] <= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle %d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijle %d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= SpecialReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijle %d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] <= var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijle %d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle %d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 <= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijle %d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 <= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
	}
	else if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] <= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijle ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= SpecialReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijle ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] <= var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijle ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle ir%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 <= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijle ir%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 <= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] <= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijle sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= SpecialReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijle sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] <= var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijle sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] <= var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijle sr%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 <= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijle sr%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 <= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
	}
}

void Op_ijg(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_IMM) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg %d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] > IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg %d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijg %d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > SpecialReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijg %d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] > var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijg %d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg %d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 > IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijg %d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 > IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
	}
	else if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] > IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijg ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > SpecialReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijg ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] > var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijg ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg ir%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 > IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijg ir%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 > IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] > IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijg sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > SpecialReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijg sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] > var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijg sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] > var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijg sr%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 > IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijg sr%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 > IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
	}
}

void Op_ijge(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_IMM) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge %d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] >= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge %d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijge %d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= SpecialReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijge %d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] >= var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijge %d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= var3) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge %d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 >= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijge %d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 >= IntReg[var3]) {
				LastIP = IP;
				IP = var1;
			}
		}
	}
	else if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] >= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijge ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= SpecialReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijge ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] >= var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijge ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= var3) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge ir%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 >= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijge ir%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 >= IntReg[var3]) {
				LastIP = IP;
				IP = IntReg[var1];
			}
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] >= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijge sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= SpecialReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijge sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (IntReg[var2] >= var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d ijge sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			if (SpecialReg[var2] >= var3) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d ijge sr%d,%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 >= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
		else if (type2 == TYPE_INT_IMM && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d ijge sr%d,%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			if (var2 >= IntReg[var3]) {
				LastIP = IP;
				IP = SpecialReg[var1];
			}
		}
	}
}

void Op_save() {
	IP += 1;
	if (debug) {
		printf("IP = %d save\n", IP - 1);
	}
	LastIP = IP;
}

void Op_isub(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d isub ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] - IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d isub ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] - IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d isub ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] - SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d isub ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] - var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d isub ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] - var3;
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d isub sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] - IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d isub sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] - IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d isub sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] - SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d isub sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] - var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d isub sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] - var3;
		}
	}
}

void Op_imul(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imul ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] * IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imul ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] * IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d imul ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] * SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imul ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] * var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imul ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] * var3;
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imul sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] * IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imul sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] * IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d imul sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] * SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imul sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] * var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imul sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] * var3;
		}
	}
}

void Op_idiv(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d idiv ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] / IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d idiv ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] / IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d idiv ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] / SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d idiv ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] / var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d idiv ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] / var3;
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d idiv sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] / IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d idiv sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] / IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d idiv sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] / SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d idiv sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] / var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d idiv sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] / var3;
		}
	}
}

void Op_imod(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_INT_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imod ir%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] % IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imod ir%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] % IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d imod ir%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] % SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imod ir%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = IntReg[var2] % var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imod ir%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			IntReg[var1] = SpecialReg[var2] % var3;
		}
	}
	else if (type1 == TYPE_SPEC_REG) {
		if (type2 == TYPE_INT_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imod sr%d,ir%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] % IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_REG) {
			if (debug) {
				printf("IP = %d imod sr%d,sr%d,ir%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] % IntReg[var3];
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_SPEC_REG) {
			if (debug) {
				printf("IP = %d imod sr%d,sr%d,sr%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] % SpecialReg[var3];
		}
		else if (type2 == TYPE_INT_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imod sr%d,ir%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = IntReg[var2] % var3;
		}
		else if (type2 == TYPE_SPEC_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d imod sr%d,sr%d,%d\n", IP - 7, var1, var2, var3);
			}
			SpecialReg[var1] = SpecialReg[var2] % var3;
		}
	}
}

void Op_fadd(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_FLOAT_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d fadd fr%d,fr%d,fr%d\n", IP - 7, var1, var2, var3);
			}
			FloatReg[var1] = FloatReg[var2] + FloatReg[var3];
		}
	}
}

void Op_fsub(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_FLOAT_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d fsub fr%d,fr%d,fr%d\n", IP - 7, var1, var2, var3);
			}
			FloatReg[var1] = FloatReg[var2] - FloatReg[var3];
		}
	}
}

void Op_fmul(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_FLOAT_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d fmul fr%d,fr%d,fr%d\n", IP - 7, var1, var2, var3);
			}
			FloatReg[var1] = FloatReg[var2] * FloatReg[var3];
		}
	}
}

void Op_fdiv(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_FLOAT_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d fdiv fr%d,fr%d,fr%d\n", IP - 7, var1, var2, var3);
			}
			FloatReg[var1] = FloatReg[var2] / FloatReg[var3];
		}
	}
}

void Op_fsqrt(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (type1 == TYPE_FLOAT_REG && type2 == TYPE_FLOAT_REG) {
		if (debug) {
			printf("IP = %d fsqrt fr%d,fr%d\n", IP - 5, var1, var2);
		}
		FloatReg[var1] = sqrtf(FloatReg[var2]);
	}
}

void Op_dadd(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_DOUBLE_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d dadd dr%d,dr%d,dr%d\n", IP - 7, var1, var2, var3);
			}
			DoubleReg[var1] = DoubleReg[var2] + DoubleReg[var3];
		}
	}
}

void Op_dsub(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_DOUBLE_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d dsub dr%d,dr%d,dr%d\n", IP - 7, var1, var2, var3);
			}
			DoubleReg[var1] = DoubleReg[var2] - DoubleReg[var3];
		}
	}
}

void Op_dmul(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_DOUBLE_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d dmul dr%d,dr%d,dr%d\n", IP - 7, var1, var2, var3);
			}
			DoubleReg[var1] = DoubleReg[var2] * DoubleReg[var3];
		}
	}
}

void Op_ddiv(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_DOUBLE_REG) {
		if (type2 == TYPE_FLOAT_REG && type3 == TYPE_FLOAT_REG) {
			if (debug) {
				printf("IP = %d ddiv dr%d,dr%d,dr%d\n", IP - 7, var1, var2, var3);
			}
			DoubleReg[var1] = DoubleReg[var2] / DoubleReg[var3];
		}
	}
}

void Op_dsqrt(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (type1 == TYPE_DOUBLE_REG && type2 == TYPE_DOUBLE_REG) {
		if (debug) {
			printf("IP = %d dsqrt dr%d,dr%d\n", IP - 5, var1, var2);
		}
		DoubleReg[var1] = sqrt(DoubleReg[var2]);
	}
}

void Op_badd(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_BYTE_REG) {
		if (type2 == TYPE_BYTE_REG && type3 == TYPE_BYTE_REG) {
			if (debug) {
				printf("IP = %d badd br%d,br%d,br%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] + ByteReg[var3];
		}
		else if (type2 == TYPE_BYTE_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d badd br%d,br%d,%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] + var3;
		}
	}
}

void Op_bsub(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_BYTE_REG) {
		if (type2 == TYPE_BYTE_REG && type3 == TYPE_BYTE_REG) {
			if (debug) {
				printf("IP = %d bsub br%d,br%d,br%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] - ByteReg[var3];
		}
		else if (type2 == TYPE_BYTE_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d bsub br%d,br%d,%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] - var3;
		}
	}
}

void Op_bmul(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_BYTE_REG) {
		if (type2 == TYPE_BYTE_REG && type3 == TYPE_BYTE_REG) {
			if (debug) {
				printf("IP = %d bmul br%d,br%d,br%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] * ByteReg[var3];
		}
		else if (type2 == TYPE_BYTE_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d bmul br%d,br%d,%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] * var3;
		}
	}
}

void Op_bdiv(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_BYTE_REG) {
		if (type2 == TYPE_BYTE_REG && type3 == TYPE_BYTE_REG) {
			if (debug) {
				printf("IP = %d bdiv br%d,br%d,br%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] / ByteReg[var3];
		}
		else if (type2 == TYPE_BYTE_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d bdiv br%d,br%d,%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] / var3;
		}
	}
}

void Op_bmod(int type1, int var1, int type2, int var2, int type3, int var3) {
	IP += 7;
	if (type1 == TYPE_BYTE_REG) {
		if (type2 == TYPE_BYTE_REG && type3 == TYPE_BYTE_REG) {
			if (debug) {
				printf("IP = %d bmod br%d,br%d,br%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] % ByteReg[var3];
		}
		else if (type2 == TYPE_BYTE_REG && type3 == TYPE_INT_IMM) {
			if (debug) {
				printf("IP = %d bmod br%d,br%d,%d\n", IP - 7, var1, var2, var3);
			}
			ByteReg[var1] = ByteReg[var2] % var3;
		}
	}
}

void Op_i2f(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d i2f ir%d,fr%d\n", IP - 5, var1, var2);
	}
	FloatReg[var2] = (float)IntReg[var1];
}

void Op_i2d(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d i2d ir%d,dr%d\n", IP - 5, var1, var2);
	}
	DoubleReg[var2] = (double)IntReg[var1];
}

void Op_i2b(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d i2b ir%d,br%d\n", IP - 5, var1, var2);
	}
	ByteReg[var2] = (char)IntReg[var1];
}

void Op_f2i(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d f2i fr%d,ir%d\n", IP - 5, var1, var2);
	}
	IntReg[var2] = (int)FloatReg[var1];
}

void Op_f2d(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d f2d fr%d,dr%d\n", IP - 5, var1, var2);
	}
	DoubleReg[var2] = (double)FloatReg[var1];
}

void Op_f2b(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d f2b fr%d,br%d\n", IP - 5, var1, var2);
	}
	ByteReg[var2] = (char)FloatReg[var1];
}

void Op_b2i(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d b2i br%d,ir%d\n", IP - 5, var1, var2);
	}
	IntReg[var2] = (int)ByteReg[var1];
}

void Op_b2f(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d b2f br%d,fr%d\n", IP - 5, var1, var2);
	}
	FloatReg[var2] = (float)ByteReg[var1];
}

void Op_b2d(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d b2d br%d,dr%d\n", IP - 5, var1, var2);
	}
	DoubleReg[var2] = (double)ByteReg[var1];
}

void Op_d2f(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d d2f dr%d,fr%d\n", IP - 5, var1, var2);
	}
	FloatReg[var2] = (float)DoubleReg[var1];
}

void Op_d2i(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d d2i dr%d,ir%d\n", IP - 5, var1, var2);
	}
	IntReg[var2] = (int)DoubleReg[var1];
}

void Op_d2b(int type1, int var1, int type2, int var2) {
	IP += 5;
	if (debug) {
		printf("IP = %d d2b dr%d,br%d\n", IP - 5, var1, var2);
	}
	ByteReg[var2] = (char)DoubleReg[var1];
}
