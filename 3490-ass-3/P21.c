#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void search(char* T[], char* P, int x, int m) {
    int p = 0;
    
    // printf("size of n %d\n size of m %d\n", n, m);
    for(int h = 0; h < x; ++h) {
        // printf("for line %d there are %ld characters\n", h, strlen(T[h]));
        int n = strlen(T[h]);
        char* text = T[h];
        for(int i = 0; i <= n - m; i++) {
            int j;
            // printf("%s\n", text);
            for(j = 0; j < m; j++) {
                // printf("%c %c\n", text[i+j], P[j]);
                if(text[i+j] != P[j]) {
                    break;
                }
                if(j == m-1) {
                    // printf("pattern found");
                    p++;
                }
            }
        }
    }

    printf("matches = %d\n", p);

}

int main(int arg, char** argc) {
    char *inputFile = argc[1];  //storing the inputFile file name
    char *inputStr = argc[2]; //
    FILE *file;    //file object
    char* data[44049];    //making an array to store the 10 elements
    // int inverCount = 0; //inversion count variable

    file = fopen(inputFile, "r");  //opening file for reading

    if(file == 0){ //checking if the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        char line[256];    //variable to store the integers scanned from the file
        int j = 0;  //index for the array
        while (fgets(line, sizeof(line), file))   //scanning file and storing the integers in the string variables
        {
            // printf("%s %ld\n", line, strlen(line));
            data[j] = malloc(strlen(line)+1);
            // printf("malloced for %d\n", strlen(string));
            strcpy(data[j],line);
            // printf("coppied\n");
            // printf("%s\n", data[j]);
            j++;
        }
        fclose(file);

        // for(int x = 0; x < 10; x++) {
        //     printf("%s\n", data[x]);
        // }

        search(data, inputStr, sizeof(data)/sizeof(data[0]), strlen(inputStr));
    }
}