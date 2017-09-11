TARGET	= stk-sim

SRCS	= main.c hexdump.c pty.c timed_read.c stk600.c

OBJS=$(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
