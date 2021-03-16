//Program to show off horspool algorithm where a bad character table is used to determine the how many characters to shift inorder to get a match.
# include <limits.h> 
# include <string.h> 
# include <stdio.h> 
# include <stdlib.h>
# include <time.h>

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

struct Pairs search( char *txt, char *pat) 	//main search function
{ 
	struct Pairs pair;
	int pLength = strlen(pat); //length of the pattern that we are searching for
	int tLength = strlen(txt); 	//length of the text we are searching in

	int badchar[NO_OF_CHARS]; //creation of badcharacter array

	badCharTable(pat, pLength, badchar); //creation of bad character table

	int shift = 0; //setting the index of the shift

    int patternShiftCount = 0;	//number of pattern shifts
	int matchCount = 0;
	while(shift <= (tLength - pLength)) //loop to search for the pattern
	{ 
		int j = pLength-1;
		while(j >= 0 && pat[j] == txt[shift+j]) { //keep reducing j until all the characters in the pattern and the text are matching
			j--; 
		}

		if (j < 0) //when a match is found j will be minus one after the loop above
		{ 
			//shift the pattern again such that the next character in the text aligns with last ocurrence of it in the pattern
			if(shift+pLength < tLength) {	
				int num = txt[shift+pLength];
				shift = shift + pLength-badchar[num];
				patternShiftCount++;
			}
			else {	//if is required for when the pattern is found at the end of the text
				shift = shift + 1;
			}
			matchCount++;
		} 

		else {	//shifting the pattern to align the bad character in the text
			int num = txt[shift+j];
			shift += max(1, j - badchar[num]); //max is used to get a positive shift incase the last occurence of the bad character was in the right
			patternShiftCount++;
		}
	} 
	
	pair.match = matchCount;
	pair.patternShift = patternShiftCount;

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
        struct Pairs pair = search(buffer, inputStr);
		end = clock() - start;
		double time_taken = ((double)end)/CLOCKS_PER_SEC;

		printf("For Horspool with word:%s	Matches:%d	Pattern Shifts:%d	time:%f\n", inputStr, pair.match, pair.patternShift, time_taken);
    }
}
