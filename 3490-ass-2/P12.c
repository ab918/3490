#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mSort(int A[], int temp[], int B, int C);
int merge(int A[], int temp[], int B, int mid, int C);

//function is first called which allocats memory for the temp pointer and calls mergesort function
int start(int A[], int array_size)
{
	int* temp = (int*)malloc(sizeof(int) * array_size);
	return mSort(A, temp, 0, array_size - 1);
}

//merging sorting recursive function
int mSort(int A[], int temp[], int B, int C)
{
	int mid, inverCount = 0;
	if (C > B) { //will continue recursing until the arrays reduced to thier smallest possible size i.e one element arrays
	
        //dividing the array into two sub arrays 
		mid = (C + B) / 2;

		//since this is happening recursively it will return inversion count that we will have to add inversion count for each of the two parts
		inverCount += mSort(A, temp, B, mid);
		inverCount += mSort(A, temp, mid + 1, C);

		//merging the two solutions
		inverCount += merge(A, temp, B, mid + 1, C);
	}
	return inverCount;
}

//this function will merge the two solutions i.e the sorted arrays to the final sorted array and also count the inversions that take place
int merge(int A[], int temp[], int B, int mid, int C)
{
	int i, j, k;
	int inverCount = 0;

	i = B; /* i is index for B subarray*/
	j = mid; /* j is index for C subarray*/
	k = B; /* k is index for resultant merged subarray*/

	while ((i <= mid - 1) && (j <= C)) {
		if (A[i] <= A[j]) {
			temp[k++] = A[i++];
		}
		else {
			temp[k++] = A[j++];

			//there mid - i inversions because all the elements in the left and right arrays are sorted therefore all the remaining elements in
			//in the left sub array that a[i+1..mid] will be greater then the elements in the right sub array a[j]
			inverCount = inverCount + (mid - i);
		}
	}

	//Copying the remaining of the left sub array to temp
	while (i <= mid - 1) { temp[k++] = A[i++]; }

	//Copying the remaining of the right sub array to temp
	while (j <= C) { temp[k++] = A[j++]; }

	//Copying the merged elements in temp to the original array
	for (i = B; i <= C; i++) { A[i] = temp[i]; }

	return inverCount;
}

//main code for running 
int main(int argv, char** args)
{
	clock_t begin = clock();
    char *input = args[1];	//taking in the file name
    FILE *inputFile;	//file object
    int A[50000];	//array of size 50000 to store the elements

    inputFile = fopen(input, "r");	

    if(inputFile == 0){	//checking of the file is present or not
        printf("File not found\n");
        return -1;
    }
    else{
        int num = 0;
        int j = 0;
        while (fscanf(inputFile, "%d", &num) > 0)	//scanning the file and storing the integers in the array
        {
            A[j] = num;
            j++;
        }
        fclose(inputFile);
		printf(" Number of inversions are %d \n", start(A, 50000));

		clock_t end = clock();
        double time = (double)(end - begin)/CLOCKS_PER_SEC;
		printf("time: %0.1f secs\n", time);
    }
	return 0;
}
