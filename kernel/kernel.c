#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main() {
  clear_screen();
  kprint("It's me again\n");
  kprint("It's me again2\n");
  /* print_char(2, 10, 'X', 0); */
  /* kprint_at("Hello bitches!\nA Sara e linda!\n", 0, 5); */
}
