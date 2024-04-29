#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../cpu/idt.h"

#define KEYBOARD_PORT 0x60

void keyboard_callback(int);
void setup_keyboard();

#endif
