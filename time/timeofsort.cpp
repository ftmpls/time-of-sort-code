#include<iostream>
#include <chrono>

using namespace std;

void insertionSort(int arr[],int size);
void merge(int array[], int const left, int const mid, int const right);
void mergeSort(int array[], int const begin, int const end);
void quickSort(int arr[], int low, int high) ;
int partition (int arr[], int low, int high) ;
void swap(int* a, int* b);

int main(void)
{
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::nanoseconds;

	int size;
	int* arr=new int[size];

	cin>>size;
	

	for(int i=0;i<size;i++)
	{
		cin>>arr[i];
	}

	auto t1=high_resolution_clock::now();
	insertionSort(arr,size);
	auto t2=high_resolution_clock::now();

	auto t3=high_resolution_clock::now();
	mergeSort(arr,0,size);
	auto t4=high_resolution_clock::now();

	auto t5=high_resolution_clock::now();
	quickSort(arr,0,size-1);
	auto t6=high_resolution_clock::now();
	
	auto time_insertion_sort=duration_cast<nanoseconds>(t2-t1);
	auto time_merge_sort=duration_cast<nanoseconds>(t3-t4);
	auto time_quick_sort=duration_cast<nanoseconds>(t5-t6);

	if(time_insertion_sort.count()>time_quick_sort.count() && time_insertion_sort.count()>time_merge_sort.count())
		cout<<"En hizli: İnsertion sort"<<endl;
	if(time_quick_sort.count()>time_insertion_sort.count() && time_quick_sort.count()>time_merge_sort.count())
		cout<<"En hizli: Quick sort"<<endl;
	if(time_merge_sort.count()>time_quick_sort.count() && time_merge_sort.count()>time_insertion_sort.count())
		cout<<"En hizli: Merge sort"<<endl;
	
	
}
  
void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;


	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];


	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, 
		indexOfSubArrayTwo = 0; 
	int indexOfMergedArray = left; 


	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}


void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; 

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
 
 
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
