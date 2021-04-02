/*Abdullah Al Naim      0993927     29/03/2021      Assignment 04 Q2
Program to show case the BST using greedy technique*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct DistinctWord //struct to store word and probability and position
{
	char word[256];
	float probability;
	int position;
} DistinctWord;


int cmp (const void * a, const void * b) {  //comparator function to compare strings
   return ( strcmp(*(char**)a,*(char**)b));
}

int cmpProb (const void * a, const void * b) {  //comparator function to compare probabilities 
    const struct DistinctWord *strA = a;
    const struct DistinctWord *strB = b;
   return ((strB->probability*1000000) - (strA->probability*1000000));
}

struct DistinctWord* copyArray(struct DistinctWord *copy, struct DistinctWord *original, int start, int end) {  //array copy function
	int count = 0;
	for(int i = start; i < end; i++) {
		strcpy(copy[count].word, original[i].word);
		copy[count].position = count;
		original[count].position = count;
		copy[count].probability = original[i].probability;
		count++;
	}
	return copy;
}

void search (struct DistinctWord *subList, int size, char* string) {    //searcg function to find key

	struct DistinctWord *temp = malloc(sizeof(struct DistinctWord)*size);
	temp = copyArray(temp, subList, 0, size);
	qsort(temp, size, sizeof(DistinctWord), cmpProb);   // sorting words in temp by probability

	if(subList[temp[0].position].probability == 0.0) {  // if key is not found then exit recursion
		printf("Not found\n");
		return;
	}

	printf("Compared with %s (%f) ", subList[temp[0].position].word, subList[temp[0].position].probability);

	if(strcmp(string,subList[temp[0].position].word) == 0) {    // if key is found then exit recursion
		printf("match found\n");
		return;
	}
	else if(strcmp(string,subList[temp[0].position].word) < 0) {    // if key is less then current key then search left sub tree
		printf(" , go left sub tree\n");
		struct DistinctWord *leftList = malloc(sizeof(struct DistinctWord)*temp[0].position);
		leftList = copyArray(leftList, subList, 0, temp[0].position);
		search(leftList, temp[0].position, string);
	}
	else {  //if key is greater than key then search right sub tree
		printf(" , go right sub tree\n");
		struct DistinctWord *rightList = malloc(sizeof(struct DistinctWord)*(size - temp[0].position));
		rightList = copyArray(rightList, subList, temp[0].position+1, size);
		search(rightList, size-temp[0].position, string);
	}
}

int main(int arg, char** argc) {
    char *inputFile = argc[1];  //storing the input file name
    char *inputStr = argc[2];
    FILE *file;    //file object

    file = fopen(inputFile, "r");  //opening file for reading

    if(file == 0){ //checking if the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        
        char string[256];    //variable to store the integers scanned from the file
        int j = 0;  //index for the array
        int words = 0;

        char** strings = (char**)malloc(sizeof(char*));

        while (fscanf(file, "%s", string) > 0)   //scanning file and storing the integers in the num variables
        {
            words++;
            strings = (char**)realloc(strings, sizeof(char*)*words);
            strings[j] = (char*)malloc(sizeof(char)*(strlen(string)+1));
            strcpy(strings[j],string); 
            j++;
        }
        fclose(file);
        
        qsort(strings, words, sizeof(char*), cmp);  //sorting the words in the file to improve efficiency of distinct word counting

		struct DistinctWord *distinctWordList = malloc(sizeof(struct DistinctWord));    //counting and calculating all the distinct words and their probabilities 
        int distinctWords = 0;
        float probability = 0;
        for(int x = 0; x < words; ++x) {
            int wordCount = 0;
            if(x == 0 || strcmp(strings[x],strings[x-1]) != 0) {
                for(int y = 0; y < words; y++) {
                    if(strcmp(strings[x],strings[y]) == 0) {
                        wordCount++;
                    }
                }
                probability  = (float)wordCount/(float)words; 
                distinctWordList = realloc(distinctWordList, sizeof(*distinctWordList)*(distinctWords+1));
                strcpy(distinctWordList[distinctWords].word,strings[x]);
				distinctWordList[distinctWords].probability = probability;
                distinctWords++;
                
            }
        }
		
		search(distinctWordList, distinctWords, inputStr);
    }
}