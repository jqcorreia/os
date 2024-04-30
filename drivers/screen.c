#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include "../kernel/utils.h"

int get_offset(int col, int row) { return (row * MAX_COLS + col) * 2; }
int get_offset_row(int offset) { return (offset / (2 * MAX_COLS)); }
int get_offset_col(int offset) { return (offset % (2 * MAX_COLS) / 2); }
/* int get_offset_col(int offset) { */
/*   return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2; */
/* } */

int get_cursor_offset()
{
    int position;

    // Read high byte (and shift it)
    port_byte_out(VGA_CONTROL_REGISTER, 14);
    position = port_byte_in(VGA_DATA_REGISTER);
    position = position << 8;

    // Read low byte
    port_byte_out(VGA_CONTROL_REGISTER, 15);
    position += port_byte_in(VGA_DATA_REGISTER);

    return position * 2;
}

void set_cursor_offset(int offset)
{
    offset /= 2;

    // Just write high byte and low byte, based on computed offset
    port_byte_out(VGA_CONTROL_REGISTER, 14);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char)(offset >> 8));
    port_byte_out(VGA_CONTROL_REGISTER, 15);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char)(offset & 0xFF));
}

int print_char(int col, int row, char ch, char attr)
{
    char* vga = (char*)VGA_MEMORY_ADDR;

    if (!attr) {
        attr = WHITE_ON_BLACK;
    }

    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else
        offset = get_cursor_offset();

    if (ch == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);

    } else if (ch == '\b') {
        offset -= 2;
        vga[offset] = ' ';
        vga[offset + 1] = attr;
    } else {
        vga[offset] = ch;
        vga[offset + 1] = attr;
        offset += 2;
    }

    if (get_offset_row(offset) > MAX_ROWS - 1) {
        memory_copy((void*)VGA_MEMORY_ADDR + MAX_COLS * 2, (void*)VGA_MEMORY_ADDR,
            MAX_COLS * (MAX_ROWS - 1) * 2);

        char* last_line = vga + ((MAX_ROWS - 1) * MAX_COLS * 2);

        for (int i = 0; i < MAX_COLS; i++) {
            last_line[i * 2] = 0;
            last_line[i * 2 + 1] = 0x0F;
        }

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);

    return offset;
}

void clear_screen()
{
    char* vga = (char*)VGA_MEMORY_ADDR;

    for (int col = 0; col < MAX_COLS; col++) {
        for (int row = 0; row < MAX_ROWS; row++) {
            int idx = get_offset(col, row);
            vga[idx] = ' ';
            vga[idx + 1] = 0x1F;
        }
    }

    set_cursor_offset(get_offset(0, 0));
}

void kprint_at(char* message, int col, int row)
{
    /* set_cursor_offset(get_offset(col, row)); */
    char* ch = message;
    int offset;
    while (*ch != '\0') {
        offset = print_char(col, row, *ch, 0);
        row = get_offset_row(offset);
        col = get_offset_col(offset);

        ch += 1;
    }
}

void kprint(char* message) { kprint_at(message, -1, -1); }
