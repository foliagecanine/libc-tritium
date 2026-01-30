#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int ispunct(int c) {
	unsigned char uc = (unsigned char)c;
	return uc == '!' || uc == '"' || uc == '#' || uc == '$' || uc == '%' || uc == '&'
		|| uc == '\'' || uc == '(' || uc == ')' || uc == '*' || uc == '+' || uc == ','
		|| uc == '-' || uc == '.' || uc == '/' || uc == ':' || uc == ';' || uc == '<'
		|| uc == '=' || uc == '>' || uc == '?' || uc == '@' || uc == '[' || uc == '\\'
		|| uc == ']' || uc == '^' || uc == '_' || uc == '`' || uc == '{' || uc == '|'
		|| uc == '}' || uc == '~';
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif