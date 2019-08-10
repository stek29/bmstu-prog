CC = i686-w64-mingw32-gcc
CFLAGS = -Wl,--enable-stdcall-fixup

.PHONY: all
all: prog.exe

SOURCES = \
					contains.c \
					io.c \
					test_tokenize.c

prog.exe: $(SOURCES) l5asm/l5asm.obj
	$(CC) $(CFLAGS) $^ -o $@

l5asm/l5asm.obj:
	echo "Please assemble l5asm.obj with masm"
	exit 1

.PHONY: clean
clean:
	rm -f prog.exe
