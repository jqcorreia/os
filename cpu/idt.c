#include "idt.h"
#include "../cpu/pic.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "type.h"

idt_entry_t idt_entries[256];
idt_ptr_struct idt_ptr;

isr_t irq_handlers[256];

void set_idt_gate(int n, u32 handler)
{
    idt_entries[n].always0 = 0;
    idt_entries[n].sel = KERNEL_CS;
    idt_entries[n].base_lo = low_16(handler);
    idt_entries[n].base_hi = high_16(handler);
    idt_entries[n].flags = 0x8E;
}

void init_idt()
{
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

    PIC_remap(0x20, 0x28);

    // Install the IRQs
    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);

    idt_ptr.base = (u32)&idt_entries;
    idt_ptr.limit = 256 * sizeof(idt_entry_t) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r"(&idt_ptr));
}

void isr_handler(registers_t r)
{
    char buf[255];

    int_to_ascii(r.int_no, buf);
    kprint(buf);
    kprint(" ");
    int_to_ascii(r.err_code, buf);
    kprint(buf);
    kprint("\n");
    /* char buf[10]; */
    /* int_to_ascii(no, buf); */

    /* kprint(buf); */
    if (r.int_no == 13) {
        asm("hlt");
    }
}

void register_irq_handler(int irq_no, isr_t handler)
{
    irq_handlers[irq_no] = handler;
}

void irq_handler(registers_t r)
{
    PIC_sendEOI(r.int_no);

    if (irq_handlers[r.int_no] != 0) {
        irq_handlers[r.int_no](r.int_no);
    }
    /* if (r.int_no == 33) { */
    /*     u8 scancode = port_byte_in(0x60); */
    /*     char buf[255]; */

    /*     kprint("IRQ "); */
    /*     int_to_ascii(r.int_no, buf); */
    /*     kprint(buf); */
    /*     kprint(" "); */
    /*     int_to_ascii(scancode, buf); */
    /*     kprint(buf); */
    /*     kprint("\n"); */
    /* } */
}
