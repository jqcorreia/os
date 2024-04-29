#include "pic.h"
#include "../drivers/ports.h"

void PIC_sendEOI(unsigned char irq)
{
    if (irq >= 8) {
        port_byte_out(PIC2_COMMAND, PIC_EOI);
    }
    port_byte_out(PIC1_COMMAND, PIC_EOI);
}

void PIC_remap(int offset_pic1, int offset_pic2)
{
    u8 init_cmd = PIC_ICW1_INIT | PIC_ICW1_ICW4;

    /* // Save the previous masks. Why??! */
    u8 mask1, mask2;
    mask1 = port_byte_in(PIC1_DATA);
    mask2 = port_byte_in(PIC2_DATA);

    port_byte_out(PIC1_COMMAND, init_cmd); // Send init command
    port_byte_out(PIC2_COMMAND, init_cmd);

    port_byte_out(PIC1_DATA, offset_pic1); // Set offset
    port_byte_out(PIC2_DATA, offset_pic2);

    port_byte_out(
        PIC1_DATA,
        4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 * 0100) */
    port_byte_out(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)

    port_byte_out(PIC1_DATA,
        PIC_ICW4_8086); // Put both master and slave PIC in 8086 mode

    port_byte_out(PIC2_DATA, PIC_ICW4_8086);

    // Restore saved masks, why again?
    port_byte_out(PIC1_DATA, mask1);
    port_byte_out(PIC2_DATA, mask2);
}
