#ifndef _PIC_H
#define _PIC_H

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define PIC_ICW1_INIT 0x10
#define PIC_ICW1_ICW4 0x01 // OR it the init word to say it has a 4th word
//
#define PIC_ICW4_8086 0x01
//
#include "../cpu/type.h"

/* On-boot interrupt mappings
Chip	    Interrupt numbers (IRQ)	Vector offset	Interrupt Numbers
Master PIC	0 to 7	                0x08  	        0x08 to 0x0F
Slave PIC	8 to 15              	0x70            0x70 to 0x77
*/

#define PIC_EOI 0x20

void PIC_sendEOI(u8 irq);
void PIC_remap(int offset_pic1, int offset_pic2);

#endif
