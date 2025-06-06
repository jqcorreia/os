#include "serial.h"
#include "../drivers/ports.h"

int setup_serial()
{
    int base_port = PORT_COM1;
    int baud = 9600;

    unsigned short divisor = UART_FREQ / baud;

    // Disable interrupts
    port_byte_out(base_port + 1, 0x00);
    // Set DLAB
    port_byte_out(base_port + 3, 0x80);
    // Set divisor
    port_byte_out(base_port + 0, divisor & 0x00FF);
    port_byte_out(base_port + 1, divisor >> 8);
    // Unset DLAB and set 8 data bits, 1 stop bit, no parity. hi byte (0) disable DLAB, lo byte(3) sets 0011 meaning 8N1
    port_byte_out(base_port + 3, 0x03);

    port_byte_out(base_port + 4, 0xC7); // Enable FIFO, clear transmit FIFO and receive FIFO, 14 bytes threshold

    port_byte_out(base_port + 4, 0x0B); // IRQs enabled, RTS/DSR set ????
    port_byte_out(base_port + 4, 0x1E); // Set in loopback mode, test the serial chip ????
    port_byte_out(base_port + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (port_byte_in(base_port + 0) != 0xAE) {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    port_byte_out(base_port + 4, 0x0F);
    return 0;
}

/* static int init_serial() */
/* { */
/*     outb(PORT + 1, 0x00); // Disable all interrupts */
/*     outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor) */
/*     outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud */
/*     outb(PORT + 1, 0x00); //                  (hi byte) */
/*     outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit */
/*     outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold */
/*     outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set */
/*     outb(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip */
/*     outb(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte) */

/*     // Check if serial is faulty (i.e: not same byte as sent) */
/*     if (inb(PORT + 0) != 0xAE) { */
/*         return 1; */
/*     } */

/*     // If serial is not faulty set it in normal operation mode */
/*     // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled) */
/*     outb(PORT + 4, 0x0F); */
/*     return 0; */
/* } */
