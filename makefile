### If you wish to use extra libraries (math.h for instance),
### add their flags here (-lm in our case) in the "LIBS" variable.

LIBS = -lm

###
CC = clang
CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: main
main: main.out
	@echo Executing $@
	@echo =====================
	@./main.out
	@echo =====================
	@echo "Memory check passed"

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM

main.out: ./*.c
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) ./*.c -o main.out $(LIBS)
