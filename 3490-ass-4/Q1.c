/*Abdullah Al Naim      0993927     29/03/2021      Assignment 04 Q1
Program showcase the BST through dynamic programming*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

typedef struct Tables	//structure to store root and probability table
{
	int **R;	//root table
	float **C;	//probability table
} Tables;


int cmp (const void * a, const void * b) {	//comparator function
   return ( strcmp(*(char**)a,*(char**)b));
}

struct Tables optimalSearchTree(float** freq, int n)	//function to calculate the root and probability table
{
	Tables tables;
	tables.C = (float **)malloc((n+1) * sizeof(float *));
    tables.R = (int **)malloc((n+1) * sizeof(int *));
	
    for (int i=0; i<=(n+1); i++) {
		tables.R[i] = (int *)malloc((n+1) * sizeof(int));
		tables.C[i] = (float *)malloc((n+1)*sizeof(float));
    }

	float *temp = *freq;	//setting a temp list to store the frequencies

	for(int i = 1; i <= n+1; ++i) {		//initializing all the tables
		for(int j = 0; j < n+1; ++j) {
			tables.C[i][j] = 0.0;
			tables.R[i][j] = 0.0;
		}
	}
	temp[n+1] = 0;

	for (int i = 0; i <= n+1; i++) {	//setting the diagonals to zero and the setting the probability and root for the single key combinations
		tables.C[i][i-1] = 0.0;
		tables.C[i+1][i+1] = temp[i];
        tables.R[i][i] = i;
    }
	tables.C[n+1][n] = 0;

	for (int d=1; d<=n-1; d++)	//calculating the root and probability of the rest of the spaces above the diagonal
	{
		for (int i=1; i<=n-d; i++)
		{
			int j = i+d;
			float minVal = INT_MAX;
            int kmin = 0;

			for (int k=i; k<=j; k++)
			{
				if(tables.C[i][k-1] + tables.C[k+1][j]<minVal) {
					minVal = tables.C[i][k-1]+tables.C[k+1][j];	//calculating the minval
					kmin = k;	//setting the root of the probability
				}
			}
            tables.R[i][j] = kmin;
			float sum = temp[i-1];	//setting the first probability of the given keys
			for (int s = i+1; s <=j; s++) {
				sum = sum + temp[s-1];	//adding all the probabilities for the given keys
			}
			tables.C[i][j] = minVal + sum;	//calculating the final probability of the given set of keys
		}
	}

	return tables;
}

void tree(char** keys, Tables tables, char* x, int i, int j) {	//search function to traverse the root table and find the key

	int n = tables.R[i][j];	//setting the initial root for key

	if(tables.C[i][j] == 0.0) {	//exiting recursion when key is not found
		printf("key not found\n");
		return;
	}
	
	printf("compared with %s (%f) ",keys[n-1], tables.C[i][j]);

	if(strcmp(x,keys[n-1])==0) {	//exiting recursion when key is found
		printf("found %s\n", keys[n-1]);
		return;
	}

	else if(strcmp(x,keys[n-1]) < 0) {	// if value is less than zero then search the left sub tree
		printf(", go to left subtree \n");
		tree(keys, tables, x, i, n-1);
	}

	else {		// if value is greater than zero then search right sub tree
		printf(", go to right subtree \n");
		tree(keys, tables, x, n+1, j);
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
        char **dWords = (char**)malloc(sizeof(char*));
        float* freqs =  malloc(sizeof(float));

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
        
		qsort(strings, words, sizeof(char*), cmp);	//sorting all the words in the file to reduce time taken to get distinct words

        int distinctWords = 0;
        float probability = 0;
        for(int x = 0; x < words; ++x) {	//counting all distinct words and calculating thier probability
            int wordCount = 0;
            if(x == 0 || strcmp(strings[x],strings[x-1]) != 0) {
                for(int y = 0; y < words; y++) {
                    if(strcmp(strings[x],strings[y]) == 0) {
                        wordCount++;
                    }
                }
                probability  = (float)wordCount/(float)words;
				dWords = (char**)realloc(dWords, sizeof(char*)*(distinctWords+1));
                dWords[distinctWords] = malloc(sizeof(char)*strlen(strings[x]));
                
                strcpy(dWords[distinctWords],strings[x]);
				freqs = realloc(freqs, sizeof(float)*(distinctWords+1));
                freqs[distinctWords] = probability;
                distinctWords++;
                
            }
        }

		printf("Enter a key: %s\n", inputStr);
        tree(dWords, optimalSearchTree(&freqs, distinctWords), inputStr, 1, distinctWords);
    }
}