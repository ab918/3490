#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void search(int data[], char num[], int size) {
    
    int x = 0;
    for(int i = 0; i < 30000; ++i) {
        int found = false;
        char buffer[255];
        sprintf(buffer, "%d", data[i]);
        for(int j = 0; j < size; j++) {
            found = false;
            for(int k = 0; k < size; k++) {

                if(strlen(buffer) != size) {
                    break;
                }

                if(num[j] == buffer[k]) {
                    found = true;
                    buffer[k] = 'f';
                    break;
                }
            }

            if(found == false) {
                break;
            }
        }
        if(found == true) {
            int realNum = atoi(num);
            if(data[i] != realNum) {
                x++;
                printf("ans: %d %d\n", data[i], x);
            }
            }
    }

}

int main(int arg, char** argc) {
    
    char *inputFile = argc[1];  //storing the input file name
    char *inputStr = argc[2];
    FILE *file;    //file object
    int data[30000];    //making an array to store the 30000 elements
    // int inverCount = 0; //inversion count variable


    file = fopen(inputFile, "r");  //opening file for reading

    if(file == 0){ //checking if the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        printf("From Brute Force\n");
        int num = 0;    //variable to store the integers scanned from the file
        int j = 0;  //index for the array
        while (fscanf(file, "%d", &num) > 0)   //scanning file and storing the integers in the num variables
        {
            data[j] = num;
            j++;
        }
        fclose(file);
        clock_t begin = clock();
        search(data, inputStr, strlen(inputStr));
        clock_t end = clock();
        double time = (double)(end - begin)/CLOCKS_PER_SEC;
        printf("time: %f secs\n", time);
    }

    
}