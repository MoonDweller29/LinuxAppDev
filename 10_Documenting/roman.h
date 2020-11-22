/*!
\file
\brief file with definitions of functions for encoding numbers to roman encoding and back
*/
#pragma once

#define MAX_ROMAN 3999 ///< max possible roman number
#define MAX_ROMAN_LEN 30 ///< max length of roman number string 

/**
Prints arabic integer to charater buffer in roman encoding
\param[in] x arabic integer in range [1, #MAX_ROMAN]
\param[out] buf char buffer for containig roman number.
Should have size at least MAX_ROMAN_LEN to contain any possible roman number.
*/
int toRoman(int x, char *buf);
/**
Decodes arabic integer from string with roman number
\param[in] roman string with roman number
\return decoded arabic number 
*/
int toArabic(const char *roman);