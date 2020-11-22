/*!
\file
\brief file with realization of functions from roman.h

This file contains realization of functions
for encoding numbers to roman encoding and back
*/
#include "roman.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ROMAN_DOMAIN_COUNT 28 ///< count of different roman string domains

/// arabic numbers corresponding to roman domains
static int arabicNum[ROMAN_DOMAIN_COUNT] = {
    1000,
    900,
    800,
    700,
    600,
    500,
    400,
    300,
    200,
    100,
    90,
    80,
    70,
    60,
    50,
    40,
    30,
    20,
    10,
    9,
    8,
    7,
    6,
    5,
    4,
    3,
    2,
    1 
};


/// roman domains
static char romanNum[ROMAN_DOMAIN_COUNT][MAX_ROMAN_LEN] = {
    "M",
    "CM",
    "DCCC",
    "DCC",
    "DC",
    "D",
    "CD",
    "CCC",
    "CC",
    "C",
    "XC",
    "LXXX",
    "LXX",
    "LX",
    "L",
    "XL",
    "XXX",
    "XX",
    "X",
    "IX",
    "VIII",
    "VII",
    "VI",
    "V",
    "IV",
    "III",
    "II",
    "I"     
};

int toRoman(int x, char *buf)
{
	if (x > MAX_ROMAN || x <= 0) {
		printf("arabic number should be 0 < x < %d\n", MAX_ROMAN);
		return -1;
	}

	int str_shift = 0;
	for (int i = 0; i < ROMAN_DOMAIN_COUNT; ++i)
	{
		while (x >= arabicNum[i])
		{
			sprintf(buf+str_shift, "%s", romanNum[i]);
			x -= arabicNum[i];
			str_shift += strlen(romanNum[i]);
		}
	}

	return 0;
}

int toArabic(const char *roman)
{
	int x = 0;
	int str_shift = 0;
	for (int i = 0; i < ROMAN_DOMAIN_COUNT; ++i)
	{
		while (roman + str_shift == strstr(roman + str_shift, romanNum[i]))
		{
			x += arabicNum[i];
			str_shift += strlen(romanNum[i]);
		}
	}

	return x;
}