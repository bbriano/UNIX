#include <stdio.h>
#include <stdbool.h>

void count(FILE *, unsigned int *nl, unsigned int *nw, unsigned int *nc);

// Wc counts the number of lines, words and characters for each file in the
// argument list and prints it to the standard output. If no argument is
// passed, it reads from the standard input.
int main(int argc, char **argv) {
	unsigned int nl, nw, nc;
	FILE *f;

	if (argc == 1) {
		count(stdin, &nl, &nw, &nc);
		printf("%8d%8d%8d\n", nl, nw, nc);
		return 0;
	}

	while (*++argv) {
		f = fopen(*argv, "r");
		if (f == NULL) {
			fprintf(stderr, "wc: %s: No such file or directory\n", *argv);
			continue;
		}
		count(f, &nl, &nw, &nc);
		fclose(f);
		printf("%8d%8d%8d\n", nl, nw, nc);
	}
}

// Count counts the number of lines, words and characters in f.
void count(FILE *f, unsigned int *nl, unsigned int *nw, unsigned int *nc) {
	int c;
	bool inword;

	*nl = *nw = *nc = 0;
	inword = false;

	while ((c = fgetc(f)) != EOF) {
		(*nc)++;
		(*nl) += c == '\n';
		switch (c) {
		case ' ':
		case '\t':
		case '\n':
			inword = false;
			break;
		default:
			if (!inword) {
				(*nw)++;
			}
			inword = true;
		}
	}
}
