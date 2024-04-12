#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "utils.h"

void main() {
  clear_screen();
  kprint("It's me again\n");
  kprint("It's me again2\n");
  kprint_at("Hello bitches!\nA Sara e linda!\n", 0, 5);
  /* kprint_at("X", 1, 6); */
  /* kprint_at("This text spans multiple lines", 75, 10); */
  /* kprint_at("There is a line\nbreak", 0, 20); */
  /* kprint("There is a line\nbreak"); */
  /* kprint_at("What happens when we run out of space?", 45, 24); */
  char buf[5];
  int_to_ascii(1024, buf);

  kprint(buf);
}
