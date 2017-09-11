#ifndef STK600_H
#define STK600_H

#include <stdint.h>
#include <stddef.h>

void stk600_process_command(int fd, uint8_t *command, size_t count);

#endif//STK600_H
