#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) 
{
	char operator;
	FILE *fp;
	int character;
	int number = 0;

	if ((fp = fopen("ssu_expr.txt", "r")) == NULL) {
		fprintf(stderr, "fopen error for ssu_expr.txt\n");
		exit(1);
	}

	while (!feof(fp)) {
		while ((character = fgetc(fp)) != EOF && isdigit(character)) { // EOF or not digit
			number = 10 * number + character - 48;
		}

		fprintf(stdout, " %d\n", number);
		number = 0;

		if (character != EOF) {
			ungetc(character, fp); // 위 while문에서 operator까지 검사되어서 ungetc로 한칸 되돌린 뒤, 다시 읽는다
			operator = fgetc(fp);
			printf("Operater => %c\n", operator);
		}
	}

	fclose(fp);
	exit(0);
}
