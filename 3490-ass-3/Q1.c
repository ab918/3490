#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char** args) {

    char command0[256] = "./P11 data_4.txt ";
    char command1[256] = "./P12 data_4.txt ";

    strcat(command0, args[1]);    
    strcat(command1, args[1]);    

    system(command0);
    system(command1);
}