CFLAGS = -Wall -Wextra
BINS = cat wc

all: $(BINS)

cat: cat.c
wc: wc.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	$(RM) $(BINS)
