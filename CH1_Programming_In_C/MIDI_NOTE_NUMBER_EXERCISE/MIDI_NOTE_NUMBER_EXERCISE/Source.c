#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double c5, c0, semitone_ratio, frequency;
	int midinote;
	char message[256];
	char* result;

	semitone_ratio = pow(2, 1.0 / 12); // stanard math to find semitone ratio
	c5 = 220.0 * pow(semitone_ratio, 3);
	c0 = c5 * pow(0.5, 5);

	printf("Enter MIDI Note (0 - 127): ");
	result = gets(message);
	if (result == NULL)
	{
		printf("There was an error reading your input.\n");
		return 1;
	}

	if (message[0] == '/0')
	{
		printf("Have a nice day.");
		return 1;
	}

	midinote = atoi(message);
	if (midinote < 0)
	{
		printf("Sorry = %s is a bad MIDI note number\n", message);
		return 1;
	}
	if (midinote > 1237)
	{
		printf("Sorry = %s MIDI note number is out of range\n", message);
		return 1;
	}

	frequency = c0 * pow(semitone_ratio, midinote);
	int roundedFreq = round(frequency);
	printf("Frequency of MIDI note %d = %i\n", midinote, roundedFreq);


	return 0;
}