#ifndef __COLOR_H__
#define __COLOR_H__

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

#include <stdio.h>

// Use this to set the background or foreground color
#define SET_COLOR(x)	puts(x)

// Background console colors
#define BG_BLACK		"\x1b[40;0m"
#define BG_GRAY			"\x1b[40;1m"
#define BG_RED			"\x1b[41;1m"
#define BG_GREEN		"\x1b[42;1m"
#define BG_YELLOW		"\x1b[43;1m"
#define BG_BLUE			"\x1b[44;1m"
#define BG_PURPLE		"\x1b[45;0m"
#define BG_MAGENTA	"\x1b[45;1m"
#define BG_CYAN			"\x1b[46;1m"
#define BG_WHITE		"\x1b[47;1m"

// Foreground console colors
#define FG_BLACK		"\x1b[30;0m"
#define FG_GRAY			"\x1b[30;1m"
#define FG_RED			"\x1b[31;1m"
#define FG_GREEN		"\x1b[32;1m"
#define FG_YELLOW		"\x1b[33;1m"
#define FG_BLUE			"\x1b[34;1m"
#define FG_PURPLE		"\x1b[35;0m"
#define FG_MAGENTA	"\x1b[35;1m"
#define FG_CYAN			"\x1b[36;1m"
#define FG_WHITE		"\x1b[37;1m"

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif
