# Cross-compiler and flags, fallback if not defined externally
CC ?= $(CROSS_COMPILE)gcc
#CFLAGS ?= -Wall
LDFLAGS ?= -li2c
CFLAGS = -I/usr/local/include -Wall
TARGET = bme280
OBJS = bme280.o compensation.o

# Default target
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) -li2c

# Pattern rule to compile .c to .o, depending on corresponding .h
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f *.o $(TARGET)
