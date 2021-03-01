#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point {  //struct to store the x and y coordinates for the points
    float x;
    float y;
};

int main (int argc, char** argv) {
    // clock_t begin = clock();
    char *input = argv[1];
    FILE *inputFile;
    struct Point point[30000];  //setting the size of the array for 30000 points
    float a;
    float b;
    float c;
    int greater = 0;    //variable to check if the point is on one side
    int lesser = 0;     //variable to check if the point is on the other side of the line

    inputFile = fopen(input, "r");

    if(inputFile == 0){
        printf("File not found\n");
        return -1;
    }
    else{
        float num = 0;
        int j = 0;
        int x = 0;
        while (fscanf(inputFile, "%f", &num) > 0)   //storing the floats into the array
        {
            if(j%2 == 0){
                point[x].x = num;
            }
            else{
                point[x].y = num;
                x++;
            }
            j++;
        }
        fclose(inputFile);
    }

    for(int i = 0; i < 30000-2; i++) {    //looping through the points to pick the first point
        for(int j = i + 1; j < 30000-1;) {    //looping through the points to pick the second set of points
            greater = 0;    
            lesser = 0;
            if(i != j) {
                for(int k = 0; k < 30000; k++) {    //looping through the points to pick the points to compare to the line point[i] and point[j]
                    a = point[i].y - point[j].y;    //calculating a in the equation ax + by > or < c
                    b = point[j].x - point[i].x;    //calculating b in the equation ax + by > or < c
                    c = (point[j].x * point[i].y) - (point[i].x * point[j].y);  //calculating c in the equation ax + by > or < c
                    if(greater != 0 && lesser != 0){break;} //skipping if line if it has points on both side of the line
                    else{
                    if(k != i && k != j) {
                        if( (a*point[k].x) + (b*point[k].y) > c ) { //ax + by is greater than c than greater is incremented each time a point on that side
                            greater = greater + 1;
                        }

                        else if( (a*point[k].x) + (b*point[k].y) < c ) {    //ax + by is lesser than c than lesser is incremented each time a point on that side
                            lesser = lesser + 1;
                        }
                    }
                    }
                    
                }
                if(greater == 0 || lesser == 0) {
                    printf("convex: %0.1f %0.1f %0.1f %0.1f greater=%d lesser=%d\n", point[i].x, point[i].y, point[j].x, point[j].y, greater, lesser); //printing all the convex hull points
                }
            }
        }
        
    }
    // clock_t end = clock();
    // double time = (double)(end - begin)/CLOCKS_PER_SEC;
    // printf("time: %0.1f secs\n", time);
}