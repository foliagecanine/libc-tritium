#ifndef _GUI_H
#define _GUI_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

void drawrect(size_t x, size_t y, size_t w, size_t h, uint8_t color);
char *fileselector(char *cd, bool newfile);

#endif
