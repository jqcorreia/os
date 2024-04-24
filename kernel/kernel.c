#include "../cpu/idt.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"

int main() {
  /* clear_screen(); */
  init_idt();
  /* kprint("It's me again\n"); */
  /* kprint("It's me again2\n"); */
  /* kprint_at("Hello bitches!\nA Sara e linda!\n", 0, 5); */

  /* char buf[5]; */
  /* int_to_ascii(1024, buf); */

  /* kprint(buf); */

  /* kprint_at("Hello bitches!\nA Sara e linda!\n", 0, 24); */
  /* int foo; */
  /* for (foo = 0; foo < 25; foo++) { */
  /*   char buf[4]; */
  /*   int_to_ascii(foo, buf); */
  /*   kprint(buf); */
  /*   kprint("\n"); */
  /* } */
  /* __asm__ __volatile__("int $1"); */
  __asm__ __volatile__("int $2");
  /* __asm__ __volatile__("int $2"); */
  __asm__ __volatile__("int $3");

  return 0;
}
