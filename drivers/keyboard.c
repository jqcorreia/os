#include "keyboard.h"
#include "../cpu/idt.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"

char scancodes_ascii[256];

void setup_qwerty()
{
    // Qwerty scancode conversion
    scancodes_ascii[0x1c] = '\n';
    scancodes_ascii[0x39] = ' ';
    scancodes_ascii[0x0e] = ' ';

    scancodes_ascii[0x2] = '1';
    scancodes_ascii[0x3] = '2';
    scancodes_ascii[0x4] = '3';
    scancodes_ascii[0x5] = '4';
    scancodes_ascii[0x6] = '5';
    scancodes_ascii[0x7] = '6';
    scancodes_ascii[0x8] = '7';
    scancodes_ascii[0x9] = '8';
    scancodes_ascii[0xA] = '9';
    scancodes_ascii[0xB] = '0';

    scancodes_ascii[0x10] = 'q';
    scancodes_ascii[0x11] = 'w';
    scancodes_ascii[0x12] = 'e';
    scancodes_ascii[0x13] = 'r';
    scancodes_ascii[0x14] = 't';
    scancodes_ascii[0x15] = 'y';
    scancodes_ascii[0x16] = 'u';
    scancodes_ascii[0x17] = 'i';
    scancodes_ascii[0x18] = 'o';
    scancodes_ascii[0x19] = 'p';

    scancodes_ascii[0x1e] = 'a';
    scancodes_ascii[0x1f] = 's';
    scancodes_ascii[0x20] = 'd';
    scancodes_ascii[0x21] = 'f';
    scancodes_ascii[0x22] = 'g';
    scancodes_ascii[0x23] = 'h';
    scancodes_ascii[0x24] = 'j';
    scancodes_ascii[0x25] = 'k';
    scancodes_ascii[0x26] = 'l';

    scancodes_ascii[0x2c] = 'z';
    scancodes_ascii[0x2d] = 'x';
    scancodes_ascii[0x2e] = 'c';
    scancodes_ascii[0x2f] = 'v';
    scancodes_ascii[0x30] = 'b';
    scancodes_ascii[0x31] = 'n';
    scancodes_ascii[0x32] = 'm';
}

void keyboard_callback(int irq_no)
{
    u8 scancode = port_byte_in(KEYBOARD_PORT);
    if (scancode > 0x7c) {
        // Keyup, do nothing
    }
    if (scancodes_ascii[scancode] != 0) {
        char buf[2];
        buf[0] = scancodes_ascii[scancode];
        buf[1] = 0;
        kprint(buf);
    }
}

void setup_keyboard()
{
    register_irq_handler(33, keyboard_callback);
    setup_qwerty();
}
