#include "../libc/mem.h"
#include "../cpu/type.h"

u32 free_memory_addr = FREE_MEMORY_START;

u32 kmalloc(int size, char align, u32* phys_addr)
{
    if (align && (free_memory_addr & 0xFFFFF000)) {
        free_memory_addr &= 0xFFFFF000;
        free_memory_addr += PAGE_SIZE;
    }
    if (phys_addr)
        phys_addr = free_memory_addr;

    u32 ret = free_memory_addr;

    free_memory_addr += size;

    return ret;
}
