#include "serial.h"
#include "../drivers/ports.h"

void setup_serial()
{
    port_byte_out(PORT_COM1, 'a');
    port_byte_out(PORT_COM1, 'b');
    port_byte_out(PORT_COM1, 'c');
    port_byte_out(PORT_COM1, 'd');
    port_byte_out(PORT_COM1, '\n');
}
