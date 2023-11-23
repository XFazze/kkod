#include <stdio.h>
#include "algorithm.h"

//
// Private
//
void swap(int *arr, int index_1, int index_2)
{
	int temp = arr[index_1];
	arr[index_1] = arr[index_2];
	arr[index_2] = temp;
}

int partition(int *arr, int low, int high)
{
	int pivot_index = (high - low) / 2 + low;
	int pivot = arr[pivot_index];
	int correct_index = low - 1;

	for (int i = low; i < high; i++)
	{
		if (arr[i] < pivot)
		{
			correct_index++;
			swap(arr, i, correct_index);
		}
	}
	swap(arr, correct_index + 1, pivot_index);

	return correct_index + 1;
}

void quick_sort_recursive(int *arr, int low, int high)
{
	if (low < high)
	{
		int middle = partition(arr, low, high);
		quick_sort_recursive(arr, low, middle - 1);
		quick_sort_recursive(arr, middle + 1, high);
	}
}

bool binary_search_recursive(int *arr, int n, int v, int low, int mid, int high)
{
	if (arr[mid] == v)
	{
		return true;
	}
	else if (mid == low)
	{
		return arr[high] == v;
	}
	else if (mid == high)
	{
		return arr[low] == v;
	}
	if (arr[mid] < v)
	{
		return binary_search_recursive(arr, n, v, mid, mid + (high - mid) / 2, high);
	}
	else
	{
		return binary_search_recursive(arr, n, v, low, low + (mid - low) / 2, mid);
	}
}
//
// Public
//
void bubble_sort(int *arr, int n)
{
	int sorted;
	do
	{
		sorted = 1;
		for (int i = 1; i < n; i++)
		{
			if (arr[i - 1] > arr[i])
			{
				swap(arr, i - 1, i);
				sorted = 0;
			}
		}
	} while (!sorted);
}

void insertion_sort(int *arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			swap(arr, i, i + 1);
			for (int o = i - 1; o >= 0; o--)
			{
				if (arr[o] > arr[o + 1])
				{
					swap(arr, o, o + 1);
				}
				else
				{
					break; // found right index in sorted part
				}
			}
		}
	}
}

void quick_sort(int *arr, int n)
{
	quick_sort_recursive(arr, 0, n - 1);
}

void linear_search(int *arr, int n, int v)
{
	for (int i = 0; i < n; i++)
	{
		if (v == arr[i])
			return;
	}
	return;
}

void binary_search(int *arr, int n, int v)
{
	binary_search_recursive(arr, n, v, 0, n / 2, n - 1);
	return;
}
