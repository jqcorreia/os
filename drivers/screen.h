#define VGA_CONTROL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_MEMORY_ADDR 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25
#define WHITE_ON_BLACK 0x0f;

void clear_screen();
void kprint_at(char *message, int row, int col);
void kprint(char *message);
