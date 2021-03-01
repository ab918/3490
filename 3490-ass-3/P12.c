//anagram search using presorting technique
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mSort(char* A[], char* temp[], int B, int C);
void merge(char* A[], char* temp[], int B, int mid, int C);

//function is first called which allocats memory for the temp pointer and calls mergesort function
void start(char* A[], int array_size)
{
	char* temp[10]; 
	return mSort(A, temp, 0, array_size - 1);
}

//merging sorting recursive function
void mSort(char* A[], char* temp[], int B, int C)
{
	int mid;
	if (C > B) { //will continue recursing until the arrays reduced to thier smallest possible size i.e one element arrays
	
        //dividing the array into two sub arrays 
		mid = (C + B) / 2;

		//since this is happening recursively it will return inversion count that we will have to add inversion count for each of the two parts
		mSort(A, temp, B, mid);
		mSort(A, temp, mid + 1, C);

		//merging the two solutions
		merge(A, temp, B, mid + 1, C);
	}
}

//this function will merge the two solutions i.e the sorted arrays to the final sorted array and also count the inversions that take place
void merge(char* A[], char* temp[], int B, int mid, int C)
{
	int i, j, k;
	int inverCount = 0;

	i = B; /* i is index for B subarray*/
	j = mid; /* j is index for C subarray*/
	k = B; /* k is index for resultant merged subarray*/

	while ((i <= mid - 1) && (j <= C)) {
		if (strcmp(A[i],A[j]) <= 0) {
            
			temp[k++] = A[i++];
		}
		else {
			temp[k++] = A[j++];
		}
	}

	//Copying the remaining of the left sub array to temp
	while (i <= mid - 1) { temp[k++] = A[i++]; }

	//Copying the remaining of the right sub array to temp
	while (j <= C) { temp[k++] = A[j++]; }

	//Copying the merged elements in temp to the original array
	for (i = B; i <= C; i++) { printf(A[i]);  A[i] = temp[i]; }
}

// void binarySearch(int array[], int left, int right, int x) {   // binary search to find the anagrams

//     if(right > left) {
        
//         int middle = left + (right - left) / 2;

//         if(array[middle] == x) {
//             return middle;
//         }

//         if(array[middle] > x) {
//             return binarySearch(array, left, middle - 1, x);
//         }

//         return binarySearch(array, middle + 1, right, x);
//     }

// }

int main(int arg, char** argc) {
    char *inputFile = argc[1];  //storing the input file name
    char *inputStr = argc[2];
    FILE *file;    //file object
    int data[30000];    //making an array to store the 30000 elements
    char *strData[30000];
    // char *test = {"2","0","4","4","8","9","7","7","6","3"};
    // char test[] = "2044897763";
    // int inverCount = 0; //inversion count variable

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
            data[j] = num;
            sprintf(strData[j], "%d", num);
            j++;
        }
        fclose(file);

        // start(test, 30000);

        // sprintf())
        // for(int x = 0; x < 30000; x++) {
        //     printf("%s\n", )
        // }

    }
}