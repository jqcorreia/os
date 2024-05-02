#include "../cpu/idt.h"
#include "../drivers/keyboard.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "../libc/mem.h"

void init_timer(u32 freq)
{
    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low = (u8)(divisor & 0xFF);
    u8 high = (u8)((divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}

void timer_irq_handler(int irq_no)
{
    /* kprint("Tick, Tock\n"); */
}
int main()
{
    init_idt();
    setup_keyboard();
    register_irq_handler(32, timer_irq_handler);

    __asm__ __volatile__("sti"); // Enable interrupts

    init_timer(1000);

    u32 page = kmalloc(1000, 1, 0);
    char buf[256];

    int_to_ascii(page, &buf);
    kprint(buf);
    kprint("\n");

    page = kmalloc(1000, 1, 0);

    char buf2[256];
    int_to_ascii(page, &buf2);
    kprint(buf2);
    kprint("\n");
}
