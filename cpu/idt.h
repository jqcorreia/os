#ifndef IDT_H
#define IDT_H

#include "./type.h"

#define KERNEL_CS 0x08

typedef struct {
    u16 base_lo;
    u16 sel;
    u8 always0;
    u8 flags;
    u16 base_hi;
} __attribute((packed)) idt_entry_t;

typedef struct {
    u16 limit;
    u32 base;
} __attribute((packed)) idt_ptr_struct;

/* Struct which aggregates many registers */
typedef struct {
    u32 ds; /* Data segment selector */
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
    u32 int_no, err_code; /* Interrupt number and error code (if applicable) */
    u32 eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;

void init_idt();
void idr_handler(registers_t r);
void set_idt_gate(int n, u32 handler);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
#endif

typedef void (*isr_t)(int);

void register_irq_handler(int irq_no, isr_t);
