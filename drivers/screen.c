#include "../drivers/screen.h"
#include "../drivers/ports.h"

int get_offset(int col, int row) { return (row * MAX_COLS + col) * 2; }

int get_cursor_offset() {
  int position;

  // Read high byte (and shift it)
  port_byte_out(VGA_CONTROL_REGISTER, 14);
  position = port_byte_in(VGA_DATA_REGISTER);
  position = position << 8;

  // Read low byte
  port_byte_out(VGA_CONTROL_REGISTER, 15);
  position += port_byte_in(VGA_DATA_REGISTER);

  return position;
}

void set_cursor_offset(int offset) {
  offset /= 2;

  // Just write high byte and low byte, based on computed offset
  port_byte_out(VGA_CONTROL_REGISTER, 14);
  port_byte_out(VGA_DATA_REGISTER, (unsigned char)(offset >> 8));
  port_byte_out(VGA_CONTROL_REGISTER, 15);
  port_byte_out(VGA_DATA_REGISTER, (unsigned char)(offset & 0xFF));
}

int print_char(int col, int row, char ch, char attr) {
  char *vga = (char *)VGA_MEMORY_ADDR;

  if (!attr) {
    attr = WHITE_ON_BLACK;
  }

  int offset = get_offset(col, row);
  vga[offset] = ch;
  vga[offset + 1] = attr;

  // Add support for newline
  set_cursor_offset(offset + 2);

  return offset + 2;
}

void clear_screen() {
  char *vga = (char *)VGA_MEMORY_ADDR;

  for (int col = 0; col < MAX_COLS; col++) {
    for (int row = 0; row < MAX_ROWS; row++) {
      int idx = get_offset(col, row);
      vga[idx] = ' ';
      vga[idx + 1] = 0x1F;
    }
  }
}

void kprint_at(char *message, int col, int row) {
  set_cursor_offset(get_offset(col, row));
  char *ch = message;
  while (*ch != '\0') {
    print_char(col++, row++, *ch, 0);
  }
}

void kprint(char *message) {}
