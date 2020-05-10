#pragma once

#define HEAP_PARENT(x) ((x-1)/2)
#define HEAP_LCHILD(x) (2*x+1)
#define HEAP_RCHILD(x) (2*x+2)

void quickSort(int *arr, int n){
	if(n <= 1)	return;
	int *_head, *_end;
	int key = arr[0];
	_head = arr, _end = arr+n-1;
	while(_head < _end){
		while(key <= *_end && _head < _end) _end--;
		*_head = *_end;
		while(key >= *_head && _head < _end) _head++;
		*_end = *_head;
	}
	*_head = key;
	quickSort(arr, _head-arr);
	quickSort(_head+1, arr+n-_head-1);
}

void __adjustHeap(int *arr, int n, int id){
	int t, minChild = H_LCHILD(id);
	if(minChild >= n)	return;
	if(H_RCHILD(id) < n && arr[H_RCHILD(id)] > arr[H_LCHILD(id)])
		minChild = H_RCHILD(id);
	if(arr[id] < arr[minChild]){
		t = arr[minChild];
		arr[minChild] = arr[id];
		arr[id] = t;
		__adjustHeap(arr, n, minChild);
	}
}

void makeHeap(int *arr, int n){
	if(n <= 1)	return;
	for(int i = H_PARENT(n-1);i >= 0;i--)
		__adjustHeap(arr, n, i);
}

void heapSort(int *arr, int n){
	int temp;
	makeHeap(arr, n);
	for(int i = n-1;i >= 0;i--){
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		__adjustHeap(arr, i, 0);
	}
}

void __merge(int *arr, int n, int mid){
	int m_arr[n];
	for(int i = 0;i < n;i++)
		m_arr[i] = arr[i];
	int p1 = 0, p2 = mid, p = 0;
	while(p1 < mid && p2 < n){
		if(m_arr[p1] <= m_arr[p2])
			arr[p++] = m_arr[p1++];
		else
			arr[p++] = m_arr[p2++];
	}
	while(p1 < mid)
		arr[p++] = m_arr[p1++];
	while(p2 < n)
		arr[p++] = m_arr[p2++];
}

void mergeSort(int *arr, int n){
	if(n <= 1)	return;
	int t;
	if(n == 2){
		if(arr[0] > arr[1]){
			t = arr[1];
			arr[1] = arr[0];
			arr[0] = t;
		}
		return;
	}
	int mid = n >> 1;
	mergeSort(arr, mid);
	mergeSort(arr+mid, n-mid);
	__merge(arr, n, mid);
}

void insertSort(int *arr, int n){
	int t, j;
	if(n <= 1)	return;
	for(int i = 1;i < n;i++){
		t = arr[i];
		for(j = i;j > 0 && t < arr[j-1];j--)
			arr[j] = arr[j-1];
		arr[j] = t;
	}
}

void selectSort(int *arr, int n){
	if(n <= 1)	return;
	int ptr, t;
	for(int i = 0;i < n;i++){
		ptr = i;
		for(int j = i;j < n;j++)
			if(arr[j] < arr[ptr])
				ptr = j;
		t = arr[i];
		arr[i] = arr[ptr];
		arr[ptr] = t;
	}
}

void bubbleSort(int *arr, int n){
	if(n <= 1)	return;
	int t;
	bool changed = true;
	for(int j = 0;changed && j < n;j++){
		changed = false;
		for(int i = 1;i < n;i++){
			if(arr[i-1] > arr[i]){
				t = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = t;
				changed = true;
			}
		}
	}
}

void shellSort(int *arr, int n){
	if(n <= 1)	return;
	int t;
	for(int d = n/2;d;d >>= 1){
		for(int i = d;i < n;i++){
			for(int j = i-d;j >= 0 && arr[j] > arr[j+d];j -= d){
				t = arr[j];
				arr[j] = arr[j+d];
				arr[j+d] = t;
			}
		}
	}
}