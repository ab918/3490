#include <stdio.h>
#include <stdlib.h>  
#include <time.h>

//struct to store points 
struct conVexPoints
{
    float x;
    float y;
};

struct conVexPoints hull[30000];	//struct to store the resutls of the quickhull
int hullNUm = 0;
 

//checks which side of the line the point is, the line is made of point p1 and p2
int getSide(struct conVexPoints p1, struct conVexPoints p2, struct conVexPoints p) 
{ 
	int val = (p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x); 

	if (val > 0) { return 1; }
	if (val < 0) { return -1; }

	return 0; 
} 

//calculates the distance between the point p and the line p1-p2
int getDist(struct conVexPoints p1, struct conVexPoints p2, struct conVexPoints p) 
{ 
	return abs ((p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x));
} 

//quick hull function to calculate the convex hull
void quickHull(struct conVexPoints arr[], int n, struct conVexPoints p1, struct conVexPoints p2, int side) 
{ 
	int index = -1; 
	int maxDist = 0; 

	//calculating the point with the largest distance from one particular side
	for (int i=0; i<n; i++) { 
		int temp = getDist(p1, p2, arr[i]); 
		if (getSide(p1, p2, arr[i]) == side && temp > maxDist) { 
			index = i; 
			maxDist = temp; 
		} 
	} 

	//if no point is found then add the point to the hull
	if (index == -1) { 
		// hull.insert(p1); 
        hull[hullNUm].x = p1.x;	//inserting x coordinate of the point into the hull
        hull[hullNUm].y = p1.y;	//inserting y coordinate of the point into the hull
        printf(" (%0.1f,%0.1f)", p1.x, p1.y);
        hullNUm++;
        
		// hull.insert(p2); 
        hull[hullNUm].x = p2.x;	//inserting x coordinate of the point into the hull
        hull[hullNUm].y = p2.y;	//inserting y coordinate of the point into the hull
        printf(" (%0.1f,%0.1f)", p2.x, p2.y);
        hullNUm++;
		return; 
	} 

	//dividing the further into two parts and calling quickhull on those corresponding sides
	quickHull(arr, n, arr[index], p1, -getSide(arr[index], p1, p2)); 
	quickHull(arr, n, arr[index], p2, -getSide(arr[index], p2, p1)); 
} 

void printHull(struct conVexPoints arr[], int n) 
{ 
	if (n < 3) {	//checking if there are enough points to make a convex hull
	 
		printf( "Not enough points for the convex hull\n" ); 
		return; 
	} 

	//Calculating the left most and right most coordinates
	int left = 0, right = 0; 
	for (int i=1; i<n; i++) { 
		if (arr[i].x < arr[left].x) { left = i; }
		if (arr[i].x > arr[right].x) { right = i; }
	} 

	//finding convex hull points on side of the line left-right
	quickHull(arr, n, arr[left], arr[right], 1); 

	//finding convex hull points on the other side of the line left-right
	quickHull(arr, n, arr[left], arr[right], -1);
} 

// Driver code 
int main(int argc, char** argv) 
{ 
	clock_t begin = clock();
    char *input = argv[1];
    FILE *inputFile;
    struct conVexPoints arr[30000];	//array for holding the 30 000 points

    inputFile = fopen(input, "r");

    if(inputFile == 0) {
        printf("File not found\n");
        return -1;
    }
    else {
        float num = 0;
        int j = 0;
        int x = 0;
        while (fscanf(inputFile, "%f", &num) > 0) {	//storing the points in the array
            if(j%2 == 0) {
                arr[x].x = num;
            }
            else {
                arr[x].y = num;
                x++;
            }
            j++;
        }
        fclose(inputFile);
    }

	int n = sizeof(arr)/sizeof(arr[0]); 
	printHull(arr, n); //calling the quickhull function
	clock_t end = clock();
    double time = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("time: %0.1f secs\n", time);
	return 0; 
} 
