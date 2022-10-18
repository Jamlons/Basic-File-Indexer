// chris
#include <stdio.h>
#include <stdlib.h>

#include "first_day_of_month.c"

#define DEF_MONTH       4
#define DEF_YEAR        2022

#define DAYS_IN_WEEK    7
#define NWEEKS          6


/*
    August 2022       
Su Mo Tu We Th Fr Sa  
    1  2  3  4  5  6  
 7  8  9 10 11 12 13  
14 15 16 17 18 19 20  
21 22 23 24 25 26 27  
28 29 30 31           
 */

void print_cal(int month, int year)
{
    int days_in_month;

    switch (month) {
    case 4:     printf("   April  %i\n", year);
                days_in_month = 30;
                break;

    case 8:     printf("   August %i\n", year);
                days_in_month = 31;
                break;
    }
    printf("Su Mo Tu We Th Fr Sa\n");

    int day1    = first_day_of_month(month, year);

    int day = 1 - day1;


    for(int w=0 ; w<NWEEKS ; ++w) {
        for(int d=0 ; d<DAYS_IN_WEEK ; ++d) {
            if(day < 1 || day > days_in_month) {
                printf(".. ");
            }
            else {
                printf("%2i ", day);
            }
            ++day;
        }
        printf("\n");
    }
}

int main(int argc,  char *argv[])
{
    int month       = DEF_MONTH;
    int year        = DEF_YEAR;

    print_cal(month, year);

//    exit(EXIT_SUCCESS);

    return EXIT_SUCCESS;
}

