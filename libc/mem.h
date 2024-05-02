#ifndef _MEM_H
#define _MEM_H

#include "../cpu/type.h"

#define FREE_MEMORY_START 0x10000
#define PAGE_SIZE 0x1000

u32 kmalloc(int size, char align, u32* phys_addr);
#endif
