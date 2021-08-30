#include <stdio.h>
#include <stdbool.h>

void count(FILE *);

// Wc counts the number of lines, words and characters for each file in the
// argument list and prints it to the standard output. If no argument is
// passed, it reads from the standard input.
int main(int argc, char **argv) {
	FILE *f;

	if (argc == 1) {
		count(stdin);
		return 0;
	}

	while (*++argv) {
		f = fopen(*argv, "r");
		if (f == NULL) {
			fprintf(stderr, "wc: %s: No such file or directory\n", *argv);
			continue;
		}
		count(f);
		fclose(f);
	}
}

// Count prints the number of lines, words and characters in f to stdout.
void count(FILE *f) {
	unsigned int nl, nw, nc;
	int c;
	bool inword;

	nl = nw = nc = 0;
	inword = false;

	while ((c = fgetc(f)) != EOF) {
		nc++;
		nl += c == '\n';
		switch (c) {
		case ' ':
		case '\t':
		case '\n':
			inword = false;
			break;
		default:
			if (!inword) {
				nw++;
			}
			inword = true;
		}
	}

	printf("%8d%8d%8d\n", nl, nw, nc);
}
