#include <stdio.h>

void dump(FILE *);

// Cat prints each file in the argument list to the standard output.
int main(int argc, char **argv) {
	FILE *f;

	if (argc == 1) {
		dump(stdin);
		return 0;
	}

	while (*++argv) {
		f = fopen(*argv, "r");
		if (f == NULL) {
			fprintf(stderr, "cat: %s: No such file or directory\n", *argv);
			continue;
		}
		dump(f);
		fclose(f);
	}
}

// Dump prints the content of f to stdout.
void dump(FILE *f) {
	int c;

	while ((c = fgetc(f)) != EOF) {
		putchar(c);
	}
}
