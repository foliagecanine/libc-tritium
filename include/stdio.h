#ifndef _STDIO_H
#define _STDIO_H 1

//#include <sys/cdefs.h>
#include <stdint.h>
#include <sys.h>
#include <tty.h>
#include <stdlib.h>
#include <stdarg.h>

#define EOF (-1)
#define FOPEN_MAX 255
#define FILENAME_MAX 12

#define _FILE_FLAGS_ERR (1 << 0)
#define _FILE_FLAGS_EOF (1 << 1)
#define _FILE_FLAGS_TMP (1 << 2)

#ifdef __cplusplus
extern "C"
{
#endif

#define true 1
#define false 0
#define bool _Bool

    int          __print_formatted(int (*printfn)(const char *, size_t), const char *format, va_list parameters);
    int          printf(const char *__restrict, ...);
    int          putchar(int);
    int          puts(char *str);
    int          sprintf(char *s, const char *format, ...);
    int          snprintf(char *s, size_t n, const char *format, ...);
    int          vsprintf(char *s, const char *format, va_list arg);
    int          vsnprintf(char *s, size_t n, const char *format, va_list arg);
    int          vsscanf(const char *s, const char *format, va_list parameters);
    int          sscanf(const char *s, const char *format, ...);
    void         terminal_clear();
    void         terminal_init();
    char         getchar();
    unsigned int getkey();

    enum kbdin_key
    {
        KBDIN_KEY_NONE = 0,
        KBDIN_KEY_ESCAPE,
        KBDIN_KEY_1,
        KBDIN_KEY_2,
        KBDIN_KEY_3,
        KBDIN_KEY_4,
        KBDIN_KEY_5,
        KBDIN_KEY_6,
        KBDIN_KEY_7,
        KBDIN_KEY_8,
        KBDIN_KEY_9,
        KBDIN_KEY_0,
        KBDIN_KEY_MINUS,
        KBDIN_KEY_EQUALS,
        KBDIN_KEY_BACKSPACE,
        KBDIN_KEY_TAB,
        KBDIN_KEY_Q,
        KBDIN_KEY_W,
        KBDIN_KEY_E,
        KBDIN_KEY_R,
        KBDIN_KEY_T,
        KBDIN_KEY_Y,
        KBDIN_KEY_U,
        KBDIN_KEY_I,
        KBDIN_KEY_O,
        KBDIN_KEY_P,
        KBDIN_KEY_OPEN_BRACKET,
        KBDIN_KEY_CLOSE_BRACKET,
        KBDIN_KEY_ENTER,
        KBDIN_KEY_LCONTROL,
        KBDIN_KEY_A,
        KBDIN_KEY_S,
        KBDIN_KEY_D,
        KBDIN_KEY_F,
        KBDIN_KEY_G,
        KBDIN_KEY_H,
        KBDIN_KEY_J,
        KBDIN_KEY_K,
        KBDIN_KEY_L,
        KBDIN_KEY_SEMICOLON,
        KBDIN_KEY_APOSTROPHE,
        KBDIN_KEY_BACKTICK,
        KBDIN_KEY_LSHIFT,
        KBDIN_KEY_BACKSLASH,
        KBDIN_KEY_Z,
        KBDIN_KEY_X,
        KBDIN_KEY_C,
        KBDIN_KEY_V,
        KBDIN_KEY_B,
        KBDIN_KEY_N,
        KBDIN_KEY_M,
        KBDIN_KEY_COMMA,
        KBDIN_KEY_PERIOD,
        KBDIN_KEY_SLASH,
        KBDIN_KEY_RSHIFT,
        KBDIN_KEY_PRINTSCREEN,
        KBDIN_KEY_KP_ASTERISK = 0x37,
        KBDIN_KEY_LALT,
        KBDIN_KEY_SPACE,
        KBDIN_KEY_CAPSLOCK,
        KBDIN_KEY_F1,
        KBDIN_KEY_F2,
        KBDIN_KEY_F3,
        KBDIN_KEY_F4,
        KBDIN_KEY_F5,
        KBDIN_KEY_F6,
        KBDIN_KEY_F7,
        KBDIN_KEY_F8,
        KBDIN_KEY_F9,
        KBDIN_KEY_F10,
        KBDIN_KEY_NUMLOCK,
        KBDIN_KEY_SCROLLLOCK,
        KBDIN_KEY_HOME,
        KBDIN_KEY_KP_7 = 0x47,
        KBDIN_KEY_UPARROW,
        KBDIN_KEY_KP_8 = 0x48,
        KBDIN_KEY_PAGEUP,
        KBDIN_KEY_KP_9 = 0x49,
        KBDIN_KEY_KP_MINUS,
        KBDIN_KEY_LEFTARROW,
        KBDIN_KEY_KP_4 = 0x4B,
        KBDIN_KEY_KP_5,
        KBDIN_KEY_RIGHTARROW,
        KBDIN_KEY_KP_6 = 0x4D,
        KBDIN_KEY_KP_PLUS,
        KBDIN_KEY_END,
        KBDIN_KEY_KP_1 = 0x4F,
        KBDIN_KEY_DOWNARROW,
        KBDIN_KEY_KP_2 = 0x50,
        KBDIN_KEY_PAGEDOWN,
        KBDIN_KEY_KP_3 = 0x51,
        KBDIN_KEY_INSERT,
        KBDIN_KEY_KP_0 = 0x52,
        KBDIN_KEY_DELETE,
        KBDIN_KEY_KP_PERIOD = 0x52,
        KBDIN_KEY_ALT_SYSRQ,
        KBDIN_KEY_F11 = 0x57,
        KBDIN_KEY_F12 = 0x58,

        KBDIN_KEY_RELEASED = 0x80,
    };

    void terminal_backup();
    void terminal_setcolor(uint8_t color);

#ifndef _VGA_COLOR
#define _VGA_COLOR
    enum vga_color
    {
        VGA_COLOR_BLACK         = 0,
        VGA_COLOR_BLUE          = 1,
        VGA_COLOR_GREEN         = 2,
        VGA_COLOR_CYAN          = 3,
        VGA_COLOR_RED           = 4,
        VGA_COLOR_MAGENTA       = 5,
        VGA_COLOR_BROWN         = 6,
        VGA_COLOR_LIGHT_GREY    = 7,
        VGA_COLOR_DARK_GREY     = 8,
        VGA_COLOR_LIGHT_BLUE    = 9,
        VGA_COLOR_LIGHT_GREEN   = 10,
        VGA_COLOR_LIGHT_CYAN    = 11,
        VGA_COLOR_LIGHT_RED     = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN   = 14,
        VGA_COLOR_WHITE         = 15,
    };

    static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) { return fg | bg << 4; }
#endif

    typedef struct
    {
        uint64_t location;
        uint64_t size;
        uint8_t  mountNumber;
        uint32_t clusterNumber; // For FAT based systems
        uint64_t dir_entry;
        uint8_t  flags;
        int32_t  desc;
        _Bool    valid;
        _Bool    directory;
        _Bool    writelock;
    } FILE, *PFILE;

    FILE *  openfile(const char *filename, const char *mode);
    uint8_t readfile(FILE *file, char *buf, uint64_t start, uint32_t len);
    uint8_t writefile(FILE *file, char *buf, uint64_t start, uint32_t len);
    FILE *  createfile(const char *filename);
    uint8_t deletefile(const char *filename);
    bool    existfile(const char *filename);
    FILE *  finddir(FILE *d, char *buf, uint32_t n);
    int     closefile(FILE *fp);

#ifdef __cplusplus
}
#endif

#endif
