CC 	= gcc
CFLAGS 	= -std=c99 -O2 -Wall -Wextra -Wpedantic -Iinclude
LIBS 	= -lm -lSDL2 -lSDL2_ttf

SRCDIR 	= src
OBJDIR	= build
TARGET 	= snake

SRC 	= $(wildcard $(SRCDIR)/*.c)
OBJ 	= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean
