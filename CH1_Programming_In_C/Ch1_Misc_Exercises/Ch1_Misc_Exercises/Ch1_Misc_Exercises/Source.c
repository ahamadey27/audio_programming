#include <stdio.h>
#include <stdlib.h> //includes the NULL value

int main()
{

	//--- Pointer example of printer 2, 4 6, 8 --- //
	char* two = "two";
	char* four = "four";
	char* six = "six";

	printf("%s %s %s eight\n", two, four, six);

	char* message = "%s, %s, %s eight";
	printf(message, two, four, six);

	// -- Basic Array -- // 
	//char Beatle[5] = "John";
	/*char letter;
	char letter_two;
	letter = Beatle[0]; //letter = "J"
	Beatle[2] = 'a'; //Beatle string now is "Joan
	printf(Beatle, "\n");*/

	/*--- Converting number strings to variables ---*/
	double dval;
	int ival;
	long lval;

	dval = atof("1.509589"); // atof() converts double
	ival = atoi("440");  // atoi() converts int
	lval = atol("65536"); //atol() converts long 


	return 0;

}