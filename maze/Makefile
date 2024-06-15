PREFIX ?= 
CC ?= ${PREFIX}gcc
CFLAGS = -Wall -Wextra -DCOMPLEX=${CPX}
LDFLAGS = -lncurses 
OBJDIR = bin
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))
TARGET = maze

CPX ?= 0

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(TARGET)
	rm -rf $(OBJDIR)

rebuild: clean all

.PHONY: all clean rebuild