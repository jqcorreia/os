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
} idt_ptr_struct;

static void init_idt();

#endif
