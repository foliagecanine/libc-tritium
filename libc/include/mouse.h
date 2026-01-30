#ifndef _MOUSE_H
#define _MOUSE_H

#include <stdbool.h>
#include <stdint.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int get_mouse_deltaX();
int get_mouse_deltaY();
int get_mouse_deltaZ();
uint8_t get_mouse_buttons();
bool get_mouse_button_lclick();
bool get_mouse_button_rclick();
bool get_mouse_button_mclick();

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif

#endif
