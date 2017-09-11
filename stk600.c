#include "stk600.h"

#include <stdio.h>
#include <unistd.h>

#include "hexdump.h"

void stk600_reply(int fd, uint8_t seq, uint8_t *reply, size_t count);

void stk600_process_command(int fd, uint8_t *command, size_t count)
{
    printf("Processing command\n");

    if (command[5] == 0x01) {
        stk600_reply(fd, command[1], "\x01\x00\x08STK600", 9);
    }
}

void stk600_reply(int fd, uint8_t seq, uint8_t *reply, size_t count)
{
    uint8_t msg[275];

    msg[0] = 0x1B;
    msg[1] = seq;
    msg[2] = count / 256;
    msg[3] = count % 256;
    msg[4] = 0x0E;

    for (int i = 0; i < count; i++) {
        msg[5 + i] = reply[i];
    }

    msg[5 + count] = 0;

    for (int i = 0; i < count + 5; i++) {
        msg[5 + count] ^= msg[i];
    }

    count += 6;
    write(fd, msg, count);

    printf("\nSent %d byte%s\n", count, count == 1 ? ":" : "s:");
    hexdump(msg, count);
    putchar('\n');
}
