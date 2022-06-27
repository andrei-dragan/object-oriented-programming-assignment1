#include <stdio.h>
#include <stdlib.h>

// ####################### general ####################### //
/*
	Read the command input from the user
	Input: - 
	Output: An integer (0 = exit, 1 = a) point, 2 = b) point) representing the command
*/
int chooseCommand() {
	printf("Choose your next command\n");
	printf("To solve the first point, type: 1\n");
	printf("To solve the second point, type: 2\n");
	printf("To exit the application, type: 0\n");
	
	printf("Your command: ");

	int user_input;
	scanf("%d", &user_input);

	return user_input;
}

// ####################### a) point ####################### //
/*
	Get the number input from the user
	Input: - 
	Output: The number chosen by the user - double
*/
double readNumber() {
	int ok = 1;
	double number;
	while (ok) {
		printf("Type your positive real number: ");
		scanf("%lf", &number);

		if (number <= 0) {
			printf("This number is lower or equal than 0!\n");
		}
		else {
			ok = 0;
			break;
		}
	}
	return number;
}

/*
	Get the precision input by the user
	Input: -
	Output: The precision - integer
*/
int readPrecision() {
	int precision, ok = 1;
	while (ok) {
		printf("Type your positive integer precision: ");
		scanf("%d", &precision);

		if (precision <= 0) {
			printf("This number is lower or equal than 0!\n");
		}
		else {
			ok = 0;
			break;
		}
	}
	return precision;
}

/*
	Get the approximated square root of the number with the specific precision
	Input: -
	Output: the result - double
*/
double solveA() {
	double number, solution = 0, incrementing_precision = 0.1;
	int left, right, mid, precision;
	
	// Get the input from the user
	number = readNumber();
	precision = readPrecision();

	// Using binary search, find the correct integer part of the result
	left = 0;
	right = number;
	while (left <= right) {
		mid = (left + right) / 2;
		if (mid * mid <= number) {
			solution = mid; // good candidate, but we search for more
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}

	// Now we start increment each fractional digit starting from precision 1
	for (int i = 0; i < precision; i++) {
		while (solution * solution <= number) {
			solution += incrementing_precision;
		}
		solution -= incrementing_precision;
		incrementing_precision /= 10; // we move to an even lower precision
	}

	return solution;
}

// ####################### b) point ####################### //
typedef struct {
	int arr[101];
	int size;
} Vector;

/*
	Reads a vector of integer numbers.
	Input: -
	Output: v - Vector
*/
Vector readVector() {
	Vector v;
	
	// Get the length of the vector
	int n = 0;
	while (n <= 0) {
		printf("Enter the length of the array (positive integer): ");
		scanf("%d", &n);
	}
	v.size = n;

	// Read the elements of the vector
	int x;
	printf("Enter the elements of the array: \n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		v.arr[i] = x;
	}

	return v;
}

/*
	Check if the number is prime
	Input: x - integer (the number to be checked)
	Output: 1 if the number is prime, 0 otherwise
*/
int checkPrime(x) {
	if (x == 1 || x == 0) return 0;
	else if (x == 2) return 1;
	else {
		for (int i = 2; i * i < x; i++) {
			if (x % i == 0) return 0;
		}
		return 1;
	}
}

/*
	Find the longest contiguous subsequence such that the difference of any two consecutive elements is a prime number.
	Input: v - vector of integers
	Output: start and end index of the correct subsequence
*/
void solveB(Vector v, int* startIdx, int* endIdx) {
	int dif, start, end, max_length;

	// The first solution is represented by the first lonely element 
	max_length = 1; // The maximum length is 1
	start = 0; end = 0; // The current solution is from 0 to 0

	for (int i = 1; i < v.size; i++) {
		dif = abs(v.arr[i] - v.arr[i - 1]);
		
		if (checkPrime(dif)) {
			// If the difference is prime, we keep incrementing the end of the subsequence
			end = i;
		}
		else {
			// We reinitialize the current subsequence
			start = i; end = i;
		}

		// Every time, we compare the length of the current good subsequence with the maximum and we update it, if it's the case
		if (end - start + 1 > max_length) {
			max_length = end - start + 1;
			*startIdx = start;
			*endIdx = end;
		}
	}
}

/*
	Prints the elements between start and end indexes.
	Input: v - Vector
		   start, end - integers
	Output: prints the elements
*/
void printSolution(Vector v, int startIdx, int endIdx) {
	printf("The solution is: \n");
	for (int i = startIdx; i <= endIdx; i++) {
		printf("%d ", v.arr[i]);
	}
	printf("\n");
}

// ####################### main ####################### //
int main()
{
	int user_input, ok = 1;
	double solution_a;
	while (ok) {
		// Get the input from the user
		user_input = chooseCommand();
		if (user_input == 1) {
			// Solve the a) point
			solution_a = solveA();
			printf("%.20f\n", solution_a);
		}
		else if (user_input == 2) {
			// Solve the b) point
			Vector v; 
			int startIdx = 0, endIdx = 0;

			// Read the vector
			v = readVector();

			// Find the subsequence
			solveB(v, &startIdx, &endIdx);

			// Print the solution
			printSolution(v, startIdx, endIdx);
			
		}
		else if (user_input == 0) {
			// Exit the app
			ok = 0;
			break;
		}
		else {
			// Invalid command
			printf("This is an invalid command!\n");
		}
	}
}