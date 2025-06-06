#ifndef TYPE_H
#define TYPE_H

#define u32 unsigned int
#define s32 int
#define u16 unsigned short
#define s16 short
#define u8 unsigned char
#define s8 char

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif
