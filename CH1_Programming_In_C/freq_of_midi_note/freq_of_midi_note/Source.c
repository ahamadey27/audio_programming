/*Calculate the frequency of a MIDI note*/
#include <stdio.h>
#include <math.h> //required for pow() functionm 

int main()
{
	double semitone_ratio;
	double c0; //The frequency of MIDI note 0
	double c5; //The frequency of middle C
	double freq; //which frequency we want to find
	int midiNote; //...given this note
	/*Can use --- double semitone_ratio, c0, c5, freq--- to save line space*/

	/*Calculate required numbers*/
	semitone_ratio = pow(2, 1 / 12.0); //calcultes the semitone ratio...standard equation 
	c5 = 220.0 * pow(semitone_ratio, 3); //find middle C, 3 semitones above low A = 220.0
	c0 = c5 * pow(0.5, 5); //MIDI note 0 is C, 5 octaves below middle C
	/*for pow() arguments pow(double base, double power)*/

	/*Calculate a frequency for a given MIDI note*/
	midiNote = 80;
	freq = c0 * pow(semitone_ratio, midiNote);

	printf("MIDI note %d has frequency %f\n", midiNote, freq);

	return 0;
}