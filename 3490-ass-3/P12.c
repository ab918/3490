//anagram search using presorting technique
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct pair
{
    char string[255] ;
    char signature[255];
} pair;

struct pair pairs[25];

int cmp (const void * a, const void * b) {
    const struct pair *strA = a;
    const struct pair *strB = b;
   return ( strcmp(strB->signature,strA->signature));
}

int cmpChar (const void * a, const void * b) {
   return ( *(char*)b- *(char*)a );
}

int rightHalf(pair arr[], int low, int high, char *x, int n) {

    if(high >= low) {

        int middle = (low + high)/2;

        if( (middle == 0 || strcmp(x,arr[middle-1].signature) < 0) && strcmp(arr[middle].signature,x) == 0) {
            return middle;
        }

        else if(strcmp(x,arr[middle].signature)<0) {
            return rightHalf(arr, (middle+1), high, x, n);
        }

        else {
            return rightHalf(arr, low, (middle-1), x, n);
        }

    }

    return -1;

} 

int leftHalf(pair arr[], int low, int high, char *x, int n) {

    if(high >= low) {

        int middle = (low + high)/2;

        if( (middle == n-1 || strcmp(x,arr[middle+1].signature)>0) && strcmp(arr[middle].signature,x) == 0) {
            return middle;
        }

        else if(strcmp(x,arr[middle].signature) > 0) {
            return leftHalf(arr, low, (middle-1), x, n);
        }

        else {
            return leftHalf(arr, (middle+1), high, x, n);
        }

    }

    return -1;

}

int count(pair arr[], char *x, int n, char *oGX) {
    int r;
    int l;

    r  = rightHalf(arr, 0, n-1, x, n);

    if(r == -1) {
        return r;
    }

    l = leftHalf(arr, r, n-1, x, n);

    for(int z = r; z <= l; ++z) {
        if(strcmp(arr[z].string,oGX)!=0){
            printf("%s\n", arr[z].string);
        }
    }

    return l-r;
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
        int num = 0;    //variable to store the integers scanned from the file
        int j = 0;  //index for the array
        while (fscanf(file, "%d", &num) > 0)   //scanning file and storing the integers in the num variables
        {
            char string[255];
            sprintf(string, "%d", num);
            strcpy(pairs[j].string,string);
            qsort(string, strlen(string), sizeof(char), cmpChar);
            strcpy(pairs[j].signature,string);
            j++;
        }
        fclose(file);

        // for(int x = 0; x < 25; x++) {
        //    printf("%s\n", pairs[x].signature);
        // }
        // printf("\n\n");
        qsort(pairs, 25, sizeof(pair), cmp);

        // for(int x = 0; x < 25; x++) {
        //    printf("%s\n", pairs[x].signature);
        // }
        printf("searching for %s\n", inputStr);
        char oGX[255];
        strcpy(oGX,inputStr);
        qsort(inputStr, strlen(inputStr), sizeof(char), cmpChar);
        printf("number of anagrams %d", count(pairs, inputStr, 25, oGX));

    }

    
}