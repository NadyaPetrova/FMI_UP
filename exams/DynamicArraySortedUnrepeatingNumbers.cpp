/*Input an unsigned integer N and then allocate dynamic memory for an array of N real numbers. Then input N numbers
of this type and save them in descending order in the array as you don't add repeating numbers that are already saved.
Lastly print the numbers from the array on the screen.

Enter N: 10
Enter numbers: 4 2 5 2 4 2 3 7 4 2
7 5 4 3 2*/

#include <iostream>
using namespace std;

void print(double* arr, unsigned n);

int main()
{
	unsigned n;
	cout << "Enter N: ";
	cin >> n;

	double* arr = new double[n];
	cout << "Enter numbers: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	//sort
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] < arr[j]) {
				double temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	//how many numbers, that don't repeat
	int count = 1;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] == arr[i + 1]) {
			continue;
		}
		if (i == n - 2 && arr[i] != arr[i + 1]||arr[i]!=arr[i+1]) {
			count++;
		}
	}

	double* result = new double[count];
	size_t index = 0;

	//if we have only one number
	if (n == 1) {
		result[index++] = arr[0];
	}

	for (int i = 0; i < n-1; i++) {
		if (arr[i] == arr[i + 1]&&i!=n-2) {
			continue;
		}
		if (arr[i] != arr[i + 1]) {
			result[index++] = arr[i];
		}
		if (i == n - 2) {
			result[index++] = arr[i + 1];
		}
	}

	print(result, count);

	delete[] arr;
	delete[] result;
	return 0;
}

void print(double * arr, unsigned n)
{
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}