#include <stdio.h>
#include <mouse.h>
#include <sys.h>

char savechar;
unsigned int savekey;
bool charused = true;
bool charzero = false;
bool keyused = true;

char getchar() {
	if (charzero) {
		charzero = false;
		return 0;
	} if (charused) {
		uint32_t out = _syscall1(5, 0);
		savekey = (unsigned int)(out&0xFF);
		keyused = false;
		charused = true;
		if (savekey<0x80) {
			charzero = true;
			return (char)((out>>8)&0xFF);
		} else
			return 0;
	} else {
		charused = true;
		return savechar;
	}
}

unsigned int getkey() {
	if (keyused) {
		uint32_t out = _syscall1(5, 0);
		if ((out&0xFF)<0x80) {
			savechar = (unsigned int)((out>>8)&0xFF);
			charused = false;
			charzero = false;
		} else {
			charzero = true;
		}
		keyused = true;
		return (unsigned int)(out&0xFF);
	} else {
		keyused = true;
		return savekey;
	}
}

int get_mouse_deltaX() {
	return _syscall1(5, 1);
}

int get_mouse_deltaY() {
	return _syscall1(5, 2);
}

int get_mouse_deltaZ() {
	return _syscall1(5, 3);
}

uint8_t get_mouse_buttons() {
	return _syscall1(5, 4);
}

bool get_mouse_button_lclick() {
	return _syscall1(5, 4) & 1;
}

bool get_mouse_button_rclick() {
	return _syscall1(5, 4) & 2;
}

bool get_mouse_button_mclick() {
	return _syscall1(5, 4) & 4;
}
