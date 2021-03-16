#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pairs
{
    int match;
    int patternShift;
}Pairs;

struct Pairs search(char* pat, char* txt) //function to search for string using bruteforce
{ 
    struct Pairs pair;
	int patLength = strlen(pat); 
	int txtLength = strlen(txt); 
    int patternShift = 0;
    int matchCount = 0;
    
	for (int i = 0; i <= txtLength - patLength; i++) { //looping through the text
		int j; 
		for (j = 0; j < patLength; j++) {   //looping through the pattern and comparing characters with the text
			if (txt[i + j] != pat[j]) {
				break; 
            }
        }
        patternShift++; //counting all th pattern shifts
		if (j == patLength) {
			matchCount++;   //counting all the matches that were found
        }
	}

    pair.match = matchCount;
    pair.patternShift = patternShift;

    return pair; 
    
} 

int main(int arg, char** argc) {
    char *inputFile = argc[1];  //storing the inputFile file name
    char *inputStr = argc[2]; //
    FILE *file;    //file object
    char * buffer = 0;
    long length;
    clock_t start;
    clock_t end;

    file = fopen(inputFile, "r");  //opening file for reading

    if(file == 0){ //checking if the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        // char line[256];    //variable to store the integers scanned from the file
        fseek (file, 0, SEEK_END);
        length = ftell (file);
        fseek (file, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, file);
        }

        start = clock();
        struct Pairs pair = search(inputStr,buffer);
        end = clock() - start;

        double time_taken = ((double)end)/CLOCKS_PER_SEC;
        printf("For Bruteforce with word:%s    Matches:%d      Pattern Shifts:%d       time:%f\n", inputStr, pair.match, pair.patternShift, time_taken);
    }
}