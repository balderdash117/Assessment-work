/*
File Name: Bitwise operation
Purpose: 
Author: Benjamin Mitchell Alder
Modified:
*/
#include <iostream>
#include <string>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;



int binaryAdd(int num1, int num2)
{
	int carry;

	do
	{
		carry = num1 & num2;
		num1 = num1 ^ num2;
		num2 = carry << 1;
	} while (num2);

	return num1;
}

int binaryNegate(int num1)
{
	int result = ~num1;
	// Twos compliment rule (add 1 to the 1st bit)
	// num1 & 0x1 (0000 0001) = 0000 0001
	result = binaryAdd(result, 0x1);
	return result;
}

int binarySubtract(int num1, int num2) {
	return binaryAdd(num1, binaryNegate(num2));
}

int binaryMultiplication(int num1, int num2)
{
	//int carry;
	int result = 0;

	while (num2)
	{
		result = binaryAdd(num1, result);
		num2--;
	} 

	return result;
}

int binaryDivision(int num1, int num2)
{
	int incriment = 0;
	int result = 0;

	while (result < num1)
	{
		result = binaryAdd(result, num2);
		incriment++;
	} 

	return incriment;
}

void main() 
{
	int a;
	int b;
	cout << "please enter two numbers" << endl;
	cin >> a;
	cin >> b;
	cout << "Thank you for your cooperation" << endl;
	cout << "Addition: " << binaryAdd(a, b) << endl;
	cout << "Subtraction: " << binarySubtract(a, b) << endl;
	cout << "Multiplication: " << binaryMultiplication(a, b) << endl;
	cout << "Tom Clancy's: The Division: " << binaryDivision(a, b) << endl;

	system("pause");
}
