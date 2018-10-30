/*
Assignment:		3
Author:			Haakon Skaug Ingbrigtsen
Student ID:		40105722
Date:			28th October, 2018
*/

#include <iostream>
using namespace std;

int index[3];

//Functions that will be used.
int indexDigits(int sequence);
void displayDigits(int sequence);
void reverseSequence(int sequence);
void sumDigits(int sequence);
bool checkPrime(int sequence);

int main()
{
	int userInt, choice = 1;

	cout << "Welcome!\nPlease enter an integer between 10 and 999.\n>>";
	cin >> userInt; //Expecting perfect user.
	cout << "MENU:\nChoose on of the following options:\n";
	while (choice) { //While choice != 0
		cout << "\n1) Display secquence.\n2) Display the reversed sequence.\n3) Display the sum of the sequence.\n";
		cout <<	"4) Check if atleast one of the numbers are a prime number.\n0) Quit.\n";
		cout << "Enter choice:\n>> ";
		cin >> choice;

		//Menu of choices
		switch (choice) {
		case 1:
			cout << "\nThe sequence you entered is: ";
			displayDigits(userInt);												//Calling the desired function with the specific sequence
			break;
		case 2:
			cout << "\nThe reversed sequence is: ";
			reverseSequence(userInt);
			break;
		case 3:
			cout << "\nThe sum of the digits are: ";
			sumDigits(userInt);
			break;
		case 4:
			checkPrime(userInt);
			if (checkPrime(userInt)) {
				cout << "\nAtleast one of the numbers are a prime number.\n";
			}
			else {
				cout << "\nNone of the numbers are a prime number.\n";
			}
			break;
		default:
			cout << "You did not enter a valid option.\n";
		}
	}

	
}

//Function that will index the inputed sequence of numbers into index[]
int indexDigits(int sequence) {										//Assuming an integer over 100
	if (sequence < 100) {
		index[0] = sequence / 10;
		index[1] = sequence - 10*index[0];
		index[2] = NULL;
		return 2;													//Returning number of integers
	}
	else {
		index[0] = sequence / 100;
		index[1] = (sequence - 100*index[0]) / 10;
		index[2] = (sequence - 100 * index[0] - 10 * index[1]);
		return 3;													//Returning number of integers to the other functions
																	//So that they "know" how many loops to take
	}
	//I made an algorithm to index at first, but realized there's no point with only 3 integers.
	//Time-consuming
}
//	1) Function to dispay the sequence of numbers
void displayDigits(int sequence) {
	int length = indexDigits(sequence);								//Making the indexing function check the length of
	for (int i = 0; i < length; i++) {								//the sequence;
		printf("%d", index[i]);
		if (i != length - 1) {
			cout << " - ";
		}
	}
}
//	2) Function to dispay the reversed sequence of numbers
void reverseSequence(int sequence) {
	int length = indexDigits(sequence);
	for (int i = length - 1; i >= 0; i--) {
		printf("%d", index[i]);
		if (i != 0) {
			cout << " - ";
		}
	}
	
}
//	3) Function to dispay the sum of numbers
void sumDigits(int sequence) {
	int sum = 0;
	int length = indexDigits(sequence);
	for (int i = 0; i < length; i++) {
		sum += index[i];
	}
	cout << sum;
}

//	4) Function to check for prime numbers in the sequence.
bool checkPrime(int sequence) {
	int length = indexDigits(sequence);
	int check = 0, checkTwo = 0;

	//Go through every divisor except 1 and the number itself. 
	//If the number is not a prime, save that info for after.
	for (int i = 0; i < length; i++) {
		check = 0;
		for (int j = 2; j < index[i]; j++) {						//If the number is divisable with any number other
			if (index[i] % j == 0 && index[i] != 0) {				//than 1 and the number itself: Not a prime
				check++;
			}
		}
		if (index[i] == 2 || index[i] == 0) {						//2 is a tricky number when checking for primes.
			check++;
		}
		if (check == 0) {
			return true;
			break;
		}
		else {
			checkTwo++;
		}
	}
	if (checkTwo < length) {
		return true;
	}
	else {
		return false;
	}
}