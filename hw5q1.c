/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define N 4
#define NO_ROAD -1
#define NO_PATH -1
#define HOME 0


int ShortestFullPath(int roads[N][N]);
int find_path(int roads[N][N], bool prev[], int column, int len, int* pshortest);


// Print functions declarations
void PrintRoadsInputMessage();
void PrintLenOfShortestFullPath(int min_len);

/*-------------------------------------------------------------------------
  The main program. 
  Using backtracking to find shortest path in array.
  if does not exist return -1. 
 -------------------------------------------------------------------------*/
int main()
{
    int roads[N][N];
    PrintRoadsInputMessage();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (scanf("%d", (*(roads + i) + j)) < 1)exit(1);
        }
    }
    ShortestFullPath(roads);
    PrintLenOfShortestFullPath(ShortestFullPath(roads));
    return 0;
}


int ShortestFullPath(int roads[N][N])
{
    bool prev[N];
    for (int i = 0; i < N; i++) {
        prev[i] = false;
    }
    int column = 0, len = 0, shortest = INT_MAX;
    find_path(roads, prev, column, len, &shortest);
    if (shortest == INT_MAX) return NO_PATH;
    return shortest;
}

int find_path(int roads[N][N], bool prev[] ,int column, int len, int* pshortest) {
    int path = NO_PATH;
    bool ways = false;
    // recursion base

    for (int i = 1; i < N; i++) {
        if (prev[i] == false && roads[column][i] != NO_ROAD) {
            ways = true;
            break;
        }
    }

    if (ways == false) {
        if (roads[column][HOME] != NO_ROAD) {
            for (int k = 1; k < N; k++) {
                if (prev[k] == false)return NO_PATH;
            }
            return len + roads[column][HOME];
            // the last stop reaches a loop
        }
        else {
            return NO_PATH;
        }
    }

    // been to all stops


    for (int i = 1; i < N; i++) {

        if (prev[i] == true) {
            continue;
        }

        // recursion step
        if (roads[column][i] != NO_ROAD) {
            
            // len & prev update
            prev[i] = true;
            
            // next step
            path = find_path(roads, prev, i, len + roads[column][i], pshortest);
            if (path != NO_PATH) {
                // printf("a path - %d\n", path);
                if (*pshortest > path)*pshortest = path;
            }

            // arrays are not being copied
            prev[i] = false;
        }
    }
    return NO_PATH;
}




// Print functions
void PrintLenOfShortestFullPath(int min_len)
{
    if(min_len == NO_PATH)
    {
        printf("There is no such path!\n");
    }
    else
    {
        printf("The shortest path is of length: %d\n", min_len);
    }
}

void PrintRoadsInputMessage()
{
    printf("Please enter the roads %dX%d matrix row by row:\n", N, N);
}
