#include "idt.h"
#include "type.h"

idt_entry_t idt_entries[256];
idt_ptr_struct idt_ptr;

void set_idt_gate(int n, u32 handler) {
  idt_entries[n].always0 = 0;
  idt_entries[n].sel = KERNEL_CS;
  idt_entries[n].base_lo = handler & 0x0000FFFF;
  idt_entries[n].base_hi = handler >> 16 & 0xFFFF0000;
  idt_entries[n].flags = 0b10000110;
}

static void init_idt() {
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = &idt_entries;
}
