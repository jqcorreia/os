#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main() {
  clear_screen();
  /* kprint("It's me again\n"); */
  /* kprint("It's me again2\n"); */
  /* print_char(2, 10, 'X', 0); */
  /* kprint_at("Hello bitches!\nA Sara e linda!\n", 0, 5); */
  kprint_at("X", 1, 6);
  kprint_at("This text spans multiple lines", 75, 10);
  kprint_at("There is a line\nbreak", 0, 20);
  kprint("There is a line\nbreak");
  kprint_at("What happens when we run out of space?", 45, 24);
}
