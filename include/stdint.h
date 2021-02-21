#ifndef _STDINT_H
#define _STDINT_H

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long long int_least64_t;

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long uint_least64_t;

typedef char int_fast8_t;
typedef short int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;

typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long uint_fast64_t;

typedef long intptr_t;
typedef unsigned long uintptr_t;

typedef long long intmax_t;
typedef unsigned long long uintmax_t;

#define INT8_MIN 		-128
#define INT8_MAX 		127
#define INT16_MIN 		-32768
#define INT16_MAX 		32767
#define INT32_MIN 		-2147483648
#define INT32_MAX 		2147483647
#define INT64_MIN 		-9223372036854775808
#define INT64_MAX 		9223372036854775807

#define INT_LEAST8_MIN 	-128
#define INT_LEAST8_MAX 	127
#define INT_LEAST16_MIN 	-32768
#define INT_LEAST16_MAX 	32767
#define INT_LEAST32_MIN 	-2147483648
#define INT_LEAST32_MAX 	2147483647
#define INT_LEAST64_MIN 	-9223372036854775808
#define INT_LEAST64_MAX 	9223372036854775807

#define INT_FAST8_MIN 		-128
#define INT_FAST8_MAX 		127
#define INT_FAST16_MIN 	-32768
#define INT_FAST16_MAX 	32767
#define INT_FAST32_MIN 	-2147483648
#define INT_FAST32_MAX 	2147483647
#define INT_FAST64_MIN 	-9223372036854775808
#define INT_FAST64_MAX 	9223372036854775807

#define UINT8_MIN 0
#define UINT8_MAX 		255
#define UINT16_MIN 		0
#define UINT16_MAX 		65535
#define UINT32_MIN 		0
#define UINT32_MAX 		4294967295
#define UINT64_MIN 		0
#define UINT64_MAX 		18446744073709551615

#define UINT_LEAST8_MIN 	0
#define UINT_LEAST8_MAX 	255
#define UINT_LEAST16_MIN 	0
#define UINT_LEAST16_MAX 	65535
#define UINT_LEAST32_MIN 	0
#define UINT_LEAST32_MAX 	4294967295
#define UINT_LEAST64_MIN 	0
#define UINT_LEAST64_MAX 	18446744073709551615

#define UINT_FAST8_MIN 	0
#define UINT_FAST8_MAX 	255
#define UINT_FAST16_MIN 	0
#define UINT_FAST16_MAX 	65535
#define UINT_FAST32_MIN 	0
#define UINT_FAST32_MAX 	4294967295
#define UINT_FAST64_MIN 	0
#define UINT_FAST64_MAX 	18446744073709551615

#define INTPTR_MIN 		-2147483648
#define INTPTR_MAX 		2147483647
#define UINTPTR_MIN 		0
#define UINTPTR_MAX 		4294967295

#define INTMAX_MIN		-9223372036854775808
#define INTMAX_MAX		9223372036854775807
#define UINTMAX_MAX		18446744073709551615

#endif
