/*
 Created by Mariia Romaniuk
 Sorting Analysis
 
 Program compares the relative performance of different sorting algorithms on
 datasets containing  integers. Ultimately, the data sorted in ascending order.
 Program tested on two different array sizes : 100 and 1000.
 Use the following random number distributions :
 a) Completely random
 b) Almost sorted in ascending order (about 90% of the items are in increasing order,
 10% are random)
 c) Almost reversed -  same as b) but in reverse order
 d) Array is sorted except for the last 10%
 The following sorting algorithms are used:
 - Selection Sort
 - Insertion Sort
 - Heap Sort
 - Merge Sort
 - Quick Sort
 */


#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;


#define MAX 1000 // define default size of the array
int swaps[5] = {0,0,0,0,0}; // global variables for counting swaps in sorting algorithms
int comps[5] = {0,0,0,0,0}; // global variables for comparison counts in sorting algorithms


// sorting algorithm functions
void selectionSort(int a[], int size);
void insertionSort(int a[], int size);
void heapSort(int a[], int size);
void heapDown(int a[], int n, int i);
void mergeSort(int a[], int first, int last);
void merge(int a[], int lfirst, int llast, int rfirst, int rlast);
void quickSort(int a[], int first, int last);
int partition(int a[], int first, int last);

// functions to generate arrays with various number distributions
void allRandom(int a[], int size);
void randomLast(int a[], int size);
void almostSorted(int a[], int size);
void almostReversed(int a[], int size);

// helper functions
void printArray(int a[], int size);
int* copyArray(int a[], int size);


int main(){
    // dynamically allocate an array of MAX size for future use
    int* test = new int[MAX];
    int size, sizeChoice, arrayChoice;
    
    cout << "Select a size of an array: \n1. 100 \n2. 1000 " << endl;
    cin >> sizeChoice;
    
    if (sizeChoice == 1)
        size = 100;
    else
        size = 1000;
    
    cout << "Select a type of an array: " << endl;
    cout << "1. All completely random integers" << endl;
    cout << "2. Almost sorted - 10% randomly placed " << endl;
    cout << "3. Almost sorted - same as 2 but in reverse order " << endl;
    cout << "4. Array is sorted except of last 10% " << endl;
    cin >> arrayChoice;
    
    
    switch (arrayChoice){
        case 1: allRandom(test,size);
            break;
        case 2: almostSorted(test,size);
            break;
        case 3: almostReversed(test,size);
            break;
        case 4: randomLast(test,size);
            break;
    }
    
    cout << "\nUnsorted array: ";
    printArray(test, size);
    
    for (int i = 0; i < 5; i++){
        int* arr = copyArray(test,size);
        switch (i){
        case 0: cout << "\n\nSelection Sort:";
                selectionSort(arr,size);
            break;
        case 1: cout << "\nInsertion Sort:";
                insertionSort(arr,size);
            break;
        case 2: cout << "\nHeap Sort:";
                heapSort(arr,size);
            break;
        case 3: cout << "\nMerge Sort:";
                mergeSort(arr,0,size-1);
            break;
        case 4: cout << "\nQuick Sort:";
                quickSort(arr,0,size-1);
            break;
        }
        delete [] arr;
        arr = nullptr;
        cout << endl;
        cout << swaps[i] << " swaps" << endl;
        cout << comps[i] << " comparisons " << endl;
    }
    delete [] test;
    test = nullptr;
    return 0;
}


// selection sort algorithm
void selectionSort(int a[], int size){
    int min;
    for (int i = 0; i < size-1; i++){
        min = i;
        for (int j = i+1; j < size; j++){
            ++comps[0];
            if (a[j] < a[min]){
                min = j;
            }
        }
        swap(a[i], a[min]);
        ++swaps[0];
    }
}


// insertion sort algorithm
void insertionSort(int a[], int size){
    int j;
    bool order;
    for (int i = 1; i < size; i++){
        j = i;
        order = false;
        while (j != 0 && !order){
            ++comps[1];
            if (a[j] < a[j-1]){
                swap(a[j], a[j-1]);
                ++swaps[1];
                j--;
            } else
                order = true;
        }
    }
}


// heap sort algorithm
void heapSort(int a[], int n){
    // create the heap
    for (int i = (n/2 - 1); i >= 0; i--)
        heapDown(a, n, i);
    
    // heap sort
    for (int i = n-1; i >= 0; i--){
        swap(a[0], a[i]);
        ++swaps[2];
        // heap down root element to get highest element at root again
        heapDown(a, i, 0);
    }
}


// heap sort helper function
void heapDown(int arr[], int n, int i){
    // find the largest among roots, left child and right child
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
    ++comps[2];
    if (l < n && arr[l] > arr[largest])
        largest = l;
    
    ++comps[2];
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i){
        swap(arr[i], arr[largest]);
        ++swaps[2];
        heapDown(arr, n, largest);
    }
}


// merge sort algorithm
void mergeSort(int a[], int first, int last){
    if (first < last){
        int mid = (first + last)/2;
        // split the data into two halves
        mergeSort(a, first, mid);
        mergeSort(a, mid+1, last);
        // merge them to get sorted output
        merge(a, first, mid, mid+1, last);
    }
}


// merge sort helper function
void merge(int a[], int lfirst, int llast, int rfirst, int rlast){
    int temp[MAX];
    int k = lfirst;
    int save = lfirst;
    
    // merge the two parts into temp[]
    while (lfirst <= llast && rfirst <= rlast){
        ++comps[3];
        if (a[lfirst] < a[rfirst])
            temp[k++] = a[lfirst++];
        else
            temp[k++] = a[rfirst++];
        ++comps[3];
        ++swaps[3];
    }
    // insert all the remaining values from lfirst to llast into temp[]
    while (lfirst <= llast){
        temp[k++] = a[lfirst++];
        ++comps[3];
        ++swaps[3];
    }
    // insert all the remaining values from rfirst to rlast into temp[]
    while (rfirst <= rlast){
        temp[k++] = a[rfirst++];
        ++comps[3];
        ++swaps[3];
    }
    // assign sorted data stored in temp[] to a[]
    for (int i = save; i <= rlast; i++)
        a[i] = temp[i];
}


// quick sort algorithm
void quickSort(int a[], int first, int last){
    int partitionPoint;
    if (first < last){
        partitionPoint = partition(a, first, last);
        quickSort(a, first, partitionPoint-1);
        quickSort(a, partitionPoint+1, last);
    }
}


// quick sort helper function
int partition(int a[], int first, int last){
    int pivot = a[first];
    int small = first; // index of the last small element
    int i;
    
    for (i = first+1; i <= last; i++){
        ++comps[4];
        if (a[i] < pivot){
            small++;
            swap(a[i], a[small]);
            ++swaps[4];
        }
    }
    swap(a[first], a[small]);
    ++swaps[4];
    return small;
}


// function to generate an array with completely random number distribution
void allRandom(int a[], int size){
    srand((unsigned)time(0));
    int random;
    for (int i = 0; i < size; i++){
        random = (rand() % 100) + 1;
        a[i] = random;
    }
}


// function to generate an almost sorted in ascending order array
// (about 90% of the items are in increasing order, 10% are random)
void almostSorted(int a[], int size){
    srand((unsigned)time(0));
    
    for (int i = 0; i < size; i++)
        a[i] = i+1;

    int rand1, rand2, i = 0;
    while (i < (size * .10)) {
        rand1 = (rand() % size) + 1;
        rand2 = (rand() % size) + 1;
        a[rand1] = rand2;
        i++;
    }
}


// function to generate an array with almost sorted reversed number distribution
// same as b) but in reverse order
void almostReversed(int a[], int size){
    int n = 1;
    srand((unsigned)time(0));
    
    for (int i = size; i >= 0; i--)
        a[i] = n++;
    
    int rand1, rand2, i = 0;
    while (i < (size * .10)){
        rand1 = (rand() % size) + 1;
        rand2 = (rand() % size) + 1;
        a[rand1] = rand2;
        i++;
    }
}


// function to generate an sorted array except for the last 10%
void randomLast(int a[], int size){
    int m = size * .10;      // calculate last 10% of integers
    int l = size - m;        // calculate first 90% of integers
    int n = 1;
    
    srand((unsigned)time(0));
    int random;
    
    for (int i = 0; i < l; i++)
        a[i] = n++;
    
    // calculate last 10% as random
    for (int i = 0; i < m; i++){
        random = (rand() % 100) + 1;
        a[l] = random;
        l++;
    }
}


// function to copy array
int* copyArray(int a[], int size){
    int * b = new int[size];
    for (int i = 0; i < size; i++)
        b[i] = a[i];
    return b;
}


// function to print array
void printArray(int a[], int size){
    cout << endl;
    for (int i = 0; i < size; i++)
        cout << a[i] << " ";
}

