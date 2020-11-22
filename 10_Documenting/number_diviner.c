/*! 
\mainpage Main page
number_diviner : a simple terminal game

###Rules:

Choose a number in range [1, 100] and the programm will try to divine it  

###Usage: number_diviner [options]

###options:
 -  -r             enable roman numbers
 -  -h, --help     print help
*/

/*!
\file
\brief main file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <unistd.h>
#include <getopt.h>

#include "roman.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

#define BUF_SIZE 30
#define WRONG_INPUT -1 ///< incorrect input
#define YES 1 ///< positive answer
#define NO 0 ///< negative answer

int roman_encoding = 0; ///< if true program will work with roman numbers, otherwise - with arabic

/**
\brief prints integer to string according to #roman_encoding
prints integer to string according to #roman_encoding
\param[in] x arabic integer in range [1, #MAX_ROMAN]
\param[out] buf char buffer for containig roman or arabic number.
*/
char *intToS(int x, char *buf) {
    if (roman_encoding) {
        toRoman(x, buf);
    } else {
        sprintf(buf, "%d", x);
    }

    return buf;
}

/**
\brief extracts user answer from string
extracts user answer from string
\param[in] str string with user input
\return integer code of answer (one of #YES, #NO, #WRONG_INPUT)
*/
int check_answer(const char* str) {
    if (strcmp(str, _("Yes")) == 0 ||
        strcmp(str, _("yes")) == 0 ||
        strcmp(str, _("Y"))   == 0 ||
        strcmp(str, _("y"))   == 0) {
        return YES;
    } else if (
        strcmp(str, _("No")) == 0 ||
        strcmp(str, _("no")) == 0 ||
        strcmp(str, _("N"))   == 0 ||
        strcmp(str, _("n"))   == 0) {
        return NO;
    }
    else {
        printf(_("wrong input\n"));
        return WRONG_INPUT;
    }
}

/**
\brief reads user input line to buffer
reads user input line to buffer, ingoring extra chars in line
\param[out] buf buffer where user input will be stored
\param[in] size size of buffer. All extra chars from input line would be ignored
*/
void read_to_buf(char buf[], int size) {
    int i = 0;
    int c = getchar();
    while (i < size-1 && c != '\n' && c != EOF) {
        buf[i] = c;
        
        ++i;
        c = getchar();
    }
    buf[i] = '\0';
    if (i == size-1) {
        return;
    }
    if (c == EOF) {
        exit(0);
    }
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
}

/**
\brief core function of the program
makes bin search of user's number in specified range
\param[in] low low border of input range [low, high]
\param[out] high high border of input range [low, high]
\return returns user's number
*/
int bin_search(int low, int high) {
    char buf[BUF_SIZE];
    char number_str[BUF_SIZE];

    while (low < high) {
        int mid = (high - low)/2 + low;
        printf(_("Is the number higher than %s?\n"), intToS(mid, number_str));
        
        read_to_buf(buf, BUF_SIZE);
        int answer = check_answer(buf);
        while(answer == WRONG_INPUT) {
            read_to_buf(buf, BUF_SIZE);
            answer = check_answer(buf);
        }
        if (answer == YES) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}


/**
This function prints help info
*/
void printHelp() {
    printf("%s", _(
        "number_diviner : a simple terminal game\n"
        "\nRules:\n"
        "Choose a number in range [1, 100] and the programm will try to divine it\n"  
        "Usage: number_diviner [options]\n"
        "Options:\n"
        "  -r             enable roman numbers\n"
        "  -h, --help     print help\n"
    ));
}

int main(int argc, char **argv)
{
    int help = 0;
    int print_version = 0;
    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];


    const char* short_options = "rh";
    const struct option long_options[] = {
        {"help",    no_argument, NULL,'h'},
        {"version", no_argument, NULL,'v'},
        {NULL,0,NULL,0}
    };

    int rez;
    int option_index;

    while ((rez=getopt_long(argc, argv, short_options,
                            long_options, &option_index))!=-1)
    {
        switch(rez)
        {  
            case 'r':
                roman_encoding = 1;
                break;
            case 'h':
                help = 1;
                break;
            case 'v':
                print_version = 1;
                break;
            default:
                return -1;
        }
    }

    if (print_version) {
        printf("0:0\n");
        return 0;
    }

    setlocale (LC_ALL, "");
    bindtextdomain ("number_diviner", LOCALE_PATH);
    textdomain ("number_diviner");
    
    if (help) {
        printHelp();
        return 0;
    }

    printf(_("Make a number from %s to %s\n(don't tell it, just imagine and press Enter)\n"),
        intToS(1, buf1), intToS(100, buf2)
    );
    int c = getchar();
    while ((c != '\n') && (c != EOF)) {
        c = getchar();
    }

    int x = bin_search(1, 100);
    printf(_("Your number is %s\n"), intToS(x, buf1));

    return 0;
}