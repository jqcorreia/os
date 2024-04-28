#include "../drivers/ports.h"

void port_byte_out(unsigned short port, unsigned char data)
{
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

unsigned char port_byte_in(unsigned short port)
{
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    unsigned char data;
    __asm__("in %%dx, %%al" : "=a"(data) : "d"(port));

    return data;
}

unsigned short port_word_in(unsigned short port)
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : : "a"(data), "d"(port));
}
