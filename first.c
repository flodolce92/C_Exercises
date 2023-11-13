// #include <iostream>
#include <stdio.h>

int main()
{
	// std::cout << "Hello World" << std::endl;
	printf("Hello World!!!\n");
	
	// Primo
	
	// Declare and initialize an array of integers
	int numbers[5] = {10, 20, 30, 40, 50};

	// Accessing elements of the array
	printf("Element at index 2: %d\n", numbers[2]); // Output: 30

	// Modifying elements of the array
	numbers[1] = 25;

	// Looping through an array
	for (int i = 0; i < 5; i++) {
		printf("Element at index %d: %d\n", i, numbers[i]);
	}

	// Secondo

	int num = 42;
	int *ptr; // Declare a pointer

	ptr = &num; // Assign the address of num to ptr

	printf("Value of num: %d\n", num);
	printf("Value of num using pointer: %d\n", *ptr); // Dereference the pointer

	// Working with arrays and pointers
	int arr[3] = {10, 20, 30};
	int *arrPtr = arr; // Pointer to the first element of the array

	printf("First element of arr: %d\n", *arrPtr); // Output: 10
	printf("Second element of arr: %d\n", *(arrPtr + 1)); // Output: 20

	return 0;
}