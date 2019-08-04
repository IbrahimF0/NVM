// nvmm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "nvm.h"

int main(int argc, char *argv[]) {
	int n = 0;
	int buf = 0;
	FILE* fp = NULL;
	if (strcmp(argv[1], "-d") == 0) {
		debug = true;
		fopen_s(&fp, argv[2], "r+");
	}
	else {
		fopen_s(&fp, argv[1], "r+");
	}
	while (!feof(fp)) {
		buf = 0;
		fread(&buf, 4, 1, fp);
		Instructions[n] = buf;
		n++;
	}
	fclose(fp);
	Exec(n);
	return 0;
}

