
CC = cc
LD = ld
NASM = nasm
OUTDIR = bin

all: $(OUTDIR)/prog

clean:
	rm -rf $(OUTDIR)

.PHONY: all clean

$(OUTDIR)/prog.o: prog.s | util.inc $(OUTDIR)
	$(NASM) -fmacho $^ -o $@

$(OUTDIR)/prog: $(addprefix $(OUTDIR)/,prog.o util.o) | $(OUTDIR)
	$(LD) $^ -lSystem /usr/lib/crt1.o -o $@

$(OUTDIR)/util.o: util.c | $(OUTDIR)
	$(CC) -m32 -c $^ -o $@

$(OUTDIR):
	mkdir -p $@
