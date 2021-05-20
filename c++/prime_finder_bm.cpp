// Prime-Finder CPU Bechmark
// Author: Lieutenant Debaser
// This benchmark works by calculating the number of primes between zero and the number specified as
// the UPPER_LIM.
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main (int argc, char** argv) {
	unsigned int UPPER_LIM;

	// Upper limit is specified as a CLI argument
	if (argc > 1) {
		stringstream charToInt;
		unsigned int temp = 0;
		charToInt << argv [1];
		charToInt >> temp;
		UPPER_LIM = temp;
	}
	// Default upper limit
	else
		UPPER_LIM = 1000000;


	// Declare variables
	vector <unsigned int> primeNums;
	unsigned int num = 1;
	bool failed = false;

	// Do infinite loop
	while (true) {
	    // Stop once the upper limit number has been reached
		if (num > UPPER_LIM)
			break;
			
		// Determine if the number is a prime
		for (int i = 1; i < primeNums.size(); i++) {
			if (num % primeNums[i] == 0) {
				failed = true;
				break;
			}
		}
		
		// If the number was a prime, add it to the list
		if (failed == false)
			primeNums.push_back(num);
			
		// Increment counter by 2 (never need to test even numbers as they can never be prime) and reset for next test
		num += 2;
		failed = false;
	}

	cout << "\n\nThere are " << primeNums.size() << " primes between 0 and " << UPPER_LIM << "\n";
	return 0;
}
