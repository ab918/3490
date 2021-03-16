#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <time.h>

# define NO_OF_CHARS 256 

typedef struct Pairs
{
    int match;
    int patternShift;
}Pairs;

int max (int a, int b) { 	//function to return the max input from a and b
	if(a > b) {
		return a;
	}
	else {
		return b;
	}
 } 
 
void badCharTable( char *str, int size, int badchar[]) 	//function to make bad character table
{ 
	for (int i = 0; i < NO_OF_CHARS; i++) {	//setting all the entries in the badchar table to -1
		badchar[i] = -1; 
	}

	for (int i = 0; i < size; i++) {	//filling the bad char table with characters
		badchar[(int) str[i]] = i; 
	}
} 

void preprocess_strong_suffix(int *shift, int *borderPostion, char *pat, int patLength) //good suffix to hold the characters that were matched
{ 
	int i=patLength, j=patLength+1; 
	borderPostion[i]=j; 

	while(i>0) 
	{ 
		while(j<=patLength && pat[i-1] != pat[j-1]) 
		{ 
			if (shift[j]==0) {
				shift[j] = j-i; 
			}
			j = borderPostion[j]; 
		} 
		i--;j--; 
		borderPostion[i] = j; 
	} 
} 

void preprocess_case2(int *shift, int *borderPostion, char *pat, int patLength) 
{ 
	int j = borderPostion[0]; 
	for(int i=0; i<=patLength; i++) 
	{ 
		if(shift[i]==0) {
			shift[i] = j;
		} 

		if (i==j) {
			j = borderPostion[j]; 
		}
	} 
} 

struct Pairs search(char *text, char *pat) 
{ 
	struct Pairs pair;
	int j;
	int shiftIndex=0;
	int patLength = strlen(pat); 
	int textLength = strlen(text); 
	int patternShiftCount = 0;
	int matchCount = 0;

	int badChar[NO_OF_CHARS];
	int borderPostion[patLength+1];
	int shift[patLength+1]; 

	for(int i=0;i<patLength+1;i++) { 
		shift[i]=0; 
	}

	preprocess_strong_suffix(shift, borderPostion, pat, patLength); 
	preprocess_case2(shift, borderPostion, pat, patLength);
	badCharTable(pat, patLength, badChar); 

	while(shiftIndex <= textLength-patLength) 
	{ 

		j = patLength-1; 

		while(j >= 0 && pat[j] == text[shiftIndex+j]) {
			j--; 
		}

		if (j<0) 
		{
			if(shiftIndex+patLength < textLength) {
				patternShiftCount++;
				int num = text[shiftIndex+patLength];

				if((shiftIndex+shift[0]) > (shiftIndex+patLength-badChar[num])) {
					shiftIndex += shift[0];
				}
				else {
					shiftIndex += patLength-badChar[num];
				}
			}

			else {
				shiftIndex += shift[0];
			}			
			
			matchCount++;
		} 
		else{
			patternShiftCount++;
			int num = text[shiftIndex+j];
			if((shiftIndex + shift[j+1]) > (shiftIndex+max(1,j-badChar[num]))) {
				shiftIndex+= shift[j+1];
			}
			else {
				shiftIndex+= max(1,j-badChar[num]);
			}
		}
	} 

	pair.match = matchCount;
	pair.patternShift = patternShiftCount;

	return pair;
} 

//Driver 
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
        struct Pairs pair = search(buffer, inputStr);
		end = clock() - start;
		double time_taken = ((double)end)/CLOCKS_PER_SEC;
		
		printf("For B&M with word:%s	Matches:%d	Pattern Shifts:%d	time:%f\n", inputStr, pair.match, pair.patternShift, time_taken);
    }
}
