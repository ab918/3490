#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void search(char* pat, char* txt) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt); 
    int ps = 0;
    int p = 0;

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) { 
		int j; 
		for (j = 0; j < M; j++) {
			if (txt[i + j] != pat[j]) {
				break; 
            }
        }
        // printf("comparison done ps=%d\n", ps++);
		if (j == M) { // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			p++;
        }
	} 
    printf("pattern shift %d\n", ps-1);
} 

int main(int arg, char** argc) {
    char *inputFile = argc[1];  //storing the inputFile file name
    char *inputStr = argc[2]; //
    FILE *file;    //file object
    char * buffer = 0;
    long length;

    file = fopen(inputFile, "r");  //opening file for reading

    if(file == 0){ //checking if the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        // char line[256];    //variable to store the integers scanned from the file
        int j = 0;  //index for the array
        fseek (file, 0, SEEK_END);
        length = ftell (file);
        fseek (file, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, file);
        }


        // printf("%s\n", buffer);
        // for(int x = 0; x < 10; x++) {
        //     printf("%s\n", data[x]);
        // }


        printf("%ld\n", strlen(buffer));
        search(inputStr,buffer);
    }
}