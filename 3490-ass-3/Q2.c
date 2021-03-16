#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char** args) {

    char command0[256] = "./P21 data_5.txt ";
    char command1[256] = "./P22 data_5.txt ";
    char command2[256] = "./P23 data_5.txt ";    

    strcat(command0, args[1]);    
    strcat(command1, args[1]);        
    strcat(command2, args[1]);        


    system(command0);
    system(command1);
    system(command2);

}