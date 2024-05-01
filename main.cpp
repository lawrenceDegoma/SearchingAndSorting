#include <iostream>
#include <algorithm>
#include <array>
#include <SFML/Graphics.hpp>

void mergeSort(int [], int);
void quickSort(int [], int);
void partition(int [], int, int&);
void merge(int [], int, int);
int binarySearch(int [], int, int, int);
void print(int [], int);


int main() {
    int arr[] = {3, 33, 15, 7, 3, 10, 45};
    int nums[] = {3, 33, 15, 7, 3, 10, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    int sizeNums = sizeof(nums) / sizeof(arr[0]);
    std::cout << "Original array: " << std::endl;
    print(arr, size);

    quickSort(arr, size);

    std::cout << "Sorted array using quick sort: " << std::endl;
    print(arr, size);

    std::cout << "Original array for nums: " << std::endl;
    print(nums, sizeNums);

    mergeSort(nums, sizeNums);

    std::cout << "Sorted array for nums using merge sort: " << std::endl;
    print(nums, sizeNums);

    int target;
    std::cout << "Enter target value for second array: ";
    std:: cin >> target;

    int index = binarySearch(nums, target, 0, sizeNums-1);
    if (index>0)
        std::cout << "Target found at index " << index << " (zero-based indexing)." << std::endl;
    else
        std::cout << "Target not found" << std::endl;

    return 0;
}

void quickSort(int data[], int size){
    /*
     * pivot_index
     * n1
     * n2
     *
     * if (size>1){
     * partition(data, size, pivot_index)
     * n1=pi
     * n2=size-pi-1
     *
     * quickSort(data,n1)
     * quickSort(data+pi+1, n2);
     */
    int pivot_index=0;
    int left_side, right_side;

    if (size > 1){
        partition(data, size, pivot_index);
        left_side = pivot_index;
        right_side = size - pivot_index - 1;

        quickSort(data, left_side);
        quickSort(data + pivot_index + 1, right_side);
    }

}

//void partition(int data[], int size, int& pivot_index) {
//    int pivot = data[0];
//    int i = 1, j = size - 1;
//    while (i <= j) {
//        while (i < size && data[i] < pivot) {
//            i++;
//        }
//
//        while (data[j] > pivot) {
//            j--;
//        }
//
//        if (i<j)
//            std::swap(data[i], data[j]);
//
//        else if (i >= j) {
//            std::swap(data[j], pivot);
//            pivot_index = j;
//            break;
//        }
//
//    }
//}

void partition(int data[], int size, int& pivot_index) {
    // choose a pivot
    //  the first item in our data
    // create variable i and j
    //   set i to the first value next to the pivot
    //   set j to the last value in the array
    // repeat until i and j cross each other
    // while (i < size && data[i] <= pivot)

    // while (data[j] > pivot)
    //  keep decrementing j

    // if (j<i)
    //  swap values at data[i] and data[j]

    // Once we are done
    //  set pivot_index to j
    //  move data[j] to data[0]
    // data[pivot_index] = pivot
    int pivot = data[0];
    int i = 1, j = size - 1;
    while (i <= j) {
        while (i < size && data[i] < pivot) {
            i++;
        }
        while (data[j] > pivot) {
            j--;
        }
        if (i < j) {
            std::swap(data[i], data[j]);
            i++;
            j--;
        }
    }
    std::swap(data[0], data[j]); // Move pivot to its correct position
    pivot_index = j; // Update pivot index
}

void mergeSort(int data[], int n) {
    /*
     *  n1 left side size
     *  n2 right side size
     *
     *  if (n>1){
     *  	n1 = n/2
     *  	n2 = n - n1
     *  	mergeSort(data[], n1)
     *  	mergeSort(data + n1, n)
     *
     *  	merge(data, n1, n2)
     *  }
     */

    int n1, n2;
    if (n > 1) {
        n1 = n / 2;
        n2 = n - n1;
        mergeSort(data, n1);
        mergeSort(data + n1, n2);

        merge(data, n1, n2);
    }
}

void merge(int data[], int n1, int n2){
	/*
	 * int *temp; // Holds the sorted array
	 * int copied = 0 // keep track of how many elements are copied to temp
	 * int copied1 = 0 // keep track of how many elements were copied from the first half
	 * int copied2 = 0 // keep track of how many elements were copied from the second half
	 * 
	 * dynamically create an array of size n1+n2
	 * while we haven't copied everything from the arrays
	 * 	if (data[copied1] < data[copied2])
	 * 		temp[copied++] = data[copied1++]
	 * put the remaining values in temp
	 * while (copied1 < n1)
	 * 	blah blah blah
	 * while (copied2 < n2)
	 * 	blah blah blah
	 *
	 * copy everything from temp back to data
	 * delete temp
    */

    int *temp = new int[n1+n2];

    int copied=0, copied1=0, copied2=0;

    while (copied1 < n1 && copied2 < n2) {
        if (data[copied1] < data[copied2 + n1])
            temp[copied++] = data[copied1++];
        else
            temp[copied++] = data[n1 + copied2++];
    }

    while (copied1 < n1){
        temp[copied++] = data[copied1++];
    }

    while (copied2 < n2){
        temp[copied++] = data[n1 + copied2++];
    }

    for (int i=0; i<n1+n2; i++){
        data[i] = temp[i];
    }

    delete[] temp;
}

int binarySearch(int data[], int target, int left, int right){
    if (left <= right) {
        int midpt = left + (right - left) / 2;
        if (data[midpt] == target)
            return midpt;
        if (data[midpt] < target)
            return binarySearch(data, target, midpt + 1, right);
        else if (data[midpt] > target)
            return binarySearch(data, target, left, midpt - 1);
    }
    return -1;
}

void print(int data[], int size){
    for (int i=0; i<size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}