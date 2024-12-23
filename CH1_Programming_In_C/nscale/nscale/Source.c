/* Displays E.T frequencies for an N-note octave, from a given MIDI note */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
    int notes, i, midinote;
    double freq, ratio;
    double c0, c5;
    double* intervals; // Use a dynamically allocated array for flexibility

    if (argc != 3) // Ensure two inputs: notes and midinote
    {
        printf("Usage: nscale notes midinote\n");
        return 1;
    }

    notes = atoi(argv[1]);
    if (notes < 1 || notes > 24)
    {
        printf("Error: notes must be between 1 and 24\n");
        return 1;
    }

    midinote = atoi(argv[2]);
    if (midinote < 0 || midinote > 127)
    {
        printf("Error: MIDI note must be between 0 and 127\n");
        return 1;
    }

    /* Find the frequency of the MIDI note */
    ratio = pow(2.0, 1.0 / 12.0); // Standard semitone ratio
    c5 = 220.0 * pow(ratio, 3); // Middle C (C5) is three semitones above A 220 Hz
    c0 = c5 * pow(0.5, 5); // C0 is 5 octaves below C5
    freq = c0 * pow(ratio, midinote);

    /* Allocate memory for the frequency intervals */
    intervals = (double*)malloc(notes * sizeof(double));
    if (intervals == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    /* Calculate the frequencies */
    ratio = pow(2.0, 1.0 / notes); // Equal temperament ratio for N notes
    for (i = 0; i < notes; i++)
    {
        intervals[i] = freq;
        freq *= ratio;
    }

    /* Print the frequencies */
    for (i = 0; i < notes; i++)
    {
        printf("%f\n", intervals[i]);
    }

    /* Free allocated memory */
    free(intervals);

    return 0;
}
