#include <stdio.h>   // Standard I/O library
#include <stdlib.h>  // Library for general-purpose functions like atoi()
#include <math.h>    // Math library for pow()

int main(int argc, char* argv[])
{
    double c5, c0, semitone_ratio, frequency; // Variables for calculations
    int midinote; // MIDI note input from the user

    // Calculate the ratio of a semitone in 12-tone equal temperament
    semitone_ratio = pow(2, 1.0 / 12); // 12th root of 2
    c5 = 220.0 * pow(semitone_ratio, 3); // Frequency of C5 (three semitones above A4 at 220 Hz)
    c0 = c5 * pow(0.5, 5); // Calculate C0 by dividing C5 by 2^5 (octaves lower)

    // Check if the user provided exactly one argument
    if (argc != 2)
    {
        printf("cpsmidi: Converts MIDI note to frequency.\n");
        printf("Usage: cpsmidi MIDInote\n");
        printf("Range: 0 <= MIDInote <= 127\n");
        return 1; // Exit with error code
    }

    // Convert the argument to an integer
    midinote = atoi(argv[1]);

    // Validate the MIDI note range
    if (midinote < 0)
    {
        printf("Bad MIDI note value: %s\n", argv[1]);
        return 1; // Exit with error code
    }
    if (midinote > 127)
    {
        printf("%s is beyond the MIDI range\n", argv[1]);
        return 1; // Exit with error code
    }

    // Calculate the frequency of the MIDI note
    frequency = c0 * pow(semitone_ratio, midinote);

    // Output the result
    printf("Frequency of MIDI note %d = %.2f Hz\n", midinote, frequency);

    return 0; // Exit successfully
}
