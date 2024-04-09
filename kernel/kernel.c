#include "../drivers/ports.h"
#include "../drivers/screen.h"

void main() {
  clear_screen();
  print_char(2, 10, 'X', 0);
  kprint_at("Hello bitches!", 0, 5);
  /* // Create a pointer to a char , and point it to the first text cell of */
  /* // video memory (i.e. the top - left of the screen ) */
  /* char *video_memory = (char *)0xb8000; */
  /* // At the address pointed to by video_memory , store the character ’X’ */
  /* // (i.e. display ’X’ in the top - left of the screen ). */
  /* *video_memory = 'X'; */

  /* /1* for (int x = 0; x < 10; x++) { *1/ */
  /* /1*   video_memory[x * 2] = 'X'; *1/ */
  /* /1* } *1/ */

  /* int position; */

  /* port_byte_out(VGA_CONTROL_REGISTER, 14); */

  /* position = port_byte_in(VGA_DATA_REGISTER); */
  /* position = position << 8; */

  /* port_byte_out(VGA_CONTROL_REGISTER, 15); */
  /* position += port_byte_in(VGA_DATA_REGISTER); */

  /* video_memory[position * 2] = 'Y'; */
}
