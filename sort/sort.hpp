#pragma once

int binarySearch(int *sort, int start, int end, int x)
{
	if(start == end || x == sort[(start+end)/2])
		return start;
	else
	{
		if(x > sort[(start+end)/2])
			return binarySearch(sort,(start+end)/2+1,end,x);
		else
			return binarySearch(sort,start,(start+end)/2-1,x);
	}
	return -1;
}

void mergeSort(int *a, int *b, int start, int end)
{
	if(start >= end - 1)
	{
		if(a[start] > a[end])
		{
			int temp = a[end];
			a[end] = a[start];
			a[start] = temp;
		}
	}
	else if(end - start > 1)
	{
		int half = start + (end - start) / 2;
		mergeSort(a, b, start, half);
		mergeSort(a, b, half + 1, end);
		merge(a, b, start, half, end);
	}
}

void merge(int *a, int *b, int start, int half, int end)
{
	int count = start;
	int temp_start = start;
	int temp_half = half;
	while(count <= end)
	{
		if(temp_start <= half && temp_half <= end)
			b[count++] = a[temp_start] < a[temp_half + 1] ? a[temp_start++] : a[temp_half++ + 1];
		else if(temp_start > half)
			b[count++] = a[temp_half++ +1];
		else if(temp_half > end)
			b[count++] = a[temp_start++];
	}
	for(count = start;count <= end;count++)
		a[count] = b[count];
}

void shellSort(int *arr, int k)
{
	int span = k/2;
	while(span > 0)
	{
		for(int i = 0;i < span;i++)
			insertSort(arr, i, k, span);
		span /= 2;
	}
}

void insertSort(int *arr, int from, int end, int span)
{
	int n = 1, i;
	while(from+n*span < end)
	{
		i = n-1;
		while(i >= 0 && arr[from+i*span] > arr[from+(i+1)*span])
		{
			arr[from+(i+1)*span] ^= arr[from+i*span] ^= arr[from+(i+1)*span] ^= arr[from+i*span];
			i--;
		}
		n++;
	}
}

void makeHeap(int *a, int x, int len)
{
	for(int i = x;2*i < len;)
	{
		if(a[i-1] > a[2*i-1])
		{
			if(a[2*i-1] > a[2*i])
			{
				a[i-1] ^= a[2*i] ^= a[i-1] ^= a[2*i];
				i = 2*i+1;
			}
			else
			{
				a[i-1] ^= a[2*i-1] ^= a[i-1] ^= a[2*i-1];
				i = 2*i;
			}
		}
		else if(a[i-1] > a[2*i])
		{
			a[i-1] ^= a[2*i] ^= a[i-1] ^= a[2*i];
			i = 2*i+1;
		}
		else
			i <<= 1;
	}
}

void heapSort(int *a, int len)
{
	for(int i = len/2;i > 0;i--)
		makeHeap(a, i, len);
	for(int i = 1;i < len-2;i++)
		makeHeap(a+i, 1, len-i);
	if(a[len-2] > a[len-1])
		a[len-1] ^= a[len -2] ^= a[len-1] ^= a[len-2];
}

void quickSort(int *start, int *end)
{
	int *_Start, *_End;
	int key = *start;
	_Start = start, _End = end-1;
	if(_Start > _End);
	else
	{
		while(_Start < _End)
		{
			while(key < *_End && _Start < _End) _End--;
			*_Start = *_End;
			while(key > *_Start && _Start < _End) _Start++;
			*_End = *_Start;
		}
		*_Start = key;
		quickSort(start, _Start);
		quickSort(_Start+1, end);
	}
}