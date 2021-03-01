#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char **argv){
    
    clock_t begin = clock();

    char *input = argv[1];  //storing the input file name
    FILE *inputFile;    //file object
    int data[50000];    //making an array to store the 50000 elements
    int inverCount = 0; //inversion count variable

    inputFile = fopen(input, "r");  //opening file for reading

    if(inputFile == 0){ //checking if the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        int num = 0;    //variable to store the integers scanned from the file
        int j = 0;  //index for the array
        while (fscanf(inputFile, "%d", &num) > 0)   //scanning file and storing the integers in the num variables
        {
            data[j] = num;
            j++;
        }
        fclose(inputFile);
        
        for(int x = 0; x < 50000; x++){ //counting the number of inversions
            for(int y = 0; y < 50000; y++){
                if(data[x] > data[y] && x < y){ //comparing the x integer with all the other integers to see if there is an inversion
                    inverCount++;
                }
            }
        }

        clock_t end = clock();
        double time = (double)(end - begin)/CLOCKS_PER_SEC;

        printf("number of inversions is %d\n", inverCount);
        printf("time: %0.1f secs\n", time);
        
    }
}