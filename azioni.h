#define WHITE "\033[0;37m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\e[0m"
#ifndef AZIONI_H
#define AZIONI_H
#include <stdio.h>
#include <string.h>

float evita_caratteri_float();

int evita_caratteri_int();

void titolo();

void fgets_newline_kill(char a[]);


#endif
