
CC = cc
NASM = nasm
OUTDIR = bin
CFLAGS += -fno-PIC -m32
LDFLAGS += -no_pie -read_only_relocs suppress
NASMFLAGS += -fmacho

DEBUG ?= 0
ifneq ($(DEBUG), 0)
	CFLAGS += -DDEBUG -g
	NASMFLAGS += -dDEBUG
endif


all: $(OUTDIR)/prog

clean:
	rm -rf $(OUTDIR)

.PHONY: all clean

$(OUTDIR)/asm.o: asm.s | $(OUTDIR)
	$(NASM) $(NASMFLAGS) $^ -o $@

$(OUTDIR)/clang.o: clang.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $^ -o $@

WLPREFIX=-Wl,
$(OUTDIR)/prog: $(addprefix $(OUTDIR)/,asm.o clang.o) | $(OUTDIR)
	$(CC) $(CFLAGS) $(addprefix $(WLPREFIX),$(LDFLAGS)) $^ -o $@

$(OUTDIR):
	mkdir -p $@

