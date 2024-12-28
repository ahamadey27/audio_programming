#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define constants for the initial number of breakpoints and buffer sizes.
#define NPOINTS (64)           // Initial size of the breakpoint array.
#define BUFSIZE_CHAN (32768)   // Unused in the program, but could relate to channel buffer sizes.
#define LINELENGTH (80)        // Maximum length of a line read from the input file.

// Define a structure to hold breakpoint data: time-value pairs.
typedef struct breakpoint {
    double time;   // Time at which the breakpoint occurs.
    double value;  // Value at that time.
} BREAKPOINT;

// Function to find the maximum value and its corresponding time from a list of breakpoints.
BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints)
{
    int i;
    BREAKPOINT point;

    // Initialize the point structure with default values.
    point.time = 0.0;
    point.value = 0.0;

    // Iterate through all breakpoints to find the one with the highest value.
    for (i = 0; i < npoints; i++) {
        if (point.value < points[i].value) {
            point.value = points[i].value;  // Update max value.
            point.time = points[i].time;   // Update the corresponding time.
        }
    }
    return point; // Return the maximum point found.
}

// Function to read breakpoints from a file and return a dynamically allocated array of breakpoints.
BREAKPOINT* get_breakpoints(FILE* fp, long* psize)
{
    int got;
    long npoints = 0, size = NPOINTS; // Start with an initial array size.
    double lasttime = 0.0;           // To ensure time values are strictly increasing.
    BREAKPOINT* points = NULL;       // Pointer to dynamically allocated breakpoint array.
    char line[LINELENGTH];           // Buffer to read each line from the file.

    // If the file pointer is NULL, return NULL.
    if (fp == NULL)
        return NULL;

    // Allocate initial memory for the breakpoint array.
    points = (BREAKPOINT*)malloc(sizeof(BREAKPOINT) * size);
    if (points == NULL)
        return NULL; // Memory allocation failed.

    // Read lines from the file until the end is reached.
    while (fgets(line, LINELENGTH, fp)) {
        // Parse the line for two double values (time and value).
        if ((got = sscanf_s(line, "%lf%lf", &points[npoints].time, &points[npoints].value)) < 0)
            continue; // Skip empty lines.

        // Error handling for invalid or incomplete data.
        if (got == 0) {
            printf("Line %d has non-numeric data\n", npoints + 1);
            break;
        }
        if (got == 1) {
            printf("Incomplete breakpoint found at point %d\n", npoints + 1);
            break;
        }
        if (points[npoints].time < lasttime) {
            printf("Error in breakpoint data at point %d: time not increasing\n", npoints + 1);
            break;
        }

        lasttime = points[npoints].time; // Update the last time read.

        // Increment the number of points read.
        if (++npoints == size) {
            BREAKPOINT* tmp;

            // Reallocate memory to accommodate more breakpoints.
            size += NPOINTS;
            tmp = (BREAKPOINT*)realloc(points, sizeof(BREAKPOINT) * size);
            if (tmp == NULL) { // If reallocation fails.
                npoints = 0;   // Reset the point count.
                free(points);  // Free the memory.
                points = NULL; // Return NULL.
                break;
            }
            points = tmp; // Update the pointer to the new memory block.
        }
    }

    // If any points were successfully read, update the size.
    if (npoints)
        *psize = npoints;
    return points; // Return the array of breakpoints.
}

int main(int argc, char* argv[])
{
    long size;                // Number of breakpoints read.
    double dur;               // Duration of the breakpoint data.
    BREAKPOINT point, * points;// Maximum point and array of breakpoints.
    FILE* fp;                 // File pointer for the input file.

    printf("breakdur:  find duration of breakpoint file\n");

    // Check if the program is run with a file argument.
    if (argc < 2) {
        printf("usage: breakdur infile.txt \n");
        return 0;
    }

    // Open the input file in read mode.
    if (fopen_s(&fp, argv[1], "r") != 0) {
        return 0; // File opening failed.
    }

    // Read breakpoints from the file.
    size = 0;
    points = get_breakpoints(fp, &size);
    if (points == NULL) {
        printf("No breakpoints read.\n");
        fclose(fp);
        return 1;
    }

    // Ensure there are at least two breakpoints.
    if (size < 2) {
        printf("Error: at least two breakpoints required\n");
        free(points);
        fclose(fp);
        return 1;
    }

    // Ensure the first breakpoint starts at time 0.
    if (points[0].time != 0.0) {
        printf("Error in breakpoint data: first time must be 0.0\n");
        free(points);
        fclose(fp);
        return 1;
    }

    // Print the number of breakpoints read.
    printf("read %d breakpoints\n", size);

    // Calculate the duration of the data (time of the last breakpoint).
    dur = points[size - 1].time;
    printf("duration: %f seconds\n", dur);

    // Find the maximum value and its corresponding time.
    point = maxpoint(points, size);
    printf("maximum value: %f at %f secs\n", point.value, point.time);

    // Free the allocated memory and close the file.
    free(points);
    fclose(fp);

    return 0; // Exit the program successfully.
}
